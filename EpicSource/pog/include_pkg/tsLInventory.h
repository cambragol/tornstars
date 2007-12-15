//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsLInventory.h
//
// Compiler-generated export header for package "tsLInventory"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tsLInventory.Init();

prototype int tsLInventory.Inventory( hisim producer, hcargo cargo );

prototype tsLInventory.ChangeInventory( hisim producer, hcargo cargo, int amount );

prototype tsLInventory.ClearInventory( hisim producer, hcargo cargo );

prototype tsLInventory.SetGrowthRate( hisim producer, float growth_rate );

prototype float tsLInventory.GrowthRate( hisim producer );

// EOF /////////////////////////////////////////////////////////////////////////

