#!/usr/local/bin/python
#
# $Id: lwo2.py,v 1.8 2008/06/11 00:20:08 jasper Exp $
#
# A class to generate .lwo files
#

import sys, os, os.path
import chunk
from struct import unpack, pack, calcsize
from hexdump import hexdump
from IFF import IFF
from saveiff import make_chunk, make_sub_chunk, make_string
import pprint

pp = pprint.PrettyPrinter(indent=1, depth=5)

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

class LWO2Reader(IFF):
	"""class to read a LWO2 and turn it into vairous data structures"""
	def __init__(self, verbose=True, nodata=False, veryverbose=False):
		""" verbose -> print more stuff
			nodata -> don't bother building data structures
			veryverbose -> also dump pols, txuv, etc.
		"""
		self.types = ["LWO2"]
		self.callbacks = {"TAGS": self.tags,
						"PNTS": self.pnts,
						"POLS": self.pols,
						"SURF": self.surf,
						"PTAG": self.ptag,
						"BBOX": self.bbox,
						"VMAD": self.vmad,
						"VMAP": self.vmap,
						"CLIP": self.clip,
						"*": self.dump_chunk
							}
		self.verbose = verbose
		self.nodata = nodata
		self.veryverbose = veryverbose

		self.surfaces = {}
		# surf : [p,p,p]
		self.surftopoly = {}
		self.seen_surfaces = 0
		self.tags = []
		self.indx_to_tag = {}
		self.textures = {}
		self.txuv = {}
		self.vmad = {}
	
	def done(self):
		#assert len(self.tags) == self.seen_surfaces, "Woah! number of surface names does not equal the number of SURF chunks"
		print len(self.tags), self.seen_surfaces, self.tags
	
	def tags(self, type, blob):
		off = 0
		while off < len(blob):
			s = self.get_string(blob[off:])
			if self.verbose:
				print s
			self.indx_to_tag[len(self.tags)] = s
			self.tags.append(s)
			self.surftopoly[s] = []
			off += len(s)
			off += 1
			if off % 2 == 1:
				off += 1
				
	def bbox(self, type, blob):
		if self.verbose:
			print unpack(">ffffff", blob)
			print
	
	def surf(self, type, blob):
		# .lwo surf chunk.
		indent = " "
		self.seen_surfaces += 1
		off = 0
		tag = self.get_string(blob)
		assert tag not in self.surfaces, "surface already seen?"
		self.surfaces[tag] = {
			'r': 1.0,
			'g': 1.0,
			'b': 1.0,
			'diff': 1.0,
			'spec': 1.0,
			'lumi': 0.0,
			'tran': 1.0,
			'tex' : {}
		}
		if self.verbose:
			print "surface: " + tag, ":", self.tags.index(tag)
		bloks = []

		off += len(tag)
		off += 1
		if off % 2 == 1:
			off += 1

		# ???
		source = self.get_string(blob[off:])
		if self.verbose:
			if len(source) > 0:
				print "Source surface: ", source
		
		off += len(source)
		off += 1

		# pad to even boundry
		if off % 2 == 1:
			off += 1

		while off < len(blob):
			# grab the subchunk
			scn, l2 = unpack(">4sH", blob[off:off+6])
			off += 6
			
			if self.verbose:
				print indent, scn, ":",
			# "VTRN", "VRFL",
			if scn in ["DIFF", "TRAN", "SPEC", "LUMI"]:
				(intensity, envelope) = unpack(">fH", blob[off:off + 6])
				if self.verbose:
					print intensity
				
				self.surfaces[tag][scn.lower()] = intensity
				
				if envelope != 0:
					print "warning, non zero envelope in", scn, envelope

			elif scn == "COLR":
				r,g,b = unpack (">fff", blob[off:off + 12])
				if self.verbose:
					print "<", r, g, b, ">"
				self.surfaces[tag]['r'] = r
				self.surfaces[tag]['g'] = g
				self.surfaces[tag]['b'] = b				
			elif scn == "SMAN":
				# SMoothing ANgle
				sman = unpack (">f", blob[off:off + 4])
				if self.verbose:
					print 'sman', sman
				self.surfaces[tag][scn.lower()] = sman
			elif scn == "BLOK":
