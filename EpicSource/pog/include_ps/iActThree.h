//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// iActThree.h
//
// Compiler-generated export header for package "iActThree"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_ps/iActThree.h,v 1.1.1.1 2005/05/13 09:27:22 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype task iActThree.MasterScript();

prototype iActThree.BaseMasterScript();

prototype iActThree.ActThreeGlobals();

prototype iActThree.ActThreeStart();

// Defence creation functions for use in Act3 - Mission 10

prototype hgroup iActThree.PlaceDefencesGunstars();

prototype hgroup iActThree.PlaceDefencesMines();

prototype hgroup iActThree.PlaceDefencesJunked();

prototype hgroup iActThree.PlaceDefencesShips();

prototype hship iActThree.PlaceDefencesEscapeTransport(); // This transport is marked mission critical

// This function updates the globals storing which defences are still alive

prototype iActThree.UpdateDefencesAlive(hgroup gunstars, hgroup mines, hgroup junked, hgroup ships);

// EOF /////////////////////////////////////////////////////////////////////////

