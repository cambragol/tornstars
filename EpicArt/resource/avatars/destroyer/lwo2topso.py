#!/usr/local/bin/python
#
# $Id: lwo2topso.py,v 1.10 2008/06/22 16:00:52 jasper Exp $
#
# A class to convert lwo2 to pso2
#
# http://www.newtek.com/products/lightwave/developer/LW80/8lwsdk/docs/filefmts/lwo2.html
# http://www.newtek.com/products/lightwave/developer/LW80/8lwsdk/docs/filefmts/lwo2ex/lwo2ex.html
#
# http://www.openscenegraph.org/svn/osg/OpenSceneGraph/tags/OpenSceneGraph-2.0.0/src/osgPlugins/lwo/lwo2chunks.h
#
# https://svn.blender.org/svnroot/bf-blender/trunk/blender/release/scripts/lightwave_import.py
# https://svn.blender.org/svnroot/bf-blender/trunk/blender/release/scripts/lightwave_export.py
#

import chunk
import sys, os, os.path
from hexdump import hexdump
from struct import unpack, pack, calcsize
from IFF import IFF
from saveiff import make_chunk
import math, array
import lwo2

class UnpackIter:
	def __init__(self, ups, blob):
		self.blob = blob
		self.ups = ups
		self.size = calcsize(self.ups)
		assert len(self.blob) % self.size == 0, "blob not a multiple of struct size"
		self.pos = 0
		
	def __iter__(self):
		return self
		
	def next(self):
		if self.pos == len(self.blob):
			raise StopIteration
		vec = unpack(self.ups, self.blob[self.pos:self.pos + self.size])
		self.pos += self.size
		return vec

# e3d_vec.erl in /wings-0.98.32a/e3d/

def trinormals(t):
#	out = []
#	for iss in [(0, 1, 2), (1, 2, 0), (2, 0, 1)]:
#		out.append(normal(*(t[i] for i in iss)))
#	print out
	out = normal(*(t[i] for i in (0, 1, 2)))
	return out

def normal(v0, v1, v2):
	# use Numeric etc.
	d10 = v0[0] - v1[0]
	d11 = v0[1] - v1[1]
	d12 = v0[2] - v1[2]
	d20 = v1[0] - v2[0]
	d21 = v1[1] - v2[1]
	d22 = v1[2] - v2[2]
	n0 = d11*d22 - d12*d21
	n1 = d12*d20 - d10*d22
	n2 = d10*d21 - d11*d20
	d = math.sqrt(n0*n0+n1*n1+n2*n2)
	try:
		return ((n0/d) + 0.0, (n1/d) + 0.0, (n2/d) + 0.0)
	except ZeroDivisionError:
		# or 0.0, 1.0, 0.0??
		return (0.0, 0.0, 0.0)

def dotproduct(v1, v2):
	return sum([v1[i] * v2[i] for i in [0,1,2]])

def crossproduct(v1, v2, v3):
	return ((v2[1] * v3[2]) - (v2[2] * v3[1]), 
			(v2[2] * v3[0]) - (v2[0] * v3[2]), 
			(v2[0] * v3[1]) - (v2[1] * v3[0]))

def mag(v):
	return math.sqrt(sum([v[i] * v[i] for i in [0,1,2]]))

def unitise(v):
	ms = sum([v[i] * v[i] for i in [0,1,2]])
	if ms > 0:
		oneovermag = 1.0 / math.sqrt(ms)
		return (oneovermag * v[i] for i in [0,1,2])
	else:
		return (0.0, 0.0, 0.0)

class LWO2ToPSO2(lwo2.LWO2Reader):
	def __init__(self):
		lwo2.LWO2Reader.__init__(self, verbose=True, nodata=False, veryverbose=False)
		
	def save_as_pso(self, fn):
		"""
	in LWO2 there is a list of verts, and a list of polys, which has
	an index into the list of verts per vert in the poly.
	
	There is a list of indexes of polys per surface.
	
	This lets you see which verts are shared by which poly.
	
	In PSO2 there is a list of <vert, normals, ([txu, txv]*)>+ (in the
	VERT chunk), and then a list of indicies of verts of tris in the
	INDX chunk.
	
	There is a VERT and INDX chunk per surface in PSO2, but in LWO2
	there is only one global list
	
	beacause the entries in the VERT chunk in PSO2 have normals and
	txu,txv per vert the verts are 'less' shared than in LWO2 - 
	e.g. in a cube, a corner vert will have a different normal 
	depending on which face it's corresponding triangle is on.
	
	So we need to build a mapping between the poly vert index into
	the lwo2 VERT chunk and the index into the per surface
	<vert, norm, (txu,txv)*> VERT chunk in PSO2
		"""
		# XXX no it isn't...
