//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tStationFilter.h
//
// Compiler-generated export header for package "tStationFilter"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tStationFilter.h,v 1.3 2006/04/08 22:43:59 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype set tStationFilter.OnStatus( set habitats, int station_status );

prototype set tStationFilter.OnType( set habitats, int station_type );

prototype set tStationFilter.OnCategory( set habitats, int station_category );

prototype set tStationFilter.OnStatusAndCategory( set habitats, int station_status, int station_category );

prototype set tStationFilter.OnGreaterFeeling( set habitats, hfaction faction, float feeling_level );

prototype set tStationFilter.OnLowerFeeling( set habitats, hfaction faction, float feeling_level );

prototype set tStationFilter.OnPodSpewer( set habitats );

prototype list tStationFilter.OnDistance( set habitats, hisim mark );

prototype set tStationFilter.OnMapVisible( set habitats, bool visible );

// EOF /////////////////////////////////////////////////////////////////////////

