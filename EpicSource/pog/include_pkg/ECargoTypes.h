//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// ECargoTypes.h
//
// Compiler-generated export header for package "ECargoTypes"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/ECargoTypes.h,v 1.2 2005/05/13 09:42:03 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////
uses iCargoScript;
// Enumerated types ////////////////////////////////////////////////////////////

enum eCargoValue
{ ECV_Invalid,
  ECV_Cheap,
  ECV_Average,
  ECV_Expensive,
  ECV_Exorbitant
};

// Functions ///////////////////////////////////////////////////////////////////
prototype string ECargoTypes.CargoString2DBKey( string to_cast );

prototype eCargoValue Int2CargoValue ( int to_cast );

prototype string ECargoTypes.CargoCategory2String( eCargoCategory to_cast );

prototype string ECargoTypes.CargoSuperSet2String( eCargoSuperSet to_cast );

prototype string ECargoTypes.CargoType2String( eCargoType to_cast );

prototype eCargoCategory ECargoTypes.Int2CargoCategory( int to_cast );

prototype eCargoSuperSet ECargoTypes.Int2CargoSuperSet( int to_cast );

prototype eCargoType ECargoTypes.Int2CargoType( int to_cast );

prototype eCargoCategory ECargoTypes.String2CargoCategory( string to_cast );

prototype eCargoSuperSet ECargoTypes.String2CargoSuperSet( string to_cast );

prototype eCargoType ECargoTypes.String2CargoType( string to_cast );

// EOF /////////////////////////////////////////////////////////////////////////