#				hexdump(blob[off:off + l2], indent + " ")
#				self.r_chunk_dumper(blob[off: off + l2], 2)
				bloks.append(self.subchunkdict(blob[off: off + l2], 2))
			else:
				if self.verbose:
					print
					hexdump(blob[off: off + l2], indent + " ")
			off += l2
		if self.verbose:
			print
		if self.verbose:
			print '  checking bloks for', tag + ':'
		for b in bloks:
			if self.verbose:
				pp.pprint(b)
			if 'PROJ' not in b:
				print 'no PROJ block for %s, ignoring it' % (tag)
				continue
			if b['PROJ'] != 5:
				projs = {0:'Planer',1:'Cylindrical',2:'Spherical',3:'Cubic',4:'Front Projection',5:'UV'}
				print 'Only u,v maps supported, this one (%s:%s) is %s' % (tag, b['IMAP']['children']['CHAN'], projs[b['PROJ']])
			else:
				if self.verbose:
					print  '    ' + b['IMAP']['children']['CHAN'], 'uses texture', self.textures[b['IMAG']],'and uvmap', b['VMAP']
				self.surfaces[tag]['tex'][b['IMAP']['children']['CHAN'].lower()] = {'tex' : b['IMAG'] - 1, 'map': b['VMAP']}
		if self.verbose:
			print

	def subchunkdict(self, blob, depth):
		if self.verbose:
			print '  ' * depth,
		unpackmap = {
			'CHAN': '4s',
			'OPAC': '>HfH',
			'ENAB': '>H',
			'NEGA': '>H',
			'CNTR': '>fffH',
			'SIZE': '>fffH',
			'ROTA': '>fffH',
			'FALL': '>ffff',
			'OREF': None,
			'CSYS': '>H',
			'PROJ': '>H',
			'AXIS': '>H',
			'IMAG': '>H',
			'WRAP': '>HH',
			'WRPW': '>fH',
			'WRPH': '>fH',
			'VMAP': None, # null terminated string
			'AAST': '>Hf',
			'PIXB': '>H',
		}
		# {name:{ data:, children},}
		out = {}
		off = 0
		while off < len(blob):
			scn, l2 = unpack('>4sH', blob[off:off + 6])
			off += 6
			if self.verbose:
				print scn,
			out[scn] = {}
			if scn in ['BLOK', 'IMAP', 'TMAP']:
				if scn == 'IMAP':
					if self.verbose:
						print
					ords = self.get_string(blob[off:])
					ords = [hex(ord(c)) for c in ords]
					ords = ''.join(ords)
					if self.verbose:
						print '  ' * depth, 'ord: ', ords,
					out[scn]['data'] = ords
					off += 2
					l2 -= 2
				if self.verbose:
					print
				out[scn]['children'] = self.subchunkdict(blob[off:off + l2], depth + 1)
				if self.verbose:
					print '  ' * depth,
			else:
				if scn in unpackmap:
					ups = unpackmap[scn]
					if ups == None:
						out[scn] = self.get_string(blob[off:])
					else:
						assert calcsize(ups) == l2, 'wrong un pack string for %s' % (scn)
						out[scn] = unpack(ups, blob[off:off + calcsize(ups)])
						# make life eaiser for us.5~
						if len(out[scn]) == 1:
							out[scn] = out[scn][0]
				else:
					out[scn] = blob[off:off + l2]
			off += l2
		if self.verbose:
			print
		return out

	def r_chunk_dumper(self, blob, depth):
		# Obsolete...
		indent = '  ' * depth
		off = 0
		while off < len(blob):
			scn, l2 = unpack(">4sH", blob[off:off + 6])
			off += 6
			if self.verbose:
				print indent, scn, ":"
			if scn in ["BLOK", "IMAP", "TMAP"]:
#				hexdump(blob[off:off + l2], indent + " ")
				if scn == "IMAP":
					if self.verbose:
						# this is wrong for ord strings.
						print indent, "ord: %04x" % (unpack(">H", blob[off: off + 2]))
					off += 2
					l2 -= 2
				self.r_chunk_dumper(blob[off:off + l2], depth + 1)
			else:
				hexdump(blob[off:off + l2], indent + " ")
			off += l2

	def clip(self, type, blob):
