#!/usr/local/bin/python
#
# A class to load IFF format files.
#
# $Id: IFF.py,v 1.5 2007/12/05 20:50:24 jasper Exp $
#

import chunk
import sys, os
from hexdump import hexdump
from struct import unpack
from saveiff import *
import StringIO

class IFF:
	def __init__(self):
		"""
			In your own __init__
			self.types should be an array of strings of the IFF files types
			that you support (i.e. the bit after the FORM - LWOB, ILBM etc).
			
			self.callbacks is a dict of chunk names (the 4 character id things),
			and functions to call with that chunk, you can use '*' as a chunk
			name for a catch all function.
			
			set self.verbose to 1 if you want more output.
			
			you can override the start and done methods with ones that will
			be called after the file id has bee retreived and before parseing
			has started, and one thats called after parseing has ended.
		"""
		self.types = []
		self.callbacks = {"*": self.dump_chunk}
		self.verbose = 1
		
	def load(self, filename):
		"""
			load from a file
		"""
		self.fh = open(filename, "rb")
		self.filename = filename
		self._parse()

	def load_string(self, data):
		"""
			load from a string
		"""
		self.filename = "__fromstring__"
		self.fh = StringIO.StringIO(data)
		self._parse()
	
	def _parse(self):
		form, total_size, type = unpack(">4sl4s", self.fh.read(12))
		assert form == "FORM", "Not an IFF file."
		self.type = type
		
		if not self.filename.startswith('__'):
			s = os.stat(self.filename)
			assert total_size + 8 == s.st_size, "Size wrong in FROM header for %s, maybe RIFF/IFF endianess? - %d vs. on disk: %d" % (self.filename, total_size, s.st_size)
		
		if len(self.types) > 0 and type not in self.types:
			print "Not a recognised IFF subtype: >%s< in %s." % (type, self.filename)
			# XXX should be an exception really.
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
				print "type: >%s< length: %d" % (name, size)
			
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

	def print_type(self, type, blob):
		print ">%s<" % (type)
	
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
		return blob[:blob.find('\x00')]

if __name__ == "__main__":
	if (len(sys.argv) > 1):
		for f in sys.argv[1:]:
			iff = IFF()
			iff.load(f)
	else:
		print "%s: <IFFfile>" % (sys.argv[0])
