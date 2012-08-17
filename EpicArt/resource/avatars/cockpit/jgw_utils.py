#!/usr/local/bin/python
#
# $Id: jgw_utils.py,v 1.2 2006/04/26 18:41:55 meep-cvs Exp $
#
# some functions to make usage() pretty
#

import sys
import textwrap

def usage(flags):
	print "%s : " % (sys.argv[0])

	# find the length of the Longest Flag
	lf = 0
	for f in flags.keys():
		if len(f) > lf:
			lf = len(f)

	formatstr = "%-" + str(lf) + "s - "

	# XXX use curses etc to get actual columns.
	wrapper = textwrap.TextWrapper(width = 75)
	
	for f in flags.keys():
		wrapper.initial_indent = formatstr % (f)
		wrapper.subsequent_indent = ' ' * (3 + lf)
		print wrapper.fill(flags[f])		

def finder(s):
	s = s.lstrip('-')
	if s.rfind('=') > 0:
		return s[0:s.rfind('=') + 1]
	else:
		return s


if __name__ == "__main__":
	flags = {
		"--fish"		: "print more fish",
		"--verylong"	: "a very long info line, a very long info line, a very long info line, a very long info line, a very long info line, a very long info line, a very long info line,a very long info line, a very long info line, a very long info line.",
		"--quack=fish"	: "foo, this is info about foo, if you pass fish as an arg to foo, bad things may happen"
		}
	usage(flags)
	
