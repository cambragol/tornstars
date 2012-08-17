#!/usr/bin/env python
#
# $Id: lwsc.py,v 1.4 2008/06/22 16:02:02 jasper Exp $
#
# Parse a .lws file (Lightwave Scene)
#

import sys,re
from hexdump import tobin
import pprint

class LWSC:
  def __init__(self, verbose=0):
    self.verbose = verbose

    self.scene = {}
    # objects is indexed from 1, so have a blank zeroth
    self.objects = [None]
    self.lightopts = {}
    self.lights = [None]
    self.cameras = [None]
    self.effects = {}
    self.render = {}
    self.layoutopts = {}

    self.pp = pprint.PrettyPrinter(indent=1, depth=None)
    
    self.loaded = False
  
  def mre_dict_mangle(self, dict, res, line):
    for are, conv in res:
      results = are.match(line)
      if results:
        key, value = results.groups()
        dict[key] = conv(value)
        return (True, key, value)
    return (False, None, None)
    
  def load_motion(self, f, line, ln):
    # XXX int and float rather than str please.
    data = {}
    rs = '^' + '(-?[0-9.\-e]+)\s+' * 8 + '(-?[0-9.\-e]+)$'
    mre_a = re.compile(rs)
    rs = '^' + '(-?[0-9.\-e]+)\s+' * 4 + '(-?[0-9.\-e]+)$'
    mre_b = re.compile(rs)
    fields_a = ['x', 'y', 'z', 'Heading', 'Pitch', 'Bank', 'XScale', 'YScale', 'ZScale']
    fields_b = ['Frame Number', 'Linear Value', 'Tension', 'Continuity', 'Bias']
    # the line we're passed is the one that triggered the call to this function
    # it will either be ObjectMotion or LightMotion XXX
    line = f.readline().strip()
    ln += 1
    # datapoints, should always be 9.
    assert int(line) == 9, "at line %d Motion had unexpected amount of data: %s" % (ln, line)
    # number of keyframes
    line = f.readline().strip()
    ln += 1
    frames = int(line)
    # no brainer
    assert frames > 0
    data['frames'] = frames
    data['data'] = []
    
    line = f.readline().strip()
    ln += 1
    i = 0
    while (i < frames):
      o = {}
      res = mre_a.match(line)
      assert res != None, "Parse error at line %d: >%s<" % (ln, line)
      res = res.groups()
      j = 0
      for k in fields_a:
        o[k] = res[j]
        j += 1
      line = f.readline().strip()
      ln += 1
      # now the next lot.
      res = mre_b.match(line)
      assert res != None, "Parse error at line %d: >%s<" % (ln, line)
      res = res.groups()
      j = 0
      for k in fields_b:
        o[k] = res[j]
        j += 1

      data['data'].append(o)
      # 
      line = f.readline().strip()
      ln += 1

      i += 1
          
    return (line, ln, data)

  def load_envelope(self, f, line, ln):
    # XXX int and float rather than str please.
    data = {}
    rs = '^(-?[0-9.e\-]+)$'
    mre_a = re.compile(rs)
    rs = '^' + '(-?[0-9.]+)\s+' * 4 + '(-?[0-9.]+)$'
    mre_b = re.compile(rs)
    fields_a = ['Envelope Value']
    fields_b = ['Frame Number', 'Linear Value', 'Tension', 'Continuity', 'Bias']
    # the line we're passed is the one that triggered the call to this function
    # it will be FlareIntensity
    line = f.readline().strip()
    ln += 1
    # datapoints, should always be 1 for envelopes
    assert int(line) == 1, "at line %d FlareIntensity had unexpected amount of data: %s" % (ln, line)
    # number of keyframes
    line = f.readline().strip()
    ln += 1
    frames = int(line)
    # no brainer
    assert frames > 0
    data['frames'] = frames
    data['data'] = []
    
    line = f.readline().strip()
    ln += 1
    i = 0
    while (i < frames):
      o = {}
      res = mre_a.match(line)
      assert res != None, "Parse error at line %d: >%s<" % (ln, line)
      res = res.groups()
      j = 0
      for k in fields_a:
        o[k] = res[j]
        j += 1
      line = f.readline().strip()
      ln += 1
      # now the next lot.
      res = mre_b.match(line)
      assert res != None, "Parse error at line %d: >%s<" % (ln, line)
      res = res.groups()
      j = 0
      for k in fields_b:
        o[k] = res[j]
        j += 1

      data['data'].append(o)
      # 
      line = f.readline().strip()
      ln += 1

      i += 1
          
    return (line, ln, data)

  def load(self, file):
    ln = 0 # line number
    
    # key int value
    kivre = re.compile('^([a-zA-Z]+)\s+([0-9]+)$')
    # key float value XXX e-10 etc???
    kfvre = re.compile('^([a-zA-Z]+)\s+([0-9\.]+)$')    
    # key value, we don't really care about value
    kvre = re.compile('^([a-zA-Z]+)\s+(.+)$')

    res = [[kivre, int], [kfvre, float], [kvre, str]]
    
    f = open(file, 'r')

    # header
    magic = f.readline().strip()
    assert magic == 'LWSC', "Not an LWSC file: %s" % (file)
    self.version = int(f.readline().strip())
    assert self.version == 1, "Sorry, only version 1 LWSC files understood"
 
    if self.verbose:
      print "parseing %s, version %d" % (file, self.version)
 
    ln += 2
    # next line should be blank
    assert f.readline().strip() == '', "parse error on %s line %d" % (file, ln)
    ln += 1
    
    # now scene info
    line = f.readline().strip()
    ln += 1
    while (line != ''):
      self.mre_dict_mangle(self.scene, res, line)
      line = f.readline().strip()
      ln += 1


    if self.verbose:
      self.pp.pprint(self.scene)

    # objects now
    object = {}
    ore = re.compile('^(AddNullObject|LoadObject) (.+)$')
    line = f.readline().strip()
    ln += 1
        
    while (ore.match(line)):
      object = {}
      result = ore.match(line)
      object['_header'] = {result.groups()[0]: result.groups()[1]}
        
      line = f.readline().strip()
      ln += 1
      while (line != ''):
        
        found, key, value = self.mre_dict_mangle(object, res, line)
        if not found:
          print "not found @ %d: >%s<" % (ln, line)
        if key == 'ObjectMotion':
          line, ln, motion = self.load_motion(f, line, ln)
          object['_keyframes'] = motion
        elif key == 'ObjDissolve':
          line, ln, motion = self.load_envelope(f, line, ln)
          object['_disolve'] = motion          
        else:
          line = f.readline().strip()
          ln += 1
      self.objects.append(object)
      line = f.readline().strip()
      ln += 1

    if self.verbose:
      self.pp.pprint(self.objects)

    # Slightly odd
    assert line.startswith("AmbientColor"), "Parse error in %s at line %d" % (file, ln)
    
    while (line != ''):
      self.mre_dict_mangle(self.lightopts, res, line)
      line = f.readline().strip()
      ln += 1

    if self.verbose:
      print self.lightopts

    # lights now
    light = {}
    lre = re.compile('^AddLight$')
    line = f.readline().strip()
    ln += 1

    while (lre.match(line)):
      light = {}
        
      ln += 1
      line = f.readline().strip()
      while (line != ''):
        
        found, key, value = self.mre_dict_mangle(light, res, line)
        if not found:
          print "not found@%d: >%s<" % (ln, line)
        
        if key == 'LightName':
          light['_header'] = {key : value}

        if key == 'LightMotion':
          line, ln, motion = self.load_motion(f, line, ln)
          light['_keyframes'] = motion
        elif key == 'FlareIntensity' and value == '(envelope)':
          line, ln, motion = self.load_envelope(f, line, ln)
          light['_flareintensity'] = motion
        elif key == 'LgtIntensity' and value == '(envelope)':
          line, ln, motion = self.load_envelope(f, line, ln)
          light['_lgtintensity'] = motion
        else:
          line = f.readline().strip()
          ln += 1
        
      if '_header' not in light:
        light['_header'] = {'__' : '__ Not Named'}
      self.lights.append(light)
      line = f.readline().strip()
      ln += 1
    
    if self.verbose:
      self.pp.pprint(self.lights)
    
    # cameras
    camera = {}
    lre = re.compile('^(ShowCamera) (.+)$')

    while (lre.match(line)):
      camera = {}
      result = lre.match(line)
      camera['_header'] = {result.groups()[0]: result.groups()[1]}

      line = f.readline().strip()
      ln += 1
      while (line != ''):
        
        found, key, value = self.mre_dict_mangle(camera, res, line)
        if not found:
          print "not found:", line
        if key == 'CameraMotion':
          line, ln, motion = self.load_motion(f, line, ln)
          camera['_keyframes'] = motion
        else:
          line = f.readline().strip()
          ln += 1
      self.cameras.append(camera)
      line = f.readline().strip()
      ln += 1

    if self.verbose:
      self.pp.pprint(self.cameras)
    
    # effects
    if not line.startswith("SolidBackdrop") and not line.startswith("BGImage"):
      assert False, "Parse error in %s at line %d" % (file, ln)
    
    while (line != ''):
      self.mre_dict_mangle(self.effects, res, line)
      line = f.readline().strip()
      ln += 1

    if self.verbose:
      print self.effects
    
    # render
    line = f.readline().strip()
    ln += 1    
    assert line.startswith("RenderMode"), "Parse error in %s:%d : >%s<" % (file, ln, line)
    
    while (line != ''):
      self.mre_dict_mangle(self.render, res, line)
      line = f.readline().strip()
      ln += 1

    if self.verbose:
      print self.render
             
    # layout opts
    line = f.readline().strip()
    ln += 1    
    assert line.startswith("ViewMode"), "Parse error in %s:%d" % (file, ln)
   
    while (line != ''):
      self.mre_dict_mangle(self.layoutopts, res, line)
      line = f.readline().strip()
      ln += 1

    if self.verbose:
      print self.layoutopts
  
    self.loaded = True
  
  def obj_tree(self):
    assert self.loaded, "you need to load a .lws first"
    # start it with z to sort it better with pprint
    child_node = "zzc"

    print
    print "dumping objects and lights as a tree"

    # child_node is children of this node
    
    # set up a root node.
    parents = {child_node : {}, 'lights' : {}, 'name' : {'__root__really': ''}}

    # add all objects that don't have parents to the root thing
    i = 1
    for o in self.objects[1:]:
      if 'ParentObject' not in o.keys():
        if i not in parents:
          parents[child_node][i] = {child_node : {}, 'lights' : {}, 'name' : o['_header']}
      i += 1

