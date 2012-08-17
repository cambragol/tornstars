#!/usr/bin/env python
#
# $Id: pkginfo.py,v 1.18 2008/06/01 18:31:29 jasper Exp $
#
# print info about .pkg files.
#
#
# XXX istartsystem.pkg
#
import chunk
import sys, os, shelve
from colour import CM
from hexdump import hexdump
from struct import unpack
from IFF import IFF
import jgw_utils
import getopt

class opcode:
	def __init__(self, **kwargs):
		for k in kwargs:
			self.__dict__[k] = kwargs[k]
		self.type = None

class stackitem:
	# type, value, source
	def __init__(self, **kwargs):
		for k in kwargs:
			self.__dict__[k] = kwargs[k]
	
	def __repr__(self):
		out = []
		for k in self.__dict__:
			out += ['%s : %s' % (k, str(self.__dict__[k]))]
		return '<stackitem; ' + ', '.join(out) + '>'
#		return "%7s %7s %7s\n" % (self.type, str(self.value), self.source)

class Func:
	def __init__(self, gr, name, args, ret, type):
		# our 'parent'
		self.gr = gr

		# function name
		self.name = name

		# type
		self.type = type
		
		# [type, name]
		self.args = args
		self.locals = []
		self.nlocals = 0

		# -1 = unknown
		# None = no ret
		# else: type of ret
		self.ret = ret
		
	def setlocals(self, n):
		"""
		set the number of locals and prep the array
		"""
		if len(self.locals) > 0:
			if len(self.locals) == n:
				# lurking bug (probably)
				return
			else:
				# also lurking bug (?)
				self.locals = []
		i = 0
		while i < n:
			self.locals.append([None, None])
			i += 1
		
	def setlocaltype(self, n, type):
		assert n < len(self.locals)
		if self.locals[n][0] == None:
			self.locals[n][0] = type
		elif self.locals[n][0] == type:
			pass
		else:
			self.gr.pc('setting type of local %d for %s to %s : type already set to %s, overwriting' % (n, self.name, type, self.locals[n][0]))
			self.locals[n][0] = type
	
	def setlocalname(self, n, name):
		assert n < len(self.locals), "n too big: %d" % (n)
		i = 0
		while i < len(self.locals):
			if i == n:
				pass
			elif self.locals[i][1] == name:
				self.gr.pc('%s: local %d is already called %s (trying to set %d)' % (self.name, i, name, n))
				return
			i += 1
		if self.locals[n][1] == None:
			self.locals[n][1] = name
		elif self.locals[n][1] == name:
			pass
		else:
			self.gr.pc('setting name of local %d for %s to %s : name already set to %s, overwriting' % (n, self.name, name, self.locals[n][1]))
			self.locals[n][1] = name
			
	def setret(self, ret):
		assert ret != -1
		# XXX allow none to say we know it dosn't have a ret.
		if self.ret == -1:
			self.ret = ret
	
	def setargtype(self, arg, type):
		assert type != None, "can't set a type to None!"
		if self.args[arg][0] == None:
			self.args[arg][0] = type
		elif self.args[arg][0] == type:
			self.pc("attempting to set arg %d to type %s when it's already got that type" % (arg, type))
		else:
			self.pc("***changing type of arg %d to %s from %s, hope thats ok***" % (idx, type, self.args[arg][0]))
			self.args[arg][0] = type
	
	def __str__(self):
#		if self.gr.veryverbose:
#			self.gr.pc("@0x%04x %5d" % (pos, pos))

		if self.type == 'task':
			self.ret = 'task'

		out = ''
		# XXX
		if self.ret == -1:
			out += '/* unknown return */ '
		elif self.ret == None:
			pass
		else:
			out += self.ret + ' '

		out += str(self.name)

		nargs = len(self.args)
		if nargs == 0 or nargs == None:
			out += '()'
		else:
			out += '('
						
			i = 0
			for arg in self.args:
				if arg[0] == None:
					out += '? '
				else:
					out += arg[0]
				if arg[1] == None:
					out += 'arg_%d, ' % (i)
				else:
					out += ' ' + str(arg[1]) + ', '
				i += 1
			out = out[:-2]
			out += ')'
		return out

