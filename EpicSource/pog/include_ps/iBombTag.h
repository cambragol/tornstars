//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// iBombTag.h
//
// Compiler-generated export header for package "iBombTag"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_ps/iBombTag.h,v 1.1.1.1 2005/05/13 09:27:22 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype iBombTag.ServerMain();

prototype iBombTag.ServerPlayerEnter( hsim player );

prototype iBombTag.ServerPlayerLeave( hsim player );

prototype iBombTag.ServerOnUserMessage( hsim sim, int type, string data );

prototype iBombTag.ServerPlayerKilled( hsim player );

prototype iBombTag.ClientMain();

prototype iBombTag.ClientPlayerSay();

prototype iBombTag.ClientPlayerTeamSay();

prototype iBombTag.ClientPlayerKilled();

prototype iBombTag.ClientOpponentKilled( hsim opponent );

prototype iBombTag.ClientPlayerEnter( hsim ship );

prototype iBombTag.ClientPlayerLeave();

prototype iBombTag.ClientEndGame( string wining_team, bool cycling );

prototype iBombTag.ClientRespawn( hship ship );

prototype iBombTag.ClientGUI();

prototype iBombTag.ClientTauntReturn( string taunt );

prototype iBombTag.ClientDefaultTaunt1();

prototype iBombTag.ClientDefaultTaunt2();

prototype iBombTag.ClientDefaultTaunt3();

prototype iBombTag.ClientDefaultTaunt4();

prototype iBombTag.WeaponAmmoPowerUp( hsim powerup, hsim ship );

prototype iBombTag.WeaponAmmoPowerUp( hsim powerup, hsim ship );

prototype iBombTag.HealthPowerUp( hsim powerup, hsim ship );

prototype iBombTag.SpeedPowerUp( hsim powerup, hsim ship );

prototype iBombTag.SpeedPowerDown( hsim powerup, hsim ship );

prototype BotDeath iBombTag.BotDeath( hsim ship );

prototype iBombTag.ServerOnEndGame();

// EOF /////////////////////////////////////////////////////////////////////////

