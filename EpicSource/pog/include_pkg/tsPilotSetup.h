//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsPilotSetup.h
//
// Compiler-generated export header for package "tsPilotSetup"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tsPilotSetup.SetupOperation( hship ship, float notice_level, float flee_level );

prototype OperationDeath tsPilotSetup.OperationDeath( hship ship );

prototype tsPilotSetup.SetupCargo( hship cargo_ship, float notice_level, float flee_level );

prototype CargoSelfPreserve tsPilotSetup.CargoSelfPreserve( hship cargo_ship, hship agressor_ship );

prototype CargoDeath tsPilotSetup.CargoDeath( hship cargo_ship );

prototype tsPilotSetup.SetupEscort( hship escort, float notice_level, float flee_level );

prototype EscortSelfPreserve tsPilotSetup.EscortSelfPreserve( hship escort, hship agressor_ship );

prototype EscortDeath tsPilotSetup.EscortDeath( hship escort );

// EOF /////////////////////////////////////////////////////////////////////////

