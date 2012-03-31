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
        return pack(pstr, id, len(data), data, "\x00")    
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

if __name__ == "__main__":
    hexdump(make_chunk("FISH", "\xee"))
    hexdump(make_chunk("FISH", "\xee\xbb"))
    hexdump(make_chunk("FISH", "\xee\xbb\xaa"))
    hexdump(make_chunk("FISH", "\x00\xff\x00lkshdflkhfdglsjhfdg\x00"))
    hexdump(make_sub_chunk("FISH", "\x00\xff\x00lkshdflkhfdglsjhfdg\x00"))

