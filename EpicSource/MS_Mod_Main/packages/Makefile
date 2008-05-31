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

FLAGS = --quiet

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
	$(POG_COMPILER) $(FLAGS) -i $(INCLUDE_PATH) -i $(PS_INCLUDE_PATH) -i $(INCLUDE_PKG) -hp $(INCLUDE_PKG) -pp $(PACKAGE_PATH) $<
	cp $(PACKAGE_PATH)/$@ $(MOD_PATH)/packages
	
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


PACKAGES = ECargoTypes.pkg \
	UniGUI.pkg \
	UniGUIBase.pkg \
	UniGUIMisc.pkg \
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
	tsMain.pkg




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

tsBaseNet.pkg : tsBaseNet.pog tsMail.h

tsChangeIdGui.pkg : tsChangeIdGui.pog UniGUI.h tsGui.h tsSaveGui.h tsEconUtil.h tsShip.h tsMoney.h tsFaction.h
tsPlayerShipPurGui.pkg : tsPlayerShipPurGui.pog UniGUI.h tsFaction.h tsGui.h tsSaveGui.h tsMoney.h


tsDistance.pkg : tsDistance.pog
tEAutoWatch.pkg : tEAutoWatch.pog tsTime.h tsLCenter.h tsFaction.h tsShip.h tsFormation.h tsMusic.h tsReputationWatch.h tsLocationInit.h

#tECommEvent.pkg : tECommEvent.pog

tsFaction.pkg : tsFaction.pog tsStation.h
tsPlayerFleetGui.pkg : tsPlayerFleetGui.pog tsGui.h tsLProduction.h tsMoney.h tsShip.h tsEconUtil.h tsString.h
tsCapsuleJump.pkg : tsCapsuleJump.pog tsGui.h tsShip.h tsTime.h tsPlayerFleet.h tsDistance.h tsDebug.h
tsLpointFindGui.pkg : tsLpointFindGui.pog tsGui.h 
tEPlayerOrders.pkg : tEPlayerOrders.pog tsShip.h tsFormation.h tsPodUtil.h tsFaction.h tsStation.h tsLProduction.h tsMegaTrucking.h
tsPlayerWatch.pkg : tsPlayerWatch.pog tsTime.h tsLCenter.h tsFaction.h tsShip.h tsFormation.h tsPlayerFleetUpkeep.h tsMusic.h tsReputationWatch.h tsLocationInit.h tsCapsuleJump.h
tsReferenceGui.pkg : tsReferenceGui.pog tsGui.h tsLProduction.h tsEconomy.h tsEconUtil.h tsMoney.h tsPodUtil.h tsString.h
tsShipCreation.pkg : tsShipCreation.pog tsFaction.h
tsStarSystem.pkg : tsStarSystem.pog tsFaction.h tsStation.h tsLProduction.h tsCapsuleJump.h
tsTradeBuy.pkg : tsTradeBuy.pog tsStation.h tsGui.h tsFaction.h tsLProduction.h tsLInventory.h tsLTrade.h tsEconomy.h tsEconUtil.h tsMoney.h tsPodUtil.h tsString.h tsSpewerOps.h

tsTradeSell.pkg : tsTradeSell.pog tsSpewerOps.h tsMegaTrucking.h tsStation.h tsGui.h tsFaction.h tsLProduction.h tsEconomy.h tsEconUtil.h tsMoney.h tsPodUtil.h tsLTrade.h tsString.h
tsEconomy.pkg : tsEconomy.pog tsEconUtil.h tsLProduction.h tsLTrade.h tsFaction.h ECargoTypes.h tsString.h tsStation.h
tsEconUtil.pkg : tsEconUtil.pog
tsEquipBuy.pkg : tsEquipBuy.pog tsStation.h tsGui.h tsFaction.h tsLProduction.h tsLInventory.h tsLTrade.h tsEconomy.h tsEconUtil.h tsMoney.h tsPodUtil.h tsString.h tsSpewerOps.h tsDescribeINI.h
tsEquipSell.pkg : tsEquipSell.pog tsStation.h tsGui.h tsFaction.h tsLProduction.h tsLInventory.h tsLTrade.h tsEconomy.h tsEconUtil.h tsMoney.h tsPodUtil.h tsString.h tsSpewerOps.h tsDescribeINI.h
tsDescribeINI.pkg : tsDescribeINI.pog tsStation.h tsGui.h tsFaction.h tsLProduction.h tsLInventory.h tsLTrade.h tsEconomy.h tsEconUtil.h tsMoney.h tsPodUtil.h tsString.h
tsShipComms.pkg : tsShipComms.pog
tsFactionGui.pkg : tsFactionGui.pog tsFaction.h tsGui.h tsMoney.h


