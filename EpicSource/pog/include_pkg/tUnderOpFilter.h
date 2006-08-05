//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tUnderOpFilter.h
//
// Compiler-generated export header for package "tUnderOpFilter"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tUnderOpFilter.h,v 1.1 2005/06/10 19:56:35 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype list tUnderOpFilter.FilterOperations( list station_list );

prototype list tUnderOpFilter.FilterSystem( list op_list, string system );

prototype list tUnderOpFilter.FilterType( list operation_list, eProductionType prod_type );

prototype list tUnderOpFilter.FilterKnown( list operation_list, bool known );

prototype list tUnderOpFilter.FilterNearby( list op_list, hisim center, float distance );

prototype hisim tUnderOpFilter.FindNearest( list op_list, hisim center );

// EOF /////////////////////////////////////////////////////////////////////////

