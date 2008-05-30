
/*

   ESS_Destroyed: Station is only debris field.
   ESS_Empty:     Station exists, but abandond.
   ESS_Building:  Station under construction.
   ESS_Normal:    Station intact and operating.
   ESS_Leaving:   Station is being abandond.
   ESS_Fleeing:   Station was destroyed, survivors fleeing.
   ESS_NeverBuilt: Station has not yet been created.
   ESS_Finished: Station construction finished.
   
*/

enum eStationStatus {
   ESS_Invalid = 0,
   ESS_Destroyed = 1,
   ESS_Normal = 2,
   ESS_Empty = 4, 
   ESS_Building = 8,
   ESS_Leaving = 16,
   ESS_Fleeing = 32,
   ESS_NeverBuilt = 64,
   ESS_Finished = 128
};


enum eStationCategory {
   ESC_Invalid = 0,
   ESC_Mine = 1,
   ESC_Process = 2,
   ESC_Manufacture = 4, 
   ESC_Research = 8,
   ESC_Habitat = 16,
   ESC_Headquarters = 32,
   ESC_Pirate = 64,
   ESC_Transport = 128,
   ESC_Government = 256,
   ESC_Military = 512
};



// Production type of the station or operation.
// Replaces station type, controls planning,
// Update, and Start and End planning.

enum eProductionType
{
	ept_Invalid = 0,
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

   // Keeping heavy as the representative of manufacturing.
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
	ept_TerraformingStation = 34,
	ept_BioBomber = 35,
	ept_Waystation = 36,
	ept_RepairStation = 37,
	ept_OreTransferStation = 38,
	ept_ResearchAndDevelopmentLab = 39,


   // Does research and develops new products for manufacturing and 
   // other profit making stations. Houses operations that provide
   // hacking tools.
	ept_ResearchStation = 40,
	ept_MedicalResearchCentre = 41,
	ept_BlackBudgetResearchStation = 42,
	ept_SensitiveResearchStation = 43,
	ept_FinancialCentre = 44,
	ept_RegionalHQ = 45,
	ept_Villa = 46,


   // A central HQ is the main base for a mega corporation. The 
   // mega corp can have only one HQ, and it belongs to the 
   // government that controls the system where this station
   // is located.
	ept_CentralHQ = 47,


	ept_AgriculturalSettlement = 48,
	ept_Resort = 49,
	ept_LuxuryResort = 50,
	ept_MedicalFacility = 51,
	ept_LeisureComplex = 52,
	ept_NeutroniumMine = 53,


   // A security station is a corporate fortress used to base
   // corporate mercenary forces. This station is the base
   // for launching attacks on surrounding stations.
	ept_SecurityStation = 54,


	ept_Fortress = 55,
	ept_HighSecurityPrison = 56,
	ept_LowSecurityPrison = 57,
	ept_HardLabourPrison = 58,
	ept_Homestead = 59,
	ept_MercenaryBase = 60,
	ept_TradingPost = 61,


   // Warehousing form the backbone of the transportation network.
   // These stations provide the ships that move pods from system
   // to system. And inside a system. The warehouse represents
   // a shipping company.
	ept_Warehousing = 62,


	ept_BlackMarket = 63,
	ept_DryDock = 64,
	ept_DockingStation = 65,


   // Entertainment stations are bases for pirate vice dens,
   // and provide funds for mega corps
	ept_EntertainmentStation = 66,



	ept_Settlement = 67,

   // A police station is a government station used to base
   // police forces for the defense and patrol of a planetary
   // system. Attacks on illegal operations are staged from
   // here.
	ept_PoliceBase = 68,


	ept_PoliceOutpost = 69,
	ept_SystemDefenceStation = 70,

   // The defense dock is the navy version of a police base. It houses
   // larger navy warships. Defense docks are built to bulk up the
   // governments forces. They can launch invasion operations.
	ept_SystemDefenceDock = 71,



   ept_NavalAcademy = 72,
	ept_NavalTrainingBase = 73,


   // An outpost is the government control center of a system
   // that is not a capitol system. The faction that
   // controls this station is the government of this system.

   // Every system has one government control station. Even
   // nearly empty systems. This is the smallest base possible.
   // Scouts and scientists often operate out of these stations.
	ept_Outpost = 74,



