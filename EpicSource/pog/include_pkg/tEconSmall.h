//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tEconSmall.h
//
// Compiler-generated export header for package "tEconSmall"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tEconSmall.h,v 1.4 2005/06/27 05:38:37 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype list tEconSmall.CargoList( hsim category );

prototype set tEconSmall.StationProducedCargo( hisim trade_center );

prototype set tEconSmall.StationSupplyCargo( hisim trade_center );

prototype set tEconSmall.StationUsedCargo( hisim trade_center );

prototype int tEconSmall.CargoPrice( hcargo cargo );

prototype bool tEconSmall.TradedItem( hcargo cargo );

prototype float tEconSmall.CargoMinStanding( hcargo cargo );

prototype int tEconSmall.CargoStanding( hcargo cargo );

prototype int tEconSmall.HaulFee( hcargo cargo );

prototype string tEconSmall.CategoryName( hcargo cargo );

prototype float tEconSmall.SellAdjustment( hisim trade_center );

prototype float tEconSmall.PurchaseAdjustment( hisim trade_center );

prototype tEconSmall.RunCheck();

prototype tEconSmall.CopyPricing();

prototype tEconSmall.ExitBase();

prototype tEconSmall.EnterSpace();

prototype tEconSmall.StartSystem();

prototype tEconSmall.TestRun();

prototype tEconSmall.TestINIFiles();

prototype tEconSmall.DebugNotPlayerCargo();

// EOF /////////////////////////////////////////////////////////////////////////

