//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tEShipCreation.h
//
// Compiler-generated export header for package "tEShipCreation"
//
// Revision control information:
//
// $Header: c:/epic/cvs/EpicSource/pog/include_pkg/tEShipCreation.h,v 1.2 2006/04/04 14:55:22 Owner Exp $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types /////////////////////////////////////////////////////////

enum eEShipType
{
   EST_Invalid,
	EST_Gunstar,

	EST_Drone,
	EST_Waldo,
	EST_CommandSection,
	EST_Utility,
	EST_Passenger,
	EST_Fighter,
	EST_Tug,
	EST_Patcom,
	EST_Interceptor,
	EST_Corvette,
	EST_Freighter,
	EST_Destroyer,
	EST_Cruiser,
	EST_Carrier,  

	EST_FreightLight, 
   EST_FreightHeavy, 
   EST_FreightAll, 
   EST_FreightSuperHeavy, 
	EST_FreightCourier, 

   EST_CombatFighter, 
   EST_CombatLight, 
   EST_CombatHeavy,
	EST_CombatCaptial, 
   EST_CombatAll, 

   EST_Medical, 
   EST_Interface, 
   EST_PassengerLight, 
	EST_PassengerHeavy, 
   EST_PassengerAll, 

   EST_MiningLight, 
   EST_MiningHeavy, 
   EST_MiningAll,

	EST_TankerLight, 
   EST_TankerHeavy, 
   EST_TankerAll, 

   EST_GeneralPurpose, 
   EST_Flitter, 
   EST_Recovery,
	EST_DemoShips, 
   EST_Taxi,
   EST_Max
};


// Functions ///////////////////////////////////////////////////////////////////

prototype string tEShipCreation.GetShip( hfaction faction, eEShipType ship_type );

prototype string tEShipCreation.ShipClassTemplate( string faction, string fleet_style, string ship_class );

prototype string tEShipCreation.ShipType2String( eEShipType ship_type );

prototype eEShipType tEShipCreation.String2ShipType( string type_name );

prototype tEShipCreation.TestINIFile( );

// EOF /////////////////////////////////////////////////////////////////////////