class grinder:
	def __init__(self, code, pkg, display = 'none'):
		self.byop = {}
		self.byname = {}

		self.pkg = pkg
		self.code = code
		self.indent = 0
		self.veryverbose = False
		self.verbose = False
		self.printdis = False
		self.silent = False

		self.quiet = False
		self.mode = 'disassemble'
		
		#
		# contents of the export table.
		#
		# overridden by pkg.etab
		#
		self.etab = {}

		#
		# local func calls
		#
		# indexed by address.
		#
		# we fill this in from stuff we learn as we go.
		# pos : {
		#  args : [['type', name]] (same as from protos)
		#  ret : 'type'
		#  name : 'name'
		# }
		#
		# XXX not any more, now takes Func objects
		self.locals = {}

		self.protos = shelve.open(os.path.join('header_data', 'protos'))

		#
		# names in .pkg's are lowercase so we use this to convert back to StudlyCaps
		#
		self.names = shelve.open(os.path.join('header_data', 'names'))
		
		#
		# for enum translation
		#
		self.enums = shelve.open(os.path.join('header_data', 'enums_by_value'))

		#
		# pass 2 stuff
		#		

		# the stack as pog sees it
		self.stack = []

		# a stack of chunks of source we build up as we go along
		self.sourcestack = []

		# the 'local' storage (called storage to avoid
		# confusion with self.locals)
		self.storage = []

		# the function we're currently in
		self.curr_func = None

		ops = {
			# op : name, arg len, arg unpack, arg display, pops, pushes, symbol
			#
			# if pops or pushes is None then it's special
			#
			0x01 : ['Pop', 			0, '', '', 1, 0, None],
			0x02 : ['PopN', 		1, '=B', '%d', None, 0, None],
			0x03 : ['Copy', 		0, '', '', 0, 1, None],
			0x04 : ['push zero', 	0, '', '', 0, 1, None],
			0x05 : ['push one', 	0, '', '', 0, 1, None],
			0x06 : ['push int8', 	1, '=B', ': %d', 0, 1, None],
			0x07 : ['push int16', 	2, '=H', ': %d', 0, 1, None],
			0x08 : ['push int32', 	4, '=I', ': %d', 0, 1, None],

			0x0b : ['push float', 	4, '=f', ': %f', 0, 1, None],
			0x0c : ['Load', 		4, '=I', '%d', 0, 1, None],
			0x0d : ['Store', 		4, '=I', '%d', 0, 0, None], #'= /* assignment */'],
			0x0e : ['Reserve', 		4, '=I', '%d', 0, 0, None],
			0x0f : ['jmp', 			4, '=I', 'addr: 0x%04x', 0, 0, None],
			0x10 : ['jmp false', 	4, '=I', 'addr: 0x%04x', 1, 0, None],
			0x11 : ['jmp true', 	4, '=I', 'addr: 0x%04x', 1, 0, None],

			0x13 : ['Return', 		0, '', '', 0, 0, 'return'],
			0x14 : ['local call', 	12, '=III', '%d position: 0x%04x no. args: %d', None, 0, None],
			0x15 : ['call', 		12, '=III', '%d %d %d', None, 0, None],

			0x17 : ['LocalStart', 	12, '=III', '%d 0x%04x %d', None, 0, None],
			0x18 : ['Start', 		12, '=III', '%d %d %d', None, 0, None],

			0x1a : ['addI', 		0, '', '', 2, 1, '+'],
			0x1b : ['subI', 		0, '', '', 2, 1, '-'],
			0x1c : ['mulI', 		0, '', '', 2, 1, '*'],
			0x1d : ['divI', 		0, '', '', 2, 1, '/'],
			0x1e : ['modI', 		0, '', '', 2, 1, '%'],
			0x1f : ['NegateI', 		0, '', '', 1, 1, '- /* negate */'],
			0x20 : ['test eq I', 	0, '', '', 2, 1, '=='],
			0x21 : ['test ne I', 	0, '', '', 2, 1, '!='],
			0x22 : ['test gt I', 	0, '', '', 2, 1, '>'],
			0x23 : ['test lt I', 	0, '', '', 2, 1, '<'],
			0x24 : ['test gt eq I', 0, '', '', 2, 1, '>='],
			0x25 : ['test lt eq I', 0, '', '', 2, 1, '<='],
			0x26 : ['addF', 		0, '', '', 2, 1, '+'],
			0x27 : ['subF', 		0, '', '', 2, 1, '-'],
			0x28 : ['mulF', 		0, '', '', 2, 1, '*'],
			0x29 : ['divF', 		0, '', '', 2, 1, '/'],

			0x2b : ['NegateF', 		0, '', '', 1, 1, '- /* negate */'],
			0x2c : ['test gt f', 	0, '', '', 2, 1, '>'],
			0x2d : ['test lt f', 	0, '', '', 2, 1, '<'],
			0x2e : ['test gt eq f', 0, '', '', 2, 1, '>='],
			0x2f : ['test lt eq f', 0, '', '', 2, 1, '<='],
			0x30 : ['LogicalAnd', 	0, '', '', 2, 1, '&&'],
			0x31 : ['LogicalOr', 	0, '', '', 2, 1, '||'],
			0x32 : ['LogicalNot', 	0, '', '', 1, 1, '!'], # XXX
			0x33 : ['BitwiseAnd', 	0, '', '', 2, 1, '&'],
			0x34 : ['BitwiseOr', 	0, '', '', 2, 1, '|'],
			0x35 : ['BitwiseXor', 	0, '', '', 2, 1, '^'],

			0x37 : ['IntToFloat', 	0, '', '', 			1, 1, None],
			0x38 : ['FloatToInt', 	0, '', '', 			1, 1, None],
			0x39 : ['ToBool', 		0, '', '', 			1, 1, None],
			0x3a : ['NewObject', 	4, '=I', ': %d', 	0, 1, None],
			0x3b : ['MarkObject', 	0, '', '', 			0, 0, None],
			0x3c : ['DeleteMarkedObjects', 0, '', '', 	0, 0, None],
			0x3d : ['StoreObject', 	4, '=I', '%d', 		0, 0, None], # '= /* assignment */'],
			0x3e : ['LoadString', 	4, '=I', '%d', 		0, 1, None],
			0x3f : ['EqualObjects', 0, '', '', 			2, 1, '=='],
			0x40 : ['CloneObject', 	0, '', '', 			0, 1, None], # XXX
			0x41 : ['EndTimeslice', 0, '', '', 			0, 0, '/* schedule starts and ends here */'],
			0x42 : ['TimedJump', 	12, '=IIf', 'addr: 0x%04x %d %f', 0, 1, 'every /* foo */ {'],
			0x43 : ['atomic', 		0, '', '', 			0, 0, 'atomic {'],
			0x44 : ['end atomic', 	0, '', '', 			0, 0, '} /* end atomic*/'],
			0x45 : ['debug', 		4, '=I', '0x%04x', 	0, 0, 'debug {']
		}
		for op in ops:
			(name, length, ups, disp, pops, pushes, symbol) = ops[op]
			self.addop(opcode(op = op, name = name, length = length, ups = ups, pfs = disp, pops = pops, pushes = pushes, symbol = symbol))

		for op in ['Pop', 'PopN', 'Copy']:
			self.byname[op].type = 'pop'
		
		for op in ['push zero', 'push one', 'push int8', 'push int16', 'push int32', 'push float']:
			self.byname[op].type = 'push'
		
		for op in ['Load', 'Store', 'Reserve']:
			self.byname[op].type = 'sp'

		for op in ['jmp', 'jmp false', 'jmp true']:
			self.byname[op].type = 'jump'

		self.byname['Return'].type = 'ret'

		for op in ['local call', 'call']:
			self.byname[op].type = 'call'
		
		for op in ['LocalStart', 'Start']:
			self.byname[op].type = 'start'

		for op in ['addI', 'subI', 'mulI', 'divI', 'modI', 'NegateI', 'addF', 'subF', 'mulF', 'divF', 'NegateF']:
			self.byname[op].type = 'math'

		for op in ['test eq I', 'test ne I', 'test gt I', 'test lt I', 'test gt eq I', 'test lt eq I', 'test gt f', 'test lt f', 'test gt eq f', 'test lt eq f']:
			self.byname[op].type = 'test'
		
		# should really be bitop, but can be math
		for op in ['BitwiseXor', 'BitwiseAnd', 'BitwiseOr']:
			self.byname[op].type = 'math'

		# conversions
		for op in ['IntToFloat', 'FloatToInt', 'ToBool']:
			self.byname[op].type = 'math'

		# untyped:
		# EqualObjects LogicalOr LogicalNot MarkObject EndTimeslice LogicalAnd DeleteMarkedObjects 
		# TimedJump 'end atomic' StoreObject LoadString CloneObject NewObject debug atomic

		#['LogicalAnd', 'LogicalOr', 'LogicalNot']

#'NewObject',
#'MarkObject',
#'DeleteMarkedObjects',
#'StoreObject',

#'LoadString',
#'EqualObjects',
#'CloneObject',
#'EndTimeslice',
#'TimedJump',
#'atomic',
#'end atomic',
#'debug',
		
