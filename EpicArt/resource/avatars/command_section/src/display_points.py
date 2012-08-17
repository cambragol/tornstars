#!/usr/local/bin/python
#
# $Id: display_points.py,v 1.2 2006/04/26 18:41:55 meep-cvs Exp $
#
# takes a points file and uses it to display a mesh with OpenGL
#

import string
import re

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.Tk import *
from OpenGL.GL.EXT.separate_specular_color import *
from OpenGL.GL.ARB.multitexture import *
import Image

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
        if re.match("^surf ", line):
            print "surface : ", line,
            # don't want to append an empty surf for the 1st line.
            if "r" in surf:
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
        if "t" in surf:
            mat = [surf["r"], surf["b"], surf["b"], surf["t"]]
            glMaterialfv(GL_FRONT, GL_EMISSION, mat)
            glMaterialfv(GL_FRONT, GL_DIFFUSE, mat)
        else:
            glColor3f(float(surf["r"]), float(surf["g"]), float(surf["b"]))
        glBegin(GL_TRIANGLES)
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
    
def redraw(o):

  if o.grob == -1:
    o.grob = glGenLists(1);
    # Stop using compile and execute.
    glNewList(o.grob, GL_COMPILE_AND_EXECUTE);
    glFrontFace(GL_CCW)     #
    glEnable(GL_CULL_FACE)  # added by jfp to use with new logo.py
    glEnable(GL_DEPTH_TEST) #
    glEnable(GL_TEXTURE_2D)
    glEnable(GL_LIGHTING)
    glShadeModel(GL_SMOOTH)
#    glHint(GL_NICEST, GL_GENERATE_MIPMAP_HINT)
    glMaterialfv(GL_FRONT, GL_DIFFUSE, [1., 1., 1., 0.])
    glMaterialf(GL_FRONT, GL_SHININESS, 80)
    glMaterialfv(GL_FRONT, GL_AMBIENT, [0.1, 0.1, 0.1, 0.0])
    glMaterialfv(GL_FRONT, GL_SPECULAR, [0.6, 0.6, 0.6, 0.0])

    glLightfv(GL_LIGHT0, GL_AMBIENT, [0.5, 0.5, 0.5, 0.5])
    glEnable(GL_LIGHT0)
    define_points()
    glEndList()

#    o.autospin = 0

#    o.xspin = 1
#    o.yspin = 2
    o.update()
#    o.after(10, o.do_AutoSpin)

  else:

    glCallList(o.grob)

#
# Demo starts here really.

import Tkinter, sys

o = Opengl(None, width = 640, height = 480, double = 1, depth = 1)
o.pack(expand = 1, fill = 'both')

o.redraw = redraw
o.set_centerpoint(0., 0., 0.)
o.set_eyepoint(450.)
o.far = 5000.0
o.set_background(0.1, 0.1, 0.1)
o.basic_lighting()
if glInitSeparateSpecularColorEXT():
    glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL_EXT, GL_SEPARATE_SPECULAR_COLOR_EXT)
if glInitMultitextureARB():
    print "We can multitexture!"

o.grob = -1

print glGetString(GL_VENDOR)

o.autospin_allowed = 0

# Enter the tk mainloop.

Tkinter.mainloop()

