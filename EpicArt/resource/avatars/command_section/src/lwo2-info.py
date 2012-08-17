#!/usr/local/bin/python
#
# $Id: lwo2-info.py,v 1.2 2006/04/26 18:41:55 meep-cvs Exp $
#
# A class to load LWO2 format IFF files.
#

import chunk
import sys, os
from hexdump import hexdump
from struct import unpack
from IFF import IFF

class LWO2_info(IFF):
	def __init__(self):
		self.types = ["LWO2"]
		self.callbacks = {"TAGS": self.tags,
						"PNTS": self.pnts,
						"POLS": self.pols,
						"SURF": self.surf,
						"PTAG": self.ptag,
						"BBOX": self.bbox,
						"VMAD": self.vmad,
						"VMAP": self.vmap,
						"*": self.dump_chunk
							}
		self.verbose = 1
		self.surfaces = 0
		self.seen_surfaces = 0
		self.tags = []
		self.indx_to_tag = {}
	
	def done(self):
		assert len(self.tags) == self.seen_surfaces, "Woah! number of surface names does not equal the number of SURF chunks"
	
	def tags(self, type, blob):
		off = 0
		while off < len(blob):
			s = self.get_string(blob[off:])
			print s
			self.indx_to_tag[len(self.tags)] = s
			self.tags.append(s)
			off += len(s)
			off += 1
			if off % 2 == 1:
				off += 1
				
	def bbox(self, type, blob):
		print unpack(">ffffff", blob)
		print

	def srfs(self, type, blob):
#		hexdump(blob)
		off = 0
		surfaces = 0
		while off < len(blob):
			s = self.get_string(blob[off:])
			print s
			off += len(s)
			off += 1
			if off % 2 == 1:
				off += 1
			surfaces += 1
		self.surfaces = surfaces
		print "%d surfaces" % (surfaces)
		print
	
	def surf(self, type, blob):
		# .lwo surf chunk.
#		hexdump(blob)
		indent = " "
		self.seen_surfaces += 1
		off = 0
		tag = self.get_string(blob)
		print "surface: " + tag, ":", self.tags.index(tag)
		off += len(tag)
		off += 1
		if off % 2 == 1:
			off += 1
		source = self.get_string(blob[off:])
		if len(source) > 0:
			print "Source surface: ", source
		off += len(source)
		off += 1
		if off % 2 == 1:
			off += 1
		while off < len(blob):
			scn, l2 = unpack(">4sH", blob[off:off+6])
			off += 6
			print indent, scn, ":",
			if scn in ["SMAN", "DIFF", "VTRN", "VRFL", "TRAN", "SPEC"]:
				print unpack(">f", blob[off:off + 4])[0]
				if l2 != 4:
					hexdump(blob[off:off + l2], indent + " ")
			elif scn == "COLR":
				r,g,b = unpack (">fff", blob[off:off + 12])
				print "<", r, g, b, ">"
			elif scn == "BLOK":
				print
				self.r_chunk_dumper(blob[off: off + l2], 2)
			else:
				print
				hexdump(blob[off: off + l2], indent + " ")
			off += l2
		print
	
	def r_chunk_dumper(self, blob, depth):
		indent = "  " * depth
		off = 0
		while off < len(blob):
			scn, l2 = unpack(">4sH", blob[off:off + 6])
			off += 6
			print indent, scn, ":"
			if scn in ["BLOK", "IMAP", "TMAP"]:
#				hexdump(blob[off:off + l2], indent + " ")
				if scn == "IMAP":
					print indent, "ord: %04x" % (unpack(">H", blob[off: off + 2]))
					off += 2
					l2 -= 2
				self.r_chunk_dumper(blob[off:off + l2], depth + 1)
			else:
				hexdump(blob[off:off + l2], indent + " ")
			off += l2
	
	def ptag(self, type, blob):
		# .lwo2 ptag
#		hexdump(blob)
		off = 0
		subtype, = unpack("4s", blob[:4])
		print "subtype: >" + subtype + "<"
		off += 4
		if subtype == "SURF":
			assert (len(blob) - 4) % 4 == 0, "PTAG SURF subchunk wrong length"
			while off < len(blob):
				poly, tag = unpack(">HH", blob[off:off+4])
#				print "poly", poly, "tag", self.tags[tag]
				off += 4
		else:
			print "unknown PTAG subtype",
		
		print
	
	def vmad(self, type, blob):
		# .lwo2 vmad chunk
#		hexdump(blob)
		off = 0
		subtype, dimension = unpack(">4sH", blob[:6])
		off += 6
		name = self.get_string(blob[off:])
		off += len(name)
		off += 1
		if off % 2 == 1:
			off += 1
		print "subtype: >" + subtype + "<, dim: ", dimension, "name: ", name
		if subtype == "TXUV":
			while off < len(blob):
				vert, poly, u, v = unpack(">HHff", blob[off:off+12])
#				print "vert", vert, "poly", poly, "u,v", u, v
				off += 12
		else:
			print "unknown VMAD subtype",
		
		print
	
	def vmap(self, type, blob):
		# .lwo2 vmap chunk
#		hexdump(blob)
		off = 0
		subtype, dimension = unpack(">4sH", blob[:6])
		off += 6
		name = self.get_string(blob[off:])
		off += len(name)
		off += 1
		if off % 2 == 1:
			off += 1
		print "subtype: >" + subtype + "<, dim: ", dimension, "name: ", name
		if subtype == "TXUV":
			while off < len(blob):
				point, u, v = unpack(">Hff", blob[off:off+10])
#				print "point", point, "u,v", u, v
				off += 10
		else:
			print "unknown VMAP subtype",
		
		print

	# lwo verticies blob
	def pnts(self, type, blob):
#		hexdump(blob)
		print len(blob)
		assert len(blob) % 12 == 0
		print "%d vertexes (0 - %d)" % (len(blob) / 12, (len(blob) / 12) - 1)
		print

	# lwo pols blob
	def pols(self, type, blob):
#		hexdump(blob)
		subtype, = unpack("4s", blob[:4])
		print "subtype >", subtype, "<"
		if subtype != "FACE":
			print "unknown subtype %s" % (subtype)
			return
		vert_seen = []
		max_vert = 0
		off = 4
		while off < len(blob):
			count, = unpack(">H", blob[off:off+2])
#			print count, "<",
			off += 2
			while count > 0:
				vert, = unpack(">H", blob[off:off+2])
#				print vert,
				if vert not in vert_seen:
					vert_seen.append(vert)
				if vert > max_vert:
					max_vert = vert
				count -= 1
				off += 2
#			print "> "

		print "max_vert:", max_vert
		for i in range(0, max(vert_seen)):
			assert i in vert_seen , "Oooh! unused vert: %d" % (i)

if __name__ == "__main__":
	if (len(sys.argv) > 1):
		for f in sys.argv[1:]:
			lwo = LWO2_info()
			lwo.load(f)
	else:
		print "%s: <file.lwo>" % (sys.argv[0])