#		hexdump(blob)
		index = unpack(">I", blob[:4])[0]
		if self.verbose:
			print 'index', index
		off = 4
		subtype, len = unpack(">4sH", blob[off:off+6])
		if self.verbose:
			print 'subtype: >' + subtype + '<'
		off += 6
		if subtype == 'STIL':
			texpath = self.get_string(blob[off:])
			texpath = os.path.basename(texpath)
			if index in self.textures:
				assert self.textures[index] == texpath
			self.textures[index] = texpath
			if self.verbose:
				print 'tex %d :: %s' % (index, texpath)
				print
		else:
			print "unknown clip subtype", subtype
			hexdump(blob[off:])

	def ptag(self, type, blob):
		# .lwo2 ptag
		off = 0
		subtype, = unpack("4s", blob[:4])
		if self.verbose:
			print 'subtype: >' + subtype + '<'
		off += 4
		if subtype == "SURF":
			assert (len(blob) - 4) % 4 == 0, "PTAG SURF subchunk wrong length"
			prevtag = None
			prevpoly = -1
			while off < len(blob):
				poly, tag = unpack(">HH", blob[off:off+4])
				tag = self.tags[tag]
				if prevtag == None and self.verbose:
					print 'poly', poly, '-',
				if prevtag != tag and prevtag != None and self.verbose:
					print prevpoly, 'tag', prevtag
					print 'poly', poly, '-',
				prevtag = tag
				prevpoly = poly
				self.surftopoly[tag].append(poly)
				off += 4
			print prevpoly, 'tag', prevtag
		else:
			print 'unknown %s subtype: %s' % (type, subtype)
			hexdump(blob)
		if self.verbose:
			print

	def vmad(self, type, blob):
		# .lwo2 vmad chunk
		#
		# XXX double check - why are vmad and vmap different?
		# and do we need vmad?
		#
		# yes, it's for Discontinuous UVs, mapping over a seam.
		#
		off = 0
		subtype, dimension = unpack(">4sH", blob[:6])
		off += 6
		name = self.get_string(blob[off:])
		off += len(name)
		off += 1
		if off % 2 == 1:
			off += 1
		if self.verbose:
			print "subtype: >" + subtype + "<, dim: ", dimension, "name: ", name

		if name in self.txuv:
			print 'vmad: %s in self.txuv' % (name)
#		else:
#			self.txuv[name] = {}

		if subtype == "TXUV":
			while off < len(blob):
				vert, poly, u, v = unpack(">HHff", blob[off:off+12])
#				if self.veryverbose:
				# name -> poly -> vert -> u,v
				if name not in self.vmad:
					self.vmad[name] = {}
				if poly not in self.vmad[name]:
					self.vmad[name][poly] = {}
				self.vmad[name][poly][vert] = (u,v)
				if self.veryverbose:
					print "vert", vert, "poly", poly, "u,v", u, v
					print self.pols[poly]
#				if poly not in self.txuv[name]:
#					self.txuv[name][poly] = (u,v)
				off += 12
		else:
			print "unknown VMAD subtype",

		if self.verbose:
			print
	
	def vmap(self, type, blob):
		# .lwo2 vmap chunk
		off = 0
		subtype, dimension = unpack(">4sH", blob[:6])
		off += 6
		name = self.get_string(blob[off:])
		off += len(name)
		off += 1
		if off % 2 == 1:
			off += 1
		if self.verbose:
			print "subtype: >" + subtype + "<, dim: ", dimension, "name: ", name

		self.txuv[name] = {}

		if subtype == "TXUV":
			while off < len(blob):
				point, u, v = unpack(">Hff", blob[off:off+10])
				if self.veryverbose:
					print "point", point, "u,v", u, v
				self.txuv[name][point] = (u, v)
				off += 10
		else:
			print "unknown VMAP subtype",
		if self.verbose:
			print

	# lwo verticies blob
	def pnts(self, type, blob):
		assert len(blob) % 12 == 0
		if self.verbose:
			print "%d vertexes (0 - %d)" % (len(blob) / 12, (len(blob) / 12) - 1)
			print
		self.verts = []
		for v in UnpackIter(">fff", blob):
			self.verts.append(v)

	# lwo pols blob
	def pols(self, type, blob):
