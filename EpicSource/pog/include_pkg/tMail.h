//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tMail.h
//
// Compiler-generated export header for package "tMail"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tMail.h,v 1.1 2006/01/23 16:52:16 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tMail.ReadArchives();

prototype tMail.SaveArchives();

prototype hsim tMail.CreateArchive( string name, string screen_name, string desc, bool base_only, bool player_viewable );

prototype hsim tMail.FindArchive( string name );

prototype int tMail.NewArchiveMail( hsim archive );

prototype list tMail.GetArchiveMail( hsim archive );

prototype tMail.DeleteArchiveMail( hsim archive );

prototype bool tMail.isArReady();

prototype bool tMail.isArViewable( hsim archive );

prototype bool tMail.isArBaseOnly( hsim archive );

prototype tMail.SetArViewable( hsim archive, bool player_viewable );

prototype tMail.SetArBaseOnly( hsim archive, bool base_only );

prototype string tMail.ScreenName( hsim archive );

prototype string tMail.Desc( hsim archive );

prototype int tMail.SendMail( hsim archive, string sender, string subj, string body, string reply, hobject reply_obj, string date, bool no_save, bool critical, bool html );

prototype string tMail.Sender( hsim mail );

prototype string tMail.Subject( hsim mail );

prototype string tMail.Body( hsim mail );

prototype tMail.SetRead( hsim mail );

prototype bool tMail.HasReply( hsim mail );

prototype tMail.RunReply( hsim mail );

prototype int tMail.GetReplyId();

prototype hobject tMail.GetReplyObject();

prototype bool tMail.isDeleted( hsim mail );

prototype tMail.DeleteMail( hsim mail, bool check );

prototype bool tMail.Read( hsim mail );

prototype bool tMail.isRead( hsim archive, int mail_id );

prototype bool tMail.isHtml( hsim mail );

prototype tMail.MoveMail( hsim mail, hsim old_archive, hsim new_archive );

// EOF /////////////////////////////////////////////////////////////////////////

