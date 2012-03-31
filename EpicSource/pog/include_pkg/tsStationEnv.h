//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsStationEnv.h
//
// Compiler-generated export header for package "tsStationEnv"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tsStationEnv.CallMods();

prototype tsStationEnv.ReadFile( hisim station, string filename );

prototype tsStationEnv.SetupEnv( hisim station );

prototype tsStationEnv.SystemSetup();

prototype list tsStationEnv.GetFileList( hisim station );

prototype tsStationEnv.AttachFile( string station_name, string system, string filename );

prototype tsStationEnv.SetupObjects( hmapentity station, hisim owner, string filename, float center_x, float center_y, float center_z );

prototype tsStationEnv.LeaveStation( hisim station );

prototype tsStationEnv.EnterBase();

// EOF /////////////////////////////////////////////////////////////////////////

