#
#  Make file for constructing Epic: Middle States Main package.
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
jGiftCargo.pkg : jGiftCargo.pog tEconUtil.pog tEpicMoney.pog
tDistance.pkg : tDistance.pog
tEAutoWatch.pkg : tEAutoWatch.pog tTime.pog tLCenter.pog tEFaction.pog tEpicFleet.pog tFormation.pog tEpicFleetUpkeep.pog tMusic.pog tRepWatch.pog tLocationInit.pog

#tECommEvent.pkg : tECommEvent.pog

tEFaction.pkg : tEFaction.pog
tEFleetGui.pkg : tEFleetGui.pog tEpicGui.pog tLProduction.pog tEpicMoney.pog tEpicFleet.pog tEpicFleetUpkeep.pog tEconUtil.pog uString.pog
tEJump.pkg : tEJump.pog tEpicGui.pog tEpicFleet.pog tTime.pog
tELpointFind.pkg : tELpointFind.pog tEpicGui.pog 
tEPlayerOrders.pkg : tEPlayerOrders.pog tEpicFleet.pog tFormation.pog tPodUtil.pog tEFaction.pog tStation.pog tLProduction.pog tMegaTrucking.pog
tEPlayerWatch.pkg : tEPlayerWatch.pog tTime.pog tLCenter.pog tEFaction.pog tEpicFleet.pog tFormation.pog tEpicFleetUpkeep.pog tMusic.pog tRepWatch.pog tLocationInit.pog tEJump.pog
tEReferenceGui.pkg : tEReferenceGui.pog tEpicGui.pog tLProduction.pog tEconSmall.pog tEconUtil.pog tEpicMoney.pog tPodUtil.pog uString.pog
tEShipCreation.pkg : tEShipCreation.pog tEFaction.pog
tESysSetup.pkg : tESysSetup.pog tEFaction.pog tStation.pog tLProduction.pog tEJump.pog
tETradeBuy.pkg : tETradeBuy.pog tStation.pog tEpicGui.pog tEFaction.pog tLProduction.pog tLInventory.pog tLTrade.pog tEconSmall.pog tEconUtil.pog tEpicMoney.pog tPodUtil.pog uString.pog tSpewerOps.pog
tETradeSell.pkg : tETradeSell.pog tSpewerOps.pog tMegaTrucking.pog tStation.pog tEpicGui.pog tEFaction.pog tLProduction.pog tEconSmall.pog tEconUtil.pog tEpicMoney.pog tPodUtil.pog tLTrade.pog uString.pog
tEconCategory.pkg : tEconCategory.pog tEpicGui.pog tUnderOp.pog
tEconSmall.pkg : tEconSmall.pog tEconUtil.pog tLProduction.pog tLTrade.pog tEFaction.pog ECargoTypes.pog uString.pog tStation.pog
tEconUtil.pkg : tEconUtil.pog
tEpicComms.pkg : tEpicComms.pog
tEpicFacGui.pkg : tEpicFacGui.pog tEFaction.pog tEpicGui.pog tEpicMoney.pog
tEpicFaction.pkg : tEpicFaction.pog tLRoot.pog tLProduction.pog tLFleet.pog

#tEpicFaction_t.pkg : tEpicFaction_t.pog tEpicFaction.pog

tEpicFleet.pkg : tEpicFleet.pog tEconUtil.pog tPodUtil.pog tEpicComms.pog tFormation.pog tEFaction.pog tMegaTrucking.pog

#tEpicFleetBack.pkg : tEpicFleetBack.pog tPodUtil.pog tEpicComms.pog

