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
#	tsShipBack.pkg \
#	tStation_t.pkg \
#	tsCargoShip.pkg \
#	ts_StationEvent.pkg \
#	tEpicFaction_t.pkg \
#	tLProduction_t.pkg \


PACKAGES = ECargoTypes.pkg \
	UniGUI.pkg \
	UniGUIBase.pkg \
	UniGUIMisc.pkg \
	jcEChangeIdGui.pkg \
	jcEpicShipPurGUI.pkg \
	tClaimGui.pkg \
	tDistance.pkg \
	tsFaction.pkg \
	tEFleetGui.pkg \
	tEJump.pkg \
	tELpointFind.pkg \
	tEPlayerWatch.pkg \
	tEReferenceGui.pkg \
	tsShipCreation.pkg \
	tESysSetup.pkg \
	tETradeBuy.pkg \
	tETradeSell.pkg \
	tEconSmall.pkg \
	tEconUtil.pkg \
	tEpicComms.pkg \
	tEpicFacGui.pkg \
	tsShip.pkg \
	tEpicFleetUpkeep.pkg \
	tEpicGui.pkg \
	tEpicLFPlus.pkg \
	tEpicMain.pkg \
	tEpicMoney.pkg \
	tEpicTrade.pkg \
	tExitGui.pkg \
	tFormation.pkg \
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
	tTime.pkg \
	tTimeAdvance.pkg \
	tUnderOp.pkg \
	tUnderOpFilter.pkg \
	tUnderOpGui.pkg \
	tUnderOpSave.pkg \
	tViewDock.pkg \
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
	tsPlayerDeath.pkg \
	tsPlayerSave.pkg \
	tsPlayerFleet.pkg \
	tsPosition.pkg \
	tsShipSave.pkg \
	tsWingComm.pkg \
	tsWingman.pkg \
	tsWingmanDeath.pkg \
	uString.pkg \
	zTestCapsule.pkg \
	zTestCargo.pkg \
	zTestCode.pkg \
	zTestExp.pkg \
	zTestFacShip.pkg \
	zTestObject.pkg \
	tsSystemDamage.pkg \
	tssdGUI.pkg




all: $(PACKAGES)


clean:
	rm -v *.pkg


#
# Dependency rules.
# MUST BE UPDATED FOR NEW PACKAGES AND IMPORT CHANGES!
#

tsSystemDamage.pkg : tsSystemDamage.pog
tssdGUI.pkg : tssdGUI.pog tsSystemDamage.h


ECargoTypes.pkg : ECargoTypes.pog
ExitCrashTest.pkg : ExitCrashTest.pog
UniGUI.pkg : UniGUI.pog
UniGUIBase.pkg : UniGUIBase.pog
UniGUIMisc.pkg : UniGUIMisc.pog


jcEChangeIdGui.pkg : jcEChangeIdGui.pog UniGUI.h tEpicGui.h tSaveGui.h tEconUtil.h tsShip.h tEpicMoney.h tsFaction.h
jcEpicShipPurGUI.pkg : jcEpicShipPurGUI.pog UniGUI.h tsFaction.h tEpicGui.h tSaveGui.h tEpicMoney.h


tDistance.pkg : tDistance.pog
tEAutoWatch.pkg : tEAutoWatch.pog tTime.h tLCenter.h tsFaction.h tsShip.h tFormation.h tEpicFleetUpkeep.h tMusic.h tRepWatch.h tLocationInit.h

#tECommEvent.pkg : tECommEvent.pog

