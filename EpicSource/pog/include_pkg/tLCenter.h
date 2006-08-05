//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tLCenter.h
//
// Compiler-generated export header for package "tLCenter"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tLCenter.h,v 1.3 2006/03/12 21:05:39 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tLCenter.Create( hisim producer, hmapentity center );

prototype tLCenter.Save( hisim producer );

prototype tLCenter.Restore( hisim producer );

prototype hmapentity tLCenter.GetCenter( hisim producer );

prototype tLCenter.SetCenter( hisim producer, hmapentity center );

prototype string tLCenter.GetStationName( hisim producer );

prototype string tLCenter.GetSystemName( hisim producer );

prototype list tLCenter.GetAttached( hisim center );

prototype tLCenter.SetCullMarker( hmapentity center, bool player_near );

prototype bool tLCenter.GetCullMarker( hisim center );

// EOF /////////////////////////////////////////////////////////////////////////

