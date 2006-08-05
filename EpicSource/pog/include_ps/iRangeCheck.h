//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// iRangeCheck.h
//
// Compiler-generated export header for package "iRangeCheck"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_ps/iRangeCheck.h,v 1.1.1.1 2005/05/13 09:27:23 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype task iRangeCheck.MonitorRange();

prototype iRangeCheck.AddTrafficException( hmapentity location );

prototype iRangeCheck.AddTrafficExceptionsInArea( hmapentity location, float radius );

prototype iRangeCheck.RemoveTrafficException( hmapentity location );

prototype iRangeCheck.RemoveTrafficExceptionsInArea( hmapentity location, float radius );

prototype iRangeCheck.PurgeTrafficException();

prototype iRangeCheck.AddOutOfSystemTrafficException ( hmapentity location );

prototype iRangeCheck.RemoveOutOfSystemTrafficException ( hmapentity location );

prototype iRangeCheck.PurgeOutOfSystemTrafficExceptions ();

// EOF /////////////////////////////////////////////////////////////////////////

