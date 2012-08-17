#!/usr/bin/env python
#
# $Id: psoviewer.py,v 1.8 2008/06/13 17:05:43 jasper Exp $
#
# takes a points file and uses it to display a mesh with OpenGL
#

import string, re, sys, os, chunk, getopt, Image, time

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from OpenGL.GL.EXT.separate_specular_color import *
from OpenGL.GL.ARB.multitexture import *

from struct import unpack

from hexdump import hexdump
from PSO import PSO
import jgw_utils

modellist = -1
angle = 0
fpstime = 0.0
frames = 0
anglex, angley = (0.0, 0.0)
eyedist = 10 # XXX calculate object bb and do this automatticly.

class PSO2GLList(PSO):
  def __init__(self, verbose = 1):
    PSO.__init__(self)
    self.verbose = verbose
    self.list = -1
    
  def makelist(self):
    self.list = glGenLists(1);
    glNewList(self.list, GL_COMPILE);

    #
    # XXX FIXEME
    #
    # Sick, Sick, Sick
    #
    # we flip the model inside out to get
    # the textures un-mirrored,
    # but this means the triangles are the wrong way round.
    # we don't glEnable(GL_CULL_FACE) so we can see them,
    # but thats a hack.
    #
    # oh, and flipping our model *each* *frame* is
    # very, very wrong.
    #
    # XXX FIXEME
    #
    glScalef(1.0, 1.0, -1.0)
    self.define_model()
    glEndList()
  
    return self.list

  def define_model(self):
    print ">>> defineing model <<<"
    print 'will look for textures in', os.path.dirname(self.filename)
    tdir = os.path.dirname(self.filename)
    n = glNormal3f
    v = glVertex3f
    type = -1
    surf = {}
    textures = {}
    rawtex = {}
        
    sc_off = 0
    sc = 0

    # look for textures
    for s in self.surfaces:
      surf = self.surfaces[s]
      tex = ""
      for tt in ['coltex', 'specmap', 'glowmap']:
        if tt in surf:
          if surf[tt] in rawtex:
            #' if we've already got it, use it
            print 'already got %s for %s (%s)' % (tt, s, surf[tt])
            surf['raw' + tt] = rawtex[surf[tt]]
          else:
            # else load it
            print 'looking for %s for %s (%s)' % (tt, s, surf[tt])
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
                tex = tex.convert('RGB')
                tx, ty = tex.size
                pot = [2 ** x for x in range(4,12)]
                if tx not in pot or ty not in pot:
                  print 'FAIL: texture %s size not a power of 2 (%d x %d)' % (surf[tt], tx, ty)
                  sys.exit(-1)
                surf[tt + 'x'] = tx
                surf[tt + 'y'] = ty              
                tex = tex.tostring("raw", 'RGB', 0, 0)#-1)
                surf['raw' + tt] = tex
                rawtex[surf[tt]] = tex
                break

    for s in self.surfaces:
      surf = self.surfaces[s]
      for tt in ['coltex', 'specmap', 'glowmap']:
        if 'raw' + tt in surf:
          if surf[tt] in textures:
            #glBindTexture(GL_TEXTURE_2D, textures[surf['coltex']])
            pass
          else:
            glt = glGenTextures(1)
            print "glt for %s: %d" % (surf[tt], glt)
            glBindTexture(GL_TEXTURE_2D, glt)
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1)
            glTexImage2D(GL_TEXTURE_2D, 0, 3, surf[tt + 'x'], surf[tt + 'y'], 0, GL_RGB, GL_UNSIGNED_BYTE, surf['raw' + tt])
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE)
            textures[surf[tt]] = glt

    #            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP)
    #            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP)
    #            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
    #            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
  #        if 'alpha' in surf:
  #            mat = [surf['red'], surf['green'], surf['blue'], surf['alpha']]
  #            glMaterialfv(GL_FRONT, GL_EMISSION, mat)
  #            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat)
  #        else:

    # now do the triangles etc      
    for s in self.surfaces:
      print s
      surf = self.surfaces[s]
      if surf['alpha'] != 1.0:
        print 'skipping transparent surface', s
        continue

      if 'coltex' in surf and surf['coltex'] in textures:
        glBindTexture(GL_TEXTURE_2D, textures[surf['coltex']])
