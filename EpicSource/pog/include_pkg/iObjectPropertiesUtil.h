//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// iObjectPropertiesUtil.h
//
// Compiler-generated export header for package "iObjectPropertiesUtil"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype bool iObjectPropertiesUtil.SetIntProperty( hobject obj, string property_name, int value );

prototype iObjectPropertiesUtil.SetArrayString( hobject obj, string array_name, int index, string value );

prototype string iObjectPropertiesUtil.GetArrayString( hobject obj, string array_name, int index );

prototype iObjectPropertiesUtil.SetArrayHandle( hobject obj, string array_name, int index, hobject value );

prototype hobject iObjectPropertiesUtil.GetArrayHandle( hobject obj, string array_name, int index );

prototype iObjectPropertiesUtil.SetArrayBool( hobject obj, string array_name, int index, bool value );

prototype bool iObjectPropertiesUtil.GetArrayBool( hobject obj, string array_name, int index );

prototype iObjectPropertiesUtil.SetArrayInt( hobject obj, string array_name, int index, int value );

prototype int iObjectPropertiesUtil.GetArrayInt( hobject obj, string array_name, int index );

prototype iObjectPropertiesUtil.ShrinkArray( hobject obj, string array_name, int size );

prototype iObjectPropertiesUtil.DeleteArray( hobject obj, string array_name );

prototype int iObjectPropertiesUtil.ArraySize( hobject obj, string array_name );

prototype int iObjectPropertiesUtil.ItemCount( hobject obj, string array_name );

prototype int iObjectPropertiesUtil.AddArrayProperty( hobject obj, string array_name, string array_type );

prototype int iObjectPropertiesUtil.RemoveArrayProperty( hobject obj, string array_name );

prototype int iObjectPropertiesUtil.AddIntArrayPropertyTail( hobject obj, string array_name, int value );

prototype int iObjectPropertiesUtil.AddFloatArrayPropertyTail( hobject obj, string array_name, float value );

prototype int iObjectPropertiesUtil.AddBoolArrayPropertyTail( hobject obj, string array_name, bool value );

prototype int iObjectPropertiesUtil.AddStringArrayPropertyTail( hobject obj, string array_name, string value );

prototype int iObjectPropertiesUtil.AddHandleArrayPropertyTail( hobject obj, string array_name, hobject value );

// EOF /////////////////////////////////////////////////////////////////////////