#		hexdump(blob)
		subtype, = unpack("4s", blob[:4])
		if self.verbose:
			print "subtype >", subtype, "<"
		if subtype != "FACE" and subtype != 'PTCH':
			print "unknown %s subtype %s" % (type, subtype)
			hexdump(blob)
			return
		vert_seen = []
		max_vert = 0
		off = 4
		self.pols = []
		while off < len(blob):
			count, = unpack(">H", blob[off:off+2])
			# top 6 bits are flags for CURV, which we don't support
			# so ignore the flags for the moment.			
			if self.veryverbose:
				print count, "<",
			off += 2
			v = []
			while count > 0:
				vert, = unpack(">H", blob[off:off+2])
				v.append(vert)
				if self.veryverbose:
					print vert,
				if vert not in vert_seen:
					vert_seen.append(vert)
				if vert > max_vert:
					max_vert = vert
				count -= 1
				off += 2

			if self.veryverbose:
				print "> "
			self.pols.append(v)

		if self.verbose:
			print 'max_vert:', max_vert, 'polys:', len(self.pols)
		for i in range(0, max(vert_seen)):
			assert i in vert_seen , "Oooh! unused vert: %d" % (i)
		
		if self.verbose:
			print

class LWO2:
	""""class to make a LWO2 .lwo file"""
	def __init__(self):
		self.surfaces = {}
		self.surface_names = []
		self.pols = "FACE"
		self.points = ""
		self.ptag = "SURF"
		self.txuv = {}
		self.tex_to_clip = {}
		self.texfileext = ".iff"
	
	def set_fileext(self, ext):
		self.texfileext = ext
	
	def add_surface(self, surface_name):
		assert surface_name not in self.surfaces, "A surface with that name already exists."
		self.surfaces[surface_name] = {}
		self.surface_names.append(surface_name)
	
	def add_color_to_surface(self, surface_name, r, g, b):
		assert surface_name in self.surfaces
		
		for c in [r, g, b]:
			assert c <= 1.0
			assert c >= 0.0
		
		self.surfaces[surface_name]["COLR"] = {
			"r" : r,
			"g" : g,
			"b" : b,
		}

	def add_tran_to_surface(self, surface_name, t):
		assert surface_name in self.surfaces
		
		assert t <= 1.0
		assert t >= 0.0
		
		self.surfaces[surface_name]["TRAN"] = t

	def add_flag_to_surface(self, surface_name, data):
		assert surface_name in self.surfaces
		
		assert data <= 65535
		assert data >= 0
		
		self.surfaces[surface_name]["FLAG"] = data

	def add_diff_to_surface(self, surface_name, data):
		assert surface_name in self.surfaces
		
		assert data >= 0.0
		
		self.surfaces[surface_name]["DIFF"] = data

	def add_vrfl_to_surface(self, surface_name, data):
		assert surface_name in self.surfaces
		assert data <= 1.0
		assert data >= 0
		self.surfaces[surface_name]["VRFL"] = data

	def add_spec_to_surface(self, surface_name, data):
		assert surface_name in self.surfaces
		assert data <= 1.0
		assert data >= 0
		self.surfaces[surface_name]["SPEC"] = data
		
	def add_lumi_to_surface(self, surface_name, data):
		assert surface_name in self.surfaces
		assert data <= 1.0
		assert data >= 0
		self.surfaces[surface_name]["LUMI"] = data

	def add_sman_to_surface(self, surface_name, data):
		assert surface_name in self.surfaces
		
		# XXX radians
#		assert data <= 3.6
		assert data >= 0
		
		#
		# XXX for now leave out SMAN.
		#
		
#		self.surfaces[surface_name]["SMAN"] = data
		
	def add_rimg_to_surface(self, surface_name, file):
		self.surfaces[surface_name]["RIMG"] = file

	def add_pol(self, surf_number, verts):
		assert (len(self.pols) - 4) % 8 == 0, "length of self.pols is wrong (?)"
		assert len(verts) == 3, "Triangles only please"
		pol_no = (len(self.pols) - 4) / 8
#		print pol_no
		data = pack(">H", len(verts))
		# XXX ok, looks like we don't need to reverse the poly order
		for v in verts:
			assert v < (len(self.points) / 12)
			data += pack(">H", v)
		
		self.pols += data

#		print "sn:",surf_number
		# XXX PTAG here.
