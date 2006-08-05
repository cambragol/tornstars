//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tStationEnv.h
//
// Compiler-generated export header for package "tStationEnv"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tStationEnv.h,v 1.5 2006/03/17 06:39:42 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tStationEnv.CallMods();

prototype tStationEnv.ReadFile( hisim station, string filename );

prototype tStationEnv.SetupEnv( hisim station );

prototype tStationEnv.SystemSetup();

prototype list tStationEnv.GetFileList( hisim station );

prototype tStationEnv.AttachFile( string station_name, string system, string filename );

prototype tStationEnv.SetupObjects( hisim station, hisim owner, string filename, float center_x, float center_y, float center_z );

prototype tStationEnv.LeaveStation( hisim station );

prototype tStationEnv.EnterBase();

// EOF /////////////////////////////////////////////////////////////////////////

