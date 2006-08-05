//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// uString.h
//
// Compiler-generated export header for package "uString"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/uString.h,v 1.3 2006/03/15 06:47:27 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype string uString.RemoveSpace( string words );

prototype int uString.Locate( string source, string mark );

prototype string uString.Replace( string source, string mark, string replacement );

prototype string uString.Htmlize( string source );

prototype string uString.EndName( string source );

prototype string uString.CargoNameNoSpace( string source );

prototype string uString.TranslatedString( string key_string, string style, int index );

prototype string uString.TranslatedStringRandom( string key_string, string style, int highest_index );

prototype string uString.CommsString( string key_string, string style, int index );

prototype string uString.CommsStringRandom( string key_string, string style, int highest_index );

// EOF /////////////////////////////////////////////////////////////////////////

