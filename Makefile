#
#  Make file for constructing Epic: Middle States Master Build File
#

RELEASE_NUMBER = 10_17_0


BASE_PATH= f:/eoc/tornstars/trunk/EpicSource
CODE_PATH= $(BASE_PATH)/pog
MAIN_PATH= $(BASE_PATH)/MS_Mod_Main
PS_INCLUDE_PATH= $(CODE_PATH)/include_ps

INCLUDE_PATH= $(CODE_PATH)/include
INCLUDE_PKG= $(CODE_PATH)/include_pkg
PACKAGE_PATH= $(MAIN_PATH)/packages

TEXT_PATH= $(BASE_PATH)/TEXT
HTML_PATH= $(BASE_PATH)/html
INI_PATH= $(BASE_PATH)/INI
IMAGE_PATH= $(BASE_PATH)/images
DEBUG_PATH= $(BASE_PATH)/debug

MODULE=MS_Mod_Main
DEBUG_MODULE=EpicDebug
MOD_PATH=f:/eoc_tornstars/mods/$(MODULE)

RELEASE_PATH=f:/projects/epic/release/Epic


POG_COMPILER = f:/eoc_tornstars/bin/release/pc.exe

.PHONY: all clean

.SUFFIXES:
.SUFFIXES: .pkg .pog

#vpath %.pkg ./packages
vpath %.pog ../source

# Pattern rule
%.pkg: %.pog
	$(POG_COMPILER) -q -i $(INCLUDE_PATH) -i $(PS_INCLUDE_PATH) -i $(INCLUDE_PKG) -hp $(INCLUDE_PKG) -pp $(PACKAGE_PATH) $<
#	copy $(PACKAGE_PATH)\$(*B).pkg $(MOD_PATH)\packages


all:


clean:
	rm -v *.pkg