#		print self.surfaces
		surfs = self.tags
		# 1st arg was surfs
		file = make_ohdr(self.surfaces.keys(), self.textures)
		
		#
		# first pass:
		#
		# split quads
		# calculate normals
		#
		
		# we need to do this on a per surface basis
		# so we can add the poly index back to surftopols
		#
		for s in surfs:
			print 'pass 1:', s
			# firstly look for non triangular polys, and split them
			# we don't create new vertexes.
			for p in self.surftopoly[s]:
				# keep an index for later
				i = p
				p = self.pols[p]
				if len(p) != 3:
					if len(p) == 4:
						# split the quad
						# this one will be our new one
						tmpp = [p[0], p[1], p[2]]
						# and the 2nd one goes on the end of the list
						self.pols.append([p[0], p[2], p[3]])
						# add the index of the pol we just created to the end
						# of the list of pols for this surface.
						self.surftopoly[s].append(len(self.pols) - 1)
						# now we're on our new poly
						self.pols[i] = tmpp
					else:
						# XXX we only split quads atm, 
						# really we shouldn't bother with even that
						# and people creating content should make the
						# meshes trianglular themselves.
						print "non triangle poly: ", len(p), p
						print 'quitting'
						sys.exit(1)
			
		#
		# now go through each triangle
		# and calculate it's normal
		#
		polytonormal = [None for x in range(0, len(self.pols))]
		verttonormals = [[] for x in range(0, len(self.verts))]
		for pi, p in enumerate(self.pols):
			# make a list of verts
			pv = [self.verts[vi] for vi in p]
			# calculate the normal
			normal = trinormals(pv)
			polytonormal[pi] = normal
			for vi in p:
				verttonormals[vi].append(normal)
				
		
		for vni, ns in enumerate(verttonormals):
			norm = (0.0, 0.0, 0.0)
			for n in ns:
				norm = [norm[i] + n[i] for i in [0, 1, 2]]
			verttonormals[vni] = tuple(unitise(norm))
			
		
		#
		# 2nd pass, make PSO bits
		#
		for s in surfs:
			print 'processing', s
			if s not in self.surfaces:
				print "WARNING: missing surface >%s<" % (s)
				continue
			sf = self.surfaces[s]
#			print s, sf, self.surftopoly[s]
#			print sf
			tmp = ''
			indexs = []
			verts = []
	
			# same number of polys as surftopolys, but each index is
			# into the PSO2.INDX chunk that we're generating
			pout = []
			# will be put directly into the VERT chunk
			vout = []
			# if we have uv's 0 < or > 1
			wrappeduv = False
			for poly in self.surftopoly[s]:
				# poly is an index into the LWO2.POLS chunk
				# p is a list of vert indicies
				p = self.pols[poly]

				# pv is a list of vertexes
				pv = [self.verts[vi] for vi in p]

				# verts + normals (and u,v if any) for this poly
				tmpvout = []
				# list of polys -> list of indixes into vout -> PSO2.VERT chunk
				tmppout = []
				
#				print '>', self.txuv.keys(), '<'

				for i, v in enumerate(pv):
#					print poly
					txuv = ()
					for chan in ['colr', 'spec', 'lumi']:
						if chan in sf['tex']:
							map = sf['tex'][chan]['map']
							
							uv = None
							if map in self.txuv:
								if p[i] in self.txuv[map]:
#									print 'txuv', p[i], map, self.txuv[map][p[i]]
									uv = self.txuv[map][p[i]]

							if map in self.vmad:
								if poly in self.vmad[map]:
									if p[i] in self.vmad[map][poly]:
