//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tEFaction.h
//
// Compiler-generated export header for package "tEFaction"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tEFaction.Init();

prototype tEFaction.NewGame();

prototype tEFaction.SaveGame();

prototype tEFaction.SetDescription( hfaction faction, string html_file );

prototype string tEFaction.Description( hfaction faction );

prototype tEFaction.SetFleetStyle( hfaction faction, string fleet_style );

prototype string tEFaction.FleetStyle( hfaction faction );

prototype tEFaction.SetKnown( hfaction faction, bool known );

prototype bool tEFaction.IsKnown( hfaction faction );

prototype int tEFaction.Type( hfaction faction );

prototype tEFaction.SetType( hfaction faction, int type );

prototype tEFaction.SetEName( hfaction faction, string name );

prototype string tEFaction.EName( hfaction faction );

prototype hfaction tEFaction.EFind( string epic_name );

prototype float tEFaction.CurrentAction( hfaction faction );

prototype tEFaction.SetCurrentAction( hfaction faction, float event_value );

prototype tEFaction.AdjustCurrentAction( hfaction faction, float event_value );

prototype float tEFaction.PastAction( hfaction faction );

prototype tEFaction.SetPastAction( hfaction faction, float event_value );

prototype float tEFaction.DefaultFeeling( hfaction faction );

prototype tEFaction.SetDefaultFeeling( hfaction faction, float feeling );

prototype bool tEFaction.IsPublic( hfaction faction );

prototype bool tEFaction.IsGovernment( hfaction faction );

prototype bool tEFaction.IsCriminal( hfaction faction );

prototype bool tEFaction.IsIndependent( hfaction faction );

prototype hfaction tEFaction.PlayerFaction();

prototype hfaction tEFaction.EmptyFaction();

prototype tEFaction.CopyFeelings( hfaction source, hfaction new_faction );

prototype eFeelingType tEFaction.String2Type( string level );

prototype float tEFaction.String2Level( string level );

prototype float tEFaction.String2LowerLevel( string level );

prototype string tEFaction.Level2String( eFeelingType feeling_type );

prototype string tEFaction.Feeling2String( float feeling );

prototype string tEFaction.Type2String( int faction_type );

prototype float tEFaction.Type2LowerLevel( eFeelingType feeling_type );

prototype tEFaction.AddStation( hhabitat station, hfaction faction );

prototype list tEFaction.Stations( hfaction faction );

// EOF /////////////////////////////////////////////////////////////////////////

