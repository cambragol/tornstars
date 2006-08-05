//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tESysSetup.h
//
// Compiler-generated export header for package "tESysSetup"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tESysSetup.h,v 1.2 2006/02/28 13:24:31 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype hfaction tESysSetup.Government();

prototype tESysSetup.SetGovernment( hfaction government_faction );

prototype tESysSetup.FindGovernment();

prototype bool tESysSetup.IsKnown( string system );

prototype tESysSetup.SetKnown( string system, bool known );

prototype tESysSetup.UpdateSystem();

prototype tESysSetup.DebugInfo();

// EOF /////////////////////////////////////////////////////////////////////////

