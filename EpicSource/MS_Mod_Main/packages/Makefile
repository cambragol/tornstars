#
#  Make file for constructing Epic: Middle States Main package.
#

# last modified 2012-May-23 SRC

# Several environment variables need to be defined for this make script to run.
# They depend on local install locations
# define EPIC_BASE as the path to the start of the source working directory
# define EPIC_INSTALL as the path to the iwar2 install directory

MODULE=MS_Mod_Main

SOURCE_PATH=$(EPIC_BASE)/EpicSource

CODE_PATH= $(SOURCE_PATH)/pog
MODULE_PATH= $(SOURCE_PATH)/$(MODULE)

PS_INCLUDE_PATH= $(CODE_PATH)/include_ps
INCLUDE_PATH= $(CODE_PATH)/include
INCLUDE_PKG= $(CODE_PATH)/include_pkg

PACKAGE_PATH= $(MODULE_PATH)/packages

DEPEND_TOOL= $(SOURCE_PATH)/python/pogmkdep/pogmkdep.py
DEPEND=pogdepend

MOD_PATH= $(EPIC_INSTALL)/mods/$(MODULE)

POG_COMPILER = $(EPIC_INSTALL)/bin/release/pc.exe

FLAGS = --quiet

.PHONY: all clean clean-headers depends

.SUFFIXES:
.SUFFIXES: .pkg .pog .h

#vpath %.pkg ../packages
vpath %.h ../../pog/include
vpath %.h ../../pog/include_pkg
vpath %.h ../../pog/include_ps
vpath %.pog ../source

# Pattern rule
#
# On a case sensitive filesystem this won't work
#
# Instead pogmkdep.py generates a per-target rule
#
#%.pkg: %.pog
#	$(POG_COMPILER) -q -i $(INCLUDE_PATH) -i $(PS_INCLUDE_PATH) -i $(INCLUDE_PKG) -hp $(INCLUDE_PKG) -pp $(PACKAGE_PATH) $<
#	cp $(PACKAGE_PATH)/$@ $(MOD_PATH)/packages
	
# copy the target to the iwar mod directory (to save a manual copy for the programmer which keeps all files up to date).

#
# Package list for TornStars
# MUST BE KEPT UP TO DATE!
#

# Non compilng and suspect targets
#	tECommEvent.pkg \
#	tsShipBack.pkg \
#	tsStation_t.pkg \
#	tsCargoShip.pkg \
#	ts_StationEvent.pkg \
#	tEpicFaction_t.pkg \
#	tLProduction_t.pkg \