#										if uv != None:
#											print 'overiding VMAP uvs with VMAD uvs'
#											print uv
#											print 'vmad:', map, poly, self.vmad[map][poly]
										uv = self.vmad[map][poly][p[i]]
							
							# if we have one there's no point checking the rest 
							if not wrappeduv:
								for c in uv:
									if c > 1 or c < 0:
										wrappeduv = True
							#
							# Invert the V coord when going lwo2 -> pso
							#
							txuv += (uv[0], 1 - uv[1])
					tmpvout.append((v + verttonormals[p[i]] + (txuv)))

				for v in tmpvout:
					found = False
					for i, vov in enumerate(vout):
						# already in vout, so use it's index
						if v == vov:
							tmppout.append(i)
							found = True
					# else it's not in there, so add it.
					if found != True:
						vout.append(v)
						tmppout.append(len(vout) - 1)
				pout.append(tmppout)

#			print 'dumping vout for',s
#			for q in vout:
#				print q
#			print pout
#			print
#			print 'done'

			# SHDR first
			file += make_shdr(s, sf, len(vout), wrappeduv)
			
			tmp = ''
			for vs in vout:
				tmp += pack('<' + 'f' * len(vs), *vs)

			# list of vertices
			file += make_chunk('VERT', tmp)

			# end PSO2.VERT chunk, begin PSO2.INDX chunk

			# list of polys indexed into the associated VERT chunk
			nverts = len(vout)

			# we may be better off just leaving this as 0
			tmp = pack('<H', nverts)

			# p is list of indicies into PSO2.VERT
			for p in pout:
				tmp += pack('<HHH', *p)

			file += make_chunk('INDX', tmp)
			# PSO2.INDX done.

			print 'done surface:',s
			print

		file = make_chunk('FORM', 'PSO2' + file)
		
		print
		print "starting pso dump"
		
#		import PSO

#		pso = PSO.PSO()
#		pso.load_string(file)
		
		# pso dump done.

		print "Saveing as", fn
		fh = open(fn, 'wb')
		fh.write(file)
		fh.close()

#
# PSO bits, should be merged into PSO.py
#
def make_ohdr(surf, tex):
	ohdr = pack('>III', 1, len(surf), len(tex))
	ks = tex.keys()
	ks.sort()
	for t in ks:
		ohdr += tex[t] + '\x00'
	return make_chunk('OHDR', ohdr)

def make_shdr(name, sf, nverts, wrappeduv):
  shdr = name + "\x00"
					  # r, g, b, a
  shdr += pack('>ffff', sf['r'], sf['g'], sf['b'], sf['tran'])

  def tex(sf, chan, prop):
  	tex = 0
  	tflags = 0
  	if chan in sf['tex']:
  		tex = sf['tex'][chan]['tex'] + 1
  		# 
  		# if this surface has uv's < 0 or > 1 then
  		# use tflags == 0x21 rather than 0x24
  		#
  		# the other, unknown tflags value is 0x1
  		# still working on it.
  		#
  		if wrappeduv:
  			tflags = 0x21
  		else:
  			tflags = 0x24
  	return pack('>fII', sf[prop], tex, tflags)
  
  # first is colour
  shdr += tex(sf, 'colr', 'diff')

  # then specular/gloss
  shdr += tex(sf, 'spec', 'spec')

  # final glow/luminance
  shdr += tex(sf, 'lumi', 'lumi')

  shdr += '' + "\x00"

  numtex = 0
  for chan in ['colr', 'spec', 'lumi']:
  	# there may be other chanels we ignore.
  	if chan in sf['tex']:
  		numtex += 1

  # num vertices, num textures (i.e. number of effects that use textures)
  shdr += pack(">II", nverts, numtex)
  
  return make_chunk('SHDR', shdr)

if __name__ == "__main__":
	try:
		import psyco
		psyco.log()
		psyco.full()
		psyco.profile()
	except ImportError:
		pass
	if len(sys.argv) == 3:
		lwo = LWO2ToPSO2()
		lwo.load(sys.argv[1])
		lwo.save_as_pso(sys.argv[2])
	else:
		print "%s: <file.lwo> <file.pso>" % (sys.argv[0])
