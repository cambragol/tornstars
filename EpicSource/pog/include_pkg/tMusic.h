//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tMusic.h
//
// Compiler-generated export header for package "tMusic"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tMusic.h,v 1.3 2005/06/10 19:56:34 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tMusic.Play( string track, bool crossfade, bool loop );

prototype tMusic.Resume();

prototype tMusic.Pause();

prototype tMusic.PlayEvent( int event );

prototype bool tMusic.LoadSuite( string suite_filename );

prototype tMusic.SetSuite( string key_name );

prototype string tMusic.ReturnSuite();

prototype tMusic.SetMood( string mood );

prototype string tMusic.ReturnMood();

prototype tMusic.Init();

prototype list tMusic.SuiteList();

prototype tMusic.Discovery();

prototype tMusic.Combat();

prototype tMusic.NewSystem();

prototype tMusic.SoundNear();

// EOF /////////////////////////////////////////////////////////////////////////

