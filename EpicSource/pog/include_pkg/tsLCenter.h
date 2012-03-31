//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsLCenter.h
//
// Compiler-generated export header for package "tsLCenter"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tsLCenter.Create( hisim producer, hmapentity center );

prototype tsLCenter.Save( hisim producer );

prototype tsLCenter.Restore( hisim producer );

prototype hmapentity tsLCenter.GetCenter( hisim producer );

prototype tsLCenter.SetCenter( hisim producer, hmapentity center );

prototype string tsLCenter.GetStationName( hisim producer );

prototype string tsLCenter.GetSystemName( hisim producer );

prototype list tsLCenter.GetAttached( hisim center );

prototype tsLCenter.SetCullMarker( hmapentity center, bool player_near );

prototype bool tsLCenter.GetCullMarker( hisim center );

// EOF /////////////////////////////////////////////////////////////////////////

