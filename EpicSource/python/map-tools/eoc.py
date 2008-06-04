#!/usr/bin/env python
#
# $Id$
#

from eocdata import EntityTypes, BodyTypes, HabitatType, eoc_allegiance
import os, struct, ConfigParser

class MapEntity(object):
  '''
    Placeholder until we start dealing with entities better.
  '''
  def __init__(self, entity):
    self.entity = entity

class Map(object):
  map_header = '>I'
  # each record is 360 bytes
  map_struct = (
    ('B', 'entity type'),
    ('260s', 'name'), # null terminated, but padded with junk
    ('>ddd', 'x,y,z position'),
    ('>fff', 'x,y,z origin'),
    ('>f', 'y scale'),
    ('>i', 'parent'),
    ('>i' , 'body type'),
    ('B' , 'station type'),
    ('B' , 'faction'),
    ('B' , 'population'),
    ('f', 'radius'),
    ('B' , 'texture type'),
    ('B' , 'texture 1'),
    ('B' , 'texture 2'),
    ('B' , 'texture 3'),
    ('fff', 'colour 1'),
    ('fff', 'colour 2'),
    ('fff', 'colour 3'),
    ('B' , 'cloud'),
    ('B' , 'ring'),
    ('B' , 'cloud opacity'),
    ('B' , 'unk2'), # always 0
  )
  # after the map entities.
  lpoint_route = (
    ('>I', 'index'),
    ('<H', 'lead1'), # could actually be a 16 bit int
    ('>H', 'length'),
  )

  def __init__(self, file, base, verbose=0):
    self._file = base + os.path.sep + file[4:] + '.map'
    self.base = base
    self.verbose = verbose
    size = os.stat(self._file).st_size
    self.entities = []
    self.lpoints = []

    fh = open(self._file, 'rb')
    entries = struct.unpack(self.map_header, 
            fh.read(struct.calcsize(self.map_header)))[0]
    if self.verbose:
      print '%d entities' % (entries)
    e = {}
    i = entries
    cur = 0
    while i > 0:
      for s in self.map_struct:
        e[s[1]] = struct.unpack(s[0], fh.read(struct.calcsize(s[0])))
      for k in e.keys():
        if len(e[k]) == 1:
          e[k] = e[k][0]
      #
      # struct needs a null padded string type.
      #
      e['name'] = e['name'][:e['name'].find('\x00')]

      if self.verbose:
        try:
          if e['entity type'] == 0: # Body
            print 'num: %d name %s type %s, body type %s, hab_type %d yscale %.2f radius %10.0f' % (cur, e['name'], EntityTypes[e['entity type']], BodyTypes[e['body type']], e['station type'], e['y scale'], e['radius'])
          elif e['entity type'] == 1: # Station
#            if e['station type'] > len(HabitatType):
#              station_type = 'XXX unknown: %d XXX' % (e['station type'])
#            else:
            station_type = HabitatType[e['station type']]
            print 'num: %d name %s type %s, body type %d, hab_type %s yscale %.2f radius %10.0f' % (cur, e['name'], EntityTypes[e['entity type']], e['body type'], station_type, e['y scale'], e['radius'])
          else:
            print 'num: %d name %s type %s, body type %d, hab_type %d yscale %.2f radius %10.0f' % (cur, e['name'], EntityTypes[e['entity type']], e['body type'], e['station type'], e['y scale'], e['radius'])
          print 'colour 1: %.2f %.2f %.2f' % e['colour 1']
          print 'colour 2: %.2f %.2f %.2f' % e['colour 2']
          print 'colour 3: %.2f %.2f %.2f' % e['colour 3']
          print 'Parent %d, Faction %d, Population %d' % (e['parent'], e['faction'], e['population'])
          print 'Texture type %d, t1 %d, t2 %d, t3 %d' % (e['texture type'], e['texture 1'], e['texture 2'], e['texture 3'])
          print 'Ring: %d Cloud: %d cloud opacity: %d' % (e['ring'], e['cloud'], e['cloud opacity'])
          print 'Pos: %10.2f %10.2f %10.2f' % e['x,y,z position']
          print 'Ori: %10.2f %10.2f %10.2f' % e['x,y,z origin']
        except:
          print '############## bust!'
          print 'entity, body, station', e['entity type'], e['body type'], e['station type']
          print e
        print
      
      cur += 1
      i -= 1
      self.entities.append(e)

    # now lpoints
    unknown = struct.unpack('8s', fh.read(8))[0]
    nlpoints = struct.unpack('>I', fh.read(4))[0]
    assert unknown == '\x00\x00\x00\x11\x00\x00\x00\x11'

    if self.verbose:
      print
      print '%d lpoints' % (nlpoints)
        
    i = nlpoints
    lp = {}
    while i > 0:
      for s in self.lpoint_route:
        lp[s[1]] = struct.unpack(s[0], fh.read(struct.calcsize(s[0])))
      # turn single item tuples into just the items
      for k in lp.keys():
        if len(lp[k]) == 1:
          lp[k] = lp[k][0]
      lp['name'] = struct.unpack(str(lp['length']) + 's', fh.read(lp['length']))[0]
      lp['name'] = lp['name'][:lp['name'].rfind('\x00')] # could just be [:-1]
      del lp['length']
      if self.verbose:
        print lp
      assert lp['lead1'] == 128
      self.lpoints.append(lp)
      i -= 1

    assert fh.tell() == size, "Didn't read the whole file!?!"

