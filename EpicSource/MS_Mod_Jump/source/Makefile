
#
#  Make file for constructing Epic: Middle States Main package.
#

RELEASE_NUMBER = 7_3_0


BASE_PATH= c:\Epic\EpicSource
CODE_PATH= $(BASE_PATH)\pog
MAIN_PATH= $(BASE_PATH)\MS_Mod_Jump
PS_INCLUDE_PATH= $(CODE_PATH)\include_ps

INCLUDE_PATH= $(CODE_PATH)\include
INCLUDE_PKG= $(CODE_PATH)\include_pkg
PACKAGE_PATH= $(MAIN_PATH)\packages

TEXT_PATH= $(BASE_PATH)\TEXT
HTML_PATH= $(BASE_PATH)\html
INI_PATH= $(BASE_PATH)\INI
IMAGE_PATH= $(BASE_PATH)\images
DEBUG_PATH= $(BASE_PATH)\debug

MODULE=MS_Mod_Jump
DEBUG_MODULE=EpicDebug
MOD_PATH=c:\iwar2\mods\$(MODULE)

RELEASE_PATH=c:\projects\epic\release\Epic


POG_COMPILER = c:\iwar2\bin\release\pc.exe

.SUFFIXES : .pkg .pog


# Inference rule for building and moving updated pog files.
{}.pog{packages}.pkg:
	$(POG_COMPILER) -i $(INCLUDE_PATH) -i $(PS_INCLUDE_PATH) -i $(INCLUDE_PKG) -hp $(INCLUDE_PKG) -pp $(PACKAGE_PATH) $(*B).pog
	copy $(PACKAGE_PATH)\$(*B).pkg $(MOD_PATH)\packages

#{}.pog{include}.h :
#    	$(POG_COMPILER) -i $(INCLUDE_PATH) -i $(PS_INCLUDE_PATH) -hp $(INCLUDE_PATH) -pp $(PACKAGE_PATH) $(*B).pog
	



LOW =  tEpicGui tTime tMultimod\
	tEpicMoney\
	tDebug\
	uString\
        tPodUtil\
	tEpicComms\
	tEpicFleet\
	tEpicFleetUpkeep\
	tDistance\
	tSysInventory\
	tPogClass\
	tPcHiredShip\
	UniGUI UniGUIMisc UniGUIBase \
	tJumpPoint\
	jGiftCargo\
	tEpicLFPlus\
	tEPlayerOrders tWingComm \
	tEconUtil tEconSmall \
	tETradeBuy tETradeSell \
	
#	fsw_SystemDamage fsw_AutoRepair fsw_ENGCompact \		
#	flm_Ut fsw_SD fsw_AR fsw_EC \
#	tTimeAdvance \

MID = tLRoot tLCenter tLProduction \
	tStation tStationSave tStationEnv	

HIGH =	tEPlayerWatch\
	tEpicMain tSaveGui 
	



all: $(LOW) $(MID) $(HIGH) $(DEBUG)


headerclean:
	erase $(INCLUDE_PKG)\*.h

	
clean: 
	erase $(PACKAGE_PATH)\*.pkg





##########################

## Creating the Release


release: all release_dir copy_files

	




release_dir:
	-mkdir $(RELEASE_PATH)$(RELEASE_NUMBER)\mods\$(MODULE)\packages		
	-mkdir $(RELEASE_PATH)$(RELEASE_NUMBER)\mods\$(MODULE)\source			
	-mkdir $(RELEASE_PATH)$(RELEASE_NUMBER)\mods\$(MODULE)\include				
	-mkdir $(RELEASE_PATH)$(RELEASE_NUMBER)\mods\$(MODULE)\html					
	-mkdir $(RELEASE_PATH)$(RELEASE_NUMBER)\mods\$(MODULE)\TEXT
	-mkdir $(RELEASE_PATH)$(RELEASE_NUMBER)\mods\$(MODULE)\images\gui

	-mkdir $(RELEASE_PATH)$(RELEASE_NUMBER)\mods\$(DEBUG_MODULE)