tsFaction.pkg : tsFaction.pog tStation.h
tEFleetGui.pkg : tEFleetGui.pog tEpicGui.h tLProduction.h tEpicMoney.h tsShip.h tEpicFleetUpkeep.h tEconUtil.h uString.h
tEJump.pkg : tEJump.pog tEpicGui.h tsShip.h tTime.h tsPlayerFleet.h
tELpointFind.pkg : tELpointFind.pog tEpicGui.h 
tEPlayerOrders.pkg : tEPlayerOrders.pog tsShip.h tFormation.h tPodUtil.h tsFaction.h tStation.h tLProduction.h tMegaTrucking.h
tEPlayerWatch.pkg : tEPlayerWatch.pog tTime.h tLCenter.h tsFaction.h tsShip.h tFormation.h tEpicFleetUpkeep.h tMusic.h tRepWatch.h tLocationInit.h tEJump.h
tEReferenceGui.pkg : tEReferenceGui.pog tEpicGui.h tLProduction.h tEconSmall.h tEconUtil.h tEpicMoney.h tPodUtil.h uString.h
tsShipCreation.pkg : tsShipCreation.pog tsFaction.h
tESysSetup.pkg : tESysSetup.pog tsFaction.h tStation.h tLProduction.h tEJump.h
tETradeBuy.pkg : tETradeBuy.pog tStation.h tEpicGui.h tsFaction.h tLProduction.h tLInventory.h tLTrade.h tEconSmall.h tEconUtil.h tEpicMoney.h tPodUtil.h uString.h tSpewerOps.h
tETradeSell.pkg : tETradeSell.pog tSpewerOps.h tMegaTrucking.h tStation.h tEpicGui.h tsFaction.h tLProduction.h tEconSmall.h tEconUtil.h tEpicMoney.h tPodUtil.h tLTrade.h uString.h
tEconSmall.pkg : tEconSmall.pog tEconUtil.h tLProduction.h tLTrade.h tsFaction.h ECargoTypes.h uString.h tStation.h
tEconUtil.pkg : tEconUtil.pog
tEpicComms.pkg : tEpicComms.pog
tEpicFacGui.pkg : tEpicFacGui.pog tsFaction.h tEpicGui.h tEpicMoney.h


tsPosition.pkg : tsPosition.pog

#tEpicFaction_t.pkg : tEpicFaction_t.pog tEpicFaction.h

tsShip.pkg : tsShip.pog tEconUtil.h tPodUtil.h tEpicComms.h tFormation.h tsFaction.h tMegaTrucking.h
tsPlayerFleet.pkg : tsPlayerFleet.pog tsShip.h tEconUtil.h tPodUtil.h tEpicComms.h tFormation.h tsFaction.h tMegaTrucking.h
tsPlayerDeath.pkg : tsPlayerDeath.pog tsShip.h tEconUtil.h tPodUtil.h tEpicComms.h tFormation.h tsFaction.h tMegaTrucking.h
tsWingmanDeath.pkg : tsWingmanDeath.pog tsShip.h tEconUtil.h tPodUtil.h tEpicComms.h tFormation.h tsFaction.h tMegaTrucking.h tsWingComm.h


tsShipSave.pkg : tsShipSave.pog tsPosition.h tsShip.h

tsPlayerSave.pkg : tsPlayerSave.pog tsShip.h tsShipSave.h 



#tsShipBack.pkg : tsShipBack.pog tPodUtil.h tEpicComms.h

tEpicFleetUpkeep.pkg : tEpicFleetUpkeep.pog tStation.h tsFaction.h tsShip.h tEpicMoney.h tLProduction.h tLInventory.h tEconUtil.h tEconSmall.h tPodUtil.h tShipMail.h
tEpicGui.pkg : tEpicGui.pog
tEpicLFPlus.pkg : tEpicLFPlus.pog tStation.h tEpicGui.h tEconUtil.h tLProduction.h tLFleet.h tUnderOp.h tUnderOpFilter.h tESysSetup.h tEJump.h 
tEpicMain.pkg : tEpicMain.pog tTime.h tDistance.h tMultimod.h UniGUI.h UniGUIBase.h tEpicLFPlus.h tsFaction.h tEpicGui.h tsShip.h tDistance.h tsWingComm.h tEPlayerWatch.h tStationEnv.h tEpicComms.h tEpicFleetUpkeep.h tUnderOp.h tUnderOpSave.h tLInventory.h tEconSmall.h tETradeBuy.h tETradeSell.h tEFleetGui.h tExitGui.h tStationSave.h tESysSetup.h tMusic.h tMail.h tNewsNet.h tShipMail.h tViewDock.h tEJump.h  tELpointFind.h tStationRules.h tsFleetOpUpdate.h tsCrewSpeak.h tRepUpdate.h tOptionsGui.h tStartGui.h tEReferenceGui.h
tEpicMoney.pkg : tEpicMoney.pog

#ECargoScript.h 

tEpicTrade.pkg : tEpicTrade.pog UniGUI.h ECargoTypes.h tEpicGui.h tEconUtil.h tEconSmall.h tPodUtil.h tsShip.h

tExitGui.pkg : tExitGui.pog UniGUI.h tEpicGui.h tLProduction.h tEconSmall.h tEconUtil.h tEpicMoney.h tPodUtil.h uString.h
tFormation.pkg : tFormation.pog