tEpicFleetUpkeep.pkg : tEpicFleetUpkeep.pog tStation.pog tEFaction.pog tEpicFleet.pog tEpicMoney.pog tLProduction.pog tLInventory.pog tEconUtil.pog tEconSmall.pog tPodUtil.pog tShipMail.pog
tEpicGui.pkg : tEpicGui.pog
tEpicLFPlus.pkg : tEpicLFPlus.pog tStation.pog tEpicGui.pog tEconUtil.pog tLProduction.pog tLFleet.pog tUnderOp.pog tUnderOpFilter.pog tESysSetup.pog tEJump.pog 
tEpicMain.pkg : tEpicMain.pog tTime.pog tDistance.pog tMultimod.pog UniGUI.pog UniGUIBase.pog tEpicLFPlus.pog tEFaction.pog tEpicGui.pog tEpicFleet.pog tDistance.pog jGiftCargo.pog tWingComm.pog tEPlayerWatch.pog tStationEnv.pog tEpicComms.pog tEpicFleetUpkeep.pog tUnderOp.pog tUnderOpSave.pog tLInventory.pog tEconSmall.pog tETradeBuy.pog tETradeSell.pog tEFleetGui.pog tExitGui.pog tStationSave.pog tESysSetup.pog tMusic.pog tMail.pog tNewsNet.pog tShipMail.pog tViewDock.pog tEJump.pog  tELpointFind.pog tStationRules.pog tsFleetOpUpdate.pog tsCrewSpeak.pog tRepUpdate.pog tOptionsGui.pog
tEpicMoney.pkg : tEpicMoney.pog

#ECargoScript.pog 

tEpicTrade.pkg : tEpicTrade.pog UniGUI.pog ECargoTypes.pog tEpicGui.pog tEconUtil.pog tEconSmall.pog tPodUtil.pog tEpicFleet.pog

tExitGui.pkg : tExitGui.pog UniGUI.pog tEpicGui.pog tLProduction.pog tEconSmall.pog tEconUtil.pog tEpicMoney.pog tPodUtil.pog uString.pog
tFormation.pkg : tFormation.pog
tJumpSim.pkg : tJumpSim.pog tEpicGui.pog UniGUI.pog
tLCenter.pkg : tLCenter.pog tLRoot.pog
tLFleet.pkg : tLFleet.pog tLRoot.pog
tLInventory.pkg : tLInventory.pog tTime.pog tLRoot.pog tEconUtil.pog tStation.pog
tLProduction.pkg : tLProduction.pog tLRoot.pog

#tLProduction_t.pkg : tLProduction_t.pog tEpicFaction.pog tLRoot.pog tLProduction.pog