copy_files:
	copy $(PACKAGE_PATH)\*.pkg $(RELEASE_PATH)$(RELEASE_NUMBER)\mods\$(MODULE)\packages
	copy $(INCLUDE_PATH)\*.h $(RELEASE_PATH)$(RELEASE_NUMBER)\mods\$(MODULE)\include	
	copy $(INCLUDE_PKG)\*.h $(RELEASE_PATH)$(RELEASE_NUMBER)\mods\$(MODULE)\include		
	copy $(HTML_PATH)\*.html $(RELEASE_PATH)$(RELEASE_NUMBER)\mods\$(MODULE)\html		
	copy $(TEXT_PATH)\*.csv $(RELEASE_PATH)$(RELEASE_NUMBER)\mods\$(MODULE)\TEXT
	copy $(INI_PATH)\*.ini $(RELEASE_PATH)$(RELEASE_NUMBER)\mods\$(MODULE)	
	copy $(IMAGE_PATH)\gui\*.* $(RELEASE_PATH)$(RELEASE_NUMBER)\mods\$(MODULE)\images\gui

	copy $(DEBUG_PATH)\*.ini $(RELEASE_PATH)$(RELEASE_NUMBER)\mods\$(DEBUG_MODULE)	

##########################

##  Pog files


jGiftCargo : packages\jGiftCargo.pkg

tEpicLFPlus : packages\tEpicLFPlus.pkg
LFPlus : packages\LFPlus.pkg

tMultimod : packages\tMultimod.pkg

Sandbox : packages\Sandbox.pkg

tAFOpKill : packages\tAFOpKill.pkg
tAFtest2.pog : packages\tAFtest2.pog
tBaseNet : packages\tBaseNet.pkg

tEAutoWatch : packages\tEAutoWatch.pkg

tDebug : packages\tDebug.pkg
tDebugGui : packages\tDebugGui.pkg

tEAction : packages\tEAction.pkg
tEActionEvent : packages\tEActionEvent.pkg
tEActionEvent_t : packages\tEActionEvent_t.pkg
tEActionNews : packages\tEActionNews.pkg
tEActionResponse : packages\tEActionResponse.pkg
tEActionSelect : packages\tEActionSelect.pkg



tECareer : packages\tECareer.pkg
tECareerEnum : packages\tECareerEnum.pkg
tECareerGui : packages\tECareerGui.pkg
tECareerRules : packages\tECareerRules.pkg


tECommEvent : packages\tECommEvent.pkg

tEIFFGui : packages\tEIFFGui.pkg

tEOGuard : packages\tEOGuard.pkg
tEOrderUtil : packages\tEOrderUtil.pkg

tEpicAction : packages\tEpicAction.pkg

tEpicFacGui : packages\tEpicFacGui.pkg
tEFaction : packages\tEFaction.pkg


tEconUtil : packages\tEconUtil.pkg
tEconSmall : packages\tEconSmall.pkg
tEpicTrade : packages\tEpicTrade.pkg
tETradeSell : packages\tETradeSell.pkg
tETradeBuy : packages\tETradeBuy.pkg

tEReferenceGui : packages\tEReferenceGui.pkg
tEpicMoney : packages\tEpicMoney.pkg

tFormation : packages\tFormation.pkg
tEpicFleet : packages\tEpicFleet.pkg
tEpicFleetUpkeep : packages\tEpicFleetUpkeep.pkg
tEFleetGui : packages\tEFleetGui.pkg
tRepWatch : packages\tRepWatch.pkg

tESysSetup : packages\tESysSetup.pkg


tEpicGui : packages\tEpicGui.pkg

tEpicMain : packages\tEpicMain.pkg

tEPlayerOrders : packages\tEPlayerOrders.pkg
tEPlayerWatch : packages\tEPlayerWatch.pkg

tEShipEvent : packages\tEShipEvent.pkg
tEShipUtil : packages\tEShipUtil.pkg
tESoundEvent : packages\tESoundEvent.pkg


tESysInfo : packages\tESysInfo.pkg

tFacLook : packages\tFacLook.pkg

tHackGui : packages\tHackGui.pkg
tHackNet : packages\tHackNet.pkg

tLCenter : packages\tLCenter.pkg
tLFleet : packages\tLFleet.pkg
tLFleetRules : packages\tLFleetRules.pkg
tLMission : packages\tLMission.pkg
tLocation : packages\tLocation.pkg
tLProdRules : packages\tLProdRules.pkg
tLProduction : packages\tLProduction.pkg
tLProduction_t : packages\tLProduction_t.pkg
tLInventory : packages\tLInventory.pkg
tLTrade : packages\tLTrade.pkg