tsPosition.pkg : tsPosition.pog

#tEpicFaction_t.pkg : tEpicFaction_t.pog tEpicFaction.h

tsShip.pkg : tsShip.pog tsEconUtil.h tsPodUtil.h tsShipComms.h tsFormation.h tsFaction.h tsMegaTrucking.h
tsPlayerFleet.pkg : tsPlayerFleet.pog tsShip.h tsEconUtil.h tsPodUtil.h tsShipComms.h tsFormation.h tsFaction.h tsMegaTrucking.h
tsPlayerDeath.pkg : tsPlayerDeath.pog tsShip.h tsEconUtil.h tsPodUtil.h tsShipComms.h tsFormation.h tsFaction.h tsMegaTrucking.h
tsWingmanDeath.pkg : tsWingmanDeath.pog tsShip.h tsEconUtil.h tsPodUtil.h tsShipComms.h tsFormation.h tsFaction.h tsMegaTrucking.h tsWingComm.h
tsPlayerFleetUpkeep.pkg : tsPlayerFleetUpkeep.pog tsStationEnum.h tsShipEnum.h tsShip.h tsStation.h tsEconUtil.h tsEconomy.h tsPodUtil.h tsFaction.h tsShipMail.h tsMoney.h tsLProduction.h tsLInventory.h

tsShipSave.pkg : tsShipSave.pog tsPosition.h tsShip.h

tsPlayerSave.pkg : tsPlayerSave.pog tsShip.h tsShipSave.h 



#tsShipBack.pkg : tsShipBack.pog tsPodUtil.h tsShipComms.h


tsGui.pkg : tsGui.pog
tsNavGui.pkg : tsNavGui.pog tsStation.h tsGui.h tsEconUtil.h tsLProduction.h tsLFleet.h tsFleetOp.h tsFleetOpFilter.h tsStarSystem.h tsCapsuleJump.h 
tsMain.pkg : tsMain.pog tsTime.h tsDistance.h tMultimod.h UniGUI.h UniGUIBase.h tsNavGui.h tsFaction.h tsGui.h tsShip.h tsDistance.h tsWingComm.h tsPlayerWatch.h tsStationEnv.h tsShipComms.h tsFleetOp.h tsFleetOpSave.h tsLInventory.h tsEconomy.h tsTradeBuy.h tsTradeSell.h tsPlayerFleetGui.h tsExitGui.h tsStationSave.h tsStarSystem.h tsMusic.h tsMail.h tsNewsNet.h tsShipMail.h tsViewDock.h tsCapsuleJump.h  tsLpointFindGui.h tsStationRules.h tsFleetOpUpdate.h tsCrewSpeak.h tsReputationUpdate.h tsOptionsGui.h tsStartGui.h tsReferenceGui.h tsDebug.h
tsMoney.pkg : tsMoney.pog

#ECargoScript.h 

tEpicTrade.pkg : tEpicTrade.pog UniGUI.h ECargoTypes.h tsGui.h tsEconUtil.h tsEconomy.h tsPodUtil.h tsShip.h

tsExitGui.pkg : tsExitGui.pog UniGUI.h tsGui.h tsLProduction.h tsEconomy.h tsEconUtil.h tsMoney.h tsPodUtil.h tsString.h tsPlayerFleetUpkeep.h
tsFormation.pkg : tsFormation.pog

