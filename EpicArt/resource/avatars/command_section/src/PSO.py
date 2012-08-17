#!/usr/local/bin/python
#
# $Id: PSO.py,v 1.2 2006/04/26 18:41:55 meep-cvs Exp $
#
# A class to load PSO format files.
#

import chunk
import sys, os
from hexdump import hexdump, tobin
from struct import unpack
from IFF import IFF
from lwo import LWO
from math import sqrt
import pprint

class PSO(IFF):
	def __init__(self):
		IFF.__init__(self)
		self.types = ["PSO2", "PSO "]
		self.verbose = 1
		self.callbacks = {"OHDR": self.ohdr, "SHDR": self.shdr, "VERT": self.vert, "INDX": self.indx, "DELT": self.dump_chunk, "FRAM": self.dump_chunk}
		

	def done(self):
		assert self.n_surfaces == len(self.surfaces), "Number of surfaces don't match, in ohdr: %d, parsed: %d" % (self.n_surfaces, len(self.surfaces))
#		print self.verts
#		print self.newverts
#		print self.oldverts
		assert len(self.verts) == len(self.newverts)

	def close(self, dist, v1, v2):
		res = 0.0
		for v in [0, 1, 2]:
			res += (v1[v] - v2[v]) ** 2
		
		res = sqrt(res)
		
		if res < dist:
			return 1
		else:
			return 0

	def ohdr(self, type, blob):
		bit = blob[0:12]
		version, surfaces, textures = unpack(">III", bit)
		assert version == 1, "Unexpected version: %d" % (version)
		if self.verbose:
			print "ver: %d, surfs: %d, textures: %d" % (version, surfaces, textures)
			print
		self.n_surfaces = surfaces
		self.n_textures = textures
		off = 12
		i = 0;
		self.textures = []
		self.surfaces = {}
		self.snames = []	# ordered list of surfaces.
		self.verts = []
		#
		# old -> new
		#
		self.oldverts = {}
		# new -> [old, old]
		self.newverts = {}
		# uniq verts
		# therefore verts near each other
		#
		# need to map from uniq verts -> old verts to find uv coords
		# need to map backwards?
		#
		while 1:
			tex = self.get_string(blob[off:])
			off += len(tex) + 1
			if len(tex) == 0:
				tex = "(null)"
			if self.verbose:
				print "%%%", tex, "%%%"
			self.textures.append(tex)
			i += 1
			if off >= len(blob):
				break
		if not (textures == 0 and i == 1):
			assert i == textures, "Expected %d textures, got %d in %s" % (textures, i, self.filename)

	def shdr(self, type, blob):
		surface_name = self.get_string(blob)
		self.surfaces[surface_name] = {}
		self.snames.append(surface_name)
		
		
		if self.verbose:
			print "Surface name: %s" % (surface_name)
		off = len(surface_name) + 1

		if self.verbose:
			print unpack(">ffff", blob[off:off + (4 * 4)])
		
		(self.surfaces[surface_name]['red'],
		self.surfaces[surface_name]['green'], 
		self.surfaces[surface_name]['blue'],
		self.surfaces[surface_name]['alpha']) = unpack(">ffff", blob[off:off + (4 * 4)])
		
		off += 4 * 4
		
		coltex = specmap = glowmap = ""
		
		#
		# texture flags:
		#
		# 24 is very common 32 & 4
		# 21 is rarer		32 & 1 (Truck0_T.PSO: TRK_Pistons)
		#
		# only ever there when a texture is there.
		#
		# guess:
		# 32 == use spec.
		# 4  == ?
		# 1  == ?
		
		diffuse, coltex, tflags = unpack(">fII", blob[off:off + (3 * 4)])
		if self.verbose:
			print "base texture  : %s %02x : %s %f" % (coltex, tflags, tobin(tflags), diffuse)
		if coltex > 0:
			self.surfaces[surface_name]['coltex'] = self.textures[coltex - 1]
			self.surfaces[surface_name]['colflags'] = tflags
		
		# XXX sometime diffuse is specified without a texture,
		self.surfaces[surface_name]['diffuse'] = diffuse
		
		off += 3 * 4
		
		reflection, specmap, tflags = unpack(">fII", blob[off:off + (3 * 4)])
		if self.verbose:
			print "gloss/spec map: %s %02x : %s %f" % (specmap, tflags, tobin(tflags), reflection)
		if specmap > 0:
			self.surfaces[surface_name]['specmap'] = self.textures[specmap - 1]
			self.surfaces[surface_name]['specflags'] = tflags
		self.surfaces[surface_name]['specular'] = reflection
		
		off += 3 * 4
		
		thing, glowmap, tflags = unpack(">fII", blob[off:off + (3 * 4)])
		if self.verbose:
			print "glow map      : %s %02x : %s %f" % (glowmap, tflags, tobin(tflags), thing)
		if glowmap > 0:
			self.surfaces[surface_name]['glowmap'] = self.textures[glowmap - 1]
			self.surfaces[surface_name]['glowflags'] = tflags

		self.surfaces[surface_name]['glow'] = thing
		off += 3 * 4
		
		
		surf_str = self.get_string(blob[off:])
		off += len(surf_str) + 1
		if len(surf_str) == 0:
			surf_str = "(null)"
		
		if self.verbose:
			print "Highlight texture: %s" % (surf_str)
		
		self.surfaces[surface_name]['highlighttex'] = surf_str
		
		self.has_tex = 0
		# thing is a count of vertices in this surface
		nverts, tex_count = unpack(">II", blob[off:])
		if self.verbose:
			print "last 2 ints:", nverts, tex_count
			print
		
		tct = 0
		for f in [coltex, specmap, glowmap]:
			if f != 0:
				tct += 1
		
		assert tex_count < 4
		assert tex_count > -1
		assert tex_count == tct, "Texture count missmatch"
		
		self.surfaces[surface_name]['ntex'] = tex_count
		self.surfaces[surface_name]['vertsz'] = 24 + (tex_count * 8)
		
		self.current_surface = surface_name
		
	def vert(self, type, blob):
		length = len(blob)
		self.vertlen = length	# XXX
		ups = ""
		surf = self.surfaces[self.current_surface]
		vertsz = surf['vertsz']
		surf['verts'] = []
		
		assert length % vertsz == 0, "Vertsz wrong for %s - this means i don't understand SHDR chunks properly (yet)." % (self.filename)
		
		ups = "f" * (vertsz / 4)
		ups = "<" + ups
		
		vn = len(self.oldverts)
		off = 0
		
		while off < length:
			vert = unpack(ups, blob[off:off + (vertsz)])
			
			off += vertsz
			
			surf['verts'].append(vert)
			v = vert[0:3]
			
			found = 0
			
			if len(self.verts) != 0:
				for vnew in self.verts:
					if self.close(0.00001, vnew, v):
						idx = self.verts.index(vnew)
						self.oldverts[vn] = idx
						if idx in self.newverts:
							self.newverts[idx].append(vn)
						else:
							print "not in newverts"
							self.newverts[idx] = [vn]