#		print "poly", pol_no, " surf", surf_number
		self.ptag += pack(">HH", pol_no, surf_number)
	
	def add_point(self, x, y, z):
		self.points += pack(">fff", x, y, z)
	
	def create_txuv(self, name, surface_name, tex, chan, texno, numtexes):
		assert name not in self.txuv
		assert surface_name in self.surfaces, "" + surface_name
		
		if tex not in self.tex_to_clip:
			self.tex_to_clip[tex] = len(self.tex_to_clip) + 1
		
		self.txuv[name] = ""
		
		data = ""
#		imap = self.make_ord(numtexes, texno)
		imap = self.make_ord(1, 0)
		imap += make_sub_chunk("CHAN", chan)
		imap += make_sub_chunk("OPAC", pack(">HfH", 0, 1.0, 0))
		imap += make_sub_chunk("ENAB", pack(">H", 1))
		imap += make_sub_chunk("NEGA", pack(">H", 0))
		
		data += make_sub_chunk("IMAP", imap)

		tmap = make_sub_chunk("CNTR", pack(">fffH", 0, 0, 0, 0))
		tmap += make_sub_chunk("SIZE", pack(">fffH", 1, 1, 1, 0))
		tmap += make_sub_chunk("ROTA", pack(">fffH", 0, 0, 0, 0))
		tmap += make_sub_chunk("FALL", pack(">HfffH", 0, 0, 0, 0, 0))
		tmap += make_sub_chunk("OREF", make_string("(none)"))
		tmap += make_sub_chunk("CSYS", pack(">H", 0))
		
		data += make_sub_chunk("TMAP", tmap)

		data += make_sub_chunk("PROJ", pack(">H", 5))
		data += make_sub_chunk("AXIS", pack(">H", 2))
		data += make_sub_chunk("IMAG", pack(">H", self.tex_to_clip[tex]))
		data += make_sub_chunk("WRAP", pack(">HH", 1, 1))
		data += make_sub_chunk("WRPW", pack(">fH", 1, 0))
		data += make_sub_chunk("WRPH", pack(">fH", 1, 0))
		data += make_sub_chunk("VMAP", make_string(name))
		data += make_sub_chunk("AAST", pack(">Hf", 1, 1.0))
		data += make_sub_chunk("PIXB", pack(">H", 1))
		
		
		if "BLOK" not in self.surfaces[surface_name]:
			self.surfaces[surface_name]["BLOK"] = []
		
		self.surfaces[surface_name]["BLOK"].append(data)
		
	def add_to_txuv(self, name, vert, pol, uvs):
		assert name in self.txuv
#		print name, vert, pol
		# first try, swap them around.
		u = uvs[0]
		v = uvs[1]
		bad = 0
		for t in [u, v]:
			if t < 0.0 or t > 1.0:
				bad = 1
		if bad:
			print "bad (?) u,v", u, v
#		if v > 1.0:
#			c = (v / 1.0) - v % 1.0
#			v = v % 1.0
#			v = 1 - v
#			v += c
#		else:
#			v = 1 - v
		#
		# XXX
		#
		# WARNING : this assumes the v coords are from a .PSO
		# 
		# if your u,v coords come from a different source
		# then this code may be wrong.
		#
		# XXX
		#
		v = 1 - v


		#
		# XXX we used to shove this into the VMAD chunk
		#
		# but thats ment for discontinuos u,v which we 
		# don't have (well actually we might), XXX be better about this
		#
		#
		# for VMAD
		self.txuv[name] += pack(">HHff", vert, pol, u, v)
		# for VMAP
