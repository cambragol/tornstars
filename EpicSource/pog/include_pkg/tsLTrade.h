//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsLTrade.h
//
// Compiler-generated export header for package "tsLTrade"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tsLTrade.Create( hisim producer, string trade_filename, string key_name );

prototype tsLTrade.Save( hisim producer );

prototype tsLTrade.Restore( hisim producer );

prototype string tsLTrade.TradeFile( hisim producer );

prototype tsLTrade.SetTradeFile( hisim producer, string trade_file );

prototype string tsLTrade.KeyName( hisim producer );

prototype tsLTrade.SetKeyName( hisim producer, string key_name );

prototype bool tsLTrade.IsTradeCenter( hisim producer );

// EOF /////////////////////////////////////////////////////////////////////////

