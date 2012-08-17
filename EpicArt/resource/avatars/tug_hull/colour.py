#!/usr/bin/env python 
#
# muck about with colourising text
#
# I'm sure i've written this before and lost it
# for some reason this annoys me intensly
#
#

class CM:
  def __init__(self, type):
    self.cols = {
      'none' : {
      },
      'ansi' : {
        'black'   : '30',
        'red'     : '31',
        'green'   : '32',
        'yellow'  : '33',
        'blue'    : '34',
        'magenta' : '35',
        'cyan'    : '36',
        'white'   : '37',
        
        'start'     : '\033[',
        'stop'	    : 'm',
        'reset'     : '\033[0m',
        
        'bold'      : '1',
        'reverse'   : '7',
        'underline' : '4',
      
        'blackbg' : '40',
        'redbg' : '41',
        'greenbg' : '42',
        'yellowbg' : '43',
        'bluebg' : '44',
        'magentabg' : '45',
        'cyanbg' : '46',
        'whitebg' : '47',

      },
      'html' : {
        'black'   : 'color: #000000',
        'white'   : 'color: #ffffff',

        'red'     : 'color: #ff0000',
        'green'   : 'color: #00ff00',
        'blue'    : 'color: #0000ff',

        'yellow'  : 'color: #ffff00',
        'magenta' : 'color: #ff00ff',
        'cyan'    : 'color: #00ffff',
        
        'bold'      : 'font-weight: bold',
#        'reverse'   : '7',
        'underline' : 'text-decoration: underline',
      
#        'blackbg' : '40',
#        'redbg' : '41',
#        'greenbg' : '42',
#        'yellowbg' : '43',
#        'bluebg' : '44',
#        'magentabg' : '45',
#        'cyanbg' : '46',
#        'whitebg' : '47',

      }
    }
    
    self.printers = {
      'none' : lambda x, s : s,
      'ansi' : self.ansi,
      'html' : self.html
    }
    
    if type not in self.cols or type not in self.printers:
      # yes, i'm lazy
      raise RuntimeError
    
    self.type = type

  def ansi(self, cols, s):
    for c in cols:
      if c not in self.cols[self.type]:
        return s

    o = '\033['
    cols = map(lambda x: self.cols[self.type][x], cols)
    o += ';'.join(cols)
    o += 'm' + s
    o += '\033[0m'
    return o

  def html(self, cols, s):
    oc = []
    for c in cols:
      if c in self.cols[self.type]:
        oc += [c]
    cols = oc

    cols = map(lambda x: self.cols[self.type][x], cols)

    c = ';'.join(cols)
    c += ';'

    o = '<font style=\"%s\">' % (c)
#    cols = map(lambda x: self.cols[self.type][x], cols)
#    o += ';'.join(cols)
    o += s
    o += '</font>'
    return o

  def printcolour(self, cols, s):
    return self.printers[self.type](cols, s)
    
  def colmaker(self, c):
    return lambda x : self.printcolour(c, x)

if __name__ == "__main__":
  fish = CM('ansi')
  red = fish.colmaker(['red', 'bold', 'bluebg', 'underline'])
  green = fish.colmaker(['green', 'redbg', 'bold'])
  blue = fish.colmaker(['blue'])
  print red('fish')
  print green('fish')
  print blue('fish')

  for i in range(16, 255 - (16), 6):
#    print '\033[38;5;%dmXXX\033[0;0m' % (i),
      o = ''
      for j in range(0, 6):
          o += '\033[48;5;%dmXXX\033[0;0m' % (i + j)
      print o
  
  fish = CM('html')
  red = fish.colmaker(['red', 'bold', 'bluebg', 'underline'])
  green = fish.colmaker(['green', 'redbg', 'bold'])
  blue = fish.colmaker(['blue'])
  print red('fish')
  print green('fish')
  print blue('fish')
  
#  print '\033[34;43mfish\033[0;0m'