PACKAGES = usPOGexperiments.pkg \
        iShipConfigurationUtil.pkg \
        iINIFileUtil.pkg \
        iObjectPropertiesUtil.pkg \
        iStringUtil.pkg \
	ECargoTypes.pkg \
	UniGUI.pkg \
	UniGUIBase.pkg \
	UniGUIMisc.pkg \
	tsArray.pkg \
	tsBaseNet.pkg \
	tsChangeIdGui.pkg \
	tsPlayerShipPurGui.pkg \
	tsClaimGui.pkg \
	tsDistance.pkg \
	tsFaction.pkg \
	tsPlayerFleetGui.pkg \
	tsCapsuleJump.pkg \
	tsReferenceGui.pkg \
	tsShipCreation.pkg \
	tsStarSystem.pkg \
	tsTradeBuy.pkg \
	tsTradeSell.pkg \
	tsLoadoutGui.pkg \
	tsEquipBuy.pkg \
	tsEquipSell.pkg \
	tsDescribeINI.pkg \
	tsEconomy.pkg \
	tsEconUtil.pkg \
	tsShipComms.pkg \
	tsFactionGui.pkg \
	tsShip.pkg \
	tsShipDeath.pkg \
	tsShipEscort.pkg \
	tsGui.pkg \
	tsNavGui.pkg \
	tsMoney.pkg \
	tsExitGui.pkg \
	tsFormation.pkg \
	tsLCenter.pkg \
	tsLFleet.pkg \
	tsLInventory.pkg \
	tsLProduction.pkg \
	tsLRoot.pkg \
	tsLTrade.pkg \
	tsMail.pkg \
	tsMegaTrucking.pkg \
	tMultimod.pkg \
	tsMusic.pkg \
	tsMusicChange.pkg \
	tsNewsNet.pkg \
	tsOptionsGui.pkg \
	tsStartGui.pkg \
	tsPcAsteroidBelt.pkg \
	tsPcCargoShip.pkg \
	tsPcConstructionShip.pkg \
	tsPcCustomsToll.pkg \
	tsPcEmbezzleOp.pkg \
	tsPcTankerOp.pkg \
	tsPcFenceShip.pkg \
	tsPcGuards.pkg \
	tsPcHiredShip.pkg \
	tsPcMerc.pkg \
	tsPcFreeTrader.pkg \
	tsPcFreeMiner.pkg \
	tsPcFreeTanker.pkg \
	tsPcFreeScience.pkg \
	tsPcFreeMerchant.pkg \
	tsPcOwner.pkg \
	tsPcPirateToll.pkg \
	tsPcPodScrapper.pkg \
	tsPcRumorSeller.pkg \
	tsPcTankerShip.pkg \
	tsPcWeaponSeller.pkg \
	tsPcWreckBelt.pkg \
	tsPodUtil.pkg \
	tsPogClass.pkg \
	tsLocationInit.pkg \
	tsPlayerWatch.pkg \
	tsReputationUpdate.pkg \
	tsReputationWatch.pkg \
	tsSaveGui.pkg \
	tsShipMail.pkg \
	tsShipName.pkg \
	tsShipHire.pkg \
	tsSpewerOps.pkg \
	tsStation.pkg \
	tsStationAi.pkg \
	tsStationEnv.pkg \
	tsStationFilter.pkg \
	tsStationRules.pkg \
	tsStationSave.pkg \
	tsTime.pkg \
	tsTimeAdvance.pkg \
	tsFleetOp.pkg \
	tsFleetOpFilter.pkg \
	tsFleetOpGui.pkg \
	tsFleetOpPhysical.pkg \
	tsFleetOpSave.pkg \
	tsViewDock.pkg \
	tsCrewSpeak.pkg \
	tsCull.pkg \
	tsDebug.pkg \
	tsDebugGui.pkg \
	tsDistress.pkg \
	tsEvent.pkg \
	tsFleetOpCombat.pkg \
	tsFleetOpUpdate.pkg \
	tsFleetOpCall.pkg \
	tsFoConstruction.pkg \
	tsFoCustoms.pkg \
	tsFoEmbezzle.pkg \
	tsFoTanker.pkg \
	tsFoTrade.pkg \
	tsFoFleetAttack.pkg \
	tsFoFleetDefense.pkg \
	tsFoPatrol.pkg \
	tsFoProtection.pkg \
	tsFoRaider.pkg \
	tsFoThugs.pkg \
	tsFoArmsDealer.pkg \
	tsFoMerc.pkg \
	tsFoFreeTrader.pkg \
	tsFoFreeMiner.pkg \
	tsFoFreeTanker.pkg \
	tsFoFreeScience.pkg \
	tsFoFreeMerchant.pkg \
	tsPilotSetup.pkg \
	tsPlayerDeath.pkg \
	tsPlayerSave.pkg \
	tsPlayerFleet.pkg \
	tsPlayerFleetUpkeep.pkg \
	tsPosition.pkg \
	tsShipSave.pkg \
	tsWingComm.pkg \
	tsWingman.pkg \
	tsWingmanDeath.pkg \
	tsString.pkg \
	tsLpointFindGui.pkg \
	zTestCapsule.pkg \
	zTestCargo.pkg \
	zTestCode.pkg \
	zTestExp.pkg \
	zTestFacShip.pkg \
	zTestObject.pkg \
	tsSystemDamage.pkg \
	tssdGUI.pkg \
<<<<<<< .mine
	usPOGexperiments.pkg \
	iStringUtil.pkg \
	iShipConfigurationUtil.pkg \
	iObjectPropertiesUtil.pkg \
	iINIFileUtil.pkg \
	tsMain.pkg
=======
	tsMain.pkg 
>>>>>>> .r835

#
# Convert the list of targets to lowercase.
#
PACKAGESLC = $(shell echo $(PACKAGES) | tr '[[:upper:]]' '[[:lower:]]' )

all: $(PACKAGESLC)

clean:
	rm -v *.pkg 

depends:
	$(DEPEND_TOOL) > $(PACKAGE_PATH)/pogdepend

#
# The compiler dumps generated header files in here
# you can check to see if there are any changes that
# need to be commited with:
#
# diff -urx .svn ../../pog/include_pkg/ ../../pog/include_tmp/
#
# Unfortunatly the $Header$ stuff in the files in include_pkg
# gets updated by svn so checking for differences is tricky to
# do automaticly
#
#clean-headers:
#	rm -vf $(CODE_PATH)/include_tmp/*.h


include $(DEPEND)

