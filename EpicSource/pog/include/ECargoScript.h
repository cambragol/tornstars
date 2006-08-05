//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// ECargoScript.h
//
// Compiler-generated export header for package "ECargoScript"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include/ECargoScript.h,v 1.2 2005/05/13 09:42:02 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype ECargoScript.Initialise();

prototype IeHabitatType ECargoScript.Int2HabitatType( int to_cast );

prototype string ECargoScript.HabitatType2String( IeHabitatType to_cast );

prototype set ECargoScript.CargoSetAll();

prototype set ECargoScript.CargoSetByCategory( eCargoCategory category );

prototype set ECargoScript.CargoSetBySuperSet( eCargoSuperSet superset );

prototype set ECargoScript.CargoSetByValue( eCargoValue value_band );

prototype set ECargoScript.CargoSetByMaxStanding( float standing );

prototype set ECargoScript.CargoSetByMinStanding( float standing );

prototype int ECargoScript.HabitatCargoCatProduced( IeHabitatType htype, eCargoCategory ccat );

prototype int ECargoScript.HabitatCargoCatUsed( IeHabitatType htype, eCargoCategory ccat );

prototype set ECargoScript.HabitatCargoSet( IeHabitatType location_type, int buy_or_sell );

prototype eCargoValue ECargoScript.CargoValueBandByPrice( int price );

prototype eCargoValue ECargoScript.CargoValueBandByType( eCargoType ctype );

prototype float ECargoScript.CargoStandingByType( eCargoType ctype );

prototype eCargoCategory ECargoScript.FirstCategoryInSuperSet( eCargoSuperSet superset );

prototype eCargoType ECargoScript.FirstTypeInCategory( eCargoCategory category );

prototype eCargoCategory ECargoScript.LastCategoryInSuperSet( eCargoSuperSet superset );

prototype eCargoType ECargoScript.LastTypeInCategory( eCargoCategory category );

prototype eCargoType ECargoScript.RandCargoTypeByCategory( eCargoCategory category );

prototype eCargoType ECargoScript.RandCargoTypeByHabitat( IeHabitatType location_type, int buy_or_sell );

prototype eCargoType ECargoScript.RandCargoTypeBySuperSet( eCargoSuperSet superset );

prototype eCargoType ECargoScript.RandCargoTypeByValue( eCargoValue value_band );

prototype eCargoType ECargoScript.RandCargoTypeByMaxStanding( float standing );

prototype eCargoType ECargoScript.RandCargoTypeByMinStanding( float standing );

prototype string ECargoScript.CargoSim( hcargo cargo );

// EOF /////////////////////////////////////////////////////////////////////////

