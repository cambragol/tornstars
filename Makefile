#
#  TornStars Master Build File
#  Add in any extra sub-build scripts you need.
#

SOURCE_PATH=EpicSource
MODULE=MS_Mod_Main
MODULE_PATH= $(SOURCE_PATH)/$(MODULE)
PACKAGE_PATH= $(MODULE_PATH)/packages
MOD_PATH= $(EPIC_INSTALL)/mods/$(MODULE)

.PHONY: all clean

all:
	$(MAKE) -C $(PACKAGE_PATH)

clean:
	$(MAKE) -C $(PACKAGE_PATH) clean