tsLCenter.pkg : tsLCenter.pog tsLRoot.h
tsLFleet.pkg : tsLFleet.pog tsLRoot.h
tsLInventory.pkg : tsLInventory.pog tsTime.h tsLRoot.h tsEconUtil.h tsStation.h
tsLProduction.pkg : tsLProduction.pog tsLRoot.h
tsLRoot.pkg : tsLRoot.pog
tsLTrade.pkg : tsLTrade.pog tsLRoot.h
tsLocationInit.pkg : tsLocationInit.pog tsEconUtil.h tsStation.h tsFleetOp.h tsLCenter.h tsLProduction.h tsStationEnv.h tsPogClass.h

tLock.pkg : tLock.pog
tsMail.pkg : tsMail.pog
tsMegaTrucking.pkg : tsMegaTrucking.pog
tMultimod.pkg : tMultimod.pog
tsMusic.pkg : tsMusic.pog tsString.h tsStation.h tsLProduction.h
tsMusicChange.pkg : tsMusicChange.pog tsMusic.h tsLProduction.h
tsMusicGui.pkg : tsMusicGui.pog tsMusic.h tsGui.h
tsNewsNet.pkg : tsNewsNet.pog UniGUI.h tsTime.h tsMail.h
tsOptionsGui.pkg : tsOptionsGui.pog UniGUI.h tsGui.h
tsClaimGui.pkg : tsOptionsGui.pog UniGUI.h tsGui.h tsFaction.h
tsStartGui.pkg : tsStartGui.pog UniGUI.h tsGui.h

tsPcAsteroidBelt.pkg : tsPcAsteroidBelt.pog tsCull.h tsLCenter.h
tsPcCargoShip.pkg : tsPcCargoShip.pog tsEconUtil.h tsEconomy.h tsStation.h tsStationFilter.h tsLRoot.h tsLTrade.h tsLProduction.h tsMoney.h tsTime.h tsFaction.h tsShip.h tsPodUtil.h tsSpewerOps.h tsPilotSetup.h tsShipCreation.h tsShipName.h tsString.h tsShip.h tsShipCreationEnum.h
tsPcConstructionShip.pkg : tsPcConstructionShip.pog tsShipComms.h tsShip.h tsLRoot.h tsLCenter.h tsLTrade.h tsFaction.h tsTradeSell.h tsMoney.h tsShipName.h tsPcOwner.h tsCull.h tsShip.h tsShipCreationEnum.h
tsPcCustomsToll.pkg : tsPcCustomsToll.pog tsShipCreation.h tsPodUtil.h tsShipComms.h tsShip.h tsFaction.h tsMoney.h tsShipName.h tsLCenter.h tsLFleet.h tsEconomy.h tsPcOwner.h tsPilotSetup.h tsShip.h tsShipCreationEnum.h
tsPcEmbezzleOp.pkg : tsPcEmbezzleOp.pog tsShipComms.h tsShip.h tsLRoot.h tsLTrade.h tsFaction.h tsTradeSell.h tsMoney.h tsShipName.h tsPcOwner.h tsLProduction.h tsLCenter.h tsFleetOp.h tsDistance.h tsShipCreation.h tsLFleet.h tsPilotSetup.h tsStationFilter.h tsDistance.h tsCapsuleJump.h tsCull.h tsShip.h tsShipCreationEnum.h
tsPcTankerOp.pkg : tsPcTankerOp.pog tsShipComms.h tsShip.h tsLRoot.h tsLTrade.h tsFaction.h tsTradeSell.h tsMoney.h tsShipName.h tsPcOwner.h tsLProduction.h tsLCenter.h tsFleetOp.h tsDistance.h tsShipCreation.h tsLFleet.h tsPilotSetup.h tsStationFilter.h tsDistance.h tsCapsuleJump.h tsCull.h tsShip.h tsShipCreationEnum.h
tsPcFenceShip.pkg : tsPcFenceShip.pog tsShipComms.h tsShip.h tsLRoot.h tsLTrade.h tsFaction.h tsTradeSell.h tsMoney.h tsShipName.h tsPcOwner.h tsLProduction.h tsFleetOp.h tsDistance.h tsShipCreation.h tsLFleet.h tsPilotSetup.h tsStationFilter.h tsDistance.h tsCapsuleJump.h tsCull.h tsShip.h tsShipCreationEnum.h
tsPcGuards.pkg : tsPcGuards.pog tsPodUtil.h tsShipComms.h tsShip.h tsFaction.h tsMoney.h tsShipName.h tsLCenter.h tsLFleet.h tsShipCreation.h tsPilotSetup.h tsCapsuleJump.h tsDistance.h tsFleetOp.h tsString.h tsEvent.h tsDistress.h tsPcOwner.h tsShip.h tsShipCreationEnum.h
tsPcHiredShip.pkg : tsPcHiredShip.pog tsShipComms.h tsShip.h tsFaction.h tsMoney.h tsShipName.h tsPcOwner.h tsCull.h tsShip.h tsShipCreationEnum.h
tsPcOwner.pkg : tsPcOwner.pog 
tsPcPirateToll.pkg : tsPcPirateToll.pog tsShipCreation.h tsPodUtil.h tsShipComms.h tsShip.h tsFaction.h tsMoney.h tsShipName.h tsLCenter.h tsLFleet.h tsEconomy.h tsPcOwner.h tsPilotSetup.h tsShip.h tsShipCreationEnum.h
tsPcPodScrapper.pkg : tsPcPodScrapper.pog tsPodUtil.h tsShipComms.h tsShip.h tsFaction.h tsMoney.h tsShipName.h tsCull.h tsShip.h tsShipCreationEnum.h
tsPcRumorSeller.pkg : tsPcRumorSeller.pog tsTime.h tsEconUtil.h tsStationFilter.h tsFleetOp.h tsFleetOpFilter.h tsShipComms.h tsShip.h tsFaction.h tsMoney.h tsShipName.h tsLCenter.h tsLProduction.h tsCull.h tsShip.h tsShipCreationEnum.h
tsPcTankerShip.pkg : tsPcTankerShip.pog tsShipComms.h tsShip.h tsFaction.h tsMoney.h tsShipName.h tsPcOwner.h tsCull.h tsShip.h tsShipCreationEnum.h
tsPcWeaponSeller.pkg : tsPcWeaponSeller.pog tsPcOwner.h tsShipComms.h tsShip.h tsLRoot.h tsLTrade.h tsFaction.h tsTradeBuy.h tsMoney.h tsShipName.h tsCull.h tsShip.h tsShipCreationEnum.h
tsPcWreckBelt.pkg : tsPcWreckBelt.pog tsCull.h tsFaction.h tsLCenter.h tsLFleet.h tsPodUtil.h

