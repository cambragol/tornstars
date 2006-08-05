//
// Jon Freise (GrandpaTrout) jon_freise@msn.com
//
// THIS MOD IS NOT MADE, DISTRIBUTED, OR SUPPORTED BY INFOGRAMES
// OR PARTICLE SYSTEMS LTD. ELEMENTS TM & (C) INFOGRAMES AND PARTICLE SYSTEMS LTD.
//
// Modified from CargoTypes.h
// 
//
//

// Include once only
#ifndef ECON_CARGO_TYPES_HDR
#define ECON_CARGO_TYPES_HDR

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Enumerations

enum eEconCargoCategory
{
   ECC_Invalid,
   ECC_Unused,

	// CS_Data
	ECC_Blueprints, 
	ECC_ConsumerData, 
	ECC_PrivateData, 
	ECC_SecureData, 
	ECC_Software,

	// CS_Electronics
	ECC_Avionics, 
	ECC_Computers, 
	ECC_ConsumerElectronics, 
	ECC_Cybernetics,
	ECC_DataStorage, 
	ECC_Instrumentation, 
	ECC_MedicalElectronics, 
	ECC_Nanotechnology,
	ECC_Robotics,

	// CS_HeavyEngineering
	ECC_AgriculturalEquipment, 
	ECC_Environmental, 
	ECC_MachineTools, 
	ECC_MiningEquipment,
	ECC_PowerSystems, 
	ECC_Terraforming, 
	ECC_Vehicles,

	// Luxuries
	ECC_Alcohol, 
	ECC_Art, 
	ECC_Furs, 
	ECC_Jewellery, 
	ECC_LuxuryConsumerGoods, 
	ECC_LuxuryFoodstuffs,
	ECC_Narcotics, 
	ECC_SportingGoods,

	// CS_ManufacturedGoods
	ECC_ConsumerGoods, 
	ECC_MedicalSupplies, 
	ECC_Pharmaceuticals, 
	ECC_SurvivalEquipment,

	// CS_OrganicMaterials
	ECC_Bacteria, 
	ECC_Biomass, 
	ECC_Fauna, 
	ECC_Flora, 
	ECC_Fungi, 
	ECC_GeneticMaterial, 
	ECC_ProcessedFoodstuffs,
	ECC_UnprocessedFoodstuffs, 
	ECC_Waste, 

	// CS_ProcessedMaterials
	ECC_AntimatterGoods, 
	ECC_ConstructionMaterial, 
	ECC_Exotics, 
	ECC_ReactorFuel, 
	ECC_Gemstones, 
	ECC_Hydrocarbons, 
	ECC_CommonMetals, 
	ECC_Radioactives,

	// CS_RawMaterials
	ECC_BulkChemicals, 
	ECC_Gasses, 

	ECC_Rocks, 
	ECC_IndustrialWater,

	// CS_WeaponSystems
	ECC_CombatVehicles, 
	ECC_NBCWarfare,  
	ECC_Ordinance, 
	ECC_PersonalWeapons, 
	ECC_SpacecraftWeapons, 
	ECC_SpacecraftDefenceSystems,

   // Added to CC to make econ simulation easier

   // Entertainment
   ECC_NightLife,
   ECC_Relaxation,
   ECC_HighLife,

   // Ore - need to break out for each mine type
	ECC_CommonOre, 
   ECC_OrganicOre,
   ECC_InorganicOre,
   ECC_RareOre,
   ECC_ExoticOre,
   ECC_RadioactiveOre,
   ECC_NeutroniumOre,
   
   // Small additions to processed goods
   ECC_LifeSupport,
   ECC_Neutronium,
   ECC_RareMetals,

   // Manufactured goods
   ECC_FusionReactors,

   // Medical care
   ECC_MedicalTreatment,

   // Population and workstaff
   ECC_Staff,
   ECC_ProfessionalStaff,
   ECC_Slaves,
   ECC_Refugees,

   // Transportation Grid support
   ECC_Transport,
   ECC_StarShip,
   ECC_ShipRefit,

   // makes for loops easy.
   ECC_MaxCargoCat
};


// EOF ////////////////////////////////////////////////////////////////////////

#endif // ECON_CARGO_TYPES_HDR