#      elif 'glowmap' in surf and surf['glowmap'] in textures:
#        glBindTexture(GL_TEXTURE_2D, textures[surf['glowmap']])

#      if 'specmap' in surf and surf['specmap'] in textures:
#        glBindTexture(GL_TEXTURE_2D, textures[surf['specmap']])

      glBegin(GL_TRIANGLES)
      rgba = [1.0, 1.0, 1.0, 1.0]
      glColor4fv(rgba)
      glMaterialfv(GL_FRONT, GL_DIFFUSE, rgba)
#      glMaterialfv(GL_FRONT, GL_AMBIENT, rgba)
      if 'coltex' not in surf:
        rgba = (surf['red'], surf['green'], surf['blue'], surf['alpha'])
        print 'rgba', rgba
        glColor4fv(rgba)
        glMaterialfv(GL_FRONT, GL_DIFFUSE, rgba)
#        glMaterialfv(GL_FRONT, GL_AMBIENT, rgba)

#      spec = surf['specular'] * 128
#      if spec == 0.0:
#        spec = 64

#      print 'spec', spec
#      glMaterialf(GL_FRONT, GL_SHININESS, int(spec))
#      glMaterialfv(GL_FRONT, GL_SPECULAR, rgba)

#      if 'coltex' not in surf:
#        print 'no coltex'

      for tri in surf['triangles']:
        assert len(tri) == 3, "Triangles have 3 verts, this one didn't"
        # put the verticies in the 'wrong' way round, so that they are right for opengl.
        for vert in (tri[2], tri[1], tri[0]):
          x, y, z, nx, ny, nz = surf['verts'][vert][:6]
          # vertex left overs
          # vlo = len(surf['verts'][vert]) - 6
          if 'coltex' in surf:
            res = surf['verts'][vert][6:8]
            res = map(float, res)
            tu, tv= res
            #
            # directX has y co-ords the other way up.
            # flipping them like this mirrors the textures
            # so we flip the model inside out, see
            # PSO2GLList.makelist for more info
            #
            # this also why the triangle verts are entered the wrong way round above.
            #
            # Actually no, for some reson we flipped the textures
            # (the -1 on the end of tex.tostring).
            #
            # If we don't flip the texture we don't need
            # to flip the v coord, so don't do either.
            # 
            #tv = 1 - tv
            glTexCoord2f(tu, tv);
#          elif 'specmap' in surf:
#            uvbase = 6
#            if 'coltex' in surf:
#              uvbase += 2
#            if 'specmap' in surf:
#              uvbase += 2
#            res = surf['verts'][vert][uvbase:uvbase + 2]
#            res = map(float, res)
#            tu, tv= res
#            glTexCoord2f(tu, tv);
          
          if 'coltex' not in surf:
            glColor4fv(rgba)
          n(nx,ny,nz)
          v(x, y, z)
      print
      glEnd()

  def done(self):
    if self.verbose:
      print "parse done"
    PSO.done(self)

    

# red
# green
# blue
# alpha
#
# ntex
# triangles
# verts
# vertsz
#
# diffuse
# glow
# specular
#
# coltex
# colflags
#
# glowmap
# glowflags
#
# specmap
# specflags
#
# highlighttex

#      for vert in surf['verts']:
#        x, y, z = vert[:3] # vert also has normals and texture co-ords.
#        print vert
#        self.lwo.add_point(x, y, z)
      
#      if surf['ntex'] > 0:
#        tc = 0
#        for t in ['coltex', 'specmap', 'glowmap']:
#          if t in surf:
#            if t == 'coltex':
#              chan = 'COLR'
#            elif t == 'specmap':
#              chan = 'SPEC'
#            elif t == 'glowmap':
#              chan = 'LUMI'
#              self.lwo.add_lumi_to_surface(s, 0.0)
#            else:
#              assert False, "unknown texture type: %s" % (str(t))
#            self.lwo.create_txuv(str(sc) + "-" + t, s, surf[t], chan, tc, surf['ntex'])
#            tc += 1
      
