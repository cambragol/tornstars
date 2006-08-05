//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tLInventory.h
//
// Compiler-generated export header for package "tLInventory"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tLInventory.h,v 1.2 2006/02/19 12:37:10 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tLInventory.Init();

prototype int tLInventory.Inventory( hisim producer, hcargo cargo );

prototype tLInventory.ChangeInventory( hisim producer, hcargo cargo, int amount );

prototype tLInventory.ClearInventory( hisim producer, hcargo cargo );

prototype tLInventory.SetGrowthRate( hisim producer, float growth_rate );

prototype float tLInventory.GrowthRate( hisim producer );

// EOF /////////////////////////////////////////////////////////////////////////

