//*******************************************************************************************/
//
// tEpicEventEnum.h
//
// Event and listener queue types added here.
// 
// 
// 
//
// May 2003, Jon Freise
//******************************************************************************************/


enum eEventQType {
   eDiplomaticEvent=1,
   eShipEvent=2
};

enum eEventType {
   etShipAttacked=1,
   etDistressCall=2,
   etHostile=4,
   etNewOrder=8,
   etPlayerArrives=16
};


// Ship events are a quick communication system
// used to signal combat events between existing
// ships.

// They also signal arriving transports for 
// customs and pirate patrols to intercept.
enum eEpicShipEvent {
   eseNone =0,
   eseTransportArrived =1,
   eseDistress =2,             // nearby ship attacked
   eseStationAttack =4,        // nearby station attacked
   eseSelfAttacked =8,         // own group attacked
   eseFlee=16                  // own group flees
};

enum eShipEventPriority {
   espNone = 0,
   espInformation,
   espDistress,
   espStationAttack,
   espSelfAttacked
};


enum eSoundEventPriority {
   esepNone = 0,
   esepUseless,
   esepImportant,
   esepCritical
};
