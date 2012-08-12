//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsStarSystem.h
//
// Compiler-generated export header for package "tsStarSystem"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype hfaction tsStarSystem.Government( string system );

prototype tsStarSystem.SetGovernment( string system, hfaction government_faction );

prototype hfaction tsStarSystem.FindGovernment( string system );

prototype bool tsStarSystem.IsKnown( string system );

prototype tsStarSystem.SetKnown( string system, bool known );

prototype tsStarSystem.UpdateSystem();

prototype list tsStarSystem.StarSystems();

// EOF /////////////////////////////////////////////////////////////////////////