#		self.txuv[name] += pack(">Hff", vert, u, v)
		

	def write(self, filename):
		blob = ""
		
		data = ""
		for s in self.surface_names:
			data += make_string(s)
		blob += make_chunk("TAGS", data)
		
		
		data = ""
		# number, flags, pivot
		data = pack(">HHfff", 0, 0, 0.0, 0.0, 0.0)
		data += make_string(filename)
		blob += make_chunk("LAYR", data)
		
		
		assert len(self.points) > 0, "some .PSO files (Notably 2_Gantry_B_D.PSO) only have an OHDR chunk and no SHDR/VERT/INDX etc, which makes them effectivley 'empty', triggering this assertion."
		assert len(self.points) > 12 * 3
		blob += make_chunk("PNTS", self.points)
		
		assert len(self.pols) > 10
		blob += make_chunk("POLS", self.pols)
		
		assert (len(self.ptag) - 4) / 4 == (len(self.pols) - 4) / 8
		blob += make_chunk("PTAG", self.ptag)
		
		names = self.txuv.keys()
		names.sort()
		for name in names:
			if len(self.txuv[name]) > 0:
				data = "TXUV"
				data += pack(">H", 2) # Dimension
				data += make_string(name)
				data += self.txuv[name]
				# or VMAP
				blob += make_chunk("VMAD", data)
			else:
				print "Warning, uvmap ", name, "has no uv's!"
		
		for t in self.tex_to_clip:
			clip = ""
			ot = t
			if t.endswith(".LBM"):
				ot = t.rstrip(".LBM")
				ot += self.texfileext    # XXX check for existing textures, and/or add a cli switch to choose.
			if t.endswith('.lbm'):
				ot = t.rstrip('.lbm')
				ot += self.texfileext
			clip += pack(">I", self.tex_to_clip[t])
			clip += make_sub_chunk("STIL", make_string(ot))
			blob += make_chunk("CLIP", clip)
		
		
		for s in self.surface_names:
			data = make_string(s)
			data += "\x00\x00" # XXX no source surface.
			for sc in self.surfaces[s]:
				bits = self.surfaces[s][sc]
				if sc == "COLR":
					data += make_sub_chunk(sc, pack(">fffH", bits["r"],
															bits["g"],
															bits["b"],
															0))
#				elif sc == "FLAG":
#					data += make_sub_chunk(sc, pack(">H", bits))
				elif sc == "DIFF":
					data += make_sub_chunk(sc, pack(">fH", bits, 0))
				elif sc == "SMAN":
					data += make_sub_chunk(sc, pack(">f", bits))
				elif sc == "TRAN":
					data += make_sub_chunk("TRAN", pack(">fH", bits, 0))
#				elif sc == "REFL":
#					data += make_sub_chunk("VRFL", pack(">fH", bits, 0))
				elif sc == "LUMI":
					data += make_sub_chunk("LUMI", pack(">fH", bits, 0))
				elif sc == "SPEC":
					data += make_sub_chunk(sc, pack(">fH", bits, 0))
				elif sc == "RIMG":
					pass # XXX
#					data += make_sub_chunk("RIMG", make_string(self.surfaces[s][sc]))
#					data += make_sub_chunk("RFLT", pack(">H", 2))
				elif sc == "BLOK":
					pass
				else:
					print "*** unknown sub chunk: ", sc
				
			if "BLOK" in self.surfaces[s]:
				for b in self.surfaces[s]["BLOK"]:
					data += make_sub_chunk("BLOK", b)
			
			
			blob += make_chunk("SURF", data)

		header = pack(">4sI4s", "FORM", len(blob) + 4, "LWO2")
#		hexdump(header + blob)
		
		ofh = open(filename, "wb")
		ofh.write(header + blob)
		ofh.close()
	
	def make_ord(self, nbloks, index):
		ord = ""
		i = 8
		d = 16
		while i < 128: 
			if i >= nbloks: break
			d /= 2
			i *= 2
		
		ord += "%c" % (128 + index * d)
		ord += "\x00";
		return ord


if __name__ == "__main__":
	lwo = LWO2()
	lwo.add_surface("fish <quack=moo>")
	lwo.add_point(1.0, 0.5, 0.5)
	lwo.add_point(1.0, 0.5, 0.5)
	lwo.add_point(1.0, 0.5, 0.5)
	lwo.add_point(1.0, 0.5, 0.5)
	lwo.add_point(1.0, 0.5, 0.5)
	lwo.add_point(1.0, 0.5, 0.5)
	lwo.add_point(1.0, 0.5, 0.5)
	lwo.add_point(1.0, 0.5, 0.5)
	lwo.add_point(1.0, 0.5, 0.5)
	lwo.add_point(1.0, 0.5, 0.23)
	lwo.add_pol(0, [0, 1, 2])
	lwo.add_pol(0, [3, 4, 5])
	lwo.add_surface("cat")
	lwo.add_pol(1, [6, 7, 2])
	lwo.add_pol(1, [8, 9, 5])
	lwo.add_color_to_surface("cat", 0.5, 0.5, 1.0)
	
	lwo.write("fish.lwo")
