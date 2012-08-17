#!/usr/local/bin/python
#
# $Id: pso2lwo.py,v 1.2 2006/04/26 18:41:55 meep-cvs Exp $
#
# A Class to load IFF format files.
#

import chunk
import sys, os
from hexdump import hexdump
from struct import unpack
from lwo import LWO
from PSO import PSO
import jgw_utils
import getopt

class PSO2LWO(PSO):
	def __init__(self, verbose=1):
		PSO.__init__(self)
		self.verbose = verbose

	def done(self):
		if self.verbose:
			print "parse done."
		PSO.done(self)
		self.num_surfs = len(self.surfaces)
		self.lwo = LWO()
		surfaces = self.snames
		
		for vert in self.verts:
			(x, y, z) = vert # vert also has normals and texture co-ords.
			self.lwo.add_point(x, y, z)

		sc_off = 0
		sc = 0
		for s in surfaces:
			surf = self.surfaces[s]
#			for vert in surf['verts']:
#				x, y, z = vert[:3] # vert also has normals and texture co-ords.
#				self.lwo.add_point(x, y, z)
			
			for tri in surf['triangles']:
				assert len(tri) == 3, "Triangles have 3 verts, this one didn't"
				self.lwo.add_pol(sc, [self.oldverts[tri[0] + sc_off], self.oldverts[tri[1] + sc_off], self.oldverts[tri[2] + sc_off]])
			
			sc_off += len(surf['verts'])
			sc += 1
		
		
		for s in surfaces:
			if self.verbose:
				print s
			surf = self.surfaces[s]
			self.lwo.add_surface(s)
			self.lwo.add_color_to_surface_f(s, surf['red'], surf['green'], surf['blue'])
			if surf['alpha'] != 1.0:
				self.lwo.add_tran_to_surface(s, surf['alpha'])
			self.lwo.add_flag_to_surface(s, 4) # 4 == smoothing
			self.lwo.add_sman_to_surface(s, 2.09999990463) # seen 2.0943951606750488 and 1.5620696544647217
			self.lwo.add_diff_to_surface(s, int(256 * surf['diffuse']))
			self.lwo.add_vdif_to_surface(s, surf['diffuse'])
			self.lwo.add_vspc_to_surface(s, surf['specular'])
			if surf['highlighttex'] != "(null)":
				self.lwo.add_rimg_to_surface(s, surf['highlighttex'])
			#REFL VRFL
			#
			# XXX tflags (if they mean something)
			# XXX sflags
			#
	
	def write_lwo(self, fn):
		self.lwo.write(fn)


if __name__ == "__main__":
	args = {
		"--quiet"			: "don't print things as the conversion is being done",
		"--output=<file>"	: "output filename, if none is specified the inputfilename is used with .lwo shoved on the end."
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
			print "you need to specify a .pso file to convert"
			jgw_utils.usage(args)
			sys.exit(-1)
		
		for o, a in flags:
			opts[o.lstrip('-')] = a
		
		if 'quiet' in opts:
			pso = PSO2LWO(0)
		else:
			pso = PSO2LWO()
		
		if 'output' not in opts:
			opts['output'] = leftovers[0] + ".lwo"
		
		pso.load(leftovers[0])
		pso.write_lwo(opts['output'])
	else:
		jgw_utils.usage(args)
