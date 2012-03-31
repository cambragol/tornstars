//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsLFleet.h
//
// Compiler-generated export header for package "tsLFleet"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tsLFleet.Init();

prototype tsLFleet.Create( hisim producer, int fleets, int supplies, int max_fleets, int max_supplies );

prototype tsLFleet.Save( hisim producer );

prototype tsLFleet.Restore( hisim producer );

prototype list tsLFleet.All();

prototype int tsLFleet.Supplies( hisim producer );

prototype tsLFleet.SetSupplies( hisim producer, int supplies );

prototype int tsLFleet.MaxSupplies( hisim producer );

prototype tsLFleet.SetMaxSupplies( hisim producer, int supplies );

prototype tsLFleet.ChangeSupplies( hisim producer, int amount );

prototype int tsLFleet.Fleets( hisim producer );

prototype tsLFleet.SetFleets( hisim producer, int fleets );

prototype tsLFleet.ChangeFleets( hisim producer, int amount );

prototype int tsLFleet.MaxFleets( hisim producer );

prototype tsLFleet.SetMaxFleets( hisim producer, int fleets );

prototype int tsLFleet.Wrecks( hisim producer );

prototype tsLFleet.SetWrecks( hisim producer, int wrecks );

prototype int tsLFleet.ChangeWrecks( hisim producer, int amount );

prototype bool tsLFleet.Distress( hisim producer );

prototype tsLFleet.SetDistress( hisim producer, bool distressed );

// EOF /////////////////////////////////////////////////////////////////////////

