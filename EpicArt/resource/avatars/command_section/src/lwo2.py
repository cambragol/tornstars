#!/usr/local/bin/python
#
# $Id: lwo2.py,v 1.2 2006/04/26 18:41:55 meep-cvs Exp $
#
# A class to generate .lwo files
#

import sys
from hexdump import hexdump
from struct import unpack, pack
from saveiff import make_chunk, make_sub_chunk, make_string

class LWO2:
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
		v *= -1
		self.txuv[name] += pack(">HHff", vert, pol, u, v)
		
	
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
