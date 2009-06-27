//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsFleetOp.h
//
// Compiler-generated export header for package "tsFleetOp"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype hisim tsFleetOp.NewOp( int op_type, hfaction faction, hmapentity center );

prototype hisim tsFleetOp.Create( int op_id, hfaction faction, bool known, int wake_day );

prototype tsFleetOp.DestroyOp( hisim operation );

prototype bool tsFleetOp.IsOperation( hisim operation );

prototype int tsFleetOp.GetOperationType( hisim operation );

prototype string tsFleetOp.GetOperationPog( hisim operation );

prototype string tsFleetOp.GetOperationEnvFoTemplate( hisim operation );

prototype int tsFleetOp.GetOperationMaxFleets( hisim operation );

prototype string tsFleetOp.GetOperationShipClass( hisim operation );

prototype hisim tsFleetOp.Find( int operation_id );

prototype tsFleetOp.SetKnown( hisim operation, bool known );

prototype bool tsFleetOp.IsKnown( hisim operation );

prototype int tsFleetOp.EventTimer( hisim operation );

prototype tsFleetOp.SetEventTimer( hisim operation, int day );

prototype int tsFleetOp.WakeTimer( hisim operation );

prototype tsFleetOp.SetWakeTimer( hisim operation, int day );

prototype bool tsFleetOp.IsCreated( hisim operation );

prototype tsFleetOp.SetCreated( hisim operation, bool existing );

prototype string tsFleetOp.Name( hisim operation );

prototype tsFleetOp.SetName( hisim operation, string name );

prototype string tsFleetOp.ShipTemplate( hisim operation );

prototype tsFleetOp.SetShipTemplate( hisim operation, string ship_template );

prototype list tsFleetOp.OperationList();

prototype list tsFleetOp.StationOperations( hisim station );

prototype list tsFleetOp.StationOperationsOfType( hisim station, int type );

prototype list tsFleetOp.SupportedOperations( hhabitat station );

prototype tsFleetOp.SetSupporter( hisim operation, hhabitat station );

prototype hhabitat tsFleetOp.Supporter( hisim operation );

prototype tsFleetOp.DisplayOps();

prototype tsFleetOp.KillShipOnOp( hisim operation, hship ship );

prototype tsFleetOp.SetShipOnOp( hisim operation, hship ship, int index );

// EOF /////////////////////////////////////////////////////////////////////////

