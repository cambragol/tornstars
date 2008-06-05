
map-tools Readme
----------------

eoc.py      			classes to read a .map file and vairous other eoc related bits
eocdata.py  			dumps of vairous enums 
hexdump.py  			ye olde traditional hexdump
dump-maps.py			dumps all the .map files it can find, not
				really needed now
tornstars-to-graphviz.py	converts the Tornstars cluster into dot

the dot format is used by a suite of programs called graphviz. Which i
thought shipped with cygwin, but don't seem to :(

You can get Windows binaries here:

http://www.graphviz.org/Download_windows.php

To create a png map:

./tornstars-to-graphviz.py| neato -s1.5  -Tpng -o clustermap.png

or svg:

./tornstars-to-graphviz.py| neato -Tsvg -o clustermap.svg

or PDF:

./tornstars-to-graphviz.py| neato -Gsize="9,10" -Grotate=90 -Tps | ps2pdf - clustermap.pdf

TODO
----

Integrate the .map reading stuff with the stuff from the .ini files.

Per-system maps.

slurp the import and export tables for each station

Using the above calculate the nearest places stations can get there imports
and exports from.

Build maps of trade routes.
