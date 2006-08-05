//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tUnderOp.h
//
// Compiler-generated export header for package "tUnderOp"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tUnderOp.h,v 1.6 2006/04/16 20:53:02 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype hisim tUnderOp.NewOp( int op_type, hfaction faction, hmapentity center );

prototype hisim tUnderOp.Create( int op_id, hfaction faction, bool known, int wake_day );

prototype tUnderOp.DestroyOp( hisim operation );

prototype bool tUnderOp.IsOperation( hisim operation );

prototype hisim tUnderOp.Find( int operation_id );

prototype tUnderOp.SetKnown( hisim operation, bool known );

prototype bool tUnderOp.IsKnown( hisim operation );

prototype int tUnderOp.EventTimer( hisim operation );

prototype tUnderOp.SetEventTimer( hisim operation, int day );

prototype int tUnderOp.WakeTimer( hisim operation );

prototype tUnderOp.SetWakeTimer( hisim operation, int day );

prototype bool tUnderOp.IsCreated( hisim operation );

prototype tUnderOp.SetCreated( hisim operation, bool existing );

prototype string tUnderOp.Name( hisim operation );

prototype tUnderOp.SetName( hisim operation, string name );

prototype string tUnderOp.ShipTemplate( hisim operation );

prototype tUnderOp.SetShipTemplate( hisim operation, string ship_template );

prototype list tUnderOp.OperationList();

prototype list tUnderOp.StationOperations( hisim station );

prototype list tUnderOp.StationOperationsOfType( hisim station, int type );

prototype list tUnderOp.SupportedOperations( hhabitat station );

prototype tUnderOp.SetSupporter( hisim operation, hhabitat station );

prototype hhabitat tUnderOp.Supporter( hisim operation );

prototype tUnderOp.DisplayOps();

// EOF /////////////////////////////////////////////////////////////////////////