#		types = {}
#		
#		for op in self.byname:
#			if self.byname[op].type not in types:
#				types[self.byname[op].type] = 1
		

		cz = CM(display)
		self.typesp = {
			'jump' : cz.colmaker(['red']),
			'start': cz.colmaker(['blue', 'bold']),
			'sp'   : cz.colmaker(['cyan']),
			'ret'  : cz.colmaker(['yellow', 'bold']),
			'push' : cz.colmaker(['white', 'underline']),
			'call' : cz.colmaker(['yellow', 'underline']),
			'pop'  : cz.colmaker(['blue']),
			'test' : cz.colmaker(['white', 'bold']),
			'math' : cz.colmaker(['green']),
		}

		# display call back
		self.byname['Return'].dcb = self.opreturn
		self.byname['local call'].dcb = self.localcall
		self.byname['call'].dcb = self.call
		self.byname['LocalStart'].dcb = self.localtask
		self.byname['Start'].dcb = self.task
		self.byname['NewObject'].dcb = self.obj
		self.byname['LoadString'].dcb = self.print_string

		# uncompile call back
		self.byname['Return'].ucb = 	self.uc_return
		self.byname['local call'].ucb = self.uc_call
		self.byname['call'].ucb = 		self.uc_call
		self.byname['LocalStart'].ucb = self.uc_call
		self.byname['Start'].ucb = 		self.uc_call
		self.byname['NewObject'].ucb = 	self.uc_obj
		self.byname['LoadString'].ucb = self.loadstr_ucb
		self.byname['Pop'].ucb = 		self.oppop

		self.byname['Copy'].ucb = 		self.uc_copy

		self.byname['push one'].ucb = 	self.push
		self.byname['push zero'].ucb = 	self.push
		self.byname['push int8'].ucb = 	self.push
		self.byname['push int16'].ucb = self.push
		self.byname['push int32'].ucb = self.push

		self.byname['push float'].ucb = self.push

		self.byname['Load'].ucb = 		self.load

		self.byname['Store'].ucb =		self.uc_store
		self.byname['StoreObject'].ucb =		self.uc_store
		
		self.byname['jmp false'].ucb = 	self.uc_jmp
		self.byname['jmp true'].ucb = 	self.uc_jmp
		self.byname['jmp'].ucb = 	self.uc_jmp

		for i in ['test eq I', 'test ne I', 'test gt I', 'test lt I', 'test gt eq I', 'test lt eq I', 'test gt f', 'test lt f', 'test gt eq f', 'test lt eq f', 'EqualObjects']:
			self.byname[i].ucb = self.uc_test

		for i in ['LogicalAnd', 'LogicalOr']:
			self.byname[i].ucb = self.uc_test

		for i in ['addI', 'subI', 'mulI', 'divI', 'modI', 'addF', 'subF', 'mulF', 'divF']:
			self.byname[i].ucb = self.uc_math

		for i in ['BitwiseAnd', 'BitwiseOr', 'BitwiseXor']:
			self.byname[i].ucb = self.uc_bitop

		self.byname['LogicalNot'].ucb = self.uc_not
		self.byname['NegateI'].ucb = self.uc_negi
		self.byname['NegateF'].ucb = self.uc_negf
		self.byname['IntToFloat'].ucb = self.uc_itof
		self.byname['FloatToInt'].ucb = self.uc_ftoi
		self.byname['ToBool'].ucb = self.uc_itob

		self.byname['atomic'].ucb = self.uc_atomic
		self.byname['end atomic'].ucb = self.uc_atomic
		self.byname['debug'].ucb = self.uc_debug

		self.byname['MarkObject'].ucb = self.uc_mark
		
		self.byname['TimedJump'].ucb = self.uc_timedjump
		
		# op's with no ucb:
		#
		# EndTimeslice DeleteMarkedObjects PopN Reserve CloneObject
		#
		# XXX is it a bug that PopN's missing?!?
		#
				
	#
	# grinder methods
	#
	def addop(self, op):
		assert op.op not in self.byop
		assert op.name not in self.byname
		self.byop[op.op] = op
		self.byname[op.name] = op
	
	def len(self, op):
		assert op in self.byop
		return self.byop[op].length

	def pass_one(self):
		if self.mode == 'both' or self.mode == 'disassemble':
			self.printdis = True
		else:
			self.printdis = False
		pos = 0
		while(pos != None):
			pos = self.dissasm(pos)
	
	def header(self):
		'''print the header (imports etc) of this file'''
		self.pl("package %s;" % (self.pkg.pkg_name))

		i = set(self.pkg.imports.keys())
		j = set(self.pkg.objects.keys())
		
		tmp = i.union(j)
		tmp2 = []
		for qqq in tmp:
			if qqq in self.names:
				tmp2.append(self.names[qqq])
			elif qqq != '__system':
				self.pc('wierd uses: <' + qqq + '>')

		tmp2.sort()
		#
		# XXX HACK HACK HACK
		#
		# this is here cos most things need eCargoType, which also needs the station
		# type enums.
		#
		# (since these includes are only enums we don't know to pull them in, cos the
		# code that decides which headers to pull in only looks at funcs. This could
		# be fixed by keeping a record of which enum fixup's we've done and then
		# adding the relevent file to the list of imports).
		#
		tmp2 = ['MapEnumerations', 'iCargoScript'] + tmp2
		if len(tmp2) < 3:
			tmp = ', '.join(tmp2)
			if tmp != '':
				self.pl('uses ' + tmp + ';')
		else:
			self.pl('uses ' + tmp2[0] + ',')
			for e in tmp2[1:-1]:
				self.pl("\t" + e + ",")
			self.pl("\t%s;" % (tmp2[-1]))
			self.pl('')

		if len(self.etab.values()) > 0:
			if len(self.etab.values()) < 3:
				self.pl('provides ' + ', '.join(self.etab.values()) +  ';')
			else:
				self.pl('provides ' + self.etab.values()[0] + ',')
				for e in self.etab.values()[1:-1]:
					self.pl("\t" + e + ",")
				self.pl("\t%s;" % (self.etab.values()[-1]))

			self.pl('')

	def dis_func(self, pos):
		func = self.locals[pos]
		self.curr_func = func
		self.pl(func)
		self.pl('{')
		self.indent = 1
		nargs = len(func.args)
		self.nslots = nargs
		self.storage = [None] * nargs

		i = 0
		while i < nargs:
			self.pc('slot %d is type %s' % (i, func.args[i][0]))
			self.storage[i] = stackitem(type = func.args[i][0], name = func.args[i][1])
			i += 1
			
		(op, args) = self.one_op(pos)
		if op.name == 'Reserve':
			self.nslots += args[0]
			self.pc('slots + ' + str(args[0]) + ' now ' + str(self.nslots))
			i = len(self.storage)
			while i < self.nslots:
				if len(func.locals) > 0:
					# 2nd pass
					self.pl('%s %s;' % (func.locals[i - nargs][0], func.locals[i - nargs][1]))
					self.storage += [stackitem(name = func.locals[i - nargs][1], type = func.locals[i - nargs][0])]
				else:
					# 1st pass
					self.pc('? local_%d;' % (i), )
					self.storage += [stackitem(name = 'local_%d' % i, type = None)]
				i += 1
		else:
			self.pc('no locals')
			
		go = 1
		while go:
			(op, args) = self.one_op(pos)			
			if op.name == 'Return':
				go = 0
			#
			# pre op actions
			#
			if pos in self.preop:
				for act in self.preop[pos]:
					act()
			# end preop

			if self.veryverbose:
				self.pc(" @%04x %s" % (pos, op.name))
			else:
				if op.name not in ['LoadString', 'MarkObject', 'call', 'Pop', 'DeleteMarkedObjects',\
				 'NewObject', 'Store', 'Load', 'StoreObject']:
					if not op.name.startswith('push'):
						if self.verbose:
							self.pc("@%04x %s" % (pos, op.name))
						elif op.name in ['EndTimeslice']: # TimedJump
							self.pc("@%04x %s" % (pos, op.name))
							self.pc(args)
				
			if op.name == 'push one':
				args = [1]
			if op.name == 'push zero':
				args = [0]

			if 'ucb' in op.__dict__:
				op.ucb(pos, args, op)
			else:
				if op.symbol != None:
#					if op.pops > 0:
#						print self.stack[:op.pops]
					self.pc("symbol: " + op.symbol)
#				print '// non ucb pop & push'
				if op.pops > 0:
					i = 0
					if op.pops > len(self.stack):
						print
						print '//',
						print '*' * 30
						print "// crap, not enough on the stack, expect breakage, %d > %d" % (op.pops, len(self.stack))
						print
					else:
						while i < op.pops:
							self.stack.pop()
							i += 1
				if op.pushes > 0:
					i = 0
					while i < op.pushes:
						self.pc('XXX pushing an unknown for %s' % (op.name))
						self.stack.append(stackitem(type = None, value = None, source = op.name, name = None))
						i += 1


			#
			# post op actions
			#
			if pos in self.postop:
				for act in self.postop[pos]:
					act()
			# end postop

			pos += op.length + 1

		if self.nslots > 0:
			self.pc('dumping args and local types:')
			self.pc('')
			i = 0
			while i < len(func.args):
				if self.storage[i].type != func.args[i][0]:
					self.pc("types changed for arg %d : %s %s" % (i, self.storage[i], func.args[i]))
				i += 1

			i = len(func.args)
			func.setlocals(self.nslots - i)
			while i < self.nslots:
				self.pc('%s %s;' % (self.storage[i].type, self.storage[i].name))
				func.setlocalname(i - len(func.args), self.storage[i].name)
				func.setlocaltype(i - len(func.args), self.storage[i].type)
				i += 1

		self.dec_indent()
		self.pl('}')
		self.indent = 0

	def pass_two(self):
		for pos in self.etab:
			iname = "%s.%s" % (self.pkg.pkg_name, self.etab[pos])
			if pos not in self.locals:
				# XXX fix from protos
				ret = None
				args = []
				type = None
				if iname.lower() in self.protos:
					call = self.protos[iname.lower()]
					ret = call['ret']
					args = call['args']
					if ret == 'task':
						type = ret
					else:
						type = 'func'
				self.locals[pos] = Func(self, self.etab[pos], args, ret, type)
			else:
				if self.locals[pos].name == None:
					self.locals[pos].name = self.etab[pos]
				if iname.lower() in self.protos:
					if self.locals[pos].ret != self.protos[iname.lower()]['ret']:
						if self.locals[pos].ret == None:
							# this may not always be a good idea, but we don't have return value discovery yet so wth.
							self.locals[pos].ret = self.protos[iname.lower()]['ret']
							if self.locals[pos].ret == 'task':
								self.locals[pos].type = 'task'
						else:
							print "// ret missmatch for ", self.etab[pos], self.locals[pos].ret, self.protos[iname.lower()]['ret']

					if self.locals[pos].args != self.protos[iname.lower()]['args']:
