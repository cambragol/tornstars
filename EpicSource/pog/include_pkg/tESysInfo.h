//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tESysInfo.h
//
// Compiler-generated export header for package "tESysInfo"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tESysInfo.h,v 1.2 2005/05/13 09:42:03 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tESysInfo.Init();

prototype hsim tESysInfo.Find( string system_name );

prototype hsim tESysInfo.Government( hsim system_info );

prototype tESysInfo.SetGovernment( hsim system_info, hsim efaction );

prototype float tESysInfo.LawLevel( hsim system_info );

prototype tESysInfo.SetLawLevel( hsim system_info, float law_level );

prototype tESysInfo.ChangeLawLevel( hsim system_info, float amount );

prototype tESysInfo.UnitTestDisplay();

// EOF /////////////////////////////////////////////////////////////////////////