tLRoot : packages\tLRoot.pkg

tMail : packages\tMail.pkg
tMusic : packages\tMusic.pkg
tMusicChange : packages\tMusicChange.pkg
tMusicGui : packages\tMusicGui.pkg

tNewsNet : packages\tNewsNet.pkg

tEpicComms : packages\tEpicComms.pkg
tPogClass : packages\tPogClass.pkg
tPcAsteroidBelt : packages\tPcAsteroidBelt.pkg
tPcHiredShip : packages\tPcHiredShip.pkg
tPcFenceShip : packages\tPcFenceShip.pkg
tPcWeaponSeller : packages\tPcWeaponSeller.pkg
tPcBlackMarket : packages\tPcBlackMarket.pkg

tPcConstructionShip : packages\tPcConstructionShip.pkg
tPcPodScrapper : packages\tPcPodScrapper.pkg
tPcRumorSeller : packages\tPcRumorSeller.pkg
tPcPirateToll : packages\tPcPirateToll.pkg
tPcCustomsToll : packages\tPcCustomsToll.pkg
tPcGuards : packages\tPcGuards.pkg


tPodUtil : packages\tPodUtil.pkg

tRepRules : packages\tRepRules.pkg
tReputation : packages\tReputation.pkg

tShipName : packages\tShipName.pkg

tSaveGui : packages\tSaveGui.pkg
tShipCreation : packages\tShipCreation.pkg
tShipMail : packages\tShipMail.pkg
tStation : packages\tStation.pkg
tStationDef : packages\tStationDef.pkg
tStationEnv : packages\tStationEnv.pkg

tLocationInit : packages\tLocationInit.pkg

tStationLook : packages\tStationLook.pkg
tStationModule : packages\tStationModule.pkg
tStationRules : packages\tStationRules.pkg
tStationSave : packages\tStationSave.pkg

tStation_t : packages\tStation_t.pkg


tSysInventory : packages\tSysInventory.pkg
tTime : packages\tTime.pkg
tTimeAdvance : packages\tTimeAdvance.pkg

tUnderOp : packages\tUnderOp.pkg
tUnderOpFilter : packages\tUnderOpFilter.pkg
tUnderOpGui : packages\tUnderOpGui.pkg
tUnderOpRules : packages\tUnderOpRules.pkg
tUnderOpSave : packages\tUnderOpSave.pkg
tUnderOp_t : packages\tUnderOp_t.pkg

tViewDock : packages\tViewDock.pkg

tWingComm : packages\tWingComm.pkg

tJumpPoint : packages\tJumpPoint.pkg
tEJump : packages\tEJump.pkg
tELpointFind : packages\tELpointFind.pkg
tJumpSim : packages\tJumpSim.pkg

uMark : packages\uMark.pkg

UniGUI : packages\UniGUI.pkg
UniGUIBase : packages\UniGUIBase.pkg
UniGUIMisc : packages\UniGUIMisc.pkg
uString : packages\uString.pkg


zDebugJump : packages\zDebugJump.pkg
zGuardTest : packages\zGuardTest.pkg
zPodDock : packages\zPodDock.pkg
zTestObject : packages\zTestObject.pkg
zTestCargo : packages\zTestCargo.pkg
zTestFacShip : packages\zTestFacShip.pkg
zTestSwap : packages\zTestSwap.pkg
zTestCapsule : packages\zTestCapsule.pkg

ExitCrashTest : packages\ExitCrashTest.pkg


zTestFrame : packages\zTestFrame.pkg
zWarp : packages\zWarp.pkg
zWarpTwo : packages\zWarpTwo.pkg
zzLocationFinder_unigui : packages\zzLocationFinder_unigui.pkg
zzUniGUI : packages\zzUniGUI.pkg

tDistance : packages\tDistance.pkg

tSensor : packages\tSensor.pkg

tLock : packages\tLock.pkg

ECargoTypes : packages\ECargoTypes.pkg

fsw_SD : packages\fsw_SD.pkg
fsw_AR : packages\fsw_AR.pkg
fsw_EC : packages\fsw_EC.pkg
flm_Ut : packages\flm_Ut.pkg
