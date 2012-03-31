//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsSpewerOps.h
//
// Compiler-generated export header for package "tsSpewerOps"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype hship tsSpewerOps.ShipDocked( hhabitat station, bool lock );

prototype bool tsSpewerOps.IsFinished( hship ship );

prototype tsSpewerOps.Initialize( hship ship, hhabitat station );

prototype tsSpewerOps.LoadShip( hship ship, hhabitat station, set pods );

prototype tsSpewerOps.UnloadShip( hship ship, hhabitat station, set pods );

prototype list tsSpewerOps.PodsOfTypeOnShip( int cargo_type, hship ship, bool legit, int max_number );

// EOF /////////////////////////////////////////////////////////////////////////

