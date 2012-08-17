#!/usr/local/bin/python
#
# $Id: parse_headers.py,v 1.4 2007/09/10 23:30:44 jasper Exp $
#
# parses all the header files in a directory and
# trys to make some sense of them
#
# outputs:
#
# dbm of enums
# dbm of func's / tasks
# dbm of types & hierarchy
#

import string, sys, re, shelve, os
from hexdump import hexdump

ere = re.compile('^enum\s+(?P<name>[a-zA-Z]+)\s*{?$')
lere = re.compile('^enum\s+(?P<name>[a-zA-Z]+)\s*{(?P<stuff>[^}]+)};$')
hre = re.compile('^handle (?P<child>[^: ]+) : (?P<parent>[^ :;]+);$')

pre = re.compile('^((?P<ret>[_a-zA-Z]+)\s+)?(?P<name>[0-9A-Za-z._]+)\s*\(\s?(?P<args>[^()]*)\s?\);$')

ncre = re.compile('/\*.*\*/')

class HeaderParser:
	def __init__(self):
		self.ei = 0
		self.enums = {}
		self.protos = {}
		# parent : child
		self.handles = {}
		self.verbose = 0

	def add_enum(self, line, enum):

		if enum not in self.enums:
			self.enums[enum] = {}

		if line.find('=') != -1:
			(name, thing) = line.split('=')
			name = name.strip()
			try:
				self.ei = int(thing)
				line = name
			except ValueError:
				try:
					self.ei = int(thing, 16)
					line = name
				except ValueError:
					if thing.find('|') != -1:
						things = thing.split('|')
						r = 0
						for thing in things:
							thing = thing.strip()
							r += self.enums[enum][thing]
						self.ei = r
						line = name
					else:
						thing = thing.strip()
						if thing not in self.enums[enum]:
							print "@@@",name, thing
							raise RuntimeError
						else:
							self.ei = self.enums[enum][thing]
							line = name

		eas = []
		if line.find(',') != -1:
			eas = line.split(',')
			eas = map(lambda x: x.strip(), eas)
		else:
			eas = [line]
		for e in eas:
			self.enums[enum][e] = self.ei
			self.ei += 1
	
	def add_proto(self, proto):
		assert proto.startswith('prototype')
		proto = ncre.subn('', proto)[0]
		proto = proto[len('prototype'):].strip()
		if self.verbose:
			print proto
		r = pre.search(proto)
		r = r.groupdict()
		if r['args'] == '':
			r['args'] = None
		
		name = r['name']
		name = name[name.find('.') + 1:]
		if name == r['ret']:
			r['ret'] = 'task'
		args = r['args']
		if args == None:
			args = []
		else:
			args = args.split(',')
			args = map(string.strip, args)
			args = map(lambda x: x.split(' '), args)

			def mangleify(t):
				if len(t) != 2:
					if len(t) == 3 and t[0] == 'ref':
						t = t[1:]
					else:
						print "XXX mangled proto?", t
				return t

			args = map(lambda x: mangleify(x), args)
		self.protos[r['name']] = {'ret' : r['ret'], 'args' : args}
	
	def parse(self, file):
		fh = open(file, "r")
		
		name = os.path.basename(file)
		self.name = name[:-2]

		# or enum or proto
		state = 'looking'
#		proto = ''
		enum = ''
		
		enumstate = 'ok'
		enumaccum = ''

		protoaccum = ''
				
		# python needs to ship with a lex/yacc type of thing.
		for line in fh:
			line = line.strip()
			if line.startswith('//'):
				continue
			elif line == '':
				continue
			elif re.match('^\s+$', line):
				continue
			elif re.match('^\s*//', line):
				continue
			elif line.startswith('#'):
				continue
			elif line.startswith('FLUX_DECLARE_EXTENSION('):
				continue
			elif line.startswith('/*'):
				continue
			elif line.startswith('*'): # also */
				continue
			elif line.startswith('uses'): # maybe we should do something with this?
				continue
			elif line.find('//') != -1:
				line = line[:line.find('//')]
				line = line.strip()

			if state == 'looking':
				if re.search('^prototype\s+.*\);$', line):
					self.add_proto(line)
					continue

				if re.search('^prototype\s+.*[^;]$', line):
					state = 'proto'
					protoaccum = line + ' '
					continue

				r = ere.search(line)
				if r != None:
					enum = r.groupdict()['name']
					state = 'enum'
					self.ei = 0
					continue

				r = lere.search(line)
				if r != None:
					r = r.groupdict()
					self.ei = 0
					self.add_enum(r['stuff'].strip(), r['name'].strip())
					continue

				r = hre.search(line)
				if r != None:
					r = r.groupdict()
					self.handles[r['parent']] = r['child']
					continue

				print '%',line,'%'
