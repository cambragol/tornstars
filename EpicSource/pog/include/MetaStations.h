
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






//*************************************************************
//*************************************************************
//*************************************************************
//*************************************************************
//
// Faction ownership limitations described in detail here.
//

enum FactionOwners{

   // ***************************************
   // Government stations. 
   //
   // Government control of a star system is represented by owning one of these
   // Admin stations. Only governments can own these stations. 

   // Only one Admin station per system is allowed. (only one government).
   // If the station has not been built, or is destroyed, the
   // government of the system becomes "Empty" faction 
   // and the system is in anarcy.

   // These stations vary in size depending on the total growth population
   // of stations that the system could support.

   // The stations have defense forces and also send out customs patrols to
   // collect taxes.
	HT_Outpost = 74,
	HT_SystemAdministration = 93,
	HT_ClusterAdministration = 94,
	HT_RegionalDepartment = 95,


   // Governments also operation extra stations for defense, patrol and attack.
	HT_PoliceBase = 68,
	HT_SystemDefenceDock = 71,


   // Governments have bases for research and spies.
   HT_BlackBudgetResearchStation = 42,



   // *******************************************************
   //
   // Independent Peoples
   //
   // Each station is owned by a seperate group of people. 
   // Independents own all the habitat and settlements. 
   // They are not a central government or a corporation so
   // they don't own security stations or central HQ stations.

   // In democracy the people will be allied with the government
   // and the government will provide protection.

   // In a dictatorship, this will be less true. The people may end
   // up using pirates for protection. Or they may be allied 
   // with a rebel government.

   // Independents represent the citizens of the cluster.
   // And they alone can own the settlements and habitats.
	HT_Settlement = 67,
	HT_Habitat = 112
	HT_AgriculturalSettlement = 48,


   // Independents can also own any of the standard production stations.
  	HT_WaterMine = 2,
	HT_WaterProcessingPlant = 11,
	HT_HeavyManufacturingPlant = 22,


	HT_Shipyard = 21,
	HT_Waystation = 36,
	HT_Warehousing = 62,
   HT_FTLArray = 88,


	HT_MedicalFacility = 51,
	HT_EntertainmentStation = 66,
	HT_Casino = 106,
   HT_Resort = 49,



   //************************************************
   // Mega Corporation

   // A central HQ is the main base for a mega corporation. The 
   // mega corp can have only one HQ, and it belongs to the 
   // government that controls the system where this station
   // is located.
	HT_CentralHQ = 47,

   // Megacorporations are almost like mini governments
   // and they can fund stations for non-profit purposes
   // such as SecurityStations. 

   // These stations protect nearby corporate stations and
   // maintain order outside of government systems.
	HT_SecurityStation = 54,

   // Mega corporations have the funds to finance huge
   // research centers. They often try to steal research from 
   // one another.
	HT_ResearchStation = 40,


   // Megacorporations can own any of the mines, processing plants, or 
   // manufacturing plants. (only 3 types represented here).
	HT_WaterMine = 2,
	HT_WaterProcessingPlant = 11,
	HT_HeavyManufacturingPlant = 22,


	HT_Shipyard = 21,
	HT_Waystation = 36,
	HT_Warehousing = 62,

   HT_FTLArray = 88,

	HT_MedicalFacility = 51,
	HT_EntertainmentStation = 66,
	HT_Casino = 106,
   HT_Resort = 49,



   // ***********************************************************
   //
   // Pirate Stations
   //
   //

   // Most of the pirate stations are tiny hidden bases
   // lurking beside one of the billions of 1km or so sized bits 
   // of ice and rock that surround most stars.
	HT_PirateBase = 101,
	HT_PirateCove = 102,
	HT_PirateOutpost = 103,
	HT_BlackMarket = 63,

   // Pirates can run casinos, but they need to stay far
   // from governments who can see and destroy these stations.
	HT_Casino = 106,

  


   //**************************************
   // Mercenaries
   //
   //
   // Mercenary factions will hire out armed warfleets to
   // other friendly factions. They are centered around a 
   // well armed mercenary bases.

   // Governments are often the largest supporters of mercenaries
   // who do thier fighting in places the government cannot 
   // take the Navy without starting a war.
	HT_MercenaryBase = 60,

