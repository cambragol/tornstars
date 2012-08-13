//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// UniGUI.h
//
// Compiler-generated export header for package "UniGUI"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/UniGUI.h,v 1.2 2005/05/13 09:42:03 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype UniGUI.Initialise();

prototype UniGUI.UniGUIScreen();

prototype UniGUI.UniGUIWelcomeScreen();

prototype UniGUI.UniGUIToggle();

prototype UniGUI.UniGUIStart();

prototype UniGUI.UniGUIAddScreen( string screen_func );

prototype UniGUI.UniGUIRemoveScreen();

prototype UniGUI.UniGUISwapScreen( string screen_func );

prototype UniGUI.UniGUIClose();

prototype UniGUI.OnShow();

prototype UniGUI.OnContinue();

prototype UniGUI.OnSelectScreen();

prototype bool UniGUI.ChargePlayer( int number );

prototype bool UniGUI.PayPlayer( int number );

prototype UniGUI.OnQuit();

prototype UniGUI.OnPDA();

prototype UniGUI.UniGUILock();

prototype UniGUI.UniGUIUnlock();

prototype hwindow UniGUI.CreateShadyBox( hwindow shady_bar );

prototype UniGUI.AddWideTitle();

prototype UniGUI.True();

// EOF /////////////////////////////////////////////////////////////////////////

