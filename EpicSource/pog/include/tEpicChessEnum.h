


enum eFleetOrders {
   FO_Idle,          // stay where located.
   FO_Transit,       // move to specified location
   FO_Flee,          // move to location, but do not stop
   FO_Attack,        // move to location, and attack faction
   FO_Blockade,      // move to location, attack faction transits
   FO_Pirate,        // move to location, hunt transits
   FO_Patrol,        // move to location, hunt pirates and smugglers
   FO_Guard          // protect station, read station flags
};


enum eChessShipState {
   CSS_PieceMode,
   CSS_ShipMode,
   CSS_Empty,
   CSS_Destroyed,
   CSS_Ok
};