#						print "// args missmatch for ", self.etab[pos], self.locals[pos].args, self.protos[iname.lower()]['args']
						assert len(self.locals[pos].args) == len(self.protos[iname.lower()]['args'])
						i = 0
						while i < len(self.protos[iname.lower()]['args']):
							if self.locals[pos].args[i][0] == None and self.locals[pos].args[i][1].startswith('arg_'):
								self.locals[pos].args[i] = self.protos[iname.lower()]['args'][i]
							else:
								self.pc('type missmatch for %s[%d] : %s %s' % (self.etab[pos], i, str(self.locals[pos].args[i]), str(self.protos[iname.lower()]['args'][i])))
							i += 1

		
		#
		# run through the locals giving them names if they've not already got one.
		#
		self.pc("%d local functions" % (len(self.locals)))
		self.pc(None)
		self.header()
		poss = self.locals.keys()
		poss.sort()
		
#		print
#		print self.pkg.etab
#		print
		
		f = 0
		u = 0
		t = 0
		for pos in poss:
			local = self.locals[pos]
			if local.name == None:
				if local.type == 'task':
					local.name = 'task_' + str(t)
					t += 1
				elif local.type == 'func':
					local.name = 'func_' + str(f)
					f += 1
				elif local.type == None:
					local.name = 'unknown_' + str(u)
					u += 1
				else:
					# only func's or tasks known
					raise RuntimeError
			self.locals[pos] = local

#		for p in poss:
#			print p, self.locals[p]
#			qqf = Func(self, self.locals[p]['name'], self.locals[p]['args'], self.locals[p]['ret'], self.locals[p]['type'])
#			print qqf

		self.silent = True		

#			if self.pkg_name + '.' + name.lower() in self.protos:
#				ret = self.protos[self.pkg_name + '.' + name.lower()]['ret']
				# call['ret'], self.calls[pos], call['args'],
		
		self.header()
		
		#
		# func posabilities:
		#
		# local func, not called:
		# 	have to work out args and ret, ignore as unknown for now		
		#
		# local func, called:
		#	know nargs, have to work out rest
		#
		# exported func, not in headers:
		#	as unknown, ick
		#
		# exported func, in headers:
		#	all known, unless headers wrong
		#	if called locally, check nargs.
		#
		# funcs with args that arn't used
		#	XXX ick
		#
		
		#
		# now try to find stuff about the funcs.
		#
		for pos in poss:
			self.func_reset()
			self.dis_func(pos)

		self.pc('done 2.0')
		#
		# now do it again with the new info we're learned.
		#
		self.silent = False
		for pos in poss:
			self.func_reset()
			self.dis_func(pos)

		self.pc('done 2.1')

	def one_op(self, pos):
		op = unpack("B", self.code[pos:pos + 1])[0]
		op = self.byop[op]
		pos += 1
		args = []
		if op.length > 0:
			args = unpack(op.ups, self.code[pos:pos + op.length])
		return (op, args)

	def func_reset(self):
		self.curr_func = None
		self.sourcestack = []
		self.stack = []
		self.storage = []
		self.nslots = 0
		# things to do before doing a particular op
		self.preop = {}
		# things to do after doing a particular op
		self.postop = {}

	def add_action_pre(self, pos, act):
		self.add_action(self.preop, pos, act)

	def add_action_post(self, pos, act):
		self.add_action(self.postop, pos, act)

	def add_action(self, where, pos, act):
		if pos not in where:
			where[pos] = []
		where[pos].append(act)

	def print_func(self, pos, local):
		if self.veryverbose:
			self.pc("@0x%04x %5d" % (pos, pos))
		out = ''
		if local['ret'] != None:
			out = local['ret'] + ' ' + local['name']
		else:
			out = str(local['name'])

		nargs = len(local.args)
		if nargs == 0 or nargs == None:
			out += '()'
		else:
			out += '('
			args = local.args
			
			i = 0
			for arg in args:
				if arg[0] == None:
					out += '? arg_%d,' % (i)
				else:
					out += ' ' + arg[0] + ' ' + str(arg[1]) + ','
				i += 1
			out = out[:-1]
			out += ')'
		self.pl(out)

	def dissasm(self, pos):
		op = unpack("B", self.code[pos:pos + 1])[0]
		assert op in self.byop
#			print "unknown op 0x%02x" % (op)
#			hexdump(self.code[pos:], '', pos)

		if pos in self.pkg.etab:
			print
			iname = self.pkg.pkg_name + '.' + self.pkg.etab[pos]
			iname = iname.lower()
#			self.curr_func = self.pkg.etab[pos]
			if iname in self.protos:
				call = self.protos[iname]
				print '//', call['ret'], self.pkg.etab[pos], call['args']
			else:
				print '// (not in protos) ', self.pkg.etab[pos], ':'
		
		op = self.byop[op]
		if self.printdis:
			print "// %04x %5d [%02x] " % (pos, pos, op.op),
		pos += 1
		if self.printdis:
			if op.type != None:
				print self.typesp[op.type](op.name),
			else:
				print op.name,

		ts = []

		if op.length > 0:
			ts = unpack(op.ups, self.code[pos:pos + op.length])
			if self.printdis:
				if op.type != None:
					print self.typesp[op.type](op.pfs % ts),
				else:
					print op.pfs % ts,

		if 'dcb' in op.__dict__:
			op.dcb(pos - 1, ts)

		if self.printdis:
			print
		if (pos + op.length) >= len(self.code):
			return None
		else:
			return pos + op.length

	# print a line of code
	def pl(self, l):
		# XXX in \n in line, split it and indent it.
		if not self.silent:
			print "%s%s" % ("\t" * self.indent, l)
	
	# print a comment
	def pc(self, l, type='misc'):
		if not self.silent:
			if l == None:
				print
			else:
				co = sys._getframe(1).f_code
				#
				# HACK HACK HACK
				#
				# rather than passing pos to every call of this func we look
				# back up the stack and read it from the parents memory.
				#
				# This is a really stupid way of doing things, and the code
				# should be restructured.
				#
				if 'pos' not in sys._getframe(1).f_locals:
					print "%s// (%s) %s" % ("\t" * self.indent, co.co_name, str(l))
				else:
					pos = sys._getframe(1).f_locals['pos']
					if co.co_name == '<lambda>':
						print "%s// (%s) %s" % ("\t" * self.indent, co.co_name, str(l))					
					else:
						print "%s// 0x%04x (%s) %s" % ("\t" * self.indent, pos, co.co_name, str(l))

	#
	# uncompilation helpers
	#
	def dec_indent(self):
		self.indent -= 1
	
	def inc_indent(self):
		self.indent += 1

	def uc_atomic(self, pos, args, op):
		if op.name == 'atomic':
			self.pl('atomic {')
			self.inc_indent()
		else:
			self.dec_indent()
			self.pl('} /* end atomic */')

	def uc_timedjump(self, pos, args, op):
		(loc, stack, time) = args
		self.pc('Timed Jump, jump @ 0x%04x, time %.2f, stack items to preserve: %d' % (loc, time, stack))
		self.pc('every %.2f {' % (time))
		self.add_action_post(loc, lambda : self.pc('Timed jump set @ 0x%04x to here (0x%04x), every %.2f secs' % (pos, loc, time)))
				
	def uc_jmp(self, pos, args, op):
		to = args[0]
		self.pc('%s from 0x%04x to 0x%04x' % (op.name, pos, to))
		if to < pos:
			self.pc('XXX jump is BACKWARDS (loop end or case test block)')
		else:
			self.add_action_pre(to, lambda : self.dec_indent())
			self.add_action_pre(to, lambda : self.pc('jump from 0x%04x to here (0x%04x)' % (pos, to)))

		if pos + op.length + 1 == to:
			self.pc('XXX jump to next op')