tLRoot.pkg : tLRoot.pog
tLTrade.pkg : tLTrade.pog tLRoot.pog
tLocationInit.pkg : tLocationInit.pog tEconUtil.pog tStation.pog tUnderOp.pog tLCenter.pog tLProduction.pog tStationEnv.pog tEpicFleetUpkeep.pog
tLock.pkg : tLock.pog
tMail.pkg : tMail.pog
tMegaTrucking.pkg : tMegaTrucking.pog
tMultimod.pkg : tMultimod.pog
tMusic.pkg : tMusic.pog uString.pog tStation.pog tLProduction.pog
tMusicChange.pkg : tMusicChange.pog tMusic.pog tLProduction.pog
tMusicGui.pkg : tMusicGui.pog tMusic.pog tEpicGui.pog
tNewsNet.pkg : tNewsNet.pog UniGUI.pog tTime.pog tMail.pog
tOptionsGui.pkg : tOptionsGui.pog UniGUI.pog tEpicGui.pog
tPcAsteroidBelt.pkg : tPcAsteroidBelt.pog tsCull.pog tLCenter.pog
tPcCargoShip.pkg : tPcCargoShip.pog tEconUtil.pog tEconSmall.pog tStation.pog tStationFilter.pog tETradeBuy.pog tPogClass.pog tLRoot.pog tLTrade.pog tLProduction.pog tEpicMoney.pog tTime.pog tEFaction.pog tEpicFleet.pog tPodUtil.pog tSpewerOps.pog tsPilotSetup.pog tEShipCreation.pog tShipName.pog uString.pog
tPcConstructionShip.pkg : tPcConstructionShip.pog tEpicComms.pog tEpicFleet.pog tLRoot.pog tLCenter.pog tLTrade.pog tEFaction.pog tETradeSell.pog tEpicMoney.pog tShipName.pog tPcOwner.pog tsCull.pog
tPcCustomsToll.pkg : tPcCustomsToll.pog tEShipCreation.pog tPodUtil.pog tEpicComms.pog tEpicFleet.pog tEFaction.pog tEpicMoney.pog tShipName.pog tLCenter.pog tLFleet.pog tEconSmall.pog tPcOwner.pog tsPilotSetup.pog
tPcEmbezzleOp.pkg : tPcEmbezzleOp.pog tEpicComms.pog tEpicFleet.pog tLRoot.pog tLTrade.pog tEFaction.pog tETradeSell.pog tEpicMoney.pog tShipName.pog tPcOwner.pog tLProduction.pog tLCenter.pog tUnderOp.pog tDistance.pog tEShipCreation.pog tLFleet.pog tsPilotSetup.pog tStationFilter.pog tDistance.pog tEJump.pog tsCull.pog
tPcFenceShip.pkg : tPcFenceShip.pog tEpicComms.pog tEpicFleet.pog tLRoot.pog tLTrade.pog tEFaction.pog tETradeSell.pog tEpicMoney.pog tShipName.pog tPcOwner.pog tLProduction.pog tUnderOp.pog tDistance.pog tEShipCreation.pog tLFleet.pog tsPilotSetup.pog tStationFilter.pog tDistance.pog tEJump.pog tsCull.pog
tPcGuards.pkg : tPcGuards.pog tPodUtil.pog tEpicComms.pog tEpicFleet.pog tEFaction.pog tEpicMoney.pog tShipName.pog tLCenter.pog tLFleet.pog tEShipCreation.pog tsPilotSetup.pog tEJump.pog tDistance.pog tUnderOp.pog uString.pog tsEvent.pog tsDistress.pog tPcOwner.pog
tPcHiredShip.pkg : tPcHiredShip.pog tEpicComms.pog tEpicFleet.pog tEFaction.pog tEpicMoney.pog tShipName.pog tPcOwner.pog tsCull.pog
tPcOwner.pkg : tPcOwner.pog
tPcPirateToll.pkg : tPcPirateToll.pog tEShipCreation.pog tPodUtil.pog tEpicComms.pog tEpicFleet.pog tEFaction.pog tEpicMoney.pog tShipName.pog tLCenter.pog tLFleet.pog tEconSmall.pog tPcOwner.pog tsPilotSetup.pog
tPcPodScrapper.pkg : tPcPodScrapper.pog tPodUtil.pog tEpicComms.pog tEpicFleet.pog tEFaction.pog tEpicMoney.pog tShipName.pog tsCull.pog
tPcRumorSeller.pkg : tPcRumorSeller.pog tTime.pog tEconUtil.pog tStationFilter.pog tUnderOp.pog tUnderOpFilter.pog tEpicComms.pog tEpicFleet.pog tEFaction.pog tEpicMoney.pog tShipName.pog tLCenter.pog tLProduction.pog tsCull.pog
tPcTankerShip.pkg : tPcTankerShip.pog tEpicComms.pog tEpicFleet.pog tEFaction.pog tEpicMoney.pog tShipName.pog tPcOwner.pog tsCull.pog
tPcWeaponSeller.pkg : tPcWeaponSeller.pog tPcOwner.pog tEpicComms.pog tEpicFleet.pog tLRoot.pog tLTrade.pog tEFaction.pog tETradeBuy.pog tEpicMoney.pog tShipName.pog tsCull.pog
tPcWreckBelt.pkg : tPcWreckBelt.pog tsCull.pog tEFaction.pog tLCenter.pog tLFleet.pog tPodUtil.pog
tPodUtil.pkg : tPodUtil.pog tEFaction.pog
tPogClass.pkg : tPogClass.pog tPcFenceShip.pog tPcAsteroidBelt.pog tPcConstructionShip.pog tPcCustomsToll.pog tPcPirateToll.pog tPcGuards.pog tPcHiredShip.pog tPcOwner.pog tPcPirateToll.pog tPcPodScrapper.pog tPcRumorSeller.pog tPcTankerShip.pog tPcWeaponSeller.pog tPcEmbezzleOp.pog tPcWreckBelt.pog tPcCargoShip.pog
tRepUpdate.pkg : tRepUpdate.pog tEFaction.pog
tRepWatch.pkg : tRepWatch.pog UniGUI.pog tTime.pog tEpicFleet.pog tEFaction.pog tESysSetup.pog tEPlayerOrders.pog
tSaveGui.pkg : tSaveGui.pog tTime.pog tEpicMain.pog tEpicGui.pog tLProduction.pog UniGUI.pog tSpewerOps.pog
tShipMail.pkg : tShipMail.pog UniGUI.pog tEpicGui.pog tMail.pog tNewsNet.pog
tShipName.pkg : tShipName.pog
tSpewerOps.pkg : tSpewerOps.pog tMegaTrucking.pog
tStation.pkg : tStation.pog
tStationEnv.pkg : tStationEnv.pog tPogClass.pog tPcOwner.pog tsCull.pog
tStationFilter.pkg : tStationFilter.pog tEconUtil.pog tEFaction.pog tStation.pog tLRoot.pog tLProduction.pog tLCenter.pog tLTrade.pog tESysSetup.pog
tStationRules.pkg : tStationRules.pog tTime.pog tStation.pog tUnderOp.pog tUnderOpFilter.pog tEconUtil.pog tLProduction.pog tLFleet.pog tsFleetOperation.pog tEFaction.pog
tStationSave.pkg : tStationSave.pog tEconUtil.pog tEFaction.pog tStation.pog tStationRules.pog tLRoot.pog tLProduction.pog tLFleet.pog tLCenter.pog tLTrade.pog tESysSetup.pog