tLCenter.pkg : tLCenter.pog tLRoot.h
tLFleet.pkg : tLFleet.pog tLRoot.h
tLInventory.pkg : tLInventory.pog tTime.h tLRoot.h tEconUtil.h tStation.h
tLProduction.pkg : tLProduction.pog tLRoot.h
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
tClaimGui.pkg : tOptionsGui.pog UniGUI.h tEpicGui.h tsFaction.h
tStartGui.pkg : tStartGui.pog UniGUI.h tEpicGui.h
tPcAsteroidBelt.pkg : tPcAsteroidBelt.pog tsCull.h tLCenter.h
tPcCargoShip.pkg : tPcCargoShip.pog tEconUtil.h tEconSmall.h tStation.h tStationFilter.h tETradeBuy.h tPogClass.h tLRoot.h tLTrade.h tLProduction.h tEpicMoney.h tTime.h tsFaction.h tsShip.h tPodUtil.h tSpewerOps.h tsPilotSetup.h tsShipCreation.h tShipName.h uString.h tsShip.h tsShipCreationEnum.h
tPcConstructionShip.pkg : tPcConstructionShip.pog tEpicComms.h tsShip.h tLRoot.h tLCenter.h tLTrade.h tsFaction.h tETradeSell.h tEpicMoney.h tShipName.h tPcOwner.h tsCull.h tsShip.h tsShipCreationEnum.h
tPcCustomsToll.pkg : tPcCustomsToll.pog tsShipCreation.h tPodUtil.h tEpicComms.h tsShip.h tsFaction.h tEpicMoney.h tShipName.h tLCenter.h tLFleet.h tEconSmall.h tPcOwner.h tsPilotSetup.h tsShip.h tsShipCreationEnum.h
tPcEmbezzleOp.pkg : tPcEmbezzleOp.pog tEpicComms.h tsShip.h tLRoot.h tLTrade.h tsFaction.h tETradeSell.h tEpicMoney.h tShipName.h tPcOwner.h tLProduction.h tLCenter.h tUnderOp.h tDistance.h tsShipCreation.h tLFleet.h tsPilotSetup.h tStationFilter.h tDistance.h tEJump.h tsCull.h tsShip.h tsShipCreationEnum.h
tPcFenceShip.pkg : tPcFenceShip.pog tEpicComms.h tsShip.h tLRoot.h tLTrade.h tsFaction.h tETradeSell.h tEpicMoney.h tShipName.h tPcOwner.h tLProduction.h tUnderOp.h tDistance.h tsShipCreation.h tLFleet.h tsPilotSetup.h tStationFilter.h tDistance.h tEJump.h tsCull.h tsShip.h tsShipCreationEnum.h
tPcGuards.pkg : tPcGuards.pog tPodUtil.h tEpicComms.h tsShip.h tsFaction.h tEpicMoney.h tShipName.h tLCenter.h tLFleet.h tsShipCreation.h tsPilotSetup.h tEJump.h tDistance.h tUnderOp.h uString.h tsEvent.h tsDistress.h tPcOwner.h tsShip.h tsShipCreationEnum.h
tPcHiredShip.pkg : tPcHiredShip.pog tEpicComms.h tsShip.h tsFaction.h tEpicMoney.h tShipName.h tPcOwner.h tsCull.h tsShip.h tsShipCreationEnum.h
tPcOwner.pkg : tPcOwner.pog 
tPcPirateToll.pkg : tPcPirateToll.pog tsShipCreation.h tPodUtil.h tEpicComms.h tsShip.h tsFaction.h tEpicMoney.h tShipName.h tLCenter.h tLFleet.h tEconSmall.h tPcOwner.h tsPilotSetup.h tsShip.h tsShipCreationEnum.h
tPcPodScrapper.pkg : tPcPodScrapper.pog tPodUtil.h tEpicComms.h tsShip.h tsFaction.h tEpicMoney.h tShipName.h tsCull.h tsShip.h tsShipCreationEnum.h
tPcRumorSeller.pkg : tPcRumorSeller.pog tTime.h tEconUtil.h tStationFilter.h tUnderOp.h tUnderOpFilter.h tEpicComms.h tsShip.h tsFaction.h tEpicMoney.h tShipName.h tLCenter.h tLProduction.h tsCull.h tsShip.h tsShipCreationEnum.h
tPcTankerShip.pkg : tPcTankerShip.pog tEpicComms.h tsShip.h tsFaction.h tEpicMoney.h tShipName.h tPcOwner.h tsCull.h tsShip.h tsShipCreationEnum.h
tPcWeaponSeller.pkg : tPcWeaponSeller.pog tPcOwner.h tEpicComms.h tsShip.h tLRoot.h tLTrade.h tsFaction.h tETradeBuy.h tEpicMoney.h tShipName.h tsCull.h tsShip.h tsShipCreationEnum.h
tPcWreckBelt.pkg : tPcWreckBelt.pog tsCull.h tsFaction.h tLCenter.h tLFleet.h tPodUtil.h
tPodUtil.pkg : tPodUtil.pog tsFaction.h
tPogClass.pkg : tPogClass.pog tPcFenceShip.h tPcAsteroidBelt.h tPcConstructionShip.h tPcCustomsToll.h tPcPirateToll.h tPcGuards.h tPcHiredShip.h tPcOwner.h tPcPirateToll.h tPcPodScrapper.h tPcRumorSeller.h tPcTankerShip.h tPcWeaponSeller.h tPcEmbezzleOp.h tPcWreckBelt.h tPcCargoShip.h
tRepUpdate.pkg : tRepUpdate.pog tsFaction.h
tRepWatch.pkg : tRepWatch.pog UniGUI.h tTime.h tsShip.h tsFaction.h tESysSetup.h tsWingman.h
tSaveGui.pkg : tSaveGui.pog tTime.h tEpicMain.h tEpicGui.h tLProduction.h UniGUI.h tSpewerOps.h
tShipMail.pkg : tShipMail.pog UniGUI.h tEpicGui.h tMail.h tNewsNet.h
tShipName.pkg : tShipName.pog
tSpewerOps.pkg : tSpewerOps.pog tMegaTrucking.h
tStation.pkg : tStation.pog
tStationEnv.pkg : tStationEnv.pog tPogClass.h tPcOwner.h tsCull.h
tStationFilter.pkg : tStationFilter.pog tEconUtil.h tsFaction.h tStation.h tLRoot.h tLProduction.h tLCenter.h tLTrade.h tESysSetup.h
tStationRules.pkg : tStationRules.pog tTime.h tStation.h tUnderOp.h tUnderOpFilter.h tEconUtil.h tLProduction.h tLFleet.h tsFleetOperation.h tsFaction.h
tStationSave.pkg : tStationSave.pog tEconUtil.h tsFaction.h tStation.h tStationRules.h tLRoot.h tLProduction.h tLFleet.h tLCenter.h tLTrade.h tESysSetup.h

