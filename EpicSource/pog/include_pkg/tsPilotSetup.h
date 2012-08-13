//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsPilotSetup.h
//
// Compiler-generated export header for package "tsPilotSetup"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tsPilotSetup.h,v 1.2 2006/03/28 13:28:59 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tsPilotSetup.SetupOperation( hship ship, float notice_level, float flee_level );

prototype task tsPilotSetup.OperationDeath( hship ship );

prototype tsPilotSetup.SetupCargo( hship cargo_ship, float notice_level, float flee_level );

prototype task tsPilotSetup.CargoSelfPreserve( hship cargo_ship );

prototype task tsPilotSetup.CargoDeath( hship cargo_ship );

prototype tsPilotSetup.SetupEscort( hship escort, float notice_level, float flee_level );

prototype task tsPilotSetup.EscortSelfPreserve( hship escort );

prototype task tsPilotSetup.EscortDeath( hship escort );

// EOF /////////////////////////////////////////////////////////////////////////