#    self.pp.pprint(parents)
    
    def find_parent_r(parents, o, i, found):
      if o['ParentObject'] in parents[child_node]:
        if i not in parents[child_node][o['ParentObject']][child_node]:
          parents[child_node][o['ParentObject']][child_node][i] = {child_node : {},
                                                     'lights' : {},
                                                     'name' : o['_header']
                                                    }
          return found, 1
#        else:
#          print 'obj %d already has child %d' % (o['ParentObject'], i)
      else:
        for p in parents[child_node]:
          found, got = find_parent_r(parents[child_node][p], o, i, found)
          found += got
      return found, 0

    # print the list of objects
    if self.verbose:
      print "dumping objects"
      print "index, type/name, parent (if it has one)"
      print
      i = 1
      for o in self.objects[1:]:
        print i, o['_header'],
        if 'ParentObject' in o.keys():
          print o['ParentObject']
        else:
          print
        i += 1
      

    found = len(parents[child_node])
    while (found < (len(self.objects) - 1)):
      i = 1
      for o in self.objects[1:]:
#        print i, found, len(self.objects), o['_header'],
        if 'ParentObject' in o.keys():
#          print o['ParentObject']
          f2, got = find_parent_r(parents, o, i, found)
          found = f2 + got
#        else:
#          print

        i += 1
    