#      for tri in surf['triangles']:
#        assert len(tri) == 3, "Triangles have 3 verts, this one didn't"
#        print
#        print tri[0], tri[0] + sc_off, self.verts[self.oldverts[tri[0] + sc_off]]
#        print tri[1], tri[1] + sc_off, self.verts[self.oldverts[tri[1] + sc_off]]
#        print tri[2], tri[2] + sc_off, self.verts[self.oldverts[tri[2] + sc_off]]
        
#        self.lwo.add_pol(sc, [self.oldverts[tri[0] + sc_off], self.oldverts[tri[1] + sc_off], self.oldverts[tri[2] + sc_off]])
        
#        uvoff = 0
#        for t in ["coltex", "specmap", "glowmap"]:
#          if t in surf:
#            for v in [0, 1, 2]:
#              print "<",
              # uvmapname, vert, poly, [u,v]
#              print tri[v],
#              print tri[v] + sc_off,
#              print self.oldverts[tri[v] + sc_off],
#              self.lwo.add_to_txuv(str(sc) + "-"  + t, self.oldverts[tri[v] + sc_off], poly, surf['verts'][tri[v]][6 + uvoff: 6 + 2 + uvoff])
#              print ">"
#            uvoff += 2
        
#        poly += 1
      
#      sc_off += len(surf['verts'])
      
#      sc += 1
    
    
#    for s in surfaces:
#      if self.verbose:
#        print s
#      surf = self.surfaces[s]
#      self.lwo.add_color_to_surface(s, surf['red'], surf['green'], surf['blue'])
#      if surf['alpha'] != 1.0:
#        self.lwo.add_tran_to_surface(s, surf['alpha'])
#      self.lwo.add_flag_to_surface(s, 4) # 4 == smoothing
#      self.lwo.add_sman_to_surface(s, 1.5620696544647217) # seen 2.0943951606750488 and 1.5620696544647217
#      self.lwo.add_diff_to_surface(s, surf['diffuse'])
#      if surf['specular'] == 0:
#        self.lwo.add_spec_to_surface(s, 0.1)
#      else:
#        self.lwo.add_spec_to_surface(s, surf['specular'])
#      if surf['highlighttex'] != "(null)":
#        self.lwo.add_rimg_to_surface(s, surf['highlighttex'])
      #REFL VRFL
      #
      # XXX tflags (if they mean something)
      # XXX sflags
      #
  

def invert(thing):
  thing -= thing * 2
  return thing
    
def redraw():
  global modellist, angle, fpstime, frames
#  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  start = time.time()
  
  fpssampletime = 20
  
  if fpstime == 0.0:
    fpstime = start + fpssampletime
    frames = 0
  
  if start > fpstime:
    print "FPS:", str(frames / fpssampletime)
    fpstime = start + fpssampletime
    frames = 0
  
  try:
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glPushMatrix()
    
#    angle = (angle + 1) % 360
    
#  glTranslatef(0, -1, 0)
    glRotatef(anglex, 1.0, 0.0, 0.0)
    glRotatef(angley, 0.0, 1.0, 0.0)
    glCallList(modellist)

    glPopMatrix()
#    glFlush()
    glutSwapBuffers()
    end = time.time()

  except KeyboardInterrupt:#, OpenGL.GL.:
    print 'exiting'
    sys.exit(0)

  fpsgoal = 75
  if end - start < (1.0 / fpsgoal):
    time.sleep((1.0 / fpsgoal) - (end - start))

  frames += 1
  sys.stdout.flush()

