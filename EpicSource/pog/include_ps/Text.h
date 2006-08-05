//
// (c) 1999 Particle Systems Ltd. All Rights Reserved
//
// Text.h
//
// API for the package Text.
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_ps/Text.h,v 1.1.1.1 2005/05/13 09:27:23 Owner Exp $
//

#include "Flux.h"

#ifdef FLUX_COMPILE

FLUX_DECLARE_EXTENSION(Text);

#ifdef FLUX_LIB
#if _MSC_VER >= 1000
#pragma comment( lib, "text" )
#endif // _MSC_VER >= 1000
#endif // FLUX_LIB

#else

uses String;

// Field enumeration
enum eFieldType { FT_Text, FT_Wav };

//
// Text.Add( string filename )
//
// Add a file to the localised text system
//
prototype Text.Add( string filename );

//
// Text.Remove( string filename )
//
// Remove a file from the localised text system
//
prototype Text.Remove( string filename );

//
// string Text.Field( string key, eFields field )
//
// Access a field for this key in the localised text system
//
prototype string Text.Field( string key, eFieldType field );

#endif // FLUX_LIB
