//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tDebug.h
//
// Compiler-generated export header for package "tDebug"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tDebug.h,v 1.2 2005/05/13 09:42:03 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tDebug.AddFlag( string name, string global_name, bool start_on );

prototype tDebug.SetFlag( string global_name, bool value );

prototype list tDebug.FlagList();

prototype bool tDebug.IsFlagSet( string global_name );

prototype tDebug.Display( string flag, string info );

// EOF /////////////////////////////////////////////////////////////////////////

