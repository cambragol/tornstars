//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tEpicFleet.h
//
// Compiler-generated export header for package "tEpicFleet"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tEpicFleet.h,v 1.7 2006/03/04 18:33:28 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////
enum eefOwnership {
   efoOwned,
   efoHired,
   efoCaptured
};


// Functions ///////////////////////////////////////////////////////////////////

prototype tEpicFleet.NewGame( string player_ship_template, string system, string location, string name );

prototype tEpicFleet.NewGameTest();

prototype tEpicFleet.StartSession();

prototype bool tEpicFleet.IsPlayerFleetShip( hsim ship );

prototype int tEpicFleet.IdNumber( hship ship );

prototype int tEpicFleet.Marines( hship ship );

prototype tEpicFleet.SetMarines( hship ship, int marines );

prototype float tEpicFleet.Fuel( hship ship );

prototype tEpicFleet.SetFuel( hship ship, float fuel_used );

prototype float tEpicFleet.FuelMax( hship ship );

prototype tEpicFleet.SetFuelMax( hship ship, float fuel_maximum );

prototype float tEpicFleet.FuelPerJump( hship ship );

prototype tEpicFleet.SetFuelPerJump( hship ship, float fuel_per_jump );

prototype float tEpicFleet.DailyFuel( hship ship );

prototype tEpicFleet.SetDailyFuel( hship ship, float fuel_amount );

prototype int tEpicFleet.DailyUpkeep( hship ship );

prototype tEpicFleet.SetDailyUpkeep( hship ship, int daily_cost );

prototype string tEpicFleet.World( hship ship );

prototype tEpicFleet.SetWorld( hship ship, string world );

prototype list tEpicFleet.PlayerFleet();

prototype bool tEpicFleet.IsCaptured( hship ship );

prototype list tEpicFleet.ShipPodList( hsim ship );

prototype tEpicFleet.SaveFleet();

prototype tEpicFleet.RestoreFleet();

prototype tEpicFleet.RemoveShip( hship ship );

prototype tEpicFleet.SetupPlayerWingman( hship ship, int id, int group, eefOwnership owner, string world );

prototype tEpicFleet.NewPlayerShip( hship ship );

prototype bool tEpicFleet.GroupRemoveShip( hsim ship );

prototype bool tEpicFleet.GroupMoveShip( hsim ship, int group );

prototype list tEpicFleet.ReturnGroup( int group );

prototype int tEpicFleet.GroupNumber( hsim ship );

prototype tEpicFleet.SetGroupNumber( hsim ship, int group );

prototype task tEpicFleet.PlayerDeath( hsim sim );

prototype task tEpicFleet.WingmanDeath( hsim wingman );

prototype task tEpicFleet.WingmanComms();

prototype tEpicFleet.HireShip( hship ship );

prototype tEpicFleet.CaptureShip( hship ship );

prototype tEpicFleet.FireShip( hship ship );

prototype tEpicFleet.RunCheck();

prototype tEpicFleet.CreateTestShip();

prototype tEpicFleet.CreateTargets();

prototype tEpicFleet.DisruptShip();

// EOF /////////////////////////////////////////////////////////////////////////

