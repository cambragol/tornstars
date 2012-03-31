//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsStationFilter.h
//
// Compiler-generated export header for package "tsStationFilter"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype set tsStationFilter.OnStatus( set habitats, int station_status );

prototype set tsStationFilter.OnType( set habitats, int station_type );

prototype set tsStationFilter.OnCategory( set habitats, int station_category );

prototype set tsStationFilter.OnStatusAndCategory( set habitats, int station_status, int station_category );

prototype set tsStationFilter.OnGreaterFeeling( set habitats, hfaction faction, float feeling_level );

prototype set tsStationFilter.OnLowerFeeling( set habitats, hfaction faction, float feeling_level );

prototype set tsStationFilter.OnPodSpewer( set habitats );

prototype list tsStationFilter.OnDistance( set habitats, hisim mark );

prototype set tsStationFilter.OnMapVisible( set habitats, bool visible );

prototype set tsStationFilter.OnFactionAllowed( set habitats, hfaction faction );

// EOF /////////////////////////////////////////////////////////////////////////

