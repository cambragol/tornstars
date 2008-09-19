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

prototype task tsShipEscort.DeathScript( hship ship );

prototype tsShipEscort.CreateStandardEscort( hisim operation, hship leader, hgroup cull_group, string ship_name_group, string ship_type );

prototype tsShipEscort.CreateMixedEscort( hisim operation, hship leader, hgroup cull_group, string ship_name_group, bool use_maxfleets, int fighter_ships, int light_ships, int heavy_ships, int capital_ships );

// EOF /////////////////////////////////////////////////////////////////////////

