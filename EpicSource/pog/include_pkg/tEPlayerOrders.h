//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tEPlayerOrders.h
//
// Compiler-generated export header for package "tEPlayerOrders"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tEPlayerOrders.h,v 1.7 2006/03/11 05:58:33 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype bool tEPlayerOrders.Halt( int group );

prototype bool tEPlayerOrders.DefendMe( int group );

prototype bool tEPlayerOrders.AttackTarget( int group, hisim target );

prototype bool tEPlayerOrders.DefendTarget( int group, hisim target );

prototype bool tEPlayerOrders.DockTarget( int group, hisim target );

prototype bool tEPlayerOrders.ApproachTarget( int group, hisim target );

prototype bool tEPlayerOrders.CaptureShip( int group, hship target );

prototype bool tEPlayerOrders.DockPod( int group );

prototype bool tEPlayerOrders.CollectPods( int group );

prototype bool tEPlayerOrders.UndockAllPods( int group );

prototype bool tEPlayerOrders.ShipToGroup( hship ship, int group );

prototype bool tEPlayerOrders.RemoveShip( hship ship );

prototype bool tEPlayerOrders.GroupExists( int group );

prototype hisim tEPlayerOrders.OrderTarget( hship ship );

prototype tEPlayerOrders.SetOrderTarget( hship ship, hisim target );

prototype bool tEPlayerOrders.FuelTarget( int group, hship target );

prototype bool tEPlayerOrders.FuelDrainTarget( int group, hship target );

prototype bool tEPlayerOrders.TankersFillFleet( int group );

prototype bool tEPlayerOrders.ScanSky( int group );

prototype bool tEPlayerOrders.ProspectAsteroid( int group );

prototype bool tEPlayerOrders.MineAsteroid( int group );

prototype bool tEPlayerOrders.DetachAsteroid( int group );

// EOF /////////////////////////////////////////////////////////////////////////

