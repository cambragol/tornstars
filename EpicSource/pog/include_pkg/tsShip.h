//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsShip.h
//
// Compiler-generated export header for package "tsShip"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype float tsShip.Fuel( hship ship );

prototype tsShip.SetFuel( hship ship, float fuel_used );

prototype float tsShip.FuelMax( hship ship );

prototype tsShip.SetFuelMax( hship ship, float fuel_maximum );

prototype float tsShip.FuelPerJump( hship ship );

prototype tsShip.SetFuelPerJump( hship ship, float fuel_per_jump );

prototype bool tsShip.CanJump( hship ship, float cost );

prototype tsShip.DeductFuelPerJump( hship ship, float cost );

prototype float tsShip.DailyFuel( hship ship );

prototype tsShip.SetDailyFuel( hship ship, float fuel_amount );

prototype int tsShip.DailyUpkeep( hship ship );

prototype tsShip.SetDailyUpkeep( hship ship, int daily_cost );

prototype string tsShip.World( hship ship );

prototype tsShip.SetWorld( hship ship, string world );

prototype list tsShip.ShipPodList( hsim ship );

prototype hisim tsShip.DockParent( hship ship );

prototype bool tsShip.IsCapsuleJumping( hship ship );

prototype bool tsShip.IsMiner( hship ship );

prototype bool tsShip.IsProspector( hship ship );

prototype bool tsShip.IsLongRangeScan( hship ship );

prototype bool tsShip.IsTanker( hship ship );

prototype bool tsShip.IsFreighter( hship ship );

prototype bool tsShip.IsWarship( hship ship );

prototype int tsShip.Owner( hship ship );

prototype tsShip.SetOwner( hship ship, int owner );

prototype bool tsShip.IsPlayerFleetShip( hsim ship );

prototype list tsShip.PlayerFleet();

prototype tsShip.AddNewShip( hship ship );

prototype tsShip.RemoveFleetShip( hship ship );

prototype tsShip.ReadIniFile( hship ship );

prototype hship tsShip.Create( string ini_file, string name );

prototype tsShip.SetSaveId( hship ship, int id );

prototype int tsShip.SaveId( hship ship );

prototype hsubsim tsShip.FindSubsimByTemplateNumber( hship ship, int template_number );

prototype hsubsim tsShip.ReplaceSubsim( hship ship, hsubsim subsim, string template_name );

prototype tsShip.PlaceSubsim( hship ship, hsubsim subsim );

prototype tsShip.LinkPlayerWeapons( hship ship );

// EOF /////////////////////////////////////////////////////////////////////////