#			self.inc_indent()

		if op.name != 'jmp':
			if self.stack[-1].type != 'bool':
				self.pc('XXX %s on non bool: %s' % (op.name, self.stack[-1]))
				if self.stack[-1].type == 'int':
					self.stack.pop()
			else:
				self.stack.pop()
			self.pl(self.sourcestack.pop().strip())
			self.inc_indent()
#			self.add_action_post(to, lambda : self.dec_indent())
		elif to > pos and to != (pos + op.length + 1):
			# unconditional jmp forwards.
			retfound = False
			i = 0
			p = to
			while i < 10:
				(op, args) = self.one_op(p)
				self.pc("looking for a ret: 0x%04x %s" % (p, op.name))

				# putting push zero in here is asking for trouble.
				# ditto for CloneObject
				if op.name not in ['DeleteMarkedObjects', 'Return', 'push zero', 'CloneObject']:
					break

				if op.name == 'Return':
					self.pc('unconditional jmp forwards hits a ret after %d ops' % (i))
					retfound = True
					op.ucb(p, args, op)
					break

				p += op.length + 1
				i += 1

			if not retfound:
				# return not found, so always a case (?)
				self.pc('***unconditional jmp forwards *without* a return***')
				
#		if not to < pos:

#		else:
#			self.dec_indent()
			
#		self.add_action_post(end, lambda : self.dec_indent())
#		self.add_action_post(end, lambda : self.pl('} /* end debug from 0x%04x */' % (pos)))

	def uc_debug(self, pos, args, op):
		end = args[0]
		self.pc('debug until 0x%04x %5d' % (end, end))
		self.pl('debug {')
		self.inc_indent()
		(nop, nargs) = self.one_op(end)
		# XXX
		if nop.name == 'debug':
			self.add_action_pre(end, lambda : self.dec_indent())
			self.add_action_pre(end, lambda : self.pl('} /* end debug from 0x%04x */' % (pos)))
		else:
			self.add_action_post(end, lambda : self.dec_indent())
			self.add_action_post(end, lambda : self.pl('} /* end debug from 0x%04x */' % (pos)))

	def uc_copy(self, pos, args, op):
		t = self.stack[-1]
		self.stack.append(t)
		t = self.sourcestack[-1]
		self.sourcestack.append('/* copied */ ' + t)

	def uc_test(self, pos, args, op):
		# XXX more/better type checking
		if self.stack[-1].type not in ['bool', 'int', None] or self.stack[-2].type not in ['bool', 'int', None]:

			def enum_fixup(a, b, pos):
				if self.stack[a].type != self.stack[b].type and self.stack[a].type == 'int':
					self.pc('type missmatch %s != %s' % (str(self.stack[a]), str(self.stack[b])))
				
					# this is a bit dangerous
					if self.stack[b].type.lower() in self.enums:
						if str(self.stack[a].value) in self.enums[self.stack[b].type.lower()]:
							self.pc('fixup: cmp to ' + self.enums[self.stack[b].type.lower()][str(self.stack[a].value)])
							assert self.sourcestack[a] == str(self.stack[a].value)
							self.sourcestack[a] = self.enums[self.stack[b].type.lower()][str(self.stack[a].value)]

			enum_fixup(-1, -2, pos)
			enum_fixup(-2, -1, pos)
			
		if self.stack[-2].value == 0 and self.stack[-1].source == 'ToBool':
			# XXX HACK HACK HACK need to put the object types from
			# parse_headers in a shelve
			if self.stack[-1].oldtype != None and self.stack[-1].oldtype.startswith('h'):
				self.pc('object == none fixup: %s %s' % (self.stack[-1], self.stack[-2]))
				self.stack[-2].value = 'none'
				assert self.sourcestack[-2] == '0'
				self.sourcestack[-2] = 'none'

		out = "(%s %s %s)" % (self.sourcestack.pop(), op.symbol, self.sourcestack.pop())
		self.sourcestack.append(out)
		self.stack.pop()
		self.stack.pop()
		self.stack.append(stackitem(type = 'bool', value = None, source = op.name, name = None))

	def uc_bitop(self, pos, args, op):
		out = "(%s %s %s)" % (self.sourcestack.pop(), op.symbol, self.sourcestack.pop())
		self.sourcestack.append(out)
		self.stack.pop()
		self.stack.pop()
		self.stack.append(stackitem(type = 'int', value = None, source = op.name, name = None))

	def uc_math(self, pos, args, op):
		out = "(%s %s %s)" % (self.sourcestack.pop(), op.symbol, self.sourcestack.pop())
		self.sourcestack.append(out)
		# XXX check types
		self.stack.pop()
		self.stack.pop()
		type = None
		if op.name.endswith('I'):
			type = 'int'
		elif op.name.endswith('F'):
			type = 'float'
		else:
			self.pc('unable to determine type')
		self.stack.append(stackitem(type = type, value = None, source = op.name, name = None))

	def uc_not(self, pos, args, op):
		out = "(!%s)" % (self.sourcestack.pop())
		self.sourcestack.append(out)
		self.stack.pop()
		self.stack.append(stackitem(type = 'bool', value = None, source = 'test', name = None))
		
	def uc_negi(self, pos, args, op):
		out = "-(%s)" % (self.sourcestack.pop())
		self.sourcestack.append(out)
		t = self.stack.pop()
		self.stack.append(stackitem(type = 'int', value = t.value, source = op.name, name = t.name))
		
	def uc_negf(self, pos, args, op):
		out = "-(%s)" % (self.sourcestack.pop())
		self.sourcestack.append(out)
		t = self.stack.pop()
		self.stack.append(stackitem(type = 'float', value = t.value, source = op.name, name = t.name))
		
	def uc_itof(self, pos, args, op):
		out = "/* float */ %s" % (self.sourcestack.pop())
		self.sourcestack.append(out)
		p = self.stack.pop()
		self.stack.append(stackitem(type = 'float', value = p.value, source = op.name, name = p.name))
	
	def uc_mark(self, pos, args, op):
		t = self.stack.pop()
		t.__dict__['marked'] = 1
