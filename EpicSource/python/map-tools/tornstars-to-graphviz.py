#!/usr/bin/env python
#
#
#
# ./ts-gv-map.py| neato -s2  -Tpng -o ts.png
#

import ConfigParser, os
from eoc import System

ts_geog_path = "/home/jasper/develop/ts/eocsvn/tornstars/trunk/EpicSource/clusters/US_Mod_Geog/"

if __name__ == "__main__":

  
  try:
    os.stat(ts_geog_path)
  except OSError:
    ts_geog_path = None
  
  if ts_geog_path == None:
    ts_geog_path = os.getenv('EPIC_BASE')
    ts_geog_path += os.path.sep + os.path.sep.join(('EpicSource','clusters','US_Mod_Geog'))
    
  cp = ConfigParser.SafeConfigParser()
  cp.read([ts_geog_path + os.path.sep + 'geog' + os.path.sep + 'clusters.ini'])
  items = cp.items('badlands')
  
  systems = []
  labels = []
  
  maps = {}
  coords = {}
  
  labels = {}
  l_coords = {}

  for i in items:
    if i[0].startswith('system'):
      maps[int(i[0][len('system['):-1])] = i[1]
    elif i[0].startswith('map_coords['):
      coords[int(i[0][len('map_coords['):-1])] = i[1]
    elif i[0].startswith('label['):
      labels[int(i[0][len('label['):-1])] = i[1]
    elif i[0].startswith('label_coords['):
      l_coords[int(i[0][len('label_coords['):-1])] = i[1]
    else:
      print '# unknown line in clusters.ini:', i
  
  ks = maps.keys()
  ks.sort()
  for k in ks:
    systems.append(System(ts_geog_path, path=maps[k], coords=coords[k]))
  
  for s in systems:
    s.setup()

#  for s in systems:
#    print s
#    print len(s.stations)
#    print len(s.stations_byname)

  #
  # we don't do anything with labels atm.
  #
  
  #
  # converts difficulty to colours
  #
  diff2c = {
    1: '#0000ff',
    2: '#00ff00',
    3: '#ffeb00',
    4: '#ffba00',
    5: '#ff0000',
  }

  #
  # visibility to colours.
  #
  vis2c = {
    'unknown': '#9900ff',
    'known': '#66ff33',
    'hidden': '#ff9900',
  }

  print 'digraph G {'
  print '\tnode [fontsize=8, shape=oval, width=.01, height=.01, color=black, fontcolor=black ];'

  for s in systems:
    if s.name == 'capsule_space': # skip capsule space
      continue
    if 1: #s.visibility != 'hidden':
      print "\t%s [pos=\"%f,%f!\" label=\"%s\" fillcolor=\"%s\" style=filled];" % (s.name, s.x, -s.y, s.name, vis2c[s.visibility])
      for lp in s.lpoints:
        print "\t%s -> %s [color=\"%s\"];" % (s.name, s.lpoints[lp]['end_system'], diff2c[s.lpoints[lp]['difficulty']])

  print '}'
  