tsPodUtil.pkg : tsPodUtil.pog tsFaction.h
tsPogClass.pkg : tsPogClass.pog tsPcFenceShip.h tsPcAsteroidBelt.h tsPcConstructionShip.h tsPcCustomsToll.h tsPcPirateToll.h tsPcGuards.h tsPcHiredShip.h tsPcOwner.h tsPcPirateToll.h tsPcPodScrapper.h tsPcRumorSeller.h tsPcTankerShip.h tsPcWeaponSeller.h tsPcEmbezzleOp.h tsPcWreckBelt.h tsPcCargoShip.h
tsReputationUpdate.pkg : tsReputationUpdate.pog tsFaction.h
tsReputationWatch.pkg : tsReputationWatch.pog UniGUI.h tsTime.h tsShip.h tsFaction.h tsStarSystem.h tsWingman.h
tsSaveGui.pkg : tsSaveGui.pog tsTime.h tsMain.h tsGui.h tsLProduction.h UniGUI.h tsSpewerOps.h
tsShipMail.pkg : tsShipMail.pog UniGUI.h tsGui.h tsMail.h tsNewsNet.h
tsShipName.pkg : tsShipName.pog
tsSpewerOps.pkg : tsSpewerOps.pog tsMegaTrucking.h


tsStation.pkg : tsStation.pog tsFaction.pog tsStationEnum.h
tsStationAi.pkg : tsStationAi.pog tsFaction.pog tsStationEnum.h tsDistress.pog
tsStationEnv.pkg : tsStationEnv.pog tsPogClass.h tsPcOwner.h tsCull.h
tsStationFilter.pkg : tsStationFilter.pog tsEconUtil.h tsFaction.h tsStation.h tsLRoot.h tsLProduction.h tsLCenter.h tsLTrade.h tsStarSystem.h
tsStationRules.pkg : tsStationRules.pog tsTime.h tsStation.h tsFleetOp.h tsFleetOpFilter.h tsEconUtil.h tsLProduction.h tsLFleet.h tsFleetOpCall.h tsFaction.h
tsStationSave.pkg : tsStationSave.pog tsEconUtil.h tsFaction.h tsStation.h tsStationRules.h tsLRoot.h tsLProduction.h tsLFleet.h tsLCenter.h tsLTrade.h tsStarSystem.h

