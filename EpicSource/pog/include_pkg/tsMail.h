//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsMail.h
//
// Compiler-generated export header for package "tsMail"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tsMail.ReadArchives();

prototype tsMail.SaveArchives();

prototype hsim tsMail.CreateArchive( string name, string screen_name, string desc, bool base_only, bool player_viewable );

prototype hsim tsMail.FindArchive( string name );

prototype int tsMail.NewArchiveMail( hsim archive );

prototype list tsMail.GetArchiveMail( hsim archive );

prototype tsMail.DeleteArchiveMail( hsim archive );

prototype bool tsMail.isArViewable( hsim archive );

prototype bool tsMail.isArBaseOnly( hsim archive );

prototype tsMail.SetArViewable( hsim archive, bool player_viewable );

prototype tsMail.SetArBaseOnly( hsim archive, bool base_only );

prototype string tsMail.ScreenName( hsim archive );

prototype string tsMail.Desc( hsim archive );

prototype int tsMail.SendMail( hsim archive, string sender, string subj, string body, string reply, hobject reply_obj, string date, bool no_save, bool critical, bool html );

prototype string tsMail.Sender( hsim mail );

prototype string tsMail.Subject( hsim mail );

prototype string tsMail.Body( hsim mail );

prototype tsMail.SetRead( hsim mail );

prototype bool tsMail.HasReply( hsim mail );

prototype tsMail.RunReply( hsim mail );

prototype int tsMail.GetReplyId();

prototype hobject tsMail.GetReplyObject();

prototype bool tsMail.isDeleted( hsim mail );

prototype tsMail.DeleteMail( hsim mail, bool check );

prototype bool tsMail.Read( hsim mail );

prototype bool tsMail.isRead( hsim archive, int mail_id );

prototype bool tsMail.isHtml( hsim mail );

prototype tsMail.MoveMail( hsim mail, hsim old_archive, hsim new_archive );

// EOF /////////////////////////////////////////////////////////////////////////