#				hexdump(line)
				continue		

			elif state == 'enum':
				if line.startswith('};') or line.startswith('} ;'):
#					print 'end ' + enum
					state = 'looking'
					# last entry
					if enumstate == 'ick':
#						print "***", enumaccum
						enumaccum = enumaccum.strip()
						self.add_enum(enumaccum, enum)
						enumstate = 'ok'
						enumaccum = ''
				elif line == '{':
					pass
				else:
					if line.endswith(','):
						# the end of an entry
						line = line[:-1]
						if enumstate == 'ick':
							line = enumaccum + ' ' + line
							enumstate = 'ok'
							enumaccum = ''
					else:
						enumstate = 'ick'
						enumaccum = enumaccum + ' ' + line
						continue


	#				if enumstate is 'ok':
					self.add_enum(line, enum)
	#				elif enumstate is 'ick':
	#					enumaccum += ' ' + line

				continue
			elif state == 'proto':
				if line.endswith(';'):
#					print protoaccum + line
					self.add_proto(protoaccum + line)
					state = 'looking'
				else:
					protoaccum += line + ' '
				continue
			else:
				print 'unknown state', state
			

def sortmaker(d):
	return lambda x,y: cmp(d[x], d[y])

def handle_r(handles, depth, key):
	print "\t" * depth, key
	if key not in handles:
		return
	else:
		for k in handles[key].keys():
			handle_r(handles, depth + 1, k)
	

if __name__ == "__main__":
	if len(sys.argv) != 2:
		print "usage %s : <directory>" % (sys.argv[0])
		sys.exit(-1)
	
	path = sys.argv[1]
	
	headers = []
	
	enums = shelve.open(os.path.join('header_data', 'enums_by_name'))
	enums_bv = shelve.open(os.path.join('header_data', 'enums_by_value'))
	protos = shelve.open(os.path.join('header_data', 'protos'))
	names = shelve.open(os.path.join('header_data', 'names'))
	
	for ent in os.listdir(path):
		if ent.endswith('.h'):
			print 'parseing ' + ent
			hp = HeaderParser()
			hp.parse(os.path.join(path, ent))
			headers += [hp]
			print

	print ">>> done parseing"
	handles = {}
	for h in headers:
		if len(h.handles) > 0:
			for hd in h.handles:
				if hd not in handles:
					handles[hd] = {}
					
				if h.handles[hd] not in handles[hd]:
					handles[hd][h.handles[hd]] = 1
	print "object tree:"
	handle_r(handles, 0, 'hobject')
	
	for h in headers:
		print h.name
		names[h.name.lower()] = h.name
		if len(h.enums) > 0:
			print "\tenums:", len(h.enums)
			for enum in h.enums:
#				if enum == 'eCargoType':
#					continue
#				ks = h.enums[enum].keys()
#				sorter = sortmaker(h.enums[enum])
#				ks.sort(cmp=sorter)
				print "\t\t",enum, ':'
#				for v in ks:
#					print "\t\t\t%5d %s" % (h.enums[enum][v], v)
				if enum.lower() in enums:
					print enum, 'already known (dup in', h.name,')'
				else:
					enums[enum.lower()] = h.enums[enum]
					bv = {}
					for key in h.enums[enum]:
#						print key, h.enums[enum][key]
						bv[str(h.enums[enum][key])] = key
					enums_bv[enum.lower()] = bv
						
		
		if len(h.protos) > 0:
			print "\tprotos:", len(h.protos)
			for proto in h.protos:
				if proto.lower() in protos:
					print proto, 'already known (dup in', h.name,')'
				else:
					protos[proto.lower()] = h.protos[proto]
		print
	
	enums.close()
	enums_bv.close()
	protos.close()
