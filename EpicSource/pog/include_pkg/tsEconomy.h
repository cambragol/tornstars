//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsEconomy.h
//
// Compiler-generated export header for package "tsEconomy"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype list tsEconomy.CargoList( hsim category );

prototype set tsEconomy.StationProducedCargo( hisim trade_center );

prototype set tsEconomy.StationSupplyCargo( hisim trade_center );

prototype set tsEconomy.StationUsedCargo( hisim trade_center );

prototype int tsEconomy.CargoPrice( hcargo cargo );

prototype bool tsEconomy.TradedItem( hcargo cargo );

prototype float tsEconomy.CargoMinStanding( hcargo cargo );

prototype int tsEconomy.CargoStanding( hcargo cargo );

prototype int tsEconomy.HaulFee( hcargo cargo );

prototype string tsEconomy.CategoryName( hcargo cargo );

prototype int tsEconomy.CategoryPrice( hsim category );

prototype hsim tsEconomy.CategoryFromCargo( hcargo cargo );

prototype float tsEconomy.SellAdjustment( hisim trade_center );

prototype float tsEconomy.PurchaseAdjustment( hisim trade_center );

prototype tsEconomy.RunCheck();

prototype tsEconomy.CopyPricing();

prototype tsEconomy.ExitBase();

prototype tsEconomy.EnterSpace();

prototype tsEconomy.StartSystem();

prototype tsEconomy.TestRun();

prototype tsEconomy.TestINIFiles();

prototype tsEconomy.DebugNotPlayerCargo();

// EOF /////////////////////////////////////////////////////////////////////////

