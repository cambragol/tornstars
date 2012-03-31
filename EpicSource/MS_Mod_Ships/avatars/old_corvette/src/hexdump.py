#!/usr/local/bin/python
#

def hexdump(str, prepend = ""):
	x = y = count = 0
	indent = 16
	out = ''

	while (count < len(str)):
		out = "%s%04x : " % (prepend, count)
		
		x = 0
		while x < indent:
			if (x + count + 1 ) > len(str):
				break
			out = out + "%02x " % (ord(str[x + count]))
			if (x + count + 1) >= len(str):
				x += 1
				y = 0
				for y in range(indent - x):
					out = out + '   '
				break

			x += 1
		
		out = out + ": "
		
		x = 0
		while x < indent:
			if (x + count + 1) > len(str):
				break
			if ord(str[x + count]) >= 32 and ord(str[x + count]) <= 126:
				out = out + str[x + count]
			elif ord(str[x + count]) == 0:
				out = out + ' '
			else:
				out = out + '.'
			
			if (x + count + 1) >= len(str):
				x += 1
				y = 0
				while y < (indent - x):
					out += ' '
					y += 1
			
			x += 1
			
		print out
		count += indent
			
	print



if __name__ == "__main__":
	hexdump("lksdhfkahsdflakhjsdflahfalsdfakhfdw98345\000\001\006\077$%$^%$%", "%% ")
	