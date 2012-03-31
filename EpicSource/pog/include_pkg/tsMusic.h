//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsMusic.h
//
// Compiler-generated export header for package "tsMusic"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tsMusic.Play( string track, bool crossfade, bool loop );

prototype tsMusic.Resume();

prototype tsMusic.Pause();

prototype tsMusic.PlayEvent( int event );

prototype bool tsMusic.LoadSuite( string suite_filename );

prototype tsMusic.SetSuite( string key_name );

prototype string tsMusic.ReturnSuite();

prototype tsMusic.SetMood( string mood );

prototype string tsMusic.ReturnMood();

prototype tsMusic.Init();

prototype list tsMusic.SuiteList();

prototype tsMusic.Discovery();

prototype tsMusic.Combat();

prototype tsMusic.NewSystem();

prototype tsMusic.SoundNear();

// EOF /////////////////////////////////////////////////////////////////////////

