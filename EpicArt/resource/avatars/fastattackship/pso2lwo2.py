#!/usr/bin/env python
#
# $Id: pso2lwo2.py,v 1.5 2008/06/22 16:30:32 jasper Exp $
#
# Convert PSO[2 ] -> LWO2
#

import chunk
import sys, os
from hexdump import hexdump
from struct import unpack
from lwo2 import LWO2
from PSO import PSO
import jgw_utils
import getopt

class PSO2LWO2(PSO):
	def __init__(self, verbose = 1):
		PSO.__init__(self)
		self.verbose = verbose

	def done(self):
		if self.verbose:
			print "parse done, generating .lwo"
		PSO.done(self)
		self.num_surfs = len(self.surfaces)
		self.lwo = LWO2()
		surfaces = self.snames
		
		for vert in self.verts:
			(x, y, z) = vert # vert also has normals and texture co-ords.
			self.lwo.add_point(x, y, z)
		
		sc_off = 0
		sc = 0
		poly = 0
		for s in surfaces:
			if self.verbose:
				print s
			self.lwo.add_surface(s)
			surf = self.surfaces[s]
#			print surf.keys()
#			for vert in surf['verts']:
#				x, y, z = vert[:3] # vert also has normals and texture co-ords.
#				self.lwo.add_point(x, y, z)
			
			if surf['ntex'] > 0:
				tc = 0
				for t in ['coltex', 'specmap', 'glowmap']:
					if t in surf:
						if t == 'coltex':
							chan = 'COLR'
						elif t == 'specmap':
							chan = 'SPEC'
						elif t == 'glowmap':
							chan = 'LUMI'
							self.lwo.add_lumi_to_surface(s, 0.0)
						else:
							assert False, "unknown texture type: %s" % (str(t))
						self.lwo.create_txuv(str(sc) + "-" + t, s, surf[t], chan, tc, surf['ntex'])
						tc += 1
			
			for tri in surf['triangles']:
				assert len(tri) == 3, "Triangles have 3 verts, this one didn't"
#				print
#				print tri[0], tri[0] + sc_off, self.verts[self.oldverts[tri[0] + sc_off]]
#				print tri[1], tri[1] + sc_off, self.verts[self.oldverts[tri[1] + sc_off]]
#				print tri[2], tri[2] + sc_off, self.verts[self.oldverts[tri[2] + sc_off]]
				
				self.lwo.add_pol(sc, [self.oldverts[tri[0] + sc_off], self.oldverts[tri[1] + sc_off], self.oldverts[tri[2] + sc_off]])
				
				uvoff = 0
				for t in ["coltex", "specmap", "glowmap"]:
					if t in surf:
						for v in [0, 1, 2]:
#							print "<",
							# uvmapname, vert, poly, [u,v]
#							print tri[v],
#							print tri[v] + sc_off,
#							print self.oldverts[tri[v] + sc_off],
							self.lwo.add_to_txuv(str(sc) + "-"  + t, self.oldverts[tri[v] + sc_off], poly, surf['verts'][tri[v]][6 + uvoff: 6 + 2 + uvoff])
#							print ">"
						uvoff += 2
				
				poly += 1
			
			sc_off += len(surf['verts'])
			
			sc += 1
		
		
		for s in surfaces:
			if self.verbose:
				print s
			surf = self.surfaces[s]
			self.lwo.add_color_to_surface(s, surf['red'], surf['green'], surf['blue'])
			if surf['alpha'] != 1.0:
				self.lwo.add_tran_to_surface(s, surf['alpha'])
#			self.lwo.add_flag_to_surface(s, 4) # 4 == smoothing
			self.lwo.add_sman_to_surface(s, 1.5620696544647217) # seen 2.0943951606750488 and 1.5620696544647217
			self.lwo.add_diff_to_surface(s, surf['diffuse'])
#			if surf['specular'] == 0:
#				self.lwo.add_spec_to_surface(s, 0.1)
#			else:
			self.lwo.add_spec_to_surface(s, surf['specular'])
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
		"--quiet"				: "don't print things as the conversion is being done",
		"--output=<file>"		: "output filename, if none is specified the inputfilename is used with .lwo shoved on the end.",
		"--texfileext=<.ext>"	: "change the file extention of the textures mentioned in the .lwo to .ext (defaults to .iff)"
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
			pso = PSO2LWO2(0)
		else:
			pso = PSO2LWO2()
		
		if 'output' not in opts:
			opts['output'] = leftovers[0] + ".lwo"
			
		
		pso.load(leftovers[0])
		
		if 'texfileext' in opts:
			pso.lwo.set_fileext(opts['texfileext'])
		
		pso.write_lwo(opts['output'])
	else:
		jgw_utils.usage(args)

