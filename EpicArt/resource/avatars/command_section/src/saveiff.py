#!/usr/local/bin/python
#
# $Id: saveiff.py,v 1.2 2006/04/26 18:41:55 meep-cvs Exp $
#
# functions to write iff chunks and subchunks
#

from struct import pack
from hexdump import hexdump

def make_chunk(id, data):
    if len(id) != 4:
        raise "id wrong length"
    if len(data) % 2 == 1:
        pstr = ">4sI" + str(len(data)) + "sc"
        # Wierd, if you pad a block, you need to add one to the length,
        # but if so how can you tell the difference between a block of (e.g.)
        # length 4 that was padded and one of length 4 that wasn't?
        # guess this is why some blocks have a length as there 1st arg...
        return pack(pstr, id, len(data) + 1, data, "\x00")
    else:
        pstr = ">4sI" + str(len(data)) + "s"
        return pack(pstr, id, len(data), data)

def make_sub_chunk(id, data):
    if len(id) != 4:
        raise "id wrong length"
    if len(data) > 65535:
        raise "subchunk too long"
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

