#!/usr/bin/env python
#
#
#
# ./ts-gv-map.py| neato -s2  -Tpng -o ts.png
#

import ConfigParser, os
from eoc import Map

#base_path = "/home/pcguest/eoc stuff/"
base_path = "/home/jasper/develop/ts/eocsvn/tornstars/trunk/EpicSource/clusters/US_Mod_Geog/"

if __name__ == "__main__":
  cp = ConfigParser.SafeConfigParser()
  cp.read([base_path + os.path.sep + 'geog' + os.path.sep + 'clusters.ini'])
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
#    else:
#      print i
  
  ks = maps.keys()
  ks.sort()
  for k in ks:
    systems.append(Map(maps[k], base_path, verbose=1))
