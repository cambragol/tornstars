//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsShipCreation.h
//
// Compiler-generated export header for package "tsShipCreation"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype string tsShipCreation.GetShip( hfaction faction, etsShipType ship_type );

prototype string tsShipCreation.ShipClassTemplate( string faction, string fleet_style, string ship_class );

prototype string tsShipCreation.ShipType2String( etsShipType ship_type );

prototype etsShipType tsShipCreation.String2ShipType( string type_name );

prototype tsShipCreation.Init();

prototype tsShipCreation.TestINIFile();

// EOF /////////////////////////////////////////////////////////////////////////