#		self.pc('marking ' + str(t))
		self.stack.append(t)
		
	def uc_ftoi(self, pos, args, op):
		out = "/* int */ %s" % (self.sourcestack.pop())
		self.sourcestack.append(out)
		p = self.stack.pop()
		self.stack.append(stackitem(type = 'int', value = p.value, source = op.name, name = p.name))

	def uc_itob(self, pos, args, op):
		p = self.stack.pop()
		out = "/* %s */ %s" % (p.type, self.sourcestack.pop())
		self.sourcestack.append(out)
		self.stack.append(stackitem(type = 'bool', value = p.value, source = op.name, name = p.name, oldtype = p.type))
		
	def load(self, pos, args, op):
		type = None
		if len(self.storage) <= args[0]:
			self.pc('XXX attempting to access non existant storage (func with unknown args?')
			self.pc('XXX len: %d, this one: %d' % (len(self.storage), args[0]))
			self.stack.append(stackitem(type = None, value = None, source = 'Load', name = 'arg_or_local_?'))
			self.sourcestack.append('arg_or_local_?')
			return
# XXX verbose/quiet
#		print '//', self.storage[args[0]]
		if self.storage[args[0]].type == None and self.storage[args[0]].name.startswith('local_'):
			self.pd('// %s loading %s which has an unknown type' % ('*' * 10, self.storage[args[0]].name))
		type = self.storage[args[0]].type
		self.stack.append(stackitem(type = type, value = None, source = 'Load', name = self.storage[args[0]].name))
		self.sourcestack.append(self.storage[args[0]].name)
#		self.pc(self.sourcestack)
#		self.pc(self.stack)

	def uc_store(self, pos, args, op):
		if args[0] >= len(self.storage):
			self.pc('XXX oh dear, we don\'t know the number of args to this function1 so we don\'t know how much storage to allocate')
			self.pc('XXX things will break now')
			self.pc('XXX nslots: %d this one: %d' % (len(self.storage), args[0]))
			return

		if self.stack[-1].type != None:
			if self.storage[args[0]].type == None:
				self.storage[args[0]].type = self.stack[-1].type
				self.pc('learned local_%d is a %s' % (args[0], self.stack[-1].type))
			elif self.storage[args[0]].type != self.stack[-1].type:
				self.pc('local_%d is thought to be a %s but is being assigned a %s' % (args[0], self.storage[args[0]].type, self.stack[-1].type))
		else:
			self.pc('local_%d is None from: %s' % (args[0], self.stack[-1]))
		#
		# special case - if we're assigning an object
		# thats been created as a stub (__system.foo ??)
		# don't print any thing, just update the type.
		#
		if self.stack[-1].source == 'NewObject':
#			self.sourcestack.append('// NewObject ' + self.stack[-1].type)
			return

		self.pl("local_%d = %s;" % (args[0], self.sourcestack.pop()))
#		if self.stack[0].source == 'push':
#			print self.stack[0].value,
#		else:
#			print self.stack[0],
		# XXX need to pop the sourcestack sometimes XXX
		self.sourcestack.append('local_%d' % (args[0]))
#		print self.storage
#		print args

	def uc_call(self, pos, args, op):
		if op.name == 'call' or op.name == 'Start':
			assert pos in self.pkg.calls
			if self.pkg.calls[pos].lower() not in self.protos:
				self.pc('@%s XXX not in protos : %s' %(self.pkg.calls[pos], self.pkg.filename))
				self.pc('WILL DIE SOON - SUSPECT FROM HERE ON')
				return
			else:
				call = self.protos[self.pkg.calls[pos].lower()]
				type = 'func'
				if call['ret'] == 'task':
					type = 'task'
				call = Func(self, self.pkg.calls[pos], call['args'], call['ret'], type)
				nargs = len(call.args)
		elif op.name == 'local call' or op.name == 'LocalStart':
			assert args[0] == 0
			(pos, nargs) = args[1:]
			assert pos in self.locals
			#
			# n.b. overrides what we think the func signature
			# with what the pog is using
			#
			call = self.locals[pos]
			if nargs != len(call.args):
				# pog has different ideas from us about how many args
				# this func has
				self.pc('arglen missmatch')
				self.pc(call.args)
		else:
			self.pc('unknown op %s expect to die soon' % (op.name))

		ret_type = 'int'
		ret_value = '0'

#		print '/*'
#		print "\n".join(map(str, self.stack))
#		print
#		print "\n".join(map(str, self.sourcestack))
#		print '*/'

		assert len(self.stack) >= nargs, "not enough stuff on the stack"
		assert args[2] == nargs, "args to call dosn't match func proto"

		i = nargs - 1
		si = -1
		while i > -1:
			fixup_ok = 0
			if self.stack[si].type == 'int' and call.args[i][0] == 'bool':
				# attempt to fix up bools
				if self.stack[si].value == 0 or self.stack[si].value == 1:
					# ok to change to true/false
					if self.stack[si].value == 0 and self.sourcestack[si] == '0':
						self.sourcestack[si] = 'false'
						fixup_ok = 1
					elif self.stack[si].value == 1 and self.sourcestack[si] == '1':
						self.sourcestack[si] = 'true'
						fixup_ok = 1
					else:
						self.pc('int -> bool fixup confused : %s %s' % (str(self.stack[si]), str(self.sourcestack[si])))
				else:
					self.pc('XXX non 1/0 int to bool (?!?)')

			if not fixup_ok and self.stack[si].type == 'int' and call.args[i][0] != None and call.args[i][0] != 'int' and self.stack[si].source == 'push':
				# may only be from push?
				if call.args[i][0].lower() in self.enums:
					# it's an enum, so change it to the text
					if str(self.stack[si].value) not in self.enums[call.args[i][0].lower()]:
						self.pc('enum fix up: %d not in enum %s (may be several values |ed together)' % (self.stack[si].value, call.args[i][0]))
					else:
						tmp = self.enums[call.args[i][0].lower()][str(self.stack[si].value)]
						# self.pc('enum fixeup int -> enum %s [%d -> %s]' % (call.args[i][0], self.stack[si].value, tmp))
						self.sourcestack[si] = tmp
						fixup_ok = True

			if self.stack[si].type != call.args[i][0] and not fixup_ok:
				self.pc("type missmatch, %s != %s" % (self.stack[si].type, call.args[i][0]))
				self.pc('%s %s' % (str(self.stack[si]), str(call.args[i])))
				# XXX do the same for load
				if self.stack[si].name != None and self.stack[si].name.startswith('arg_') and not self.stack[si].name.startswith('arg_or_local'):
					# this stack item was an arg to the func we are in with an unknown type.
					# we now know the type
					# XXX hack hack hack, we need to include a storage index in items on the stack XXX
					idx = int(self.stack[si].name[4:])
					if self.storage[idx].type != None:
						self.pc('%s was thought to be a %s, but is being used as a %s' % (self.stack[si].name, self.storage[idx].type, call.args[i][0]))
					else: 
						self.pc('learned %s is a %s' % (self.stack[si].name, call.args[i][0]))
						self.storage[idx].type = call.args[i][0]
						self.curr_func.setargtype(idx, call.args[i][0])
				if call.args[i][0] == None and self.stack[si].type != None:
					#
					# We don't know the type to this arg, but we do now.
					#
					if op.name == 'local call' or op.name == 'LocalStart':
						self.locals[pos].args[i][0] = self.stack[si].type
					
			si -= 1
			i -= 1
		
		out = ''
		
		if op.name == 'LocalStart' or op.name == 'Start':
			out += 'start '
		
		# XXX use func object
		if op.name == 'call' or op.name == 'Start':
			out +=  '%s(' % (self.pkg.calls[pos])
#			self.pc(self.pkg.calls[pos])
		elif op.name == 'local call' or op.name == 'LocalStart':
			out +=  '%s(' % (call.name)
#			self.pc(call['name'])

		i = nargs - 1
		si = len(self.stack) - 1
		oargs = []
		while i > -1:
#			if self.stack[si].value is None:
			oargs.append('%s' % (self.sourcestack.pop()))
			self.stack.pop()
