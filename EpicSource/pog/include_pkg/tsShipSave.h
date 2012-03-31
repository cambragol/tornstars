//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsShipSave.h
//
// Compiler-generated export header for package "tsShipSave"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype int tsShipSave.Save( hship ship );

prototype hship tsShipSave.Restore( int id );

prototype int tsShipSave.SaveList( list ship_list, string save_key );

prototype list tsShipSave.RestoreList( string save_key );

prototype tsShipSave.Relink();

// EOF /////////////////////////////////////////////////////////////////////////

