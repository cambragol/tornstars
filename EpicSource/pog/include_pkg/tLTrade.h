//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tLTrade.h
//
// Compiler-generated export header for package "tLTrade"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tLTrade.h,v 1.1 2005/06/10 19:56:33 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tLTrade.Create( hisim producer, string trade_filename, string key_name );

prototype tLTrade.Save( hisim producer );

prototype tLTrade.Restore( hisim producer );

prototype string tLTrade.TradeFile( hisim producer );

prototype tLTrade.SetTradeFile( hisim producer, string trade_file );

prototype string tLTrade.KeyName( hisim producer );

prototype tLTrade.SetKeyName( hisim producer, string key_name );

prototype bool tLTrade.IsTradeCenter( hisim producer );

// EOF /////////////////////////////////////////////////////////////////////////

