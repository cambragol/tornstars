//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// iINIFileUtil.h
//
// Compiler-generated export header for package "iINIFileUtil"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype int iINIFileUtil.CountNumber( string filename, string section, string key );

prototype string iINIFileUtil.StringKeyLookupStringData( hinifile ref_inifile, string ref_section, string ref_key, string search_value, hinifile lookup_inifile, string lookup_section, string lookup_key );

prototype string iINIFileUtil.StringFloatTwoKeyLookupStringData( hinifile ref_inifile, string ref_section, string ref_key_1, string search_value_1, string ref_key_2, float ref_value_2, hinifile lookup_inifile, string lookup_section, string lookup_key );

prototype string iINIFileUtil.UniqueStringKeyLookupStringData( hinifile ref_inifile, string ref_section, string ref_key, string search_value, hinifile lookup_inifile, string lookup_section, string lookup_key );

prototype int iINIFileUtil.NumberedKeyMaxIndex( hinifile inifile, string section, string key );

prototype int iINIFileUtil.InstancesOfNumberedKeyStringValue( hinifile inifile, string section, string key, string value );

prototype int iINIFileUtil.CheckSimpleKeyValueString( string simple_key_value );

prototype int iINIFileUtil.ParseSectionKeysValues( hobject obj, string sectionkeysvalues, string property_name );

prototype int iINIFileUtil.SelectSectionKeysValues( hinifile inifile, string sectionkeysvalues, string output_name );

// EOF /////////////////////////////////////////////////////////////////////////