#tStation_t.pkg : tStation_t.pog tEpicFaction.pog tStation.pog tLProduction.pog tLCenter.pog tLFleet.pog tLMission.pog

tSysInventory.pkg : tSysInventory.pog
tTime.pkg : tTime.pog
tTimeAdvance.pkg : tTimeAdvance.pog tPodUtil.pog tStation.pog tTime.pog
tUnderOp.pkg : tUnderOp.pog tEFaction.pog tStation.pog tLRoot.pog tLProduction.pog tLCenter.pog tLFleet.pog
tUnderOpFilter.pkg : tUnderOpFilter.pog tUnderOp.pog tLProduction.pog tLCenter.pog
tUnderOpGui.pkg : tUnderOpGui.pog tTime.pog tEpicGui.pog UniGUI.pog tLRoot.pog tLCenter.pog tEFaction.pog tEconUtil.pog tLProduction.pog tLFleet.pog tUnderOp.pog tUnderOpFilter.pog
tUnderOpSave.pkg : tUnderOpSave.pog tEFaction.pog tEconUtil.pog tUnderOp.pog tLRoot.pog tLProduction.pog tLCenter.pog tLFleet.pog tsFleetOperation.pog
tViewDock.pkg : tViewDock.pog UniGUI.pog
tWingComm.pkg : tWingComm.pog tPodUtil.pog tEpicFleet.pog tEPlayerOrders.pog

#tsCargoShip.pkg : tsCargoShip.pog tEconUtil.pog tEconSmall.pog tStation.pog tStationFilter.pog tETradeBuy.pog tPogClass.pog tLRoot.pog tLTrade.pog tLProduction.pog tEpicMoney.pog tTime.pog tEFaction.pog tEpicFleet.pog tPodUtil.pog tSpewerOps.pog tsPilotSetup.pog tEShipCreation.pog tShipName.pog uString.pog

