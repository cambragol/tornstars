//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// ECargoTypes.h
//
// Compiler-generated export header for package "ECargoTypes"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////


enum eCargoCategory
{
};

enum eCargoSuperSet
{
};

enum eCargoType
{
};

enum eCargoValue
{
};
// Functions ///////////////////////////////////////////////////////////////////

prototype eCargoValue ECargoTypes.Int2CargoValue( int to_cast );

prototype string ECargoTypes.CargoString2DBKey( string to_cast );

prototype string ECargoTypes.CargoCategory2String( eCargoCategory to_cast );

prototype string ECargoTypes.CargoSuperSet2String( eCargoSuperSet to_cast );

prototype string ECargoTypes.CargoType2String( eCargoType to_cast );

prototype eCargoCategory ECargoTypes.Int2CargoCategory( int to_cast );

prototype eCargoSuperSet ECargoTypes.Int2CargoSuperSet( int to_cast );

prototype eCargoType ECargoTypes.Int2CargoType( int to_cast );

prototype eCargoCategory ECargoTypes.String2CargoCategory( string to_cast );

prototype eCargoSuperSet ECargoTypes.String2CargoSuperSet( string to_cast );

prototype eCargoType ECargoTypes.String2CargoType( string to_cast );

prototype ECargoTypes.Test();

// EOF /////////////////////////////////////////////////////////////////////////

