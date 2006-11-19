//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsFaction.h
//
// Compiler-generated export header for package "tsFaction"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tsFaction.Init();

prototype tsFaction.NewGame();

prototype tsFaction.SessionStart();

prototype tsFaction.SaveGame();

prototype tsFaction.SetDescription( hfaction faction, string html_file );

prototype string tsFaction.Description( hfaction faction );

prototype tsFaction.SetFleetStyle( hfaction faction, string fleet_style );

prototype string tsFaction.FleetStyle( hfaction faction );

prototype tsFaction.SetSpeechStyle( hfaction faction, string speech_style );

prototype string tsFaction.SpeechStyle( hfaction faction );

prototype tsFaction.SetKnown( hfaction faction, bool known );

prototype bool tsFaction.IsKnown( hfaction faction );

prototype int tsFaction.Type( hfaction faction );

prototype tsFaction.SetType( hfaction faction, int type );

prototype tsFaction.SetEName( hfaction faction, string name );

prototype string tsFaction.EName( hfaction faction );

prototype hfaction tsFaction.EFind( string epic_name );

prototype float tsFaction.CurrentAction( hfaction faction );

prototype tsFaction.SetCurrentAction( hfaction faction, float event_value );

prototype tsFaction.AdjustCurrentAction( hfaction faction, float event_value );

prototype float tsFaction.PastAction( hfaction faction );

prototype tsFaction.SetPastAction( hfaction faction, float event_value );

prototype float tsFaction.DefaultFeeling( hfaction faction );

prototype tsFaction.SetDefaultFeeling( hfaction faction, float feeling );

prototype bool tsFaction.IsPublic( hfaction faction );

prototype bool tsFaction.IsGovernment( hfaction faction );

prototype bool tsFaction.IsCriminal( hfaction faction );

prototype bool tsFaction.IsIndependent( hfaction faction );

prototype hfaction tsFaction.PlayerFaction();

prototype hfaction tsFaction.EmptyFaction();

prototype tsFaction.CopyFeelings( hfaction source, hfaction new_faction );

prototype eFeelingType tsFaction.String2Type( string level );

prototype float tsFaction.String2Level( string level );

prototype float tsFaction.String2LowerLevel( string level );

prototype string tsFaction.Level2String( eFeelingType feeling_type );

prototype string tsFaction.Feeling2String( float feeling );

prototype string tsFaction.Type2String( int faction_type );

prototype float tsFaction.Type2LowerLevel( eFeelingType feeling_type );

prototype tsFaction.AddStation( hhabitat station, hfaction faction );

prototype list tsFaction.Stations( hfaction faction );

// EOF /////////////////////////////////////////////////////////////////////////

