#
# Data about EoC
#
#
# TODO:
#
# Tornstars:
#
# 	station types : ept_* : ./pog/include/tsStationEnum.h : ./MS_Mod_Main/TEXT/gt_station_types.csv
#		Factions			: US_Mod_Geog/faction_info.ini && ./MS_Mod_Main/TEXT/faction_names.csv
#		Cargo's				: 
#
#
# Factions:
#
# eoc_allegiance (enum type) -> [something in eoc] - Human Readable names -> iFaction.Find(name)
# name -> US_Mod_Geog/faction_info.ini
#
# find the eoc faction enum -> name string.
# 
#

EntityTypes = (
'ET_Body',
'ET_Station',
'ET_Lpoint',
'ET_Unused',
'ET_Belt',
'ET_Star',
'ET_Gunstar',
'ET_Nebula'
)

BodyTypes = (
'BT_SystemCentre',
'BT_Star',
'BT_Planet',
'BT_Moon',
'BT_GasGiant',
'BT_Asteroid',
'BT_DeadGasGiantCore',
'BT_AsteroidBelt',
'BT_Nebula',
'BT_Invalid'
)

HabitatType = (
	'HT_Invalid',
	'HT_Disused',
	'HT_WaterMine',
	'HT_OrganicsMine',
	'HT_InorganicsMine',
	'HT_BiomassMine',
	'HT_CommonMetalsMine',
	'HT_RareMetalsMine',
	'HT_ExoticMetalsMine',
	'HT_RadioactivesMine',
	'HT_FusionableGasesMine',
	'HT_WaterProcessingPlant',
	'HT_OrganicsProcessingPlant',
	'HT_InorganicsProcessingPlant',
	'HT_BiomassProcessingPlant',
	'HT_CommonMetalsProcessingPlant',
	'HT_RareMetalsProcessingPlant',
	'HT_ExoticMetalsProcessingPlant',
	'HT_RadioactivesProcessingPlant',
	'HT_FusionableGasesProcessingPlant',
	'HT_NeutroniumProcessingPlant',
	'HT_Shipyard',
	'HT_HeavyManufacturingPlant',
	'HT_BiologicalManufacturingPlant',
	'HT_WetwareManufacturingPlant',
	'HT_HiTechManufacturingPlant',
	'HT_ElectronicsManufacturingPlant',
	'HT_WeaponsManufacturingPlant',
	'HT_PharmaceuticalsManufacturingPlant',
	'HT_PlasticsManufacturingPlant',
	'HT_FusionReactorsManufacturingPlant',
	'HT_EnergyCellsManufacturingPlant',
	'HT_StationFabricationManufacturingPlant',
	'HT_LuxuriesManufacturingPlant',
	'HT_TerraformingStation',
	'HT_BioBomber',
	'HT_Waystation',
	'HT_RepairStation',
	'HT_OreTransferStation',
	'HT_ResearchAndDevelopmentLab',
	'HT_ResearchStation',
	'HT_MedicalResearchCentre',
	'HT_BlackBudgetResearchStation',
	'HT_SensitiveResearchStation',
	'HT_FinancialCentre',
	'HT_RegionalHQ',
	'HT_Villa',
	'HT_CentralHQ',
	'HT_AgriculturalSettlement',
	'HT_Resort',
	'HT_LuxuryResort',
	'HT_MedicalFacility',
	'HT_LeisureComplex',
	'HT_NeutroniumMine',
	'HT_SecurityStation',
	'HT_Fortress',
	'HT_HighSecurityPrison',
	'HT_LowSecurityPrison',
	'HT_HardLabourPrison',
	'HT_Homestead',
	'HT_MercenaryBase',
	'HT_TradingPost',
	'HT_Warehousing',
	'HT_BlackMarket',
	'HT_DryDock',
	'HT_DockingStation',
	'HT_EntertainmentStation',
	'HT_Settlement',
	'HT_PoliceBase',
	'HT_PoliceOutpost',
	'HT_SystemDefenceStation',
	'HT_SystemDefenceDock',
	'HT_NavalAcademy',
	'HT_NavalTrainingBase',
	'HT_Outpost',
	'HT_Base',
	'HT_RepairDock',
	None, # no entry for 77
	'HT_MarineBarracks',
	'HT_PerimeterDefences',
	'HT_NavalTestingSite',
	'HT_NavalResearchFacility',
	'HT_JumpFortress',
	None, # no entry for 83
	'HT_SupplyDepot',
	'HT_DefenceStation',
	'HT_STCPost',
	'HT_STCHQ',
	'HT_FTLArray',
	'HT_FTLInterchange',
	'HT_STLTranceiver',
	'HT_STLInterchange',
	'HT_PlanetaryAdministration',
	'HT_SystemAdministration',
	'HT_ClusterAdministration',
	'HT_RegionalDepartment',
	'HT_University',
	'HT_Ark',
	'HT_Garden',
	'HT_Asylum',
	'HT_Hospice',
	'HT_PirateBase',
	'HT_PirateCove',
	'HT_PirateOutpost',
	'HT_GangsterHideout',
	'HT_ViceDen',
	'HT_Casino',
	'HT_CollectiveSettlement',
	'HT_Hermitage',
	'HT_ReligiousCentre',
	'HT_MadScientistLab',
	'HT_Hideout',
	'HT_Habitat',
	'HT_Junkyard',
	'HT_BoxTown',
	'HT_AsteroidSculptures',
	'HT_PlayerBase',
	'HT_GunstarArray',
	'HT_JumpAccelerator',
	'HT_HoffersGap',
	'HT_HoffersHeel',
	'HT_Beanstalk',
	'HT_TransferStation'
)

eoc_allegiance = (
	'A_Neutral',
	'A_Independent',
	'A_Exile',
	'A_Military',
	'A_Underworld',
	'A_Government',
	'A_Transient',
	'A_Society',
	'A_Invalid',
	'A_Stepson',
	'A_Kong',
	'A_MAASCorporation',
	'A_CarvaCartel',
	'A_Junkers',
	'A_Police',
	'A_NOMEXCorporation',
	'A_NSOLaplace',
	'A_Marauders',
	'A_Angels',
	'A_TheOman',
	'A_MCA',
	'A_Player',
	'A_League',
	'A_TrimannShipping',
	'A_RhondusGasMining',
	'A_AshantiInvestment',
	'A_CrosspointMinerals',
	'A_HeliosMining',
	'A_JardinTerraforming',
	'A_ChonBodifule',
	'A_OrionProducts',
	'A_VonShellingIndustries',
	'A_MegalithCorp',
	'A_HibatshPMC',
	'A_DesterCorporation',
	'A_WhindWeaponsSystems',
	'A_AdvancedSecurityCorp',
	'A_Network54',
	'A_Infonet',
	'A_StellarNet',
	'A_WordsworthTechnology',
	'A_NetcomSA',
	'A_CoventryEngineeringResearch',
	'A_NINEXWetware',
	'A_UniversalConsumerProducts',
	'A_HighlifeProducts',
	'A_LowOrbitRecovery',
	'A_KIMOShipping',
	'A_DatagonTechnologies',
	'A_MicoriaCommunications',
	'A_LOMAXEngines',
	'A_LOMAXTechnologies',
	'A_NumikoProducts',
	'A_TheThirdWay',
	'A_Aliens',
)
