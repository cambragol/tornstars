//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsFleetOpFilter.h
//
// Compiler-generated export header for package "tsFleetOpFilter"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype list tsFleetOpFilter.FilterOperations( list station_list );

prototype list tsFleetOpFilter.FilterSystem( list op_list, string system );

prototype list tsFleetOpFilter.FilterType( list operation_list, eProductionType prod_type );

prototype list tsFleetOpFilter.FilterKnown( list operation_list, bool known );

prototype list tsFleetOpFilter.FilterNearby( list op_list, hisim center, float distance );

prototype hisim tsFleetOpFilter.FindNearest( list op_list, hisim center );

// EOF /////////////////////////////////////////////////////////////////////////