   // Smaller base, closer to the action.
	HT_Fortress = 55,

};



// **********************************************
// **********************************************
// **********************************************
//
//  This section describes each station in detail,
//  and the purpose each station serves.

enum StationDetails
{
   // A central HQ is the main base for a mega corporation. The 
   // mega corp can have only one HQ, and it belongs to the 
   // government that controls the system where this station
   // is located.
	HT_CentralHQ = 47,


   // A security station is a corporate fortress used to base
   // corporate mercenary forces. This station is the base
   // for launching attacks on surrounding stations.
   // Player: Can hire ships here
	HT_SecurityStation = 54,



	HT_WaterMine = 2,
	HT_WaterProcessingPlant = 11,
	HT_HeavyManufacturingPlant = 22,


   HT_FTLArray = 88,


	HT_Shipyard = 21,




   // The backbone of the systems transporation network. Freight ships 
   // refule and conduct minor repairs. They consume most of 
   // ship fuel in the cluster.
   // The player can hire freight ships at this station.
	HT_Waystation = 36,



	HT_Warehousing = 62,


   // Does research and develops new products for manufacturing and 
   // other profit making stations. Houses operations that provide
   // hacking tools.
	HT_ResearchStation = 40,




   // The habitat is the population center station. 
	HT_Habitat = 112


   // The largest of the habitats. These stations represent huge population numbers
   // of planets or other well developed systems.
	HT_Settlement = 67,


   // The food production station. These stations can also be used to represent food 
   // production of planets.
	HT_AgriculturalSettlement = 48,


   // Population needing special medical care travel to these stations.
	HT_MedicalFacility = 51,


   // Entertainment stations are bases for pirate vice dens,
   // and provide funds for mega corps
   // Player: Can purchase rumors here.
	HT_EntertainmentStation = 66,


	HT_Casino = 106,


   HT_Resort = 49,




   //
   // Mercenaries
   //
   //

   // Every mercenary faction needs at least one mercenary base to hold the majority of the 
   // fleet. 
   // Player: can hire troops and ships here.

	HT_MercenaryBase = 60,


   // Smaller base, used
	HT_Fortress = 55,






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
	HT_Outpost = 74,

   // A senators station. Placed in developed systems with large populations.
   // A system of this size could be its own government.
   // The faction that controls this station, is the government of this system.
	HT_SystemAdministration = 93,


   // The center of a national government. When this station is destroyed 
   // the government will fracture. The government that controls this station
   // is the government of this system (and possibly many others).
	HT_ClusterAdministration = 94,


   // Governors are placed at critical edge systems. Governors represent the government
   // in middle population systems. The faction that controls this station
   // controls the government in this system.
	HT_RegionalDepartment = 95,



   // A police station is a government station used to base
   // police forces for the defense and patrol of a planetary
   // system. Attacks on illegal operations are staged from
   // here.
	HT_PoliceBase = 68,


   // The defense dock is the navy version of a police base. It houses
   // larger navy warships. Defense docks are built to bulk up the
   // governments forces. They can launch invasion operations.
	HT_SystemDefenceDock = 71,




   HT_BlackBudgetResearchStation = 42,





   // A pirate base is an armed HQ for a pirate faction. Every pirate faction should
   // have at least one of these bases hidden somewhere.
   // Player: can change identity at this station.
   // Player: can hire troops and ships here.
   // Player: can convert illegal pods to legal here.
	HT_PirateBase = 101,


   // A pirate cove is a pirate shipyard. You can sell captured ships to 
   // ship breakers here.
   // Player: can hire troops and ships here.
   // Player: can convert illegal pods to legal here.
	HT_PirateCove = 102,


   // A pirate outpost is a tiny base for used for conducting raids on shipping
   // and running tolls. Small but armed, there are often many of these bases
   // scattered around a system.
   // Player: can hire troops and ships here.
   // Player: can convert illegal pods to legal here.
	HT_PirateOutpost = 103,


	HT_BlackMarket = 63,

};	







// Spares, stored here at the bottom of the file for easy cut and paste to above.

enum Spares{

	UT_Invalid = 0,

   // Epic has a special faction for disused stations. Every station should
   // have a valid type that tells us what the station was built to do.
   // Do not use this value.
	UT_Disused = 1, 


