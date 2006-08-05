//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tEconUtil.h
//
// Compiler-generated export header for package "tEconUtil"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tEconUtil.h,v 1.5 2006/04/04 14:55:22 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype int tEconUtil.CargoType( hcargo cargo );

prototype string tEconUtil.StationIntToString( int type );

prototype int tEconUtil.StationStringToEnum( string instring );

prototype eCargoType tEconUtil.String2CargoType( string to_cast );

prototype eCargoType tEconUtil.EconString2CargoType( string to_cast );

prototype string tEconUtil.ShipType2String( int ship_type );

prototype int tEconUtil.StationType2Category( int type );

prototype bool tEconUtil.IsAllowedIndependent( int type );

prototype bool tEconUtil.IsAllowedMegaCorp( int type );

prototype bool tEconUtil.IsAllowedGovernment( int type );

prototype bool tEconUtil.IsAllowedRebel( int type );

prototype bool tEconUtil.IsAllowedPirate( int type );

prototype bool tEconUtil.IsAllowedMercenary( int type );

// EOF /////////////////////////////////////////////////////////////////////////