#						print v, "vert no. ", vn, " is now ", idx
						found = 1
						break
				
			if not found:
#				print v, "vert no. ", vn, " is now ", len(self.verts)
				self.oldverts[vn] = len(self.verts)
				self.newverts[len(self.verts)] = [vn]
				self.verts.append(v)
			
			vn += 1
	
	def indx(self, type, blob):
		#
		# The 1st two byes of an INDX chunk
		# are the wierdest thing in PSO land
		#
		# for PSO2 it's usually the count of the number of
		# triangles in the chunk
		#
		# for "PSO " it's usually gibberish.
		#
		# I just go with the length of the blob.
		#
		if self.type == "PSO2":
			tris, = unpack(">H", blob[:2])
		else:
#			print unpack("BB", blob[:2])
#			print unpack("bb", blob[:2])
#			tris, = unpack("<H", blob[:2])
#					print "PSO tris", tris
#					print "%d %d %d" % ((len(blob) / 2) / 3, (len(blob) / 2) % 3, tris)
			tris = ((len(blob) - 2) / 2) / 3
#				print "%d triangles: %d %d" % (tris, tris * 6, len(blob) - 2)
		
#				assert tris *6 == len(blob) - 2, "Wierd number of triangles?!?"
		
		if tris * 6 != len(blob) - 2:
#			print "oops, that can't be right"
#			hexdump(blob[:4])
			tris, = unpack("<H", blob[:2])
#			print tris
#			print unpack("BB", blob[:2])
#			print unpack("bb", blob[:2])
			if tris * 3 * 2 == len(blob) - 2:
				pass
			else:
				tris = (len(blob) - 2) / 6
				# should really
				#sys.exit(-1)
		
		surf = self.surfaces[self.current_surface]
		
		if self.verbose:
			print "tris:", tris
		i = 0
		off = 2
		point_max = -1
		surf['triangles'] = []
		while (i < tris):
			p0, p1, p2 = unpack("<HHH", blob[off:off + (2 * 3)])
			
			surf['triangles'].append([p0, p1, p2])
			
			for p in [p0, p1, p2]:
				if p > point_max:
					point_max = p
#			self.pfh.write("%s:%s:%s\n" % (self.points[p0], self.points[p1], self.points[p2]))
			
			i += 1
			off += 2 * 3
		
		if self.verbose:
			print "max points: %d, vert len: %d :: %d" % (point_max + 1, len(surf['verts']), len(surf['verts']) / (point_max + 1))
		# XXX SmallGantryD_LOD2_T.PSO
		if (point_max + 1) != (len(surf['verts']) * (24 + (surf['ntex'] * 8))) / surf['vertsz']:
			print "DARN - vertsz dosn't match the number of points for %s: nt: %d vs: %d" % (self.filename, surf['ntex'], surf['vertsz'])
#			sys.exit(-1)

#		surf['verts'] = None
		
		if self.verbose:
			print

if __name__ == "__main__":
#	pp = pprint.PrettyPrinter(indent=1, depth=5)
	if (len(sys.argv) == 2):
		pso = PSO()
		pso.load(sys.argv[1])
	else:
		pso = PSO()
		pso.load("test-pso/2_lor_ribJB.PSO")

#	pp.pprint(pso)
#	print dir(pso)
#	pp.pprint(pso.surfaces)
