//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsEvent.h
//
// Compiler-generated export header for package "tsEvent"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tsEvent.h,v 1.1 2006/04/04 14:55:23 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype tsEvent.InitReciever( hobject listener );

prototype tsEvent.SetListenType( hobject listener, int type );

prototype int tsEvent.GetListenType( hobject listener );

prototype tsEvent.SendEvent( hobject listener, int priority, int event_type, hisim location, hisim target, hisim sender );

prototype bool tsEvent.IsNewEvent( hobject listener );

prototype tsEvent.RemoveEvent( hobject listener );

prototype tsEvent.ClearNewFlag( hobject listener );

prototype int tsEvent.GetPriority( hobject listener );

prototype int tsEvent.GetEventType( hobject listener );

prototype hisim tsEvent.GetLocation( hobject listener );

prototype hisim tsEvent.GetTarget( hobject listener );

prototype hisim tsEvent.GetSender( hobject listener );

// EOF /////////////////////////////////////////////////////////////////////////