#			else:
#				if self.stack[si].type == 'string':
#					oargs.append('"%s"' % (self.stack[si].value))
#				else:
#					oargs.append(str(self.stack[si].value))
			i -= 1
			si -= 1
		
		# hack hack hack
		# XXX understand this
		oargs.reverse()

		tl = len(out)
		for arg in oargs:
			tl += len(arg)
		
		# XXX need to get at grinder.indent to indent properly.
		if tl > 75 and len(oargs) > 1:
			out += ",\n".join(oargs)
			out += "\n"
		else:
			out += ', '.join(oargs)

		out += ')'
			
#		print '//', out
			
		self.sourcestack.append(out)
					
		ret_type = call.ret
		ret_value = None

		if op.name == 'LocalStart' or op.name == 'Start':
			self.stack.append(stackitem(type = 'htask', value = None, source = op.name, name = None))
		else:
			self.stack.append(stackitem(type = ret_type, value = ret_value, source = op.name, name = None))

	def uc_obj(self, pos, args, op):
		assert pos + 1 in self.pkg.calls
		assert args[0] == 0
		type = self.pkg.calls[pos + 1]
		if type == '__system.FcScriptString':
			type = 'string'
		elif type == '__system.FcScriptSet':
			type = 'set'
		elif type == '__system.FcScriptList':
			type = 'list'
		else:
			print '// unknown object type: ', type
		self.stack.append(stackitem(type = type, value = None, source = 'NewObject'))

	def push(self, pos, args, op):
		type = 'int'
		if op.name == 'push float':
			type = 'float'
		self.stack.append(stackitem(type = type, value = args[0], source = 'push', name = None))
		self.sourcestack.append(str(args[0]))

	def loadstr_ucb(self, pos, args, op):
		self.stack.append(stackitem(type = 'string', value = self.pkg.strings[args[0]], source = 'push', name = None))
		self.sourcestack.append('"%s"' % self.pkg.strings[args[0]])

	def oppop(self, pos, args, op):
		if len(self.stack) == 0:
			self.pd('')
			self.pd('//' + '*' * 30)
			self.pd('// attempting to pop an empty stack @%04x, expect breakage' % (pos))
			return
# XXX verbose/quiet
#		print '// poped ', self.stack[-1]
#		print ';'
		p = self.stack.pop()
#		self.pc(p)
		if 'marked' in p.__dict__:
			self.pc(p)
		if len(self.sourcestack) > 0:
			if self.sourcestack[-1].startswith('local_'):
				self.pc('poping sourcestack %s' % (self.sourcestack.pop()))
#				pass
			else:
				self.pl((self.sourcestack.pop().strip() + ';'))

	def uc_return(self, pos, args, op):
		if len(self.stack) == 1:
			if self.stack[-1].type == 'int' and self.stack[-1].source == 'push' and self.stack[-1].value == 0:
				if self.curr_func.ret == None:
					# XXX unfortunatly it's also None if we don't know what it is...
					pass
				else:
					self.pc('probable default return:')
					self.pl('return 0;')
			elif self.stack[-1].source == 'push':
				if self.stack[-1].type != 'string':
					self.pl('return /* %s */ %s; /* %s */' % (self.stack[-1].type, self.stack[-1].value, self.stack[-1]))
				else:
					self.pl('return /* %s */ "%s"; /* %s */' % (self.stack[-1].type, self.stack[-1].value, self.stack[-1]))
			elif self.stack[-1].source == 'Load':
				self.pl('return %s; /* %s */' % (self.stack[-1].name, self.stack[-1]))
			elif self.stack[-1].source == 'call':
				self.pc(self.stack[-1])
				if len(self.sourcestack) == 0:
					self.pc('XXX sourcestack empty for return')
					self.pl('return ???;')
				else:
					self.pl('return %s;' % (self.sourcestack.pop()))
				if self.curr_func.ret == None:
					self.curr_func.ret = self.stack[-1].type
				elif self.curr_func.ret != self.stack[-1].type:
					self.pc('XXX return type missmatch: %s %s' % (self.curr_func.ret, self.stack[-1].type))
			else:
				self.pl('return /* %s */ ;' % (self.stack[-1]))
			self.stack.pop()
			# Hmmm.
			if len(self.sourcestack) == 1:
				self.sourcestack.pop()
		elif len(self.stack) == 0:
			self.pc('return with empty stack (this is probably a task)')
			self.pl('return;')
			if len(self.sourcestack) != 0:
				self.pc('but there is stuff on the sourcestack')
				self.pc(self.sourcestack)
		else:
			self.pc('return - more than one item on the stack')
			self.pc(self.stack)
			self.pc(self.sourcestack)

#		print self.stack
#		assert len(self.stack) == 1
#		self.stack = []

	#
	# display helpers
	#
	
	#
	# print dissasm
	#
	def pd(self, l):
		if self.printdis:
			print l,

	def opreturn(self, pos, args):
		pos += 1
	
		self.pd("\n")
		if pos in self.pkg.etab:
			return
		if pos in self.locals:
			return
		if pos > len(self.code) - 4:
			# last return in the code section
			return
		else:
			self.pd("// func @%04x %5d\n" % (pos, pos))
			self.locals[pos] = Func(self, None, [], None, None)
			#{'type' : None, 'name' : None, 'ret' : None, 'args' : []}

	def print_string(self, pos, args):
		self.pd('"%s"' % (self.pkg.strings[args[0]]))
	
	def call(self, pos, args):
		#
		# failure of this assertion is if a package calls
		# a function that is exported from another package
		# and imported into the one we are working on, but the function is
		# not in a header file, or parse_headers hasn't been run yet.
		#
		assert pos in self.pkg.calls
		if pos not in self.pkg.calls:
			print 'XXXX call @%04x not in self.pkg.calls: %s' % (pos, args)
		else:
			if self.pkg.calls[pos].lower() not in self.protos:
				self.pd('@' + self.pkg.calls[pos] + 'XXX not in protos : ' + self.pkg.filename)
			else:
				call = self.protos[self.pkg.calls[pos].lower()]			
				self.pd('@ %s %s %s' %  (call['ret'], self.pkg.calls[pos], str(call['args'])))

	# task returns an htask
	def task(self, pos, args):
		assert pos in self.pkg.calls
		if self.pkg.calls[pos].lower() not in self.protos:
			self.pd('@ %s %s %s' % (self.pkg.calls[pos], 'XXX not in protos : ', self.pkg.filename))
		else:
			call = self.protos[self.pkg.calls[pos].lower()]
			self.pd('@ %s %s %s' % (call['ret'], self.pkg.calls[pos], call['args']))

	def localcall(self, pos, args):
		self.local(pos, args, 'func')

	def localtask(self, pos, args):
		self.local(pos, args, 'task')

	def local(self, pos, args, type):
		assert args[0] == 0
		# pos overwritten and changes meaning here,
		# pos was the position of the opcode we're looking at,
		# now it's the pos of the func/task we're calling
		(pos, nargs) = args[1:]
		if pos in self.pkg.etab:
			self.pd("func @ %s %d args" % (self.pkg.etab[pos], nargs))

		if pos in self.locals:
			local = self.locals[pos]
			# e.g. from finding a return
			if local.type == None and len(local.args) == 0:
				pass
			else:
				return

		self.pd("learned %s @ 0x%04x, %d args" % (type, pos, nargs))
		# [addr][type, ret, nargs, (type, type)]
		if nargs == 0:
			self.locals[pos] = Func(self, None, [], None, type)
			# {'type' : type, 'name' : None, 'ret' : None, 'args' : []}
		else:#
			args = []
			i = 0
			while i < nargs:
				args += [[None, 'arg_%d' % (i)]]
				i += 1
			self.locals[pos] = Func(self, None, args, None, type)
			#{'type' : type, 'name' : None, 'ret' : None, 'args' : args}

	def obj(self, pos, args):
		assert pos + 1 in self.pkg.calls
		assert args[0] == 0
		self.pd("@ <%s>" % (self.pkg.calls[pos + 1]))


