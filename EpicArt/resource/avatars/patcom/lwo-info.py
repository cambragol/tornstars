#!/usr/local/bin/python
#
# $Id: lwo-info.py,v 1.2 2006/04/26 18:41:55 meep-cvs Exp $
#
# A class to load LWO format IFF files.
#

import chunk
import sys, os
from hexdump import hexdump
from struct import unpack
from IFF import IFF

class LWO_info(IFF):
	def __init__(self):
		self.types = ["LWOB"]
		self.callbacks = {"SURF": self.surf, "PNTS": self.pnts, "POLS": self.pols, "SRFS": self.srfs}
		self.verbose = 1
		self.surfaces = 0
		self.seen_surfaces = 0
	
	def done(self):
		assert self.surfaces == self.seen_surfaces, "Woah! number of surface names does not equal the number of SURF chunks"
	
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
		self.seen_surfaces += 1
		off = 0
		print ">" + self.get_string(blob) + "<"
		off += len(self.get_string(blob))
		off += 1
		if off % 2 == 1:
			off += 1
		while off < len(blob):
			scn, l2 = unpack(">4sH", blob[off:off+6])
			off += 6
			print "    ", scn, ":",
			if scn in ["SMAN", "VDIF", "VTRN", "VRFL"]:
				print unpack(">f", blob[off:off + l2])[0]
				print
			elif scn in ["TRAN", "DIFF", "REFL"]:
				print unpack(">H", blob[off:off + l2])[0]
				print
			else:
				print
				hexdump(blob[off: off + l2], "     ")
			off += l2

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
		surf_seen = []
		vert_seen = []
		max_vert = 0
		off = 0
		while off < len(blob):
			count, = unpack(">H", blob[off:off+2])
			off += 2
			while count > -1:
				vert, = unpack(">H", blob[off:off+2])
				if vert not in vert_seen:
					vert_seen.append(vert)
				if vert > max_vert:
					max_vert = vert
				count -= 1
				off += 2
			surfno, = unpack(">H", blob[off-2:off])
			if surfno not in surf_seen:
				surf_seen.append(surfno)
		print "max_vert:", max_vert
#		print surf_seen, vert_seen
		for i in range(0, max(vert_seen)):
			if i not in vert_seen:
				print "Oooh! unused vert: %d" % (i)
#			assert i in vert_seen , "Oooh! unused vert: %d" % (i)

if __name__ == "__main__":
	if (len(sys.argv) > 1):
		for f in sys.argv[1:]:
			lwo = LWO_info()
			lwo.load(f)
	else:
		print "%s: <file.lwo>" % (sys.argv[0])
