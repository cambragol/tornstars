//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tLFleet.h
//
// Compiler-generated export header for package "tLFleet"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tLFleet.h,v 1.3 2006/04/04 14:55:22 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tLFleet.Init();

prototype tLFleet.Create( hisim producer, int fleets, int supplies, int max_fleets, int max_supplies );

prototype tLFleet.Save( hisim producer );

prototype tLFleet.Restore( hisim producer );

prototype list tLFleet.All();

prototype int tLFleet.Supplies( hisim producer );

prototype tLFleet.SetSupplies( hisim producer, int supplies );

prototype int tLFleet.MaxSupplies( hisim producer );

prototype tLFleet.SetMaxSupplies( hisim producer, int supplies );

prototype tLFleet.ChangeSupplies( hisim producer, int amount );

prototype int tLFleet.Fleets( hisim producer );

prototype tLFleet.SetFleets( hisim producer, int fleets );

prototype tLFleet.ChangeFleets( hisim producer, int amount );

prototype int tLFleet.MaxFleets( hisim producer );

prototype tLFleet.SetMaxFleets( hisim producer, int fleets );

prototype int tLFleet.Wrecks( hisim producer );

prototype tLFleet.SetWrecks( hisim producer, int wrecks );

prototype int tLFleet.ChangeWrecks( hisim producer, int amount );

// EOF /////////////////////////////////////////////////////////////////////////