#tStation_t.pkg : tStation_t.pog tEpicFaction.h tStation.h tLProduction.h tLCenter.h tLFleet.h tLMission.h

tTime.pkg : tTime.pog
tTimeAdvance.pkg : tTimeAdvance.pog tPodUtil.h tStation.h tTime.h tsShip.h
tUnderOp.pkg : tUnderOp.pog tsFaction.h tStation.h tLRoot.h tLProduction.h tLCenter.h tLFleet.h
tUnderOpFilter.pkg : tUnderOpFilter.pog tUnderOp.h tLProduction.h tLCenter.h
tUnderOpGui.pkg : tUnderOpGui.pog tTime.h tEpicGui.h UniGUI.h tLRoot.h tLCenter.h tsFaction.h tEconUtil.h tLProduction.h tLFleet.h tUnderOp.h tUnderOpFilter.h
tUnderOpSave.pkg : tUnderOpSave.pog tsFaction.h tEconUtil.h tUnderOp.h tLRoot.h tLProduction.h tLCenter.h tLFleet.h tsFleetOperation.h
tViewDock.pkg : tViewDock.pog UniGUI.h
tsWingComm.pkg : tsWingComm.pog tsPlayerFleet.h tPodUtil.h tsShipEnum.h tsShip.h tsWingman.h

#tsCargoShip.pkg : tsCargoShip.pog tEconUtil.h tEconSmall.h tStation.h tStationFilter.h tETradeBuy.h tPogClass.h tLRoot.h tLTrade.h tLProduction.h tEpicMoney.h tTime.h tsFaction.h tsShip.h tPodUtil.h tSpewerOps.h tsPilotSetup.h tsShipCreation.h tShipName.h uString.h

