//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tShipMail.h
//
// Compiler-generated export header for package "tShipMail"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tShipMail.h,v 1.1 2006/01/23 16:52:16 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tShipMail.StartScreen();

prototype tShipMail.RunCheck();

prototype int tShipMail.SendEmail( string sender, string subject, string body, string reply_function, bool critical, bool html_body );

prototype bool tShipMail.Read( int mail_id );

prototype tShipMail.OnQuit();

prototype tShipMail.ShipMailScreen();

prototype tShipMail.StartMyMod();

prototype tShipMail.MailViewListPress();

prototype tShipMail.MailViewBackPress();

prototype tShipMail.MailAcceptButtonPressed();

prototype tShipMail.ArchiveButtonPress();

prototype tShipMail.DeleteButtonPress();

prototype tShipMail.Register();

// EOF /////////////////////////////////////////////////////////////////////////

