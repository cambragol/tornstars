#!/usr/local/bin/python
#
# $Id: saveiff.py,v 1.4 2007/10/03 01:54:32 jasper Exp $
#
# functions to write iff chunks and subchunks
#
# should be in IFF.py
#

from struct import pack
from hexdump import hexdump

def make_chunk(id, data):
    assert len(id) == 4, "id should be 4 characters long"
    if len(data) % 2 == 1:
        pstr = ">4sI" + str(len(data)) + "sc"
        # Wierd, if you pad a block, you need to add one to the length,
        # but if so how can you tell the difference between a block of (e.g.)
        # length 4 that was padded and one of length 4 that wasn't?
        # guess this is why some blocks have a length as there 1st arg...
        #
        # XXX above is a bug, the length should stay the same
        # 
        # or perhaps LWO2 etc don't need padding?
        #
        return pack(pstr, id, len(data), data, "\x00")
    else:
        pstr = ">4sI" + str(len(data)) + "s"
        return pack(pstr, id, len(data), data)

def make_sub_chunk(id, data):
    assert len(id) == 4, "id wrong length"
    assert len(data) < 65535, "subchunk too long"
    pstr = ">4sH" + str(len(data)) + "s"
    return pack(pstr, id, len(data), data)

# null terminated string padded to 16 bit boundry
def make_string(s):
    s += "\x00"
    if len(s) % 2 == 1:
        pstr = str(len(s)) + "sc"
        return pack(pstr, s, "\x00")    
    else:
        pstr = str(len(s)) + "s"
        return pack(pstr, s)

if __name__ == "__main__":
    hexdump(make_chunk("FISH", "\xee"))
    hexdump(make_chunk("FISH", "\xee\xbb"))
    hexdump(make_chunk("FISH", "\xee\xbb\xaa"))
    hexdump(make_chunk("FISH", "\x00\xff\x00lkshdflkhfdglsjhfdg\x00"))
    hexdump(make_sub_chunk("FISH", "\x00\xff\x00lkshdflkhfdglsjhfdg\x00"))
    file = 'QUAK' + make_chunk("FISH", make_string("\x00\xff\x00lkshdflkhfdglsjhfdg"))
    file += make_chunk("CaT ", '123')
    file += make_chunk("BAG ", '12')
    file += make_chunk("Hat ", '123123123')
    file = make_chunk('FORM', file)
    hexdump(file)
    
    import IFF
    pqr = IFF.IFF()
    pqr.load_string(file)
    del pqr

