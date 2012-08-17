#!/usr/local/bin/python
#
# $Id: setup.py,v 1.3 2008/06/11 00:12:38 jasper Exp $
#
#

from distutils.core import setup
#import py2exe

#
# OpenGL and py2exe not working straight off, don't want to faff about now.
#
#, 'display_points.py'
#

setup(
    name = 'psotools',
    scripts = ['psotextool.py', 'pso2lwo.py', 'pso2lwo2.py', 'lwo-info.py', 
               'lwo2-info.py', 'pso-info.py', 'psoviewer.py', 'uvview.py',
               'pkginfo.py', 'lwo2topso.py', 'parse_headers.py'],
    py_modules = ['IFF', 'PSO', 'lwo', 'lwo2', 'colour', 'hexdump',
                  'jgw_utils', 'lwsc', 'saveiff'],
    version = '0.12',
    author='Jasper Wallace',
    author_email='jasper@pointless.net',
    url='http://pointless.net/eoc/',
    license = 'BSD',
    description = 'Tools for converting and creating .PSO files',
    classifiers = [
      'Development Status :: 4 - Beta',
      'Environment :: Console',
      'License :: OSI Approved :: BSD License',
      'Operating System :: OS Independent',
      'Programming Language :: Python'
    ]
#    zipfile=None
    )
  
