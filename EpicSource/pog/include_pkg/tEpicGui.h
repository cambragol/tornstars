//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tEpicGui.h
//
// Compiler-generated export header for package "tEpicGui"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tEpicGui.h,v 1.2 2005/05/13 09:42:04 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////
uses tEpicGuiEnum;
// Enumerated types ////////////////////////////////////////////////////////////



// Functions ///////////////////////////////////////////////////////////////////
prototype tEpicGui.InitGlobals();

prototype hwindow tEpicGui.CreateTitle( hwindow parent, string name );

prototype hwindow tEpicGui.CreateSubtitle( hwindow parent, string name );

prototype hwindow tEpicGui.CreateExitButton( hwindow parent, string name, string function );

prototype tEpicGui.SetStandardStateColours( hwindow to_set );

prototype tEpicGui.SetWindowStateColours( hwindow to_set, eColour n_base_colour, eIntensity n_intensity, eColour f_base_colour, eIntensity f_intensity, eColour s_base_colour, eIntensity s_intensity );

// EOF /////////////////////////////////////////////////////////////////////////