	ept_Base = 75,
	ept_RepairDock = 76,
	ept_MarineBarracks = 78,
	ept_PerimeterDefences = 79,
	ept_NavalTestingSite = 80,
	ept_NavalResearchFacility = 81,
	ept_JumpFortress = 82,
	ept_SupplyDepot = 84,
	ept_DefenceStation = 85,
	ept_STCPost = 86,
	ept_STCHQ = 87,
	ept_FTLArray = 88,
	ept_FTLInterchange = 89,
	ept_STLTranceiver = 90,
	ept_STLInterchange = 91,
	ept_PlanetaryAdministration = 92,



	ept_SystemAdministration = 93,


   // The center of a national government. When this station is destroyed 
   // the government will fracture.
	ept_ClusterAdministration = 94,


   // A regional governors offices. Controls a territory. Responsible for
   // local defense and police.
	ept_RegionalDepartment = 95,


	ept_University = 96,
	ept_Ark = 97,
	ept_Garden = 98,
	ept_Asylum = 99,
	ept_Hospice = 100,


   // A pirate base is an armed station, typically hidden, used
   // for maintaining pirate fleets and enforcers. Also used
   // by rebels and spies as a base for covert operations.
   // There are always several of these hiding in every system
   // waiting to be occupied.
	ept_PirateBase = 101,


	ept_PirateCove = 102,
	ept_PirateOutpost = 103,
	ept_GangsterHideout = 104,
	ept_ViceDen = 105,
	ept_Casino = 106,
	ept_CollectiveSettlement = 107,
	ept_Hermitage = 108,
	ept_ReligiousCentre = 109,
	ept_MadScientistLab = 110,
	ept_Hideout = 111,


   // The habitat is the population center station. 
	ept_Habitat = 112,


	ept_Junkyard = 113,
	ept_BoxTown = 114,
	ept_AsteroidSculptures = 115,
	ept_PlayerBase = 116,
	ept_GunstarArray = 117,
	ept_JumpAccelerator = 118,
	ept_HoffersGap = 119,
	ept_HoffersHeel = 120,
	ept_Beanstalk = 121,
	ept_TransferStation = 122,


   //
   // These following enums are operations that do not map to stations.
   //

   // The center of an underworld faction. 
   ept_PirateHQOp = 123,

   // Planted on production stations to drain off funds for use by pirates.
   ept_EmbezzleOp = 124,

   // Planted on entertainment stations and habitats to generate funds for pirates.
   ept_ViceDenOp = 125,

   // Planted on research stations to create and sell hacking tools.
   ept_HackerOp = 126,

   // Planted on a medical station to provide and sell Cyber gear, new identities, transplants.
   ept_CyberOp = 127,

   //Planted by pirates on anyone elses station. This provides defense fleets for the
   //station, but at a cost to the station. 
   ept_ProtectionOp = 128,



   // A special operation, used to attack and destroy a specific target faction
   // from a specific location. Replaces the "plan" system.
   ept_FleetAttackOp = 129,

   // A special operation that adds extra defense to a station.
   ept_FleetDefenseOp = 130,

   // A covert operations center, with the goal of destroying a faction.
   ept_SpyAttackOp = 131,

   ept_SpyDefenseOp = 132,

   // A covert operations center, with the goal of neutralizing a 
   // faction to break them away from allies.
   ept_SpyNeutralOp = 133,

   // A special operation that signifies a major invasion of another
   // system. Run by an admiral and launched only from a Defense Dock,
   // the invasion tries to capture opposing stations, and destroy
   // rival fleets.
   ept_InvasionOp = 134,


   // This base draws funds and people from sympathetic habitats. 
   ept_RebelSupportOp = 135,


   // Creates a black market importer/exporter into the station.
   // Hides just outside of station range, and deals in goods with
   // the criminal element at marked up prices.
   // Especially popular when attached to weapons stations.
   ept_BlackMarketOp = 136,


   // Central command for a rebel faction.
   ept_RebelHQOp = 137,



   // Factions are also production centers. Included here,
   // they recieve the funds generated by other production
   // centers.

   // Perhaps I can use this to seperate how the factions
   // update funds, and where they put those funds....
   ept_Faction = 138,


   // A customs operation that charges the player to pass.
   ept_CustomsOp = 139,

   // A pirate operation that charges the player to pass.
   ept_PirateTollOp = 140,

   // Pirate warships that drive away other pirates, cops.
   ept_ThugsOp = 141,

   // Police, navy, corporate security patrol. Looks for
   // stolen cargo, pirates.
   ept_PatrolOp = 142,

   // Cargo raiders that do distant blockades of enemy stations.
   // They attack cargo ships outside of station guard radius.
   ept_RaiderOp = 143,

   ept_StationConstructionOp = 144,

   ept_StationRepairOp = 145,
   
   ept_TankerOp = 146,
   
   ept_TradeOp = 147

};	
