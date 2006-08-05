//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tStation.h
//
// Compiler-generated export header for package "tStation"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tStation.h,v 1.9 2006/04/04 14:55:23 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype set tStation.Habitats();

prototype hsim tStation.Nearest( hsim location, list items );

prototype bool tStation.IsStation( hisim station );

prototype bool tStation.IsVisibleOnMap( hhabitat station );

prototype tStation.SetMapVisibility( hhabitat station, bool visible );

prototype bool tStation.IsHidden( hhabitat station );

prototype tStation.SetHidden( hhabitat station, bool hide );

prototype bool tStation.IsDestroyed( hhabitat station );

prototype tStation.SetDestroyed( hhabitat station, bool destroyed );

prototype tStation.SetStatus( hhabitat station, eStationStatus status );

prototype eStationStatus tStation.Status( hhabitat station );

prototype tStation.SetCategory( hhabitat station, eStationCategory category );

prototype eStationCategory tStation.Category( hhabitat station );

prototype tStation.SetChangeTime( hhabitat station, int build_time );

prototype int tStation.ChangeTime( hhabitat station );

prototype tStation.SetReactorBuildTime( hhabitat station, int build_time );

prototype int tStation.ReactorBuildTime( hhabitat station );

prototype tStation.SetControlBuildTime( hhabitat station, int build_time );

prototype int tStation.ControlBuildTime( hhabitat station );

prototype tStation.SetRichness( hhabitat station, int richness );

prototype int tStation.Richness( hhabitat station );

prototype tStation.SetKnown( hhabitat station, bool known );

prototype bool tStation.IsKnown( hhabitat station );

prototype tStation.SetAwake( hhabitat station, bool awake );

prototype bool tStation.IsAwake( hhabitat station );

prototype tStation.Create( hhabitat station, string faction_name, eStationStatus status, int event_time, int reactor_time, int control_time, int richness, bool known, bool awake );

prototype eStationStatus tStation.String2Status( string status_name );

prototype string tStation.Status2String( eStationStatus status );

prototype string tStation.Richness2String( int richness );

prototype eStationCategory tStation.String2Category( string category_string );

prototype string tStation.Category2String( eStationCategory category );

// EOF /////////////////////////////////////////////////////////////////////////

