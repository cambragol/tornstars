#
#  Make file for constructing Epic: Middle States Main package.
#


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


MOD_PATH= $(EPIC_INSTALL)/mods/$(MODULE)

POG_COMPILER = $(EPIC_INSTALL)/bin/release/pc.exe

.PHONY: all clean

#.SUFFIXES:
.SUFFIXES: .pkg .pog

#vpath %.pkg ../packages
vpath %.h ../../pog/include
vpath %.h ../../pog/include_pkg
vpath %.h ../../pog/include_ps
vpath %.pog ../source

# Pattern rule
%.pkg: %.pog
	$(POG_COMPILER) -q -i $(INCLUDE_PATH) -i $(PS_INCLUDE_PATH) -i $(INCLUDE_PKG) -hp $(INCLUDE_PKG) -pp $(PACKAGE_PATH) $<
	cp $(PACKAGE_PATH)/$@ $(MOD_PATH)/packages
# copy the target to the iwar mod directory (to save a manual copy for the programmer which keeps all files up to date).


#
# Package list for TornStars
# MUST BE KEPT UP TO DATE!
#

# Non compilng and suspect targets
#	tECommEvent.pkg \
#	tEpicFleetBack.pkg \
#	tStation_t.pkg \
#	tsCargoShip.pkg \
#	ts_StationEvent.pkg \
#	tEpicFaction_t.pkg \
#	tLProduction_t.pkg \


PACKAGES = ECargoTypes.pkg \
	ExitCrashTest.pkg \
	UniGUI.pkg \
	UniGUIBase.pkg \
	UniGUIMisc.pkg \
	jcEChangeIdGui.pkg \
	jcEpicShipPurGUI.pkg \
	jGiftCargo.pkg \
	tDistance.pkg \
	tEAutoWatch.pkg \
	tEFaction.pkg \
	tEFleetGui.pkg \
	tEJump.pkg \
	tELpointFind.pkg \
	tEPlayerOrders.pkg \
	tEPlayerWatch.pkg \
	tEReferenceGui.pkg \
	tEShipCreation.pkg \
	tESysSetup.pkg \
	tETradeBuy.pkg \
	tETradeSell.pkg \
	tEconCategory.pkg \
	tEconSmall.pkg \
	tEconUtil.pkg \
	tEpicComms.pkg \
	tEpicFacGui.pkg \
	tEpicFaction.pkg \
	tEpicFleet.pkg \
	tEpicFleetUpkeep.pkg \
	tEpicGui.pkg \
	tEpicLFPlus.pkg \
	tEpicMain.pkg \
	tEpicMoney.pkg \
	tEpicTrade.pkg \
	tExitGui.pkg \
	tFormation.pkg \
	tJumpSim.pkg \
	tLCenter.pkg \
	tLFleet.pkg \
	tLInventory.pkg \
	tLProduction.pkg \
	tLRoot.pkg \
	tLTrade.pkg \
	tLocationInit.pkg \
	tLock.pkg \
	tMail.pkg \
	tMegaTrucking.pkg \
	tMultimod.pkg \
	tMusic.pkg \
	tMusicChange.pkg \
	tMusicGui.pkg \
	tNewsNet.pkg \
	tOptionsGui.pkg \
	tStartGui.pkg \
	tPcAsteroidBelt.pkg \
	tPcCargoShip.pkg \
	tPcConstructionShip.pkg \
	tPcCustomsToll.pkg \
	tPcEmbezzleOp.pkg \
	tPcFenceShip.pkg \
	tPcGuards.pkg \
	tPcHiredShip.pkg \
	tPcOwner.pkg \
	tPcPirateToll.pkg \
	tPcPodScrapper.pkg \
	tPcRumorSeller.pkg \
	tPcTankerShip.pkg \
	tPcWeaponSeller.pkg \
	tPcWreckBelt.pkg \
	tPodUtil.pkg \
	tPogClass.pkg \
	tRepUpdate.pkg \
	tRepWatch.pkg \
	tSaveGui.pkg \
	tShipMail.pkg \
	tShipName.pkg \
	tSpewerOps.pkg \
	tStation.pkg \
	tStationEnv.pkg \
	tStationFilter.pkg \
	tStationRules.pkg \
	tStationSave.pkg \
	tSysInventory.pkg \
	tTime.pkg \
	tTimeAdvance.pkg \
	tUnderOp.pkg \
	tUnderOpFilter.pkg \
	tUnderOpGui.pkg \
	tUnderOpSave.pkg \
	tViewDock.pkg \
	tWingComm.pkg \
	tsCrewSpeak.pkg \
	tsCull.pkg \
	tsDebug.pkg \
	tsDistress.pkg \
	tsEvent.pkg \
	tsFleetOpCombat.pkg \
	tsFleetOpUpdate.pkg \
	tsFleetOperation.pkg \
	tsFoCustoms.pkg \
	tsFoEmbezzle.pkg \
	tsFoFleetAttack.pkg \
	tsFoFleetDefense.pkg \
	tsFoPatrol.pkg \
	tsFoProtection.pkg \
	tsFoRaider.pkg \
	tsFoThugs.pkg \
	tsPilotSetup.pkg \
	uString.pkg \
	zHeadMove.pkg \
	zTestCapsule.pkg \
	zTestCargo.pkg \
	zTestCode.pkg \
	zTestExp.pkg \
	zTestFacShip.pkg \
	zTestObject.pkg \
	zTestSwap.pkg