tsCrewSpeak.pkg : tsCrewSpeak.pog uString.pog
tsCull.pkg : tsCull.pog tPogClass.pog tPcOwner.pog
tsDebug.pkg : tsDebug.pog UniGUI.pog tEpicGui.pog
tsDistress.pkg : tsDistress.pog tsEvent.pog
tsEvent.pkg : tsEvent.pog
tsFleetOpCombat.pkg : tsFleetOpCombat.pog tStation.pog tEFaction.pog tTime.pog tUnderOp.pog tLCenter.pog tLFleet.pog tLProduction.pog
tsFleetOpUpdate.pkg : tsFleetOpUpdate.pog tTime.pog tUnderOp.pog tsFleetOperation.pog
tsFleetOperation.pkg : tsFleetOperation.pog tStation.pog tEFaction.pog tTime.pog tUnderOp.pog tLCenter.pog tLProduction.pog tsFoEmbezzle.pog tsFoFleetAttack.pog tsFoFleetDefense.pog tsFoProtection.pog tsFoThugs.pog tsFoRaider.pog tsFoCustoms.pog tsFoPatrol.pog
tsFoCustoms.pkg : tsFoCustoms.pog tStation.pog tEFaction.pog tTime.pog tUnderOp.pog tLCenter.pog tLProduction.pog tLFleet.pog tStationFilter.pog tShipName.pog tEShipCreation.pog tsFleetOpCombat.pog tsDebug.pog
tsFoEmbezzle.pkg : tsFoEmbezzle.pog tStation.pog tEFaction.pog tTime.pog tUnderOp.pog tLCenter.pog tLProduction.pog tLFleet.pog tStationFilter.pog tShipName.pog tEShipCreation.pog tsFleetOpCombat.pog tsDebug.pog
tsFoFleetAttack.pkg : tsFoFleetAttack.pog tStation.pog tEFaction.pog tTime.pog tUnderOp.pog tLRoot.pog tLCenter.pog tLProduction.pog tLFleet.pog tStationFilter.pog tEconUtil.pog tShipName.pog tEShipCreation.pog tsFleetOpCombat.pog tsDebug.pog
tsFoFleetDefense.pkg : tsFoFleetDefense.pog tStation.pog tEFaction.pog tTime.pog tUnderOp.pog tLRoot.pog tLCenter.pog tLProduction.pog tLFleet.pog tStationFilter.pog tEconUtil.pog tShipName.pog tEShipCreation.pog tsFleetOpCombat.pog tsDebug.pog
tsFoPatrol.pkg : tsFoPatrol.pog tStation.pog tEFaction.pog tTime.pog tUnderOp.pog tLRoot.pog tLCenter.pog tLProduction.pog tLFleet.pog tStationFilter.pog tEconUtil.pog tShipName.pog tEShipCreation.pog tsFleetOpCombat.pog tsDebug.pog
tsFoProtection.pkg : tsFoProtection.pog
tsFoRaider.pkg : tsFoRaider.pog tStation.pog tEFaction.pog tTime.pog tUnderOp.pog tLRoot.pog tLCenter.pog tLProduction.pog tLFleet.pog tStationFilter.pog tEconUtil.pog tShipName.pog tEShipCreation.pog tsFleetOpCombat.pog tsDebug.pog
tsFoThugs.pkg : tsFoThugs.pog tStation.pog tEFaction.pog tTime.pog tUnderOp.pog tLRoot.pog tLCenter.pog tLProduction.pog tLFleet.pog tStationFilter.pog tEconUtil.pog tShipName.pog tEShipCreation.pog tsFleetOpCombat.pog tsDebug.pog
tsPilotSetup.pkg : tsPilotSetup.pog tEpicComms.pog tEpicFleet.pog tLRoot.pog tLTrade.pog tEFaction.pog tETradeSell.pog tEpicMoney.pog tShipName.pog tPcOwner.pog tLProduction.pog tLFleet.pog tUnderOp.pog tPodUtil.pog tRepWatch.pog tsEvent.pog

#ts_StationEvent.pkg : ts_StationEvent.pog UniGUI.pog tTime.pog tEFaction.pog tMail.pog tShipMail.pog tNewsNet.pog tStation.pog tEconUtil.pog tUnderOp.pog tLProduction.pog

uString.pkg : uString.pog
zHeadMove.pkg : zHeadMove.pog tEconUtil.pog tEpicMoney.pog
zTestCapsule.pkg : zTestCapsule.pog tEpicFleet.pog
zTestCargo.pkg : zTestCargo.pog tEconUtil.pog tETradeBuy.pog tPogClass.pog tLRoot.pog tLTrade.pog tEpicMoney.pog tTime.pog tEFaction.pog tEpicFleet.pog tPodUtil.pog tEShipCreation.pog tPcOwner.pog
zTestCode.pkg : zTestCode.pog tEconUtil.pog tETradeBuy.pog tPogClass.pog tLRoot.pog tLTrade.pog tEpicMoney.pog tTime.pog tEFaction.pog tEpicFleet.pog tPodUtil.pog tEShipCreation.pog
zTestExp.pkg : zTestExp.pog tEconUtil.pog tETradeBuy.pog tPogClass.pog tLRoot.pog tLTrade.pog tEpicMoney.pog tTime.pog tEFaction.pog tEpicFleet.pog tPodUtil.pog tEShipCreation.pog tPcOwner.pog
zTestFacShip.pkg : zTestFacShip.pog
zTestObject.pkg : zTestObject.pog
zTestSwap.pkg : zTestSwap.pog tSaveGui.pog