#tsStation_t.pkg : tsStation_t.pog tEpicFaction.h tsStation.h tsLProduction.h tsLCenter.h tsLFleet.h tLMission.h

tsTime.pkg : tsTime.pog
tsTimeAdvance.pkg : tsTimeAdvance.pog tsPodUtil.h tsStation.h tsTime.h tsShip.h
tsFleetOp.pkg : tsFleetOp.pog tsFaction.h tsStation.h tsLRoot.h tsLProduction.h tsLCenter.h tsLFleet.h
tsFleetOpFilter.pkg : tsFleetOpFilter.pog tsFleetOp.h tsLProduction.h tsLCenter.h
tsFleetOpGui.pkg : tsFleetOpGui.pog tsTime.h tsGui.h UniGUI.h tsLRoot.h tsLCenter.h tsFaction.h tsEconUtil.h tsLProduction.h tsLFleet.h tsFleetOp.h tsFleetOpFilter.h
tsFleetOpSave.pkg : tsFleetOpSave.pog tsFaction.h tsEconUtil.h tsFleetOp.h tsLRoot.h tsLProduction.h tsLCenter.h tsLFleet.h tsFleetOpCall.h
tsViewDock.pkg : tsViewDock.pog UniGUI.h
tsWingComm.pkg : tsWingComm.pog tsPlayerFleet.h tsPodUtil.h tsShipEnum.h tsShip.h tsWingman.h

#tsCargoShip.pkg : tsCargoShip.pog tsEconUtil.h tsEconomy.h tsStation.h tsStationFilter.h tsTradeBuy.h tsPogClass.h tsLRoot.h tsLTrade.h tsLProduction.h tsMoney.h tsTime.h tsFaction.h tsShip.h tsPodUtil.h tsSpewerOps.h tsPilotSetup.h tsShipCreation.h tsShipName.h tsString.h

tsCrewSpeak.pkg : tsCrewSpeak.pog tsString.h
tsCull.pkg : tsCull.pog tsPogClass.pog tsPcOwner.h
tsDebug.pkg : tsDebug.pog
tsDebugGui.pkg : tsDebugGui.pog UniGUI.pog tsGui.h
tsDistress.pkg : tsDistress.pog tsEvent.h
tsEvent.pkg : tsEvent.pog
tsFleetOpCombat.pkg : tsFleetOpCombat.pog tsStation.h tsFaction.h tsTime.h tsFleetOp.h tsLCenter.h tsLFleet.h tsLProduction.h
tsFleetOpUpdate.pkg : tsFleetOpUpdate.pog tsTime.h tsFleetOp.h tsFleetOpCall.h

