
/*
   The station status controls the type of traffic that exists around a station.

   ESS_Destroyed: Station reduced to debris field.
   ESS_Empty:     Station exists, but abandond.
   ESS_Building:  Station under construction.
   ESS_Normal:    Station intact and operating.
   ESS_Leaving:   Station is being abandond.
   ESS_Fleeing:   Station was destroyed, survivors fleeing.
   ESS_NeverBuilt: Station has not yet been created.
*/

enum eStationStatus {
   ESS_Destroyed = 0,
   ESS_Normal = 1,
   ESS_Empty = 2, 
   ESS_Building = 4,
   ESS_Leaving = 8,
   ESS_Fleeing = 16,
   ESS_NeverBuilt = 32
};



// Production type of the station or operation.
// Replaces station type, controls planning,
// Update, and Start and End planning.

enum eProductionType
{
	ept_Invalid = 0,

   // Epic has a special faction for disused stations. Every station should
   // have a valid type that tells us what the station was built to do.
   // Do not use this value.
	ept_Disused = 1, 


   // Mines consume some raw materials and
   // manufactured goods, and produce lots of 
   // raw ore.
	ept_WaterMine = 2,
	ept_OrganicsMine = 3,
	ept_InorganicsMine = 4,
	ept_BiomassMine = 5,
	ept_CommonMetalsMine = 6,
	ept_RareMetalsMine = 7,
	ept_ExoticMetalsMine = 8,
	ept_RadioactivesMine = 9,
	ept_FusionableGasesMine = 10,


   // Processing plants consume raw materials and
   // create processed materials and simple 
   // goods.
	ept_WaterProcessingPlant = 11,
	ept_OrganicsProcessingPlant = 12,
	ept_InorganicsProcessingPlant = 13,
	ept_BiomassProcessingPlant = 14,
	ept_CommonMetalsProcessingPlant = 15,
	ept_RareMetalsProcessingPlant = 16,
	ept_ExoticMetalsProcessingPlant = 17,
	ept_RadioactivesProcessingPlant = 18,
	ept_FusionableGasesProcessingPlant = 19,
	ept_NeutroniumProcessingPlant = 20,


   // Manufacturing plants are the highest paying 
   // corporate station. Consuming processed goods and
   // other manufactures to produce manufactured items.
	ept_Shipyard = 21,

	ept_HeavyManufacturingPlant = 22,
   ept_BiologicalManufacturingPlant = 23,
	ept_WetwareManufacturingPlant = 24,
	ept_HiTechManufacturingPlant = 25,
	ept_ElectronicsManufacturingPlant = 26,
	ept_WeaponsManufacturingPlant = 27,
	ept_PharmaceuticalsManufacturingPlant = 28,
	ept_PlasticsManufacturingPlant = 29,
	ept_FusionReactorsManufacturingPlant = 30,
	ept_EnergyCellsManufacturingPlant = 31,
	ept_StationFabricationManufacturingPlant = 32,
	ept_LuxuriesManufacturingPlant = 33,


//	ept_TerraformingStation = 34,
//	ept_BioBomber = 35,


   // The backbone of the systems transporation network. Freight ships 
   // refule and conduct minor repairs. They consume most of 
   // ship fuel in the cluster.
   // The player can hire freight ships at this station.
	ept_Waystation = 36,



//	ept_RepairStation = 37,
//	ept_OreTransferStation = 38,


//	ept_ResearchAndDevelopmentLab = 39,


   // Does research and develops new products for manufacturing and 
   // other profit making stations. Houses operations that provide
   // hacking tools.
	ept_ResearchStation = 40,

//	ept_MedicalResearchCentre = 41,
// ept_BlackBudgetResearchStation = 42,
//	ept_SensitiveResearchStation = 43,
//	ept_FinancialCentre = 44,
//	ept_RegionalHQ = 45,
//	ept_Villa = 46,


   // A central HQ is the main base for a mega corporation. The 
   // mega corp can have only one HQ, and it belongs to the 
   // government that controls the system where this station
   // is located.
	ept_CentralHQ = 47,



   // The food production station. These stations can also be used to represent food 
   // production of planets.
	ept_AgriculturalSettlement = 48,


//	ept_Resort = 49,
//	ept_LuxuryResort = 50,

   // Population needing special medical care travel to these stations.
	ept_MedicalFacility = 51,


//	ept_LeisureComplex = 52,


   // Should be part of the mining stations listed above.
	ept_NeutroniumMine = 53,


   // A security station is a corporate fortress used to base
   // corporate mercenary forces. This station is the base
   // for launching attacks on surrounding stations.
   // Player: Can hire ships here
	ept_SecurityStation = 54,


//	ept_Fortress = 55,
//	ept_HighSecurityPrison = 56,
//	ept_LowSecurityPrison = 57,
// ept_HardLabourPrison = 58,
//	ept_Homestead = 59,



