//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// Sandbox.h
//
// Compiler-generated export header for package "Sandbox"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/Sandbox.h,v 1.2 2005/05/13 09:42:03 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype Sandbox.SandboxInitialise();

prototype SandboxDefendDelay_TASK Sandbox.SandboxDefendDelay_TASK();

prototype SandboxAttackDelay_TASK Sandbox.SandboxAttackDelay_TASK();

prototype list Sandbox.Sandbox_Create_Ship_LIST( hwindow Sandbox_Ship_Box );

prototype Sandbox.SandboxShipSelection( hwindow Sandbox_Ship_Box );

prototype Sandbox.SandboxScenarioContinue();

prototype Sandbox.SandboxOnQuit();

prototype Sandbox.SandboxWaypoints();

prototype Sandbox.SandboxScenarioType();

prototype Sandbox.SandboxToggle();

prototype Sandbox.SandboxScreen();

prototype Sandbox.SandboxAttackScenarioSelected();

prototype Sandbox.SandboxDefendScenarioSelected();

prototype Sandbox.SandboxStartSimulation();

prototype Sandbox.WindowTextWrapper( string window_text );

prototype Sandbox.UpdateFriendlyFleet( string friendly_ship_type );

prototype Sandbox.UpdateEnemyFleet( string enemy_ship_type );

// EOF /////////////////////////////////////////////////////////////////////////

