//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// iStation.h
//
// Compiler-generated export header for package "iStation"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_ps/iStation.h,v 1.1.1.1 2005/05/13 09:27:23 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype task iStation.CheckStationReaction();

prototype task iStation.StationReactive( hhabitat station, hisim aggressor, float damage );

prototype iStation.DisableStationReactiveReport();

prototype iStation.AddReactiveException( hhabitat station );

prototype iStation.RemoveReactiveException( hhabitat station );

prototype iStation.DisableReactiveInArea ( hsim centre, float radius );

prototype iStation.EnableReactiveInArea ( hsim centre, float radius );

// EOF /////////////////////////////////////////////////////////////////////////