   // Every mercenary faction needs at least one mercenary base to hold the majority of the 
   // fleet. 
   // Player: can hire troops and ships here.
	ept_MercenaryBase = 60,

//	ept_TradingPost = 61,
//	ept_Warehousing = 62,


//	ept_BlackMarket = 63,
//	ept_DryDock = 64,
//	ept_DockingStation = 65,


   // Entertainment stations are bases for pirate vice dens,
   // and provide funds for mega corps
   // Player: Can purchase rumors here.
	ept_EntertainmentStation = 66,


   // The largest of the habitats. These stations represent huge population numbers
   // of planets or other well developed systems.
	ept_Settlement = 67,

   // A police station is a government station used to base
   // police forces for the defense and patrol of a planetary
   // system. Attacks on illegal operations are staged from
   // here.
	ept_PoliceBase = 68,


//	ept_PoliceOutpost = 69,
//	ept_SystemDefenceStation = 70,

   // The defense dock is the navy version of a police base. It houses
   // larger navy warships. Defense docks are built to bulk up the
   // governments forces. They can launch invasion operations.
	ept_SystemDefenceDock = 71,



//   ept_NavalAcademy = 72,
//	ept_NavalTrainingBase = 73,


   // ***************************************
   // Government stations. 
   //
   // Every system must have one (and only one) government station
   // The faction that controls this station, owns the system.


   // An outpost is the government control center of a system
   // that is not a capitol system. The faction that
   // controls this station is the government of this system.

   // Every system has one government control station. 
   // This is the smallest base possible and is placed in low population
   // systems. If there is no current government, this station
   // should be "NeverBuilt".
   // Scouts and scientists often operate out of these stations.
	ept_Outpost = 74,



//	ept_Base = 75,
//	ept_RepairDock = 76,
//	ept_MarineBarracks = 78,
//	ept_PerimeterDefences = 79,
//	ept_NavalTestingSite = 80,
//	ept_NavalResearchFacility = 81,
//	ept_JumpFortress = 82,
//	ept_SupplyDepot = 84,
//	ept_DefenceStation = 85,
//	ept_STCPost = 86,
//	ept_STCHQ = 87,
//	ept_FTLArray = 88,
//	ept_FTLInterchange = 89,
//	ept_STLTranceiver = 90,
// ept_STLInterchange = 91,
//	ept_PlanetaryAdministration = 92,

   // A senators station. Placed in developed systems with large populations.
   // A system of this size could be its own government.
   // The faction that controls this station, is the government of this system.
	ept_SystemAdministration = 93,


   // The center of a national government. When this station is destroyed 
   // the government will fracture. The government that controls this station
   // is the government of this system (and possibly many others).
	ept_ClusterAdministration = 94,


   // Governors are placed at critical edge systems. Governors represent the government
   // in middle population systems. The faction that controls this station
   // controls the government in this system.
	ept_RegionalDepartment = 95,





   // Most Religious Societies also have universities for educating the general 
   // population. (Secular society is considered a form of religion in this model.)
	ept_University = 96,

//	ept_Ark = 97,
//	ept_Garden = 98,
//	ept_Asylum = 99,
//	ept_Hospice = 100,


   // A pirate base is an armed HQ for a pirate faction. Every pirate faction should
   // have at least one of these bases hidden somewhere.
   // Player: can change identity at this station.
   // Player: can hire troops and ships here.
   // Player: can convert illegal pods to legal here.
	ept_PirateBase = 101,


   // A pirate cove is a pirate shipyard. You can sell captured ships to 
   // ship breakers here.
   // Player: can hire troops and ships here.
   // Player: can convert illegal pods to legal here.
	ept_PirateCove = 102,

   // A pirate outpost is a tiny base for used for conducting raids on shipping
   // and running tolls. Small but armed, there are often many of these bases
   // scattered around a system.
   // Player: can hire troops and ships here.
   // Player: can convert illegal pods to legal here.
	ept_PirateOutpost = 103,


//	ept_GangsterHideout = 104,
//	ept_ViceDen = 105,
//	ept_Casino = 106,
//	ept_CollectiveSettlement = 107,
//	ept_Hermitage = 108,

   // The center of a Religious Society. Each religion should have at least one
   // of these stations.
	ept_ReligiousCentre = 109,


//	ept_MadScientistLab = 110,
//	ept_Hideout = 111,


   // The habitat is the population center station. 
	ept_Habitat = 112


//	ept_Junkyard = 113,
//	ept_BoxTown = 114,
//	ept_AsteroidSculptures = 115,
//	ept_PlayerBase = 116,
//	ept_GunstarArray = 117,
//	ept_JumpAccelerator = 118,
//	ept_HoffersGap = 119,
//	ept_HoffersHeel = 120,
//	ept_Beanstalk = 121,
//	ept_TransferStation = 122,

};	
