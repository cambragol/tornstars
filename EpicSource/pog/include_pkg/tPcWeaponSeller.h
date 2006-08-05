//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tPcWeaponSeller.h
//
// Compiler-generated export header for package "tPcWeaponSeller"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tPcWeaponSeller.h,v 1.3 2006/03/04 18:33:29 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype hsim tPcWeaponSeller.PogCreate( string template_name, string object_name );

prototype task tPcWeaponSeller.PogStart( hsim pog_object );

prototype task tPcWeaponSeller.Comms();

prototype task tPcWeaponSeller.CriminalComms();

prototype tPcWeaponSeller.SessionStart();

prototype tPcWeaponSeller.SessionEnd();

// EOF /////////////////////////////////////////////////////////////////////////