#      print len(self.objects), found
#    print len(self.objects), found

    def find_parent_r_lights(parents, o, i):
      if o['ParentObject'] in parents[child_node]:
        if i not in parents[child_node][o['ParentObject']]['lights']:
          parents[child_node][o['ParentObject']]['lights'][i] = {'name' : o['_header']}
        else:
          print "%d is already there??" % (i)
        return
      else:
        for p in parents[child_node]:
          find_parent_r_lights(parents[child_node][p], o, i)
    

#
#  light indicies share the same range as objects
#
    if self.verbose:
      print "dumping lights"
      print "index, type/name, parent (if it has one)"
      print
      i = 1
      for o in self.lights[1:]:
        print i, o['_header'],
        if 'ParentObject' in o.keys():
          print o['ParentObject']
        else:
          print 'no parent'
        i += 1

    i = 1
    for o in self.lights[1:]:
      if 'ParentObject' in o.keys():
        find_parent_r_lights(parents, o, i)
      else:
        parents['lights'][i] = {'name' : o['_header']}
      i += 1
    
    if self.verbose:
      self.pp.pprint(parents)
    
    self.parents = parents
    
  def find_type(self, type, item=None):
    ret = []
    child_node = "zzc"
    if item == None:
      item = self.parents
    
    for c in item[child_node]:
      if item[child_node][c]['name'].has_key(type):
        self.pp.pprint(self.objects[c])
        ret.append(c)
      ret.append(self.find_type(type, item[child_node][c]))
    
    return ret

if __name__ == "__main__":
  lws = LWSC(verbose=0)
  lws.load(sys.argv[1])
  lws.obj_tree()
  lws.find_type('LoadObject')
  



