//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsGui.h
//
// Compiler-generated export header for package "tsGui"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tsGui.InitGlobals();

prototype hwindow tsGui.CreateTitle( hwindow parent, string name );

prototype hwindow tsGui.CreateSubtitle( hwindow parent, string name );

prototype hwindow tsGui.CreateExitButton( hwindow parent, string name, string function );

prototype tsGui.SetStandardStateColours( hwindow to_set );

prototype tsGui.SetWindowStateColours( hwindow to_set, eColour n_base_colour, eIntensity n_intensity, eColour f_base_colour, eIntensity f_intensity, eColour s_base_colour, eIntensity s_intensity );

// EOF /////////////////////////////////////////////////////////////////////////