all: $(PACKAGES)


clean:
	rm -v *.pkg


#
# Dependency rules.
# MUST BE UPDATED FOR NEW PACKAGES AND IMPORT CHANGES!
#
ECargoTypes.pkg : ECargoTypes.pog
ExitCrashTest.pkg : ExitCrashTest.pog
UniGUI.pkg : UniGUI.pog
UniGUIBase.pkg : UniGUIBase.pog
UniGUIMisc.pkg : UniGUIMisc.pog
jGiftCargo.pkg : jGiftCargo.pog tEconUtil.h tEpicMoney.h


jcEChangeIdGui.pkg : jcEChangeIdGui.pog UniGUI.h tEpicGui.h tSaveGui.h tEconUtil.h tEpicFleet.h tEpicMoney.h tEFaction.h
jcEpicShipPurGUI.pkg : jcEpicShipPurGUI.pog UniGUI.h tEFaction.h tEpicGui.h tSaveGui.h tEpicMoney.h


tDistance.pkg : tDistance.pog
tEAutoWatch.pkg : tEAutoWatch.pog tTime.h tLCenter.h tEFaction.h tEpicFleet.h tFormation.h tEpicFleetUpkeep.h tMusic.h tRepWatch.h tLocationInit.h

#tECommEvent.pkg : tECommEvent.pog

tEFaction.pkg : tEFaction.pog
tEFleetGui.pkg : tEFleetGui.pog tEpicGui.h tLProduction.h tEpicMoney.h tEpicFleet.h tEpicFleetUpkeep.h tEconUtil.h uString.h
tEJump.pkg : tEJump.pog tEpicGui.h tEpicFleet.h tTime.h
tELpointFind.pkg : tELpointFind.pog tEpicGui.h 
tEPlayerOrders.pkg : tEPlayerOrders.pog tEpicFleet.h tFormation.h tPodUtil.h tEFaction.h tStation.h tLProduction.h tMegaTrucking.h
tEPlayerWatch.pkg : tEPlayerWatch.pog tTime.h tLCenter.h tEFaction.h tEpicFleet.h tFormation.h tEpicFleetUpkeep.h tMusic.h tRepWatch.h tLocationInit.h tEJump.h
tEReferenceGui.pkg : tEReferenceGui.pog tEpicGui.h tLProduction.h tEconSmall.h tEconUtil.h tEpicMoney.h tPodUtil.h uString.h
tEShipCreation.pkg : tEShipCreation.pog tEFaction.h
tESysSetup.pkg : tESysSetup.pog tEFaction.h tStation.h tLProduction.h tEJump.h
tETradeBuy.pkg : tETradeBuy.pog tStation.h tEpicGui.h tEFaction.h tLProduction.h tLInventory.h tLTrade.h tEconSmall.h tEconUtil.h tEpicMoney.h tPodUtil.h uString.h tSpewerOps.h
tETradeSell.pkg : tETradeSell.pog tSpewerOps.h tMegaTrucking.h tStation.h tEpicGui.h tEFaction.h tLProduction.h tEconSmall.h tEconUtil.h tEpicMoney.h tPodUtil.h tLTrade.h uString.h
tEconCategory.pkg : tEconCategory.pog tEpicGui.h tUnderOp.h
tEconSmall.pkg : tEconSmall.pog tEconUtil.h tLProduction.h tLTrade.h tEFaction.h ECargoTypes.h uString.h tStation.h
tEconUtil.pkg : tEconUtil.pog
tEpicComms.pkg : tEpicComms.pog
tEpicFacGui.pkg : tEpicFacGui.pog tEFaction.h tEpicGui.h tEpicMoney.h
tEpicFaction.pkg : tEpicFaction.pog tLRoot.h tLProduction.h tLFleet.h

