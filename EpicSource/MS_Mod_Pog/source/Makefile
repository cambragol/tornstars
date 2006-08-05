
#
#  Make file for constructing Epic: Middle States Main package.
#

RELEASE_NUMBER = 7_3_0


BASE_PATH= c:\Epic\EpicSource
CODE_PATH= $(BASE_PATH)\pog
MAIN_PATH= $(BASE_PATH)\MS_Mod_Pog
PS_INCLUDE_PATH= $(CODE_PATH)\include_ps

INCLUDE_PATH= $(CODE_PATH)\include
INCLUDE_PKG= $(CODE_PATH)\include_pkg
PACKAGE_PATH= $(MAIN_PATH)\packages

TEXT_PATH= $(BASE_PATH)\TEXT
HTML_PATH= $(BASE_PATH)\html
INI_PATH= $(BASE_PATH)\INI
IMAGE_PATH= $(BASE_PATH)\images
DEBUG_PATH= $(BASE_PATH)\debug

MODULE=MS_Mod_Pog
DEBUG_MODULE=EpicDebug
MOD_PATH=c:\iwar2\mods\$(MODULE)

RELEASE_PATH=c:\projects\epic\release\Epic


POG_COMPILER = c:\iwar2\bin\release\pc.exe

.SUFFIXES : .pkg .pog


# Inference rule for building and moving updated pog files.
{}.pog{packages}.pkg:
	$(POG_COMPILER) -i $(INCLUDE_PATH) -i $(PS_INCLUDE_PATH) -i $(INCLUDE_PKG) -hp $(INCLUDE_PKG) -pp $(PACKAGE_PATH) $(*B).pog
	copy $(PACKAGE_PATH)\$(*B).pkg $(MOD_PATH)\packages



clean: 
	erase $(PACKAGE_PATH)\*.pkg


##########################

##  Pog files

jcEpicShipPurGUI : packages\jcEpicShipPurGUI.pkg

jcEChangeIdGui : packages\jcEChangeIdGui.pkg
