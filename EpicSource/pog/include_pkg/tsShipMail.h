//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsShipMail.h
//
// Compiler-generated export header for package "tsShipMail"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tsShipMail.StartScreen();

prototype tsShipMail.RunCheck();

prototype int tsShipMail.SendEmail( string sender, string subject, string body, string reply_function, bool critical, bool html_body );

prototype bool tsShipMail.Read( int mail_id );

prototype tsShipMail.OnQuit();

prototype tsShipMail.ShipMailScreen();

prototype tsShipMail.StartMyMod();

prototype tsShipMail.MailViewListPress();

prototype tsShipMail.MailViewBackPress();

prototype tsShipMail.MailAcceptButtonPressed();

prototype tsShipMail.ArchiveButtonPress();

prototype tsShipMail.DeleteButtonPress();

prototype tsShipMail.Register();

// EOF /////////////////////////////////////////////////////////////////////////