def reshape(w, h):
  global eyedist
  glViewport(0, 0, int(w), int(h))
  glMatrixMode(GL_PROJECTION)
  glLoadIdentity()
  x, y, width, height = glGetDoublev(GL_VIEWPORT)
  gluPerspective(
    45, # fov in degrees
    width / float(height or 1), # aspect ratio
    .25, # near clipping plane
    5000, # far clipping plane
  )

  # and then the model view matrix
  glMatrixMode(GL_MODELVIEW)
  glLoadIdentity()
  gluLookAt(
    0,0,eyedist, # eyepoint
    0,0,0,  # center of view
    0,1,0   # up vector
  )

def key(k, x, y):
  global eyedist
  if ord(k) == 27 or k == 'q': # 27 == escape
    sys.exit(0)
  elif k == '=': # zoom in
    eyedist -= 1
    if eyedist < 1:
      eyedist = 1
  elif k == '-': # zoom out
    eyedist += 1
  else:
    print 'key', k, x, y
  
  sys.stdout.flush()
  x, y, width, height = glGetDoublev(GL_VIEWPORT)
  reshape(width, height)

def special(k, x, y):
  global anglex, angley
  if k == GLUT_KEY_UP:
    anglex = (anglex + 1) % 360
  elif k == GLUT_KEY_DOWN:
    anglex = (anglex - 1) % 360
  elif k == GLUT_KEY_LEFT:
    angley = (angley + 1) % 360
  elif k == GLUT_KEY_RIGHT:
    angley = (angley - 1) % 360
  else:
    print 'special', k, x, y
  sys.stdout.flush()

def mouse(button, state, x, y):
  print 'mouse', button, state, x, y
  sys.stdout.flush()

def glinit(pso):
  global modellist
  print glGetString(GL_VENDOR)
  glutInit(sys.argv)
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH) # | GLUT_ALPHA )
  glutInitWindowPosition(0,0)
  glutInitWindowSize(640, 480)
  glutCreateWindow("""PSO viewer""")
  
  glutKeyboardFunc(key)
  glutSpecialFunc(special)
  glutMouseFunc(mouse)
  
  glutDisplayFunc(redraw)
  glutIdleFunc(redraw)
  glutReshapeFunc(reshape)
  
  glEnable(GL_DEPTH_TEST)
#  glFrontFace(GL_CCW)
  glEnable(GL_CULL_FACE)
  glEnable(GL_TEXTURE_2D)
  glShadeModel(GL_SMOOTH)
#  glShadeModel(GL_FLAT)
#  glHint(GL_NICEST, GL_GENERATE_MIPMAP_HINT)

#  glEnable(GL_BLEND)
  #  glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE)
#  glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR)
#  glBlendFunc(GL_SRC_ALPHA, GL_ONE)
#  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
#  glBlendFunc(GL_SRC_COLOR, GL_SRC_ALPHA)

#  if glInitSeparateSpecularColorEXT():
#    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL_EXT, GL_SEPARATE_SPECULAR_COLOR_EXT)

  glLightfv(GL_LIGHT0, GL_AMBIENT, [0.0, 0.0, 0.0, 1.0])
  glLightfv(GL_LIGHT0, GL_DIFFUSE, [1.0, 1.0, 1.0, 1.0])
#  glLightfv(GL_LIGHT0, GL_SPECULAR, [1.0, 1.0, 1.0, 1.0])
  glLightfv(GL_LIGHT0, GL_POSITION, [100.0, 100.0, 100.0, 0.0])
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, [0.1, 0.1, 0.1, 1.0])
  glEnable(GL_LIGHTING)
  glEnable(GL_LIGHT0)
  glDepthFunc(GL_LESS)

  modellist = pso.makelist()
  reshape(640, 480)
  glutMainLoop()


#if glInitMultitextureARB():
#  print "We can multitexture!"

#
#
#
if __name__ == "__main__":
  args = {
    "--quiet"        : "don't print things as the conversion is being done",
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
    
    if 'quiet' in opts:
      pso = PSO2GLList(0)
    else:
      pso = PSO2GLList()
        
    pso.load(leftovers[0])
    
    glinit(pso)
  else:
    jgw_utils.usage(args)

