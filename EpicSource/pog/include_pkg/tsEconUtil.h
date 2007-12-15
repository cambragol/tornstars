//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsEconUtil.h
//
// Compiler-generated export header for package "tsEconUtil"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype int tsEconUtil.CargoType( hcargo cargo );

prototype string tsEconUtil.StationIntToString( int type );

prototype int tsEconUtil.StationStringToEnum( string instring );

prototype eCargoType tsEconUtil.String2CargoType( string to_cast );

prototype eCargoType tsEconUtil.EconString2CargoType( string to_cast );

prototype string tsEconUtil.ShipType2String( int ship_type );

prototype int tsEconUtil.StationType2Category( int type );

prototype bool tsEconUtil.IsAllowedIndependent( int type );

prototype bool tsEconUtil.IsAllowedMegaCorp( int type );

prototype bool tsEconUtil.IsAllowedGovernment( int type );

prototype bool tsEconUtil.IsAllowedRebel( int type );

prototype bool tsEconUtil.IsAllowedPirate( int type );

prototype bool tsEconUtil.IsAllowedMercenary( int type );

prototype bool tsEconUtil.IsAllowedLoadout( int type );

// EOF /////////////////////////////////////////////////////////////////////////