tsFleetOpCall.pkg : tsFleetOpCall.pog tsStation.h tsFaction.h tsTime.h tsFleetOp.h tsLCenter.h tsLProduction.h tsFoEmbezzle.h tsFoTanker.h tsFoFleetAttack.h tsFoFleetDefense.h tsFoProtection.h tsFoThugs.h tsFoRaider.h tsFoCustoms.h tsFoPatrol.h
tsFoConstruction.pkg : tsFoConstruction.pog tsStation.h tsFaction.h tsTime.h tsFleetOp.h tsLCenter.h tsLProduction.h tsLFleet.h tsStationFilter.h tsShipName.h tsShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoCustoms.pkg : tsFoCustoms.pog tsStation.h tsFaction.h tsTime.h tsFleetOp.h tsLCenter.h tsLProduction.h tsLFleet.h tsStationFilter.h tsShipName.h tsShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoEmbezzle.pkg : tsFoEmbezzle.pog tsStation.h tsFaction.h tsTime.h tsFleetOp.h tsLCenter.h tsLProduction.h tsLFleet.h tsStationFilter.h tsShipName.h tsShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoTanker.pkg : tsFoTanker.pog tsStation.h tsFaction.h tsTime.h tsFleetOp.h tsLCenter.h tsLProduction.h tsLFleet.h tsStationFilter.h tsShipName.h tsShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoTrade.pkg : tsFoTrade.pog tsStation.h tsFaction.h tsTime.h tsFleetOp.h tsLCenter.h tsLProduction.h tsLFleet.h tsStationFilter.h tsShipName.h tsShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoFleetAttack.pkg : tsFoFleetAttack.pog tsStation.h tsFaction.h tsTime.h tsFleetOp.h tsLRoot.h tsLCenter.h tsLProduction.h tsLFleet.h tsStationFilter.h tsEconUtil.h tsShipName.h tsShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoFleetDefense.pkg : tsFoFleetDefense.pog tsStation.h tsFaction.h tsTime.h tsFleetOp.h tsLRoot.h tsLCenter.h tsLProduction.h tsLFleet.h tsStationFilter.h tsEconUtil.h tsShipName.h tsShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoPatrol.pkg : tsFoPatrol.pog tsStation.h tsFaction.h tsTime.h tsFleetOp.h tsLRoot.h tsLCenter.h tsLProduction.h tsLFleet.h tsStationFilter.h tsEconUtil.h tsShipName.h tsShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoProtection.pkg : tsFoProtection.pog
tsFoRaider.pkg : tsFoRaider.pog tsStation.h tsFaction.h tsTime.h tsFleetOp.h tsLRoot.h tsLCenter.h tsLProduction.h tsLFleet.h tsStationFilter.h tsEconUtil.h tsShipName.h tsShipCreation.h tsFleetOpCombat.h tsDebug.h
tsFoThugs.pkg : tsFoThugs.pog tsStation.h tsFaction.h tsTime.h tsFleetOp.h tsLRoot.h tsLCenter.h tsLProduction.h tsLFleet.h tsStationFilter.h tsEconUtil.h tsShipName.h tsShipCreation.h tsFleetOpCombat.h tsDebug.h
tsLoadoutGui.pkg : tsLoadoutGui.pog tsStation.h tsGui.h tsFaction.h tsLProduction.h tsLInventory.h tsLTrade.h tsEconomy.h tsEconUtil.h tsMoney.h tsPodUtil.h tsString.h 
tsPilotSetup.pkg : tsPilotSetup.pog tsShipComms.h tsShip.h tsLRoot.h tsLTrade.h tsFaction.h tsTradeSell.h tsMoney.h tsShipName.h tsPcOwner.h tsLProduction.h tsLFleet.h tsFleetOp.h tsPodUtil.h tsReputationWatch.h tsEvent.h

tsWingman.pkg : tsWingman.pog tsShip.h tsFormation.h tsPodUtil.h tsFaction.h tsStationEnum.h tsStation.h tsLProduction.h tsMegaTrucking.h tsStationFilter.h
tsString.pkg : tsString.pog




zTestCapsule.pkg : zTestCapsule.pog tsShip.h
zTestCargo.pkg : zTestCargo.pog tsEconUtil.h tsTradeBuy.h tsPogClass.h tsLRoot.h tsLTrade.h tsMoney.h tsTime.h tsFaction.h tsShip.h tsPodUtil.h tsShipCreation.h tsPcOwner.h
zTestCode.pkg : zTestCode.pog tsEconUtil.h tsTradeBuy.h tsPogClass.h tsLRoot.h tsLTrade.h tsMoney.h tsTime.h tsFaction.h tsShip.h tsPodUtil.h tsShipCreation.h
zTestExp.pkg : zTestExp.pog tsEconUtil.h tsTradeBuy.h tsPogClass.h tsLRoot.h tsLTrade.h tsMoney.h tsTime.h tsFaction.h tsShip.h tsPodUtil.h tsShipCreation.h tsPcOwner.h
zTestFacShip.pkg : zTestFacShip.pog
zTestObject.pkg : zTestObject.pog
zMapTest.pkg : zMapTest.pog UniGUI.h tsGui.h tsFaction.h