class PKG_info(IFF):
	"""uses IFF to load a parse (at a high level) a .pkg file"""
	def __init__(self):
		# not actually needed, but a good habit to get into.
		IFF.__init__(self)
		self.types = ["PKG "]
		self.callbacks = {"PKHD": self.pkhd, 
				  "ITAB": self.itab,
				  "PIMP": self.pimp,
				  "FIMP": self.fimp,
				  "OIMP": self.oimp,
				  "ETAB": self.etab,
				  "FEXP": self.fexp,
				  "STAB": self.stab,
				  "CODE": self.code,
				  "*" : self.dump_chunk
#				  "*" : self.print_type
				  }
		self.verbose = False
		self.veryverbose = False
		self.mode = 'decompile'
		self.display = 'none'

		self.num_imports = -1
		self.imports = {}
		self.calls = {}
		self.done_imports = 0
		self.curr_pkg = None
		
		self.num_exports = 0
		self.exports = []
		self.done_exports = 0
		self.etab = {}
		
		self.objects = {}
		
		self.strings = []
		
		self.names = shelve.open(os.path.join('header_data', 'names'))
		
	def done(self):
		# actually 0 is valid
#		assert self.num_imports > -1
#		assert self.num_imports == self.done_imports
#		assert self.num_exports == self.done_exports
#		for pkg in self.imports:
#			print "from %s import" % (pkg),
#			for func in self.imports[pkg]:
#				print func,
#			print
#		poss = self.calls.keys()
#		poss.sort()
#		for pos in poss:
#			print "0x%04x : %s" % (pos, self.calls[pos])

		self.gr.etab = self.etab

		print "*/"

		#
		# print dissasembly output
		#
		# learn some stuff about functions
		#
		self.gr.pass_one()

		#
		# for each func, do we know the return type?
		#
		# if not go through looking for it.
		#
		if self.mode == 'both' or self.mode == 'decompile':
			self.gr.pass_two()

		#
		# now uncompile
		#
		
		print
		print "// done!"


	def code(self, type, blob):
#		hexdump(blob)
		# op : name, length, unpack, descr, optional func
		length = unpack(">I", blob[:4])[0]
		off = 4
		assert length == (len(blob) - 4)
		self.codelength = length
		self.codeblob = blob[4:]
		
		gr = grinder(blob[4:], self, self.display)
		gr.verbose = self.verbose
		gr.veryverbose = self.veryverbose
		gr.mode = self.mode
		self.gr = gr

	def itab(self, type, blob):
		assert len(blob) == 4
		self.num_imports = unpack(">I", blob[:4])[0]

	def etab(self, type, blob):
		assert len(blob) == 4
		self.num_exports = unpack(">I", blob[:4])[0]

	def fexp(self, type, blob):
		self.done_exports += 1
		name = self.get_string(blob)
		pos = unpack(">I", blob[len(name) + 1:])[0]
		if self.verbose:
			print "func %s @ %d 0x%04x" % (name, pos, pos)
		self.exports = self.exports + [(name, pos)]
		self.etab[pos] = name
		
	def pimp(self, type, blob):
		self.done_imports += 1
		name = self.get_string(blob)
		funcs, objs = unpack(">2I", blob[len(name) + 1:])
		if self.verbose:
			print "from %s import %d functions, %d objects" % (name, funcs, objs)
			if self.curr_pkg != None:
				print "finished importing from ", self.curr_pkg
		self.curr_pkg = name
		if funcs > 0:
			self.imports[name] = {}
		if objs > 0:
			self.objects[name] = {}
		
	def fimp(self, type, blob):
		assert self.curr_pkg != None
		name = self.get_string(blob)
		off = len(name) + 1
		count = unpack(">I", blob[off:off + 4])[0]
		off += 4
		if self.verbose:
			print "%s.%s is used %d times:" % (self.curr_pkg, name, count),
		
		pos = []
		i = count
		while i > 0:
			pos += unpack(">I", blob[off:off + 4])
			off += 4
			i -= 1
		if self.verbose:
			print pos
		self.imports[self.curr_pkg][name] = pos
		for p in pos:
			assert p not in self.calls
			if self.curr_pkg not in self.names:
				print "XXX", self.curr_pkg, "is not there??!?"
#			assert self.curr_pkg in self.names
			else:
				self.calls[p] = self.names[self.curr_pkg] + "." + name

	def oimp(self, type, blob):
		assert self.curr_pkg != None
		name = self.get_string(blob)
		off = len(name) + 1
		count = unpack(">I", blob[off:off + 4])[0]
		off += 4
		if self.verbose:
			print "Object %s.%s is used %d times:" % (self.curr_pkg, name, count),
		
		pos = []
		i = count
		while i > 0:
			pos += unpack(">I", blob[off:off + 4])
			off += 4
			i -= 1
		if self.verbose:
			print pos
		self.objects[self.curr_pkg][name] = pos
		for p in pos:
			assert p not in self.calls
			self.calls[p] = self.curr_pkg + "." + name
	
	def pkhd(self, type, blob):
		name = self.get_string(blob)
		version = unpack(">I", blob[len(name) + 1:])[0]
		print '// package : "%s" pog version: %d' % (name, version)
		print
		self.pkg_name = name
		assert version == 3

	def stab(self, type, blob):
		strings = unpack(">I", blob[:4])[0]
		off = 4
		if self.verbose:
			print strings, "strings"
		i = 0
		while off < len(blob):
			s = self.get_string(blob[off:])
			off += len(s)
			off += 1
			i += 1
			s = s.replace("\n", r'\n')
			if self.verbose:
				print "%d: \"%s\"" % (i, s)
			self.strings += [s]


if __name__ == "__main__":
	args = {
		'--verbose' 	: 'be verbose',
		'--veryverbose' : 'be very verbose',
		'--display=none'	: "either 'ansi' or 'html' - chooses how to colourise the disassembly output",
#		'--dontdisplay' : 'list of things to not display: disassasm, someops, allops',
		'--mode=decompile'		: "either 'disassemble', 'decompile', or 'both', defaults to 'decompile'",
	}

	flags = map(jgw_utils.finder, args.keys())
	opts = {}

	if (len(sys.argv) > 1):
		try:
			flags, leftovers = getopt.getopt(sys.argv[1:], '', flags)
		except getopt.GetoptError:
			jgw_utils.usage(args)
			sys.exit(-1)
		if len(leftovers) > 0:
			for o, a in flags:
				opts[o.lstrip('-')] = a
			
			for f in leftovers:
				pkg = PKG_info()
				if 'verbose' in opts:
					pkg.verbose = True

				if 'veryverbose' in opts:
					pkg.verbose = True
					pkg.veryverbose = True
					
				if 'dontdisplay' in opts:
					print opts['dontdisplay']
					raise RuntimeError
				
				if 'mode' in opts:
					pkg.mode = opts['mode']
				else:
					pkg.mode = 'decompile'

				if 'display' in opts:
					pkg.display = opts['display']
				else:
					pkg.display = 'none'
				
				if pkg.display == 'html':
					print '<PRE style="color: #00ff00; background-color: #000000">'
				print '// $Id: pkginfo.py,v 1.18 2008/06/01 18:31:29 jasper Exp $'
				print '//', f
				print '/*'
				pkg.load(f)
				if pkg.display == 'html':
					print '</PRE>'
	else:
		jgw_utils.usage(args)