   // Mega Corporation

	UT_WaterMine = 2,
	UT_WaterProcessingPlant = 11,
	UT_HeavyManufacturingPlant = 22,


	UT_Shipyard = 21,

	UT_Waystation = 36,



   // Mines consume some raw materials and
   // manufactured goods, and produce lots of 
   // raw ore.
	UT_WaterMine = 2,
	UT_OrganicsMine = 3,
	UT_InorganicsMine = 4,
	UT_BiomassMine = 5,
	UT_CommonMetalsMine = 6,
	UT_RareMetalsMine = 7,
	UT_ExoticMetalsMine = 8,
	UT_RadioactivesMine = 9,
	UT_FusionableGasesMine = 10,
	UT_NeutroniumMine = 53,

   // Processing plants consume raw materials and
   // create processed materials and simple 
   // goods.
	UT_WaterProcessingPlant = 11,
	UT_OrganicsProcessingPlant = 12,
	UT_InorganicsProcessingPlant = 13,
	UT_BiomassProcessingPlant = 14,
	UT_CommonMetalsProcessingPlant = 15,
	UT_RareMetalsProcessingPlant = 16,
	UT_ExoticMetalsProcessingPlant = 17,
	UT_RadioactivesProcessingPlant = 18,
	UT_FusionableGasesProcessingPlant = 19,
	UT_NeutroniumProcessingPlant = 20,


   // Manufacturing plants are the highest paying 
   // corporate station. Consuming processed goods and
   // other manufactures to produce manufactured items.

	UT_HeavyManufacturingPlant = 22,
   UT_BiologicalManufacturingPlant = 23,
	UT_WetwareManufacturingPlant = 24,
	UT_HiTechManufacturingPlant = 25,
	UT_ElectronicsManufacturingPlant = 26,
	UT_WeaponsManufacturingPlant = 27,
	UT_PharmaceuticalsManufacturingPlant = 28,
	UT_PlasticsManufacturingPlant = 29,
	UT_FusionReactorsManufacturingPlant = 30,
	UT_EnergyCellsManufacturingPlant = 31,
	UT_StationFabricationManufacturingPlant = 32,
	UT_LuxuriesManufacturingPlant = 33,



	UT_Shipyard = 21,


//	UT_TerraformingStation = 34,
//	UT_BioBomber = 35,


   // The backbone of the systems transporation network. Freight ships 
   // refule and conduct minor repairs. They consume most of 
   // ship fuel in the cluster.
   // The player can hire freight ships at this station.
	UT_Waystation = 36,



//	UT_RepairStation = 37,
//	UT_OreTransferStation = 38,


//	UT_ResearchAndDevelopmentLab = 39,


   // Does research and develops new products for manufacturing and 
   // other profit making stations. Houses operations that provide
   // hacking tools.
	UT_ResearchStation = 40,

//	UT_MedicalResearchCentre = 41,
// UT_BlackBudgetResearchStation = 42,
//	UT_SensitiveResearchStation = 43,
//	UT_FinancialCentre = 44,
//	UT_RegionalHQ = 45,
//	UT_Villa = 46,


   // A central HQ is the main base for a mega corporation. The 
   // mega corp can have only one HQ, and it belongs to the 
   // government that controls the system where this station
   // is located.
	UT_CentralHQ = 47,



   // The food production station. These stations can also be used to represent food 
   // production of planets.
	UT_AgriculturalSettlement = 48,


//	UT_Resort = 49,
//	UT_LuxuryResort = 50,

   // Population needing special medical care travel to these stations.
	UT_MedicalFacility = 51,


//	UT_LeisureComplex = 52,





   // A security station is a corporate fortress used to base
   // corporate mercenary forces. This station is the base
   // for launching attacks on surrounding stations.
   // Player: Can hire ships here
	UT_SecurityStation = 54,


//	UT_Fortress = 55,
//	UT_HighSecurityPrison = 56,
//	UT_LowSecurityPrison = 57,
// UT_HardLabourPrison = 58,
//	UT_Homestead = 59,



