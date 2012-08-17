#!/usr/local/bin/python
#
# A class to load IFF format files.
#
# $Id: IFF.py,v 1.2 2006/04/26 18:41:55 meep-cvs Exp $
#

import chunk
import sys, os
from hexdump import hexdump
from struct import unpack
from saveiff import *

class IFF:
	def __init__(self):
		self.types = []
		self.callbacks = {"*": self.dump_chunk}
		self.verbose = 1
		
	def load(self, filename):
		self.fh = open(filename, "rb")
		self.filename = filename
		
		form, total_size, type = unpack(">4sl4s", self.fh.read(12))
		assert form == "FORM", "Not an IFF file."
		self.type = type
		
		s = os.stat(filename)
		assert total_size + 8 == s.st_size, "Size wrong in FROM header"
		
		if len(self.types) > 0 and type not in self.types:
			print "Not a recognised IFF subtype: >%s< in %s." % (type, filename)
			sys.exit(-1)
		
		self.start()
		
		while 1:
			try:
				chunker = chunk.Chunk(self.fh)
			except EOFError:
				break
			name = chunker.getname()
			size = chunker.getsize()
			
			blob = chunker.read()
			
			if self.verbose:
				print "type: >%s< length: %d %d" % (name, size, len(blob))
			
			if name in self.callbacks:
				self.callbacks[name](name, blob)
			elif "*" in self.callbacks:	# generic handler
				self.callbacks["*"](name, blob)
			else:
				raise RuntimeError, "Chunk type %s not known in %s" % (name, self.filename)
		
		self.fh.close()
		self.done()
	
	def dump_chunk(self, type, blob):
		if self.verbose:
			print ">%s<" % (type)
			hexdump(blob)
	
	
	#
	# convenience function for chunks that are just lists of strings.
	#
	def dump_strings(self, type, blob):
		hexdump(blob)
		off = 0
		while off < len(blob):
			s = self.get_string(blob[off:])
			print s
			off += len(s)
			off += 1
			if off % 2 == 1:
				off += 1
		print

# called after the type of the file is found,
	# but before grabbing the chunks
	def start(self):
		if self.verbose:
			print "found a >%s<" % (self.type)
	
	def done(self):
		print "done!"
	
	def get_string(self, blob):
		str = ""
		for f in blob:
			if f != '\x00':
				str = str + f
			else:
				break
		return str
	

if __name__ == "__main__":
	if (len(sys.argv) > 1):
		for f in sys.argv[1:]:
			iff = IFF()
			iff.load(f)
	else:
		print "%s: <IFFfile>" % (sys.argv[0])
