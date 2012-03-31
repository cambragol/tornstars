//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsStation.h
//
// Compiler-generated export header for package "tsStation"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype set tsStation.Habitats();

prototype hsim tsStation.Nearest( hsim location, list items );

prototype bool tsStation.IsStation( hisim station );

prototype bool tsStation.IsVisibleOnMap( hhabitat station );

prototype tsStation.SetMapVisibility( hhabitat station, bool visible );

prototype bool tsStation.IsHidden( hhabitat station );

prototype tsStation.SetHidden( hhabitat station, bool hide );

prototype bool tsStation.IsDestroyed( hhabitat station );

prototype tsStation.SetDestroyed( hhabitat station, bool destroyed );

prototype tsStation.SetStatus( hhabitat station, eStationStatus status );

prototype eStationStatus tsStation.Status( hhabitat station );

prototype tsStation.SetCategory( hhabitat station, eStationCategory category );

prototype eStationCategory tsStation.Category( hhabitat station );

prototype tsStation.SetChangeTime( hhabitat station, int build_time );

prototype int tsStation.ChangeTime( hhabitat station );

prototype tsStation.SetReactorBuildTime( hhabitat station, int build_time );

prototype int tsStation.ReactorBuildTime( hhabitat station );

prototype tsStation.SetControlBuildTime( hhabitat station, int build_time );

prototype int tsStation.ControlBuildTime( hhabitat station );

prototype tsStation.SetRichness( hhabitat station, int richness );

prototype int tsStation.Richness( hhabitat station );

prototype tsStation.SetKnown( hhabitat station, bool known );

prototype bool tsStation.IsKnown( hhabitat station );

prototype tsStation.SetAwake( hhabitat station, bool awake );

prototype bool tsStation.IsAwake( hhabitat station );

prototype tsStation.Create( hhabitat station, string faction_name, eStationStatus status, int event_time, int reactor_time, int control_time, int richness, bool known, bool awake );

prototype eStationStatus tsStation.String2Status( string status_name );

prototype string tsStation.Status2String( eStationStatus status );

prototype string tsStation.Richness2String( int richness );

prototype eStationCategory tsStation.String2Category( string category_string );

prototype string tsStation.Category2String( eStationCategory category );

// EOF /////////////////////////////////////////////////////////////////////////

