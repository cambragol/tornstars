#!/usr/local/bin/python
#
# $Id: setup.py,v 1.2 2006/04/26 18:41:55 meep-cvs Exp $
#
#

from distutils.core import setup
import py2exe

#
# OpenGL and py2exe not working straight off, don't want to faff about now.
#
#, 'display_points.py'
#

setup(name = 'psotools',
    console=['psotextool.py', 'pso2lwo.py', 'pso2lwo2.py', 'lwo-info.py', 'lwo2-info.py', 'pso-info.py'],
    version = '0.9',
    author='Jasper Wallace',
    author_email='jasper@pointless.net',
    url='http://pointless.net/eoc/'
#    zipfile=None
    )
  
