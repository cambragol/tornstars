//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// iBotPak.h
//
// Compiler-generated export header for package "iBotPak"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_ps/iBotPak.h,v 1.1.1.1 2005/05/13 09:27:22 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

enum eGameType {

	GT_DeathMatch,
	GT_CaptureTheFlag,
	GT_BombTag
};


prototype hobject iBotPak.CreateBotShips( string ini, int number_of_ships, float skill_level, hfaction faction, hship request_ship, string team_name );

prototype iBotPak.AssignGameType( hobject bots, eGameType game_type );

// EOF /////////////////////////////////////////////////////////////////////////

