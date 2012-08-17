#!/usr/local/bin/python
#
# $Id: lwo.py,v 1.2 2006/04/26 18:41:55 meep-cvs Exp $
#
# A class generate .lwo files
#

import sys
from hexdump import hexdump
from struct import unpack, pack
from saveiff import make_chunk, make_sub_chunk, make_string

class LWO:
	def __init__(self):
		self.surfaces = {}
		self.surface_names = []
		self.pols = ""
		self.points = ""
	
	def add_surface(self, surface_name):
		assert surface_name not in self.surfaces, "A surface with that name already exists."
		self.surfaces[surface_name] = {}
		self.surface_names.append(surface_name)
	
	def add_color_to_surface_f(self, surface_name, r, g, b):
		assert surface_name in self.surfaces
		
		for c in [r, g, b]:
			assert c <= 1.0
			assert c >= 0.0
		
		self.add_color_to_surface_i(surface_name, int(255 * r), int(255 * g), int(255 * b))
	
	def add_color_to_surface_i(self, surface_name, r, g, b):
		assert surface_name in self.surfaces
		
		for c in [r, g, b]:
			assert c <= 255
			assert c >= 0
		
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
		
		assert data <= 65536
		assert data >= 0
		
		self.surfaces[surface_name]["DIFF"] = data

	def add_vdif_to_surface(self, surface_name, data):
		assert surface_name in self.surfaces
		
#		assert data <= 1.0 # XXX
		assert data >= 0
		
		self.surfaces[surface_name]["VDIF"] = data

	def add_vrfl_to_surface(self, surface_name, data):
		assert surface_name in self.surfaces
		assert data <= 1.0
		assert data >= 0
		self.surfaces[surface_name]["VRFL"] = data

	def add_rimg_to_surface(self, surface_name, file):
		self.surfaces[surface_name]["RIMG"] = file

	def add_vspc_to_surface(self, surface_name, data):
		assert surface_name in self.surfaces
#		assert data <= 1.0
		assert data >= 0
		self.surfaces[surface_name]["VSPC"] = data

	def add_sman_to_surface(self, surface_name, data):
		assert surface_name in self.surfaces
		
		# XXX
		# GUESS on max value here.
		# this is mapped to degrees somehow, so guess 3.6 == 360?!?!?
		assert data <= 3.6
		assert data >= 0
		
		self.surfaces[surface_name]["SMAN"] = data

	def add_pol(self, surf_number, pols):
		data = pack(">H", len(pols))
		# XXX ok, looks like we don't need to reverse the poly order
		for v in pols:
			assert v < (len(self.points) / 12)
			data += pack(">H", v)
		
#		print "sn:",surf_number
		data += pack(">H", surf_number + 1)
		self.pols += data
	
	def add_point(self, x, y, z):
		self.points += pack(">fff", x, y, z)
	
	def write(self, filename):
		
		data = ""
		for s in self.surface_names:
			#fs = "%dsc" % (len(s))
			#data += pack(fs, s, "\x00")
			data += make_string(s)
		srfs = make_chunk("SRFS", data)
#		srfs = make_chunk("SRFS", "Default\x00")
		blob = ""
		
		blob += srfs
		
		assert len(self.points) > 0, "some .PSO files (Notably 2_Gantry_B_D.PSO) only have an OHDR chunk and no SHDR/VERT/INDX etc, which makes them effectivley 'empty', triggering this assertion."
		assert len(self.points) > 12 * 3
		blob += make_chunk("PNTS", self.points)
		
		assert len(self.pols) > 10
		blob += make_chunk("POLS", self.pols)
		
		for s in self.surface_names:
			# XXX are we REALLY REALLY sure we need to pad this string?
			data = make_string(s)
			for sc in self.surfaces[s]:
				if sc == "COLR":
					data += make_sub_chunk(sc, pack("BBBB", self.surfaces[s][sc]["r"],
															self.surfaces[s][sc]["g"],
															self.surfaces[s][sc]["b"],
															0))
				elif sc == "FLAG":
					data += make_sub_chunk(sc, pack(">H", self.surfaces[s][sc]))
				elif sc == "DIFF":
					data += make_sub_chunk(sc, pack(">H", self.surfaces[s][sc]))
				elif sc == "VDIF":
					data += make_sub_chunk(sc, pack(">f", self.surfaces[s][sc]))
				elif sc == "SMAN":
					data += make_sub_chunk(sc, pack(">f", self.surfaces[s][sc]))
				elif sc == "TRAN":
					data += make_sub_chunk("VTRN", pack(">f", self.surfaces[s][sc]))
					data += make_sub_chunk("TRAN", pack(">H", int(256 * self.surfaces[s][sc])))
				elif sc == "VRFL":
					data += make_sub_chunk("VRFL", pack(">f", self.surfaces[s][sc]))
				elif sc == "VSPC":
					data += make_sub_chunk("VSPC", pack(">f", self.surfaces[s][sc]))
				elif sc == "RIMG":
					data += make_sub_chunk("RIMG", make_string(self.surfaces[s][sc]))
					data += make_sub_chunk("RFLT", pack(">H", 2))
				else:
					print "*** unknown sub chunk: ", sc
			blob += make_chunk("SURF", data)

		header = pack(">4sI4s", "FORM", len(blob) + 4, "LWOB")
#		hexdump(header + blob)
		
		ofh = open(filename, "wb")
		ofh.write(header + blob)
		ofh.close()
		


if __name__ == "__main__":
	lwo = LWO()
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
	lwo.add_color_to_surface_f("cat", 0.5, 0.5, 1.0, 0.0)
	
	lwo.write("fish.lwo")
