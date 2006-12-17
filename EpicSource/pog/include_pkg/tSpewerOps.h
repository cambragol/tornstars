//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tSpewerOps.h
//
// Compiler-generated export header for package "tSpewerOps"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype hship tSpewerOps.ShipDocked( hhabitat station, bool lock );

prototype bool tSpewerOps.IsFinished( hship ship );

prototype tSpewerOps.Initialize( hship ship, hhabitat station );

prototype tSpewerOps.LoadShip( hship ship, hhabitat station, set pods );

prototype tSpewerOps.UnloadShip( hship ship, hhabitat station, set pods );

prototype list tSpewerOps.PodsOfTypeOnShip( int cargo_type, hship ship, bool legit, int number );

// EOF /////////////////////////////////////////////////////////////////////////

