//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tSpewerOps.h
//
// Compiler-generated export header for package "tSpewerOps"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tSpewerOps.h,v 1.2 2006/04/08 22:43:59 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype hship tSpewerOps.ShipDocked( hhabitat station, bool lock );

prototype bool tSpewerOps.IsFinished( hship ship );

prototype tSpewerOps.Initialize( hship ship, hhabitat station );

prototype tSpewerOps.LoadShip( hship ship, hhabitat station, set pods );

prototype tSpewerOps.UnloadShip( hship ship, hhabitat station, set pods );

prototype list tSpewerOps.PodsOfTypeOnShip( hcargo cargo, hship ship, bool legit, int number );

// EOF /////////////////////////////////////////////////////////////////////////

