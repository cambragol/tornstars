//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsString.h
//
// Compiler-generated export header for package "tsString"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype string tsString.RemoveSpace( string words );

prototype int tsString.Locate( string source, string mark );

prototype string tsString.Replace( string source, string mark, string replacement );

prototype string tsString.Htmlize( string source );

prototype string tsString.EndName( string source );

prototype string tsString.CargoNameNoSpace( string source );

prototype string tsString.TranslatedString( string key_string, string style, int index );

prototype string tsString.TranslatedStringRandom( string key_string, string style, int highest_index );

prototype string tsString.CommsString( string key_string, string style, int index );

prototype string tsString.CommsStringRandom( string key_string, string style, int highest_index );

// EOF /////////////////////////////////////////////////////////////////////////

