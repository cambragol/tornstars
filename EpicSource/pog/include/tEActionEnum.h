//*******************************************************************************************/
//
// tEActionEnum.h
//
// This file contains the enumerations for the planning and action handling code.
// 
// The compiler does not handle enumerations, and this file lets the build automate.
// 
//
// 
//	
// 
//
// Feb 2004, Jon Freise
//******************************************************************************************/


enum eActionResult
{
   ARC_NotDone = 0,  // action still happening.
   ARC_Timeout = 1,  // job time up, but not done.
   ARC_Failed = 2,   // action attempted, but failed.
   ARC_Success = 3   // action attempted, success.
};

enum eActionCondition {
   ACND_Nothing =0,
   ACND_Provoking = 1,  // provoke further hostilities.
   ACND_Holding = 2,    // neither provoke, nor cool down.
   ACND_Lowering = 4,   // respond, but make clear you would like less hostility.
   ACND_Local = 8,       // inside sphere (police), or outside (mercenary).
   ACND_Integrity = 16,     // Diplomatic actions usually require integrity of target.
   ACND_Hidden = 32,       // Some actions happen without news ever knowing. (not reported).
   ACND_Criminal = 64,       // Criminal actions
   ACND_Gray = 128,       // Borderline actions (RealPolitik)
   ACND_Lawful = 256,       // Legal and Honorable actions

   ACND_Leader = 512,      // Fleet commander required
   ACND_Agent = 1024       // Intelligence agent required
};

enum ePlanCondition {

   PCND_Nothing =0,
   PCND_Leader = 1,   // Required for hired troops
   PCND_Agent = 2,    // Required for hired espionage
   PCND_Diplomat = 4, // Required for alliances, peace

   PCND_NonLocal = 8  // Can only be used outside own nation
                    
}; 



// Action Category is used to calculate the response lowering
// value. And report news.

enum eActionCategory {
   ACAT_None,
   ACAT_CargoRaid, 
   ACAT_ShipAttack, 
   ACAT_CivDestroyed,
   ACAT_OpRaided,
   ACAT_StationAttack,
   ACAT_OpDestroyed,
   ACAT_StationCapture,
   ACAT_StationSabotage,
   ACAT_StationDestroyed,
   ACAT_HabitatDestroyed
};


// Plan Category
// Unlike actions, there are very few Plans. Each has a unique
// category number. This allows custom checks to see if the 
// plan can be run. 
enum ePlanCategory {
   PCAT_None = 0,

   PCAT_Neutralize = 1,
   PCAT_OrderedNeutralize = 2,
   PCAT_HiredNeutralize = 3,

   PCAT_Damage = 4,
   PCAT_HiredDamage = 5,
   PCAT_OrderedDamage = 6,
   PCAT_Conquest = 7,

   PCAT_PeaceOffer = 8,
   PCAT_SweepScout = 9,

   PCAT_Acquire = 10,

   PCAT_Join = 11,
   PCAT_Goodwill = 12,
   PCAT_Alliance = 13,

   PCAT_Defend = 14,
   PCAT_HiredDefense = 15,

   PCAT_Espionage = 16,
   PCAT_HiredEspionage = 17
};



