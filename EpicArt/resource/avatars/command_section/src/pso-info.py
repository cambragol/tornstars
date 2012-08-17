#!/usr/local/bin/python
#
# $Id: pso-info.py,v 1.2 2006/04/26 18:41:55 meep-cvs Exp $
#
# Print out info about a .pso
#

import chunk
import sys, os
from hexdump import hexdump, tobin
from struct import unpack
from PSO import PSO
import jgw_utils
import getopt

class PSOinfo(PSO):
	def __init__(self):
		PSO.__init__(self)
		self.verbose = 0

	def done(self):
		PSO.done(self)

args = {
"--all"				: "print everything.",
"--surface"			: "print surface names.",
"--textures"		: "list the filenames of the textures used by the .lwo.",
"--reflection"		: "print the reflection maps used by each surface (if any).",
"--mesh-summary"	: "print how many triangles each surface has, and a total triangle count.",
"--tflags"			: "print the texture flags for each surface (if any).",
"--channels"		: "if any channels are mentioned in the surface names, print them.",
"--filename"		: "print name of the file being parsed before each line of info (useful if you've looking at more than one file).",
"--nl"				: "print a newline after each surface.",
"--hash"			: "If the surface name has a # in it, print out whatever is after the #.",
"--fish"			: "print the texture count and textypes",
"--baduv"			: "print the filename if it has any uv coords that are < 0 or > 1",
"--baduvverbose"	: "print lots of stuff about bad uv's"
}

if __name__ == "__main__":
	flags = map(jgw_utils.finder, args.keys())
	
	opts = {}
	
	if (len(sys.argv) > 1):
		try:
			flags, leftovers = getopt.getopt(sys.argv[1:], '', flags)
		except getopt.GetoptError:
			jgw_utils.usage(args)
			sys.exit(-1)

		if len(leftovers) < 1:
			print "you need to specify the file you want info about"
			jgw_utils.usage(args)
			sys.exit(-1)
		
		for o, a in flags:
			opts[o.lstrip('-')] = a
		
		if "all" in opts:
			for o in args.keys():
				o = o.lstrip('-')
				if o not in opts:
					opts[o] = ''
		
		def p(line):
			if 'filename' in opts:
				print pso.filename + ":",
			print line
		
		baduvfound = 0
		
		for f in leftovers:
			pso = PSOinfo()
			pso.load(f)
			
			if 'textures' in opts:
				for t in pso.textures:
					p(t)
			
			surfaces = pso.snames
			
			triangles = 0
			
			for s in surfaces:
				if 'surface' in opts:
					p(s)
				
#				print pso.surfaces[s]
				
				if 'hash' in opts:
					if '#' in s:
						p(s[s.index('#'):])
				
				if 'reflection' in opts:
					p(pso.surfaces[s]['highlighttex'])
					
				if 'tflags' in opts:
					for f in ['colflags', 'specflags', 'glowflags']:
						if f in pso.surfaces[s]:
							p("%10s : %s %s" % (f, hex(pso.surfaces[s][f]), tobin(pso.surfaces[s][f])))
				
				if 'channels' in opts:
					if "<" in s:
						p(s[s.index("<"):])
				
				if 'mesh-summary' in opts:
					p('triangles: ' + str(len(pso.surfaces[s]['triangles'])))
					triangles += len(pso.surfaces[s]['triangles'])

				if 'baduv' in opts or 'baduvverbose' in opts:
					for triz in pso.surfaces[s]['triangles']:
						for v in triz:
							if len(pso.surfaces[s]['verts'][v]) > 6:
								for ut, vt in zip(pso.surfaces[s]['verts'][v][6:][::2], pso.surfaces[s]['verts'][v][6:][1::2]):
									if ut < 0.0 or ut > 1.0 or vt < 0.0 or vt > 1.0:
										if not baduvfound and 'baduv' in opts:
											print pso.filename
											baduvfound = 1
										if 'baduvverbose' in opts:
											print triz, v, ut, vt
				
				if 'fish' in opts:
					if pso.surfaces[s]['ntex'] < 3:
						z = ""
						for t in ['coltex', 'specmap', 'glowmap']:
							if t in pso.surfaces[s]:
								z += " " + t
						p("ntex: %2d %s" % (pso.surfaces[s]['ntex'], z))
				
				if pso.surfaces[s]['ntex'] == 1:
					if 'coltex' not in pso.surfaces[s]:
						print pso.filename

				if 'nl' in opts:
					print
			
			if 'mesh-summary' in opts:
				p('total triangles: ' + str(triangles))
			
	else:
		jgw_utils.usage(args)
	
