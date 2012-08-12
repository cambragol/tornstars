//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsMegaTrucking.h
//
// Compiler-generated export header for package "tsMegaTrucking"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype string tsMegaTrucking.SlotFromInt( int slot );

prototype tsMegaTrucking.MegaDockTest( hship minipod, hsim megapod );

prototype MegaPodDeath tsMegaTrucking.MegaPodDeath( hsim sim );

prototype hsim tsMegaTrucking.CreateMegaPod();

prototype bool tsMegaTrucking.IsMegafreighter( hsim ship );

prototype list tsMegaTrucking.MegaPodsOnShip( hsim ship );

prototype tsMegaTrucking.Initialize( hship freighter );

prototype tsMegaTrucking.Uninitialize( hship freighter );

prototype set tsMegaTrucking.PodsOnMegafreighter( hship freighter );

prototype tsMegaTrucking.UnloadShip( hship freighter, hhabitat station, set pods );

prototype tsMegaTrucking.LoadShip( hship freighter, hhabitat station, set pods );

prototype SecurityWatch tsMegaTrucking.SecurityWatch( hsim ship );

prototype tsMegaTrucking.DitchPods( hship freighter );

prototype tsMegaTrucking.LoadShipFromSpace( hship freighter, set pods );

prototype tsMegaTrucking.SetUpFreighter( hship freighter, int megapods, set pods );

// EOF /////////////////////////////////////////////////////////////////////////

