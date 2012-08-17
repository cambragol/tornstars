#!/usr/bin/env python
#
# $Id: lwo2-info.py,v 1.5 2008/06/11 00:16:17 jasper Exp $
#
# A class to load LWO2 format IFF files.
#

import chunk
import sys, os, os.path
from hexdump import hexdump
from struct import unpack
from IFF import IFF
import lwo2

class LWO2_info(lwo2.LWO2Reader):
	def __init__(self):
		lwo2.LWO2Reader.__init__(self, verbose=True, nodata=True)

if __name__ == "__main__":
	if (len(sys.argv) > 1):
		for f in sys.argv[1:]:
			lwo = LWO2_info()
			lwo.load(f)
	else:
		print "%s: <file.lwo>" % (sys.argv[0])