tsCrewSpeak.pkg : tsCrewSpeak.pog uString.h
tsCull.pkg : tsCull.h tPogClass.pog tPcOwner.h
tsDebug.pkg : tsDebug.h UniGUI.pog tEpicGui.h
tsDistress.pkg : tsDistress.pog tsEvent.h
tsEvent.pkg : tsEvent.pog
tsFleetOpCombat.pkg : tsFleetOpCombat.pog tStation.h tsFaction.h tTime.h tUnderOp.h tLCenter.h tLFleet.h tLProduction.h
tsFleetOpUpdate.pkg : tsFleetOpUpdate.pog tTime.h tUnderOp.h tsFleetOperation.h
tsFleetOperation.pkg : tsFleetOperation.pog tStation.h tsFaction.h tTime.h tUnderOp.h tLCenter.h tLProduction.h tsFoEmbezzle.h tsFoFleetAttack.h tsFoFleetDefense.h tsFoProtection.h tsFoThugs.h tsFoRaider.h tsFoCustoms.h tsFoPatrol.h
tsFoCustoms.pkg : tsFoCustoms.pog tStation.h tsFaction.h tTime.h tUnderOp.h tLCenter.h tLProduction.h tLFleet.h tStationFilter.h tShipName.h tsShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoEmbezzle.pkg : tsFoEmbezzle.pog tStation.h tsFaction.h tTime.h tUnderOp.h tLCenter.h tLProduction.h tLFleet.h tStationFilter.h tShipName.h tsShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoFleetAttack.pkg : tsFoFleetAttack.pog tStation.h tsFaction.h tTime.h tUnderOp.h tLRoot.h tLCenter.h tLProduction.h tLFleet.h tStationFilter.h tEconUtil.h tShipName.h tsShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoFleetDefense.pkg : tsFoFleetDefense.pog tStation.h tsFaction.h tTime.h tUnderOp.h tLRoot.h tLCenter.h tLProduction.h tLFleet.h tStationFilter.h tEconUtil.h tShipName.h tsShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoPatrol.pkg : tsFoPatrol.pog tStation.h tsFaction.h tTime.h tUnderOp.h tLRoot.h tLCenter.h tLProduction.h tLFleet.h tStationFilter.h tEconUtil.h tShipName.h tsShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoProtection.pkg : tsFoProtection.pog
tsFoRaider.pkg : tsFoRaider.pog tStation.h tsFaction.h tTime.h tUnderOp.h tLRoot.h tLCenter.h tLProduction.h tLFleet.h tStationFilter.h tEconUtil.h tShipName.h tsShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoThugs.pkg : tsFoThugs.pog tStation.h tsFaction.h tTime.h tUnderOp.h tLRoot.h tLCenter.h tLProduction.h tLFleet.h tStationFilter.h tEconUtil.h tShipName.h tsShipCreation.h tsFleetOpCombat.h tsDebug.h
tsPilotSetup.pkg : tsPilotSetup.pog tEpicComms.h tsShip.h tLRoot.h tLTrade.h tsFaction.h tETradeSell.h tEpicMoney.h tShipName.h tPcOwner.h tLProduction.h tLFleet.h tUnderOp.h tPodUtil.h tRepWatch.h tsEvent.h

tsWingman.pkg : tsWingman.pog tsShip.h tFormation.h tPodUtil.h tsFaction.h tStationEnum.h tStation.h tLProduction.h tMegaTrucking.h tStationFilter.h

#ts_StationEvent.pkg : ts_StationEvent.pog UniGUI.h tTime.h tsFaction.h tMail.h tShipMail.h tNewsNet.h tStation.h tEconUtil.h tUnderOp.h tLProduction.h

uString.pkg : uString.pog
zTestCapsule.pkg : zTestCapsule.pog tsShip.h
zTestCargo.pkg : zTestCargo.pog tEconUtil.h tETradeBuy.h tPogClass.h tLRoot.h tLTrade.h tEpicMoney.h tTime.h tsFaction.h tsShip.h tPodUtil.h tsShipCreation.h tPcOwner.h
zTestCode.pkg : zTestCode.pog tEconUtil.h tETradeBuy.h tPogClass.h tLRoot.h tLTrade.h tEpicMoney.h tTime.h tsFaction.h tsShip.h tPodUtil.h tsShipCreation.h
zTestExp.pkg : zTestExp.pog tEconUtil.h tETradeBuy.h tPogClass.h tLRoot.h tLTrade.h tEpicMoney.h tTime.h tsFaction.h tsShip.h tPodUtil.h tsShipCreation.h tPcOwner.h
zTestFacShip.pkg : zTestFacShip.pog
zTestObject.pkg : zTestObject.pog

