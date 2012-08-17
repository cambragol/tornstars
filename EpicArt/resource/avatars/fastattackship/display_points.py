#!/usr/local/bin/python
#
# $Id: display_points.py,v 1.5 2007/12/06 01:56:51 jasper Exp $
#
# takes a points file and uses it to display a mesh with OpenGL
#

import string
import re, sys

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from OpenGL.GL.EXT.separate_specular_color import *
from OpenGL.GL.ARB.multitexture import *
import Image, time

modellist = -1
angle = 0
fpstime = 0.0
frames = 0
anglex, angley = (0.0, 0.0)

def define_points():
  n = glNormal3f
  v = glVertex3f
  fh = open("points", "r")
  type = -1
  surfaces = []
  surf = {}
  textures = {}
  rawtex = {}
  for line in fh:
    # i guess
    # surf key:value;key:value
    # keys:
    # base - base texture : filename.ext
    # r
    # g } colours
    # b
    # t - alpha
    if re.match("^surf ", line):
#      print "surface : ", line,
      # don't want to append an empty surf for the 1st line.
      if 'red' in surf:
        surfaces.append(surf)
      surf = {}
      ignore, line = line.split()
      bits = line.split(";")
      for t in bits:
        key, value = t.split(":")
        surf[key] = value
      surf["tris"] = []
      continue
    
    if not "tris" in surf:
      print "Gahhh!"
      sys.exit(-1)
    # each triangle is
    # v:v:v
    # each v is space seperated
    # x y z nx ny nz bu bv (blah...)
    surf["tris"].append(line)

  # end of file, append the last surface.
  surfaces.append(surf)

  for surf in surfaces:
    tex = ""
    if "base" in surf:
      if surf["base"] in rawtex:
        surf["rawbasetex"] = rawtex[surf["base"]]
      else:
        tex = surf["base"]
        tex = tex[:tex.rfind(".")]
        for e in [".bmp", ".ppm", ".png"]:
          tfh = 0
          try:
            tfh = open(tex + e)
            tfh.close()
          except IOError:
            pass
                
          if tfh:
            print "tex : " + tex + e + " exists"
            tex = Image.open(tex + e)
            tx, ty = tex.size
            surf["btx"] = tx
            surf["bty"] = ty
            tex = tex.tostring("raw", "RGBX", 0, -1)
                    
            surf["rawbasetex"] = tex
            rawtex[surf["base"]] = tex
            break

  #            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP)
  #            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP)
  #            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
  #            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)


  for surf in surfaces:
    if "rawbasetex" in surf:
      if surf["base"] in textures:
        glBindTexture(GL_TEXTURE_2D, textures[surf["base"]])
      else:
        glt = glGenTextures(1)
        print "glt for %s: %d" % (surf["base"], glt)
        glBindTexture(GL_TEXTURE_2D, glt)
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1)
        glTexImage2D(GL_TEXTURE_2D, 0, 3, surf["btx"], surf["bty"], 0, GL_RGBA, GL_UNSIGNED_BYTE, surf["rawbasetex"])
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE)
        textures[surf["base"]] = glt
#        if 'alpha' in surf:
#            mat = [surf['red'], surf['green'], surf['blue'], surf['alpha']]
#            glMaterialfv(GL_FRONT, GL_EMISSION, mat)
#            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat)
#        else:

    glBegin(GL_TRIANGLES)
    rgba = [float(surf['red']), float(surf['green']), float(surf['blue']), 1.0]
    print rgba
    glColor4fv(rgba)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, rgba)
    glMaterialfv(GL_FRONT, GL_AMBIENT, rgba)

    glMaterialf(GL_FRONT, GL_SHININESS, 32.0) # XXX map spec 0.0 - 1.0 to 0.0 - 128.0
    glMaterialfv(GL_FRONT, GL_SPECULAR, (1.0, 1.0, 1.0, 1.0))

    for tri in surf["tris"]:
      verts = tri.split(":")
      for vert in verts:
        res = vert.split()[:6]
        res = map(float, res)
        x, y, z, nx, ny, nz = res
        if "base" in surf:
          res = vert.split()[6:8]
          res = map(float, res)
#                    res = map(invert, res)
          tx, ty = res
#                    print tx, ty
          ty = 1 - ty
          glTexCoord2f(tx, ty);
            
        n(nx,ny,nz)
        v(x, y, z)

    glEnd()

def invert(thing):
  thing -= thing * 2
  return thing
    
def redraw():
  global modellist, angle, fpstime, frames
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

  except KeyboardInterrupt:
    print 'exiting'
    sys.exit(0)

  fpsgoal = 75
  if end - start < (1.0 / fpsgoal):
    time.sleep((1.0 / fpsgoal) - (end - start))

  frames += 1
  sys.stdout.flush()

def reshape(w, h):
  glViewport(0, 0, w, h)
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
    0,0,2, # eyepoint
    0,0,0,  # center of view
    0,1,0   # up vector
  )

def key(k, x, y):
  if ord(k) == 27 or k == 'q': # 27 == escape
    sys.exit(0)
  else:
    print k, x, y
  sys.stdout.flush()
  
  # glutPostRedisplay()

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

def modelinit():
  modellist = glGenLists(1);
  glNewList(modellist, GL_COMPILE);

  define_points()
  glEndList()
  
  return modellist

def glinit():
  global modellist
#  print glGetString(GL_VENDOR)
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
#  glEnable(GL_TEXTURE_2D)
  glShadeModel(GL_SMOOTH)
#  glHint(GL_NICEST, GL_GENERATE_MIPMAP_HINT)
  
  if glInitSeparateSpecularColorEXT():
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL_EXT, GL_SEPARATE_SPECULAR_COLOR_EXT)

#  glLightfv(GL_LIGHT0, GL_AMBIENT, [1.0, 1.0, 1.0, 1.0])
#  glLightfv(GL_LIGHT0, GL_DIFFUSE, [1.0, 1.0, 1.0, 1.0])
#  glLightfv(GL_LIGHT0, GL_SPECULAR, [1.0, 1.0, 1.0, 1.0])
  glLightfv(GL_LIGHT0, GL_POSITION, [100.0, 100.0, 100.0, 0.0]);   
#  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, [0.5, 0.5, 0.5, 1.0])
  glEnable(GL_LIGHTING)
  glEnable(GL_LIGHT0)
  glDepthFunc(GL_LESS)

  modellist = modelinit()
  reshape(640, 480)
  glutMainLoop()


#if glInitMultitextureARB():
#  print "We can multitexture!"

#
#
#
if __name__ == "__main__":
  glinit()