#tEpicFaction_t.pkg : tEpicFaction_t.pog tEpicFaction.h

tEpicFleet.pkg : tEpicFleet.pog tEconUtil.h tPodUtil.h tEpicComms.h tFormation.h tEFaction.h tMegaTrucking.h

#tEpicFleetBack.pkg : tEpicFleetBack.pog tPodUtil.h tEpicComms.h

tEpicFleetUpkeep.pkg : tEpicFleetUpkeep.pog tStation.h tEFaction.h tEpicFleet.h tEpicMoney.h tLProduction.h tLInventory.h tEconUtil.h tEconSmall.h tPodUtil.h tShipMail.h
tEpicGui.pkg : tEpicGui.pog
tEpicLFPlus.pkg : tEpicLFPlus.pog tStation.h tEpicGui.h tEconUtil.h tLProduction.h tLFleet.h tUnderOp.h tUnderOpFilter.h tESysSetup.h tEJump.h 
tEpicMain.pkg : tEpicMain.pog tTime.h tDistance.h tMultimod.h UniGUI.h UniGUIBase.h tEpicLFPlus.h tEFaction.h tEpicGui.h tEpicFleet.h tDistance.h jGiftCargo.h tWingComm.h tEPlayerWatch.h tStationEnv.h tEpicComms.h tEpicFleetUpkeep.h tUnderOp.h tUnderOpSave.h tLInventory.h tEconSmall.h tETradeBuy.h tETradeSell.h tEFleetGui.h tExitGui.h tStationSave.h tESysSetup.h tMusic.h tMail.h tNewsNet.h tShipMail.h tViewDock.h tEJump.h  tELpointFind.h tStationRules.h tsFleetOpUpdate.h tsCrewSpeak.h tRepUpdate.h tOptionsGui.h tStartGui.h
tEpicMoney.pkg : tEpicMoney.pog

#ECargoScript.h 

tEpicTrade.pkg : tEpicTrade.pog UniGUI.h ECargoTypes.h tEpicGui.h tEconUtil.h tEconSmall.h tPodUtil.h tEpicFleet.h

tExitGui.pkg : tExitGui.pog UniGUI.h tEpicGui.h tLProduction.h tEconSmall.h tEconUtil.h tEpicMoney.h tPodUtil.h uString.h
tFormation.pkg : tFormation.pog
tJumpSim.pkg : tJumpSim.pog tEpicGui.h UniGUI.h
tLCenter.pkg : tLCenter.pog tLRoot.h
tLFleet.pkg : tLFleet.pog tLRoot.h
tLInventory.pkg : tLInventory.pog tTime.h tLRoot.h tEconUtil.h tStation.h
tLProduction.pkg : tLProduction.pog tLRoot.h

#tLProduction_t.pkg : tLProduction_t.pog tEpicFaction.h tLRoot.h tLProduction.h