   // Every mercenary faction needs at least one mercenary base to hold the majority of the 
   // fleet. 
   // Player: can hire troops and ships here.
	UT_MercenaryBase = 60,

//	UT_TradingPost = 61,
//	UT_Warehousing = 62,


//	UT_BlackMarket = 63,
//	UT_DryDock = 64,
//	UT_DockingStation = 65,


   // Entertainment stations are bases for pirate vice dens,
   // and provide funds for mega corps
   // Player: Can purchase rumors here.
	UT_EntertainmentStation = 66,


   // The largest of the habitats. These stations represent huge population numbers
   // of planets or other well developed systems.
	UT_Settlement = 67,

   // A police station is a government station used to base
   // police forces for the defense and patrol of a planetary
   // system. Attacks on illegal operations are staged from
   // here.
	UT_PoliceBase = 68,


//	UT_PoliceOutpost = 69,
//	UT_SystemDefenceStation = 70,

   // The defense dock is the navy version of a police base. It houses
   // larger navy warships. Defense docks are built to bulk up the
   // governments forces. They can launch invasion operations.
	UT_SystemDefenceDock = 71,



//   UT_NavalAcademy = 72,
//	UT_NavalTrainingBase = 73,


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
	UT_Outpost = 74,



//	UT_Base = 75,
//	UT_RepairDock = 76,
//	UT_MarineBarracks = 78,
//	UT_PerimeterDefences = 79,
//	UT_NavalTestingSite = 80,
//	UT_NavalResearchFacility = 81,
//	UT_JumpFortress = 82,
//	UT_SupplyDepot = 84,
//	UT_DefenceStation = 85,
//	UT_STCPost = 86,
//	UT_STCHQ = 87,
//	UT_FTLArray = 88,
//	UT_FTLInterchange = 89,
//	UT_STLTranceiver = 90,
// UT_STLInterchange = 91,
//	UT_PlanetaryAdministration = 92,

   // A senators station. Placed in developed systems with large populations.
   // A system of this size could be its own government.
   // The faction that controls this station, is the government of this system.
	UT_SystemAdministration = 93,


   // The center of a national government. When this station is destroyed 
   // the government will fracture. The government that controls this station
   // is the government of this system (and possibly many others).
	UT_ClusterAdministration = 94,


   // Governors are placed at critical edge systems. Governors represent the government
   // in middle population systems. The faction that controls this station
   // controls the government in this system.
	UT_RegionalDepartment = 95,





   // Most Religious Societies also have universities for educating the general 
   // population. (Secular society is considered a form of religion in this model.)
	UT_University = 96,

//	UT_Ark = 97,
//	UT_Garden = 98,
//	UT_Asylum = 99,
//	UT_Hospice = 100,


   // A pirate base is an armed HQ for a pirate faction. Every pirate faction should
   // have at least one of these bases hidden somewhere.
   // Player: can change identity at this station.
   // Player: can hire troops and ships here.
   // Player: can convert illegal pods to legal here.
	UT_PirateBase = 101,


   // A pirate cove is a pirate shipyard. You can sell captured ships to 
   // ship breakers here.
   // Player: can hire troops and ships here.
   // Player: can convert illegal pods to legal here.
	UT_PirateCove = 102,

   // A pirate outpost is a tiny base for used for conducting raids on shipping
   // and running tolls. Small but armed, there are often many of these bases
   // scattered around a system.
   // Player: can hire troops and ships here.
   // Player: can convert illegal pods to legal here.
	UT_PirateOutpost = 103,


//	UT_GangsterHideout = 104,
//	UT_ViceDen = 105,
//	UT_Casino = 106,
//	UT_CollectiveSettlement = 107,
//	UT_Hermitage = 108,

   // The center of a Religious Society. Each religion should have at least one
   // of these stations.
	UT_ReligiousCentre = 109,


//	UT_MadScientistLab = 110,
//	UT_Hideout = 111,


   // The habitat is the population center station. 
	UT_Habitat = 112


//	UT_Junkyard = 113,
//	UT_BoxTown = 114,
//	UT_AsteroidSculptures = 115,
//	UT_PlayerBase = 116,
//	UT_GunstarArray = 117,
//	UT_JumpAccelerator = 118,
//	UT_HoffersGap = 119,
//	UT_HoffersHeel = 120,
//	UT_Beanstalk = 121,
//	UT_TransferStation = 122,

};	

