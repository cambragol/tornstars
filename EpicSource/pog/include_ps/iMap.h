//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// iMap.h
//
// Compiler-generated export header for package "iMap"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_ps/iMap.h,v 1.1.1.1 2005/05/13 09:27:23 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////


// this is a test section ofr matt to try out maps 

prototype iMap.Main();

prototype bool iMap.Load( string ini_name, hsim map_centre );

// these are the descriptor functions

prototype string iMap.GetAuthor ( hinifile ini );

prototype string iMap.GetDescription ( hinifile ini );

prototype string iMap.GetDate ( hinifile ini );

prototype string iMap.GetName ( hinifile ini );

// this returns the resource request for the map resource

prototype string iMap.GetMap ( hinifile ini );

prototype float iMap.GetMapSize ( hinifile ini );

// functions to return geography

prototype hgroup iMap.GetGeography ( hinifile ini, hsim map_centre );

// this returns the spawn points - this group will return 3 subgroups :
// 0 = alpha spawn points, 1 = beta spawn points, 2 = hero spawn points

prototype hgroup iMap.GetSpawnPoints ( hinifile ini, hsim map_centre );

// EOF /////////////////////////////////////////////////////////////////////////