tLRoot.pkg : tLRoot.pog
tLTrade.pkg : tLTrade.pog tLRoot.h
tLocationInit.pkg : tLocationInit.pog tEconUtil.h tStation.h tUnderOp.h tLCenter.h tLProduction.h tStationEnv.h tEpicFleetUpkeep.h
tLock.pkg : tLock.pog
tMail.pkg : tMail.pog
tMegaTrucking.pkg : tMegaTrucking.pog
tMultimod.pkg : tMultimod.pog
tMusic.pkg : tMusic.pog uString.h tStation.h tLProduction.h
tMusicChange.pkg : tMusicChange.pog tMusic.h tLProduction.h
tMusicGui.pkg : tMusicGui.pog tMusic.h tEpicGui.h
tNewsNet.pkg : tNewsNet.pog UniGUI.h tTime.h tMail.h
tOptionsGui.pkg : tOptionsGui.pog UniGUI.h tEpicGui.h
tStartGui.pkg : tStartGui.pog UniGUI.h tEpicGui.h
tPcAsteroidBelt.pkg : tPcAsteroidBelt.pog tsCull.h tLCenter.h
tPcCargoShip.pkg : tPcCargoShip.pog tEconUtil.h tEconSmall.h tStation.h tStationFilter.h tETradeBuy.h tPogClass.h tLRoot.h tLTrade.h tLProduction.h tEpicMoney.h tTime.h tEFaction.h tEpicFleet.h tPodUtil.h tSpewerOps.h tsPilotSetup.h tEShipCreation.h tShipName.h uString.h
tPcConstructionShip.pkg : tPcConstructionShip.pog tEpicComms.h tEpicFleet.h tLRoot.h tLCenter.h tLTrade.h tEFaction.h tETradeSell.h tEpicMoney.h tShipName.h tPcOwner.h tsCull.h
tPcCustomsToll.pkg : tPcCustomsToll.pog tEShipCreation.h tPodUtil.h tEpicComms.h tEpicFleet.h tEFaction.h tEpicMoney.h tShipName.h tLCenter.h tLFleet.h tEconSmall.h tPcOwner.h tsPilotSetup.h
tPcEmbezzleOp.pkg : tPcEmbezzleOp.pog tEpicComms.h tEpicFleet.h tLRoot.h tLTrade.h tEFaction.h tETradeSell.h tEpicMoney.h tShipName.h tPcOwner.h tLProduction.h tLCenter.h tUnderOp.h tDistance.h tEShipCreation.h tLFleet.h tsPilotSetup.h tStationFilter.h tDistance.h tEJump.h tsCull.h
tPcFenceShip.pkg : tPcFenceShip.pog tEpicComms.h tEpicFleet.h tLRoot.h tLTrade.h tEFaction.h tETradeSell.h tEpicMoney.h tShipName.h tPcOwner.h tLProduction.h tUnderOp.h tDistance.h tEShipCreation.h tLFleet.h tsPilotSetup.h tStationFilter.h tDistance.h tEJump.h tsCull.h
tPcGuards.pkg : tPcGuards.pog tPodUtil.h tEpicComms.h tEpicFleet.h tEFaction.h tEpicMoney.h tShipName.h tLCenter.h tLFleet.h tEShipCreation.h tsPilotSetup.h tEJump.h tDistance.h tUnderOp.h uString.h tsEvent.h tsDistress.h tPcOwner.h
tPcHiredShip.pkg : tPcHiredShip.pog tEpicComms.h tEpicFleet.h tEFaction.h tEpicMoney.h tShipName.h tPcOwner.h tsCull.h
tPcOwner.pkg : tPcOwner.pog
tPcPirateToll.pkg : tPcPirateToll.pog tEShipCreation.h tPodUtil.h tEpicComms.h tEpicFleet.h tEFaction.h tEpicMoney.h tShipName.h tLCenter.h tLFleet.h tEconSmall.h tPcOwner.h tsPilotSetup.h
tPcPodScrapper.pkg : tPcPodScrapper.pog tPodUtil.h tEpicComms.h tEpicFleet.h tEFaction.h tEpicMoney.h tShipName.h tsCull.h
tPcRumorSeller.pkg : tPcRumorSeller.pog tTime.h tEconUtil.h tStationFilter.h tUnderOp.h tUnderOpFilter.h tEpicComms.h tEpicFleet.h tEFaction.h tEpicMoney.h tShipName.h tLCenter.h tLProduction.h tsCull.h
tPcTankerShip.pkg : tPcTankerShip.pog tEpicComms.h tEpicFleet.h tEFaction.h tEpicMoney.h tShipName.h tPcOwner.h tsCull.h
tPcWeaponSeller.pkg : tPcWeaponSeller.pog tPcOwner.h tEpicComms.h tEpicFleet.h tLRoot.h tLTrade.h tEFaction.h tETradeBuy.h tEpicMoney.h tShipName.h tsCull.h
tPcWreckBelt.pkg : tPcWreckBelt.pog tsCull.h tEFaction.h tLCenter.h tLFleet.h tPodUtil.h
tPodUtil.pkg : tPodUtil.pog tEFaction.h
tPogClass.pkg : tPogClass.pog tPcFenceShip.h tPcAsteroidBelt.h tPcConstructionShip.h tPcCustomsToll.h tPcPirateToll.h tPcGuards.h tPcHiredShip.h tPcOwner.h tPcPirateToll.h tPcPodScrapper.h tPcRumorSeller.h tPcTankerShip.h tPcWeaponSeller.h tPcEmbezzleOp.h tPcWreckBelt.h tPcCargoShip.h
tRepUpdate.pkg : tRepUpdate.pog tEFaction.h
tRepWatch.pkg : tRepWatch.pog UniGUI.h tTime.h tEpicFleet.h tEFaction.h tESysSetup.h tEPlayerOrders.h
tSaveGui.pkg : tSaveGui.pog tTime.h tEpicMain.h tEpicGui.h tLProduction.h UniGUI.h tSpewerOps.h
tShipMail.pkg : tShipMail.pog UniGUI.h tEpicGui.h tMail.h tNewsNet.h
tShipName.pkg : tShipName.pog
tSpewerOps.pkg : tSpewerOps.pog tMegaTrucking.h
tStation.pkg : tStation.pog
tStationEnv.pkg : tStationEnv.pog tPogClass.h tPcOwner.h tsCull.h
tStationFilter.pkg : tStationFilter.pog tEconUtil.h tEFaction.h tStation.h tLRoot.h tLProduction.h tLCenter.h tLTrade.h tESysSetup.h
tStationRules.pkg : tStationRules.pog tTime.h tStation.h tUnderOp.h tUnderOpFilter.h tEconUtil.h tLProduction.h tLFleet.h tsFleetOperation.h tEFaction.h
tStationSave.pkg : tStationSave.pog tEconUtil.h tEFaction.h tStation.h tStationRules.h tLRoot.h tLProduction.h tLFleet.h tLCenter.h tLTrade.h tESysSetup.h