class Station(object):
  def __init__(self, bits):
    """Takes a dict where key's match the keys used in the per system-ini files for stations"""
    assert 'name' in bits
    assert 'parent_body' in bits
    self._name = bits['name']
    del bits['name']
    for k in bits:
      self.__dict__[k] = bits[k]
  
  def getname(self):
    return self._name

  name = property(getname, doc='the name of the system')  

  def __str__(self):
    return '<Station: %s (%s)>' % (self.name, self.parent_body)  

class System(object):
  """Contains lists of lpoints and stations whithin a system"""
  def __init__(self, base, path=None, coords=(0,0,0)):
    self.setpath(path)
    self.setcoords(coords)
    self.lpoints = {}
    self.stations = []
    self.stations_byname = {}
#    if self._path.find('aleppo') > 0:
    self.map = Map(self._path, base)
    self.base = base
  
  def setup(self):
    '''parse our ini file'''
    ini_path = self.base + os.path.sep + 'geog' + os.path.sep + 'middle' + os.path.sep + self.name + '.ini'
    cp = ConfigParser.SafeConfigParser()
    cp.read([ini_path])
    self.visibility = cp.get('SystemProperties', 'visibility')
    items = cp.items('starting_stations')
    for it in items:
      if it[0].startswith('start_lpoint['):
        i = int(it[0][len('start_lpoint['):-1])
        self.lpoints[i] = {
                            'start': it[1][1:-1],
                            'difficulty': cp.getint('starting_stations', 'difficulty[%d]' % (i)),
#                            'period': cp.getint('starting_stations', 'period[%d]' % (i)),
#                            'offset': cp.getint('starting_stations', 'offset[%d]' % (i)),
                            'end_system': cp.get('starting_stations', 'end_system[%d]' % (i))[1:-1],
                            'end_lpoint': cp.get('starting_stations', 'end_lpoint[%d]' % (i))[1:-1]
                          }
      elif it[0].startswith('name['):
        i = int(it[0][len('name['):-1])
#        print it, i, self.name
        ks = [('name', cp.get), ('parent_body', cp.get), ('template', cp.getint), 
              ('orbital_distance', cp.getfloat),
              ('orbital_angle_around', cp.getfloat),
              ('orbital_angle_above', cp.getfloat), 
              ('type', cp.getint), ('richness', cp.getint), ('faction', cp.get), ('status', cp.get)]
        bits = {}
        for k in ks:
          bits[k[0]] = k[1]('starting_stations', k[0] + '[%d]' % (i))
        station = Station(bits)
        self.stations.append(station)
        self.stations_byname[station.name] = station
  
  def getpath(self):
    return self._path
         
  def setpath(self, path):
    assert type(path) == type('fish')
    assert path.startswith('map:')
    self._path = path
                             
  path = property(getpath, setpath, doc='The path to the map file')

  def getcoords(self):
    return self._coords
         
  def setcoords(self, coords):
    if type(coords) == type('fish'):
      # ( 0.5, -7.5, 0 )
      coords = coords.strip()
      coords = coords.replace(' ', '')
      coords = coords[1:-1] # strip ()
      coords = coords.split(',')
      coords = tuple([float(x) for x in coords])
    self._coords = coords
                             
  coords = property(getcoords, setcoords, doc='The (x,y,z) coords of the system')  
  
  def getname(self):
    name = self.path[self.path.rfind('/') + 1:]
    return name
  
  name = property(getname, doc='the name of the system')
  
  def getx(self):
    return self._coords[0]

  def gety(self):
    return self._coords[1]

  def getz(self):
    return self._coords[2]
  
  x = property(getx)
  y = property(gety)
  z = property(getz)
  
  def __str__(self):
    return '<path: %s <%.2f, %.2f, %.2f>>' % (self._path, self.coords[0], self.coords[1], self.coords[2])
  
  def __repr__(self):
    return str(self) + '\n'

