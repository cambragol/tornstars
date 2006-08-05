//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tMegaTrucking.h
//
// Compiler-generated export header for package "tMegaTrucking"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tMegaTrucking.h,v 1.1 2006/04/08 22:43:59 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype string tMegaTrucking.SlotFromInt( int slot );

prototype tMegaTrucking.MegaDockTest( hship minipod, hsim megapod );

prototype task tMegaTrucking.MegaPodDeath( hsim sim );

prototype hsim tMegaTrucking.CreateMegaPod();

prototype bool tMegaTrucking.IsMegafreighter( hsim ship );

prototype list tMegaTrucking.MegaPodsOnShip( hsim ship );

prototype tMegaTrucking.Initialize( hship freighter );

prototype tMegaTrucking.Uninitialize( hship freighter );

prototype set tMegaTrucking.PodsOnMegafreighter( hship freighter );

prototype tMegaTrucking.UnloadShip( hship freighter, hhabitat station, set pods );

prototype tMegaTrucking.LoadShip( hship freighter, hhabitat station, set pods );

prototype task tMegaTrucking.SecurityWatch( hsim ship );

prototype tMegaTrucking.DitchPods( hship freighter );

prototype tMegaTrucking.LoadShipFromSpace( hship freighter, set pods );

prototype tMegaTrucking.SetUpFreighter( hship freighter, int megapods, set pods );

// EOF /////////////////////////////////////////////////////////////////////////