#tStation_t.pkg : tStation_t.pog tEpicFaction.h tStation.h tLProduction.h tLCenter.h tLFleet.h tLMission.h

tSysInventory.pkg : tSysInventory.pog
tTime.pkg : tTime.pog
tTimeAdvance.pkg : tTimeAdvance.pog tPodUtil.h tStation.h tTime.h
tUnderOp.pkg : tUnderOp.pog tEFaction.h tStation.h tLRoot.h tLProduction.h tLCenter.h tLFleet.h
tUnderOpFilter.pkg : tUnderOpFilter.pog tUnderOp.h tLProduction.h tLCenter.h
tUnderOpGui.pkg : tUnderOpGui.pog tTime.h tEpicGui.h UniGUI.h tLRoot.h tLCenter.h tEFaction.h tEconUtil.h tLProduction.h tLFleet.h tUnderOp.h tUnderOpFilter.h
tUnderOpSave.pkg : tUnderOpSave.pog tEFaction.h tEconUtil.h tUnderOp.h tLRoot.h tLProduction.h tLCenter.h tLFleet.h tsFleetOperation.h
tViewDock.pkg : tViewDock.pog UniGUI.h
tWingComm.pkg : tWingComm.pog tPodUtil.h tEpicFleet.h tEPlayerOrders.h

#tsCargoShip.pkg : tsCargoShip.pog tEconUtil.h tEconSmall.h tStation.h tStationFilter.h tETradeBuy.h tPogClass.h tLRoot.h tLTrade.h tLProduction.h tEpicMoney.h tTime.h tEFaction.h tEpicFleet.h tPodUtil.h tSpewerOps.h tsPilotSetup.h tEShipCreation.h tShipName.h uString.h

