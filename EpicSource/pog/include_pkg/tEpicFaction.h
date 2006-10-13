//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tEpicFaction.h
//
// Compiler-generated export header for package "tEpicFaction"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tEpicFaction.Init();

prototype tEpicFaction.SessionEnd();

prototype tEpicFaction.SaveGame();

prototype tEpicFaction.NewGame();

prototype hsim tEpicFaction.Find( string name );

prototype tEpicFaction.SetFeeling( hsim efeeler, hsim efeelee, float level );

prototype float tEpicFaction.Feeling( hsim efeeler, hsim efeelee );

prototype string tEpicFaction.FeelingToString( float feeling );

prototype string tEpicFaction.LevelToString( eFactionLevel level );

prototype eFactionLevel tEpicFaction.FeelingToLevel( float feeling );

prototype float tEpicFaction.FeelingLevel( eFactionLevel level );

prototype string tEpicFaction.Description( hsim efaction );

prototype hsim tEpicFaction.Create( string name, string eoc_faction, string html_file, int type, int alignment, string fleet_style );

prototype tEpicFaction.Destroy( hsim faction );

prototype list tEpicFaction.All();

prototype int tEpicFaction.Type( hsim efaction );

prototype int tEpicFaction.Alignment( hsim efaction );

prototype list tEpicFaction.Relations( hsim efaction );

prototype int tEpicFaction.Activity( hsim efeeler, hsim efeelee );

prototype tEpicFaction.SetActivity( hsim efeeler, hsim efeelee, int activity_level );

prototype tEpicFaction.AddAction( hsim efaction, hobject action );

prototype list tEpicFaction.ActionList( hsim efaction );

prototype tEpicFaction.AddPlan( hsim efaction, hobject plan );

prototype list tEpicFaction.PlanList( hsim efaction );

prototype list tEpicFaction.StationList( hsim efaction );

prototype tEpicFaction.AddStation( hsim efaction, hsim station );

prototype tEpicFaction.RemoveStation( hsim efaction, hsim station );

prototype tEpicFaction.ClearStations( hsim efaction );

prototype tEpicFaction.SetEpicFaction( hisim ship, hsim efaction );

prototype hsim tEpicFaction.Faction( hisim ship );

prototype hfaction tEpicFaction.EocFaction( hsim efaction );

prototype tEpicFaction.SetFleetStyle( hsim efaction, string fleet_style );

prototype string tEpicFaction.FleetStyle( hsim efaction );

prototype tEpicFaction.SetSecret( hsim efaction, bool secret );

prototype bool tEpicFaction.IsSecret( hsim efaction );

prototype tEpicFaction.SetKnown( hsim efaction, bool known );

prototype bool tEpicFaction.IsKnown( hsim efaction );

prototype bool tEpicFaction.IsGovernment( hsim efaction );

prototype bool tEpicFaction.IsPublic( hsim efaction );

prototype bool tEpicFaction.IsHidden( hsim efaction );

prototype tEpicFaction.SetPlayerDamage( hsim efaction, int player_damage );

prototype int tEpicFaction.PlayerDamage( hsim efaction );

prototype hsim tEpicFaction.FindPlayerFaction();

prototype hsim tEpicFaction.FindEmptyFaction();

prototype hsim tEpicFaction.CopyFaction( int type, hsim base_faction, string new_name );

prototype tEpicFaction.RunCheck();

// EOF /////////////////////////////////////////////////////////////////////////

