//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsArray.h
//
// Compiler-generated export header for package "tsArray"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tsArray.SetArrayString( hobject obj, string array_name, int index, string value );

prototype string tsArray.GetArrayString( hobject obj, string array_name, int index );

prototype tsArray.SetArrayHandle( hobject obj, string array_name, int index, hobject value );

prototype hobject tsArray.GetArrayHandle( hobject obj, string array_name, int index );

prototype tsArray.SetArrayBool( hobject obj, string array_name, int index, bool value );

prototype bool tsArray.GetArrayBool( hobject obj, string array_name, int index );

prototype tsArray.SetArrayInt( hobject obj, string array_name, int index, int value );

prototype int tsArray.GetArrayInt( hobject obj, string array_name, int index );

prototype tsArray.ShrinkArray( hobject obj, string array_name, int size );

prototype tsArray.DeleteArray( hobject obj, string array_name );

prototype int tsArray.ArraySize( hobject obj, string array_name );

// EOF /////////////////////////////////////////////////////////////////////////

