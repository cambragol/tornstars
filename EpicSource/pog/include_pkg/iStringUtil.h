//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// iStringUtil.h
//
// Compiler-generated export header for package "iStringUtil"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype string iStringUtil.RemoveSpace( string words );

prototype int iStringUtil.Locate( string source, string mark );

prototype string iStringUtil.Replace( string source, string mark, string replacement );

prototype string iStringUtil.Htmlize( string source );

prototype string iStringUtil.EndName( string source );

prototype string iStringUtil.CargoNameNoSpace( string source );

prototype string iStringUtil.TranslatedString( string key_string, string style, int index );

prototype string iStringUtil.TranslatedStringRandom( string key_string, string style, int highest_index );

prototype string iStringUtil.CommsString( string key_string, string style, int index );

prototype string iStringUtil.CommsStringRandom( string key_string, string style, int highest_index );

prototype int iStringUtil.LocateLastInstance( string source, string mark );

prototype int iStringUtil.LocateNthNonOverlappingInstance( string source, string mark, int n );

prototype string iStringUtil.TerminalStringAfterLastInstanceOfSearchString( string source, string mark );

prototype int iStringUtil.NumberOfNonoverlappingInstances( string source, string mark );

prototype int iStringUtil.SeparateDelimitedStrings( hobject obj, string delimited_string, string delimiter, string name );

prototype int iStringUtil.ParseSectionKey( hobject obj, string section_key );

// EOF /////////////////////////////////////////////////////////////////////////

