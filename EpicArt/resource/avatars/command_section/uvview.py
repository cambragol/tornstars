#!/usr/bin/env python
#
# $Id: uvview.py,v 1.2 2008/06/11 00:11:48 jasper Exp $
#
# takes a .pso and for each surface dumps the texture covered
# in the uvmap for that surface
#
# Useful for debugging etc.
#

import string, sys, os, getopt, Image, ImageDraw

from PSO import PSO
import jgw_utils

class PSO2uvdump(PSO):
  def __init__(self, filename, verbose = 1):
    PSO.__init__(self)
    self.verbose = verbose
    self.filename = filename
    self.load(filename)
    self.dump_uv()

  def dump_uv(self):
    print "dumping uv's"
    print 'will look for textures in', os.path.dirname(self.filename)
    tdir = os.path.dirname(self.filename)
    type = -1
    surf = {}
    textures = {}
    rawtex = {}
        
    sc_off = 0
    sc = 0

    # look for textures
    for s in self.surfaces:
      print 'surface:', s
      surf = self.surfaces[s]
      tex = ""
      for tt in ['coltex', 'specmap', 'glowmap']:
        if tt in surf:
          print 'uses %s for %s' % (surf[tt], tt)
          if surf[tt] in rawtex:
            # if we've already got it, use it
            surf['raw' + tt] = rawtex[surf[tt]][0]
            surf[tt + 'x'] = rawtex[surf[tt]][1]
            surf[tt + 'y'] = rawtex[surf[tt]][2]
          else:
            # else load it
            print 'looking for %s for %s for surface %s' % (surf[tt], tt, s)
            tex = surf[tt]
            tex = tex[:tex.rfind('.')]
            for e in ['.bmp', '.ppm', '.png', '.jpg']:
              tfh = 0
              try:
                tfh = open(os.path.join(tdir, tex + e))
                tfh.close()
              except IOError:
                pass
                    
              if tfh:
                print "tex : " + tex + e + " exists"
                tex = Image.open(os.path.join(tdir, tex + e))

                tx, ty = tex.size
                pot = [2 ** x for x in range(4,12)]
                if tx not in pot or ty not in pot:
                  print 'FAIL: texture %s size not a power of 2 (%d x %d)' % (surf[tt], tx, ty)
                  sys.exit(-1)

                tex = tex.convert('RGB')
                surf[tt + 'x'] = tx
                surf[tt + 'y'] = ty
                tex = tex.tostring('raw', 'RGB', 0, 0)#-1)
                surf['raw' + tt] = tex
                rawtex[surf[tt]] = (tex, tx, ty)
                break
    
    #
    # at this point we've got an RGB bitmap in memory for the coltex
    # for each surface that has a coltex
    #
    for s in self.surfaces:
      surf = self.surfaces[s]
      ttoff = {}
      b = 6
      for tt in ['coltex', 'specmap', 'glowmap']:
        if tt in surf:
          ttoff[tt] = b
          b+= 2

      for tt in ['coltex', 'specmap', 'glowmap']:
        if tt not in surf:
          continue

        tex = Image.new('RGB', (surf[tt + 'x'], surf[tt + 'y']), '#000000')
        tex.fromstring(surf['raw' + tt])
        x = surf[tt + 'x']
        y = surf[tt + 'y']

        #rgba = [surf['red'], surf['green'], surf['blue'], surf['alpha']]
        rgb = [surf['red'], surf['green'], surf['blue']]
        rgb = ['%02x' % (int(255 * i)) for i in rgb]
        rgb = '#' + ''.join(rgb)
  #      rgb = '#ff0000'
        print rgb
        id = ImageDraw.Draw(tex)

        def vert_to_xy(vert, x, y, off):
          res = vert[off:off + 2]
          # res is floats from 0.0 -> 1.0 (hopefully)
          tu, tv = res
#          print res
          tu = int(x * tu)
          tv = int(y * tv)
#          print tu, tv
          if 0:
            odd = False
            if tu < 0:
              tu = abs(tu)
              odd = True
            if tu > x:
              tu -= x
              odd = True
            if tv < 0:
              tv = abs(tv)
              odd = True
            if tv > y:
              tv -= y
              odd = True
            if odd:
              return tu, tv
            else:
              return 0,0
          return tu, tv

        for tri in surf['triangles']:
          # put the verticies in the 'wrong' way round, so that they are right for opengl.
          pu, pv = vert_to_xy(surf['verts'][tri[0]], x, y, ttoff[tt])
          for vert in (tri[2], tri[1], tri[0]):
            tu, tv = vert_to_xy(surf['verts'][vert], x, y, ttoff[tt])
  #          print (pu, pv, tu, tv), rgb
            id.line((pu, pv, tu, tv), fill=rgb, width=1)
            pu = tu
            pv = tv
        
        print 'done %s for %s' % (tt, s)
        out = '%s_%s.png' % (s, tt)
        out = tdir + os.path.sep + out
  #      del id
        print out
        tex.save(out)

  def done(self):
    if self.verbose:
      print "parse done"
    PSO.done(self)  

def invert(thing):
  thing -= thing * 2
  return thing

if __name__ == "__main__":
  args = {
    "--verbose"        : "verbosify",
  }
  
  flags = map(jgw_utils.finder, args.keys())
  
  opts = {}
  
  if (len(sys.argv) > 1):
    try:
      flags, leftovers = getopt.getopt(sys.argv[1:], '', flags)
    except getopt.GetoptError:
      jgw_utils.usage(args)
      sys.exit(-1)

    if len(leftovers) != 1:
      print "you need to specify a .pso file to view"
      jgw_utils.usage(args)
      sys.exit(-1)
    
    for o, a in flags:
      opts[o.lstrip('-')] = a
    
    if 'verbose' in opts:
      PSO2uvdump(leftovers[0], verbose=True)
    else:
      PSO2uvdump(leftovers[0], verbose=False)
  else:
    jgw_utils.usage(args)

