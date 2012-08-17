#!/usr/local/bin/python
#
# $Id: psotextool.py,v 1.2 2006/04/26 18:41:55 meep-cvs Exp $
#
# Take a pso and change the names of textures referenced in it. 
#
#

import sys
from struct import unpack, pack
import stat
from os import listdir, getcwd, stat
import getopt
from IFF import IFF

from saveiff import *
from hexdump import hexdump

class PSOtex(IFF):
	def __init__(self, filename):
		self.types = ["PSO ", "PSO2"]
		self.verbose = 1
		self.callbacks = {"OHDR": self.ohdr, "SHDR": self.shdr, "VERT": self.vert, "INDX": self.indx}
		self.size_total = 0
		self.filename = filename
		self.load(filename)
		
		s = stat(filename)
		self.fsize = s.st_size
		
	def ohdr(self, type, blob):
		size = len(blob)
		if size % 2 == 1:
			size += 9
		else:
			size += 8
		self.ohdrsize = size
		bit = blob[0:12]
		version, surfaces, textures = unpack(">III", bit)
		assert version == 1
		print "ver: %d, surfs: %d, textures: %d\n" % (version, surfaces, textures)
		self.surfaces = surfaces
		off = 12
		i = 0;
		self.textures = []
		while 1:
			tex = self.get_string(blob[off:])
			off += len(tex) + 1
			if len(tex) == 0:
				tex = "(null)"
#					print "%%%", tex, "%%%"
			self.textures.append(tex)
			i += 1
			if off >= len(blob):
				break
		assert i == textures, "*** PANIC: expected %d textures, got %d" % (textures, i)

	def shdr(self, type, blob):
		size = len(blob)
		if size % 2 == 1:
			size += 9
		else:
			size += 8
		self.size_total += size

	def vert(self, type, blob):
		size = len(blob)
		if size % 2 == 1:
			size += 9
		else:
			size += 8
		self.size_total += size

	def indx(self, type, blob):
		size = len(blob)
		if size % 2 == 1:
			size += 9
		else:
			size += 8
		self.size_total += size


	def done():
		print self.size_total + self.ohdrsize + 12, self.fsize
		assert self.size_total + self.ohdrsize + 12 == self.fsize, "file and content sizes don't match up for %s" % (self.filename)

	def write_dottex(self, tfn):
		# don't overwrite existing files.
		if exists(tfn):
			return
		tfn = open(tfn, "w")
		for t in self.textures:
			tfn.write("%s:%s\n" % (t, t))
		tfn.close()
	
	def load_dottex(self, fn = None):
		if fn == None:
			fn = self.filename + ".tex"
		assert exists(fn), "unable to load .tex file %s" % (fn)
		
		fh = open(fn)
		i = 0
		for line in fh:
			old, new = line.split(':')
			new = new.rstrip()
			assert old == self.textures[i], "texture %s -> %s does not match existing texture %s" % (old, new, textures[i])
			self.textures[i] = new
			i += 1
	
	def ohdr_size(self):
		size = 0
		for t in self.textures:
			# .pso does not pad strings to even 16 bit boundrys
			# chunks do get padded tho.
			if t == "(null)":
				size += 1
			else:
				size += len(t) + 1
		# ver, ntex, nsurf
		return size + (4 * 3)
		
	def make_ohdr(self):
		blob = pack(">III", 1, self.surfaces, len(self.textures))
		for t in self.textures:
			if t == "(null)":
				blob += pack("c", "\x00")
			else:
				fs = "%dsc" % (len(t))
				blob += pack(fs, t, "\x00")
		return make_chunk("OHDR", blob)
	
	def write_pso(self, fn):
		print "writting new .pso to", fn
		
		ofh = open(fn, "wb")
		ohdr = self.make_ohdr()
		
		form = pack(">4sI4s", "FORM", self.size_total + len(ohdr) + 4, self.type)
		
		ifh = open(self.filename, "rb")
		# seek past FORM <size> TYPE
		ifh.seek(12 + self.ohdrsize)
		# slurp the rest of the file
		rest = ifh.read(self.fsize - 12 + self.ohdrsize)
		ifh.close()
		# write the new FORM + OHDR + the rest
		ofh.write(form + ohdr + rest)
		ofh.close()
		

def create_dottex(filename):
	pso = PSOtex(filename)
	print filename
	for t in pso.textures:
		print t
	pso.write_dottex(filename + ".tex")
	print "wrote",filename + ".tex"

def exists(fn):
	try:
		s = stat(fn)
	except OSError:
		return 0
	else:
		return 1

if __name__ == "__main__":
	files = []
	if (len(sys.argv) > 1):
		for file in sys.argv[1:]:
			files.append(file)
	else:
		print "usage: %s <file.pso>\n" % (sys.argv[0])
		print "if no .tex file exists, one will be created, if one does then a file_new.pso will be created"
		sys.exit(-1)

	for f in files:
		if not exists(f + ".tex"):
			create_dottex(f)
		else:
			pso = PSOtex(f)
			pso.load_dottex()
			f = f.split('.')[0]
			f = f + "_new.pso"
			pso.write_pso(f)