tsCrewSpeak.pkg : tsCrewSpeak.pog uString.h
tsCull.pkg : tsCull.h tPogClass.pog tPcOwner.h
tsDebug.pkg : tsDebug.h UniGUI.pog tEpicGui.h
tsDistress.pkg : tsDistress.pog tsEvent.h
tsEvent.pkg : tsEvent.pog
tsFleetOpCombat.pkg : tsFleetOpCombat.pog tStation.h tEFaction.h tTime.h tUnderOp.h tLCenter.h tLFleet.h tLProduction.h
tsFleetOpUpdate.pkg : tsFleetOpUpdate.pog tTime.h tUnderOp.h tsFleetOperation.h
tsFleetOperation.pkg : tsFleetOperation.pog tStation.h tEFaction.h tTime.h tUnderOp.h tLCenter.h tLProduction.h tsFoEmbezzle.h tsFoFleetAttack.h tsFoFleetDefense.h tsFoProtection.h tsFoThugs.h tsFoRaider.h tsFoCustoms.h tsFoPatrol.h
tsFoCustoms.pkg : tsFoCustoms.pog tStation.h tEFaction.h tTime.h tUnderOp.h tLCenter.h tLProduction.h tLFleet.h tStationFilter.h tShipName.h tEShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoEmbezzle.pkg : tsFoEmbezzle.pog tStation.h tEFaction.h tTime.h tUnderOp.h tLCenter.h tLProduction.h tLFleet.h tStationFilter.h tShipName.h tEShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoFleetAttack.pkg : tsFoFleetAttack.pog tStation.h tEFaction.h tTime.h tUnderOp.h tLRoot.h tLCenter.h tLProduction.h tLFleet.h tStationFilter.h tEconUtil.h tShipName.h tEShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoFleetDefense.pkg : tsFoFleetDefense.pog tStation.h tEFaction.h tTime.h tUnderOp.h tLRoot.h tLCenter.h tLProduction.h tLFleet.h tStationFilter.h tEconUtil.h tShipName.h tEShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoPatrol.pkg : tsFoPatrol.pog tStation.h tEFaction.h tTime.h tUnderOp.h tLRoot.h tLCenter.h tLProduction.h tLFleet.h tStationFilter.h tEconUtil.h tShipName.h tEShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoProtection.pkg : tsFoProtection.pog
tsFoRaider.pkg : tsFoRaider.pog tStation.h tEFaction.h tTime.h tUnderOp.h tLRoot.h tLCenter.h tLProduction.h tLFleet.h tStationFilter.h tEconUtil.h tShipName.h tEShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoThugs.pkg : tsFoThugs.pog tStation.h tEFaction.h tTime.h tUnderOp.h tLRoot.h tLCenter.h tLProduction.h tLFleet.h tStationFilter.h tEconUtil.h tShipName.h tEShipCreation.h tsFleetOpCombat.h tsDebug.h
tsPilotSetup.pkg : tsPilotSetup.pog tEpicComms.h tEpicFleet.h tLRoot.h tLTrade.h tEFaction.h tETradeSell.h tEpicMoney.h tShipName.h tPcOwner.h tLProduction.h tLFleet.h tUnderOp.h tPodUtil.h tRepWatch.h tsEvent.h

#ts_StationEvent.pkg : ts_StationEvent.pog UniGUI.h tTime.h tEFaction.h tMail.h tShipMail.h tNewsNet.h tStation.h tEconUtil.h tUnderOp.h tLProduction.h

uString.pkg : uString.pog
zHeadMove.pkg : zHeadMove.pog tEconUtil.h tEpicMoney.h
zTestCapsule.pkg : zTestCapsule.pog tEpicFleet.h
zTestCargo.pkg : zTestCargo.pog tEconUtil.h tETradeBuy.h tPogClass.h tLRoot.h tLTrade.h tEpicMoney.h tTime.h tEFaction.h tEpicFleet.h tPodUtil.h tEShipCreation.h tPcOwner.h
zTestCode.pkg : zTestCode.pog tEconUtil.h tETradeBuy.h tPogClass.h tLRoot.h tLTrade.h tEpicMoney.h tTime.h tEFaction.h tEpicFleet.h tPodUtil.h tEShipCreation.h
zTestExp.pkg : zTestExp.pog tEconUtil.h tETradeBuy.h tPogClass.h tLRoot.h tLTrade.h tEpicMoney.h tTime.h tEFaction.h tEpicFleet.h tPodUtil.h tEShipCreation.h tPcOwner.h
zTestFacShip.pkg : zTestFacShip.pog
zTestObject.pkg : zTestObject.pog
zTestSwap.pkg : zTestSwap.pog tSaveGui.h
