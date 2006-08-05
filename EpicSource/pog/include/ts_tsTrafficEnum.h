//*******************************************************************************************/
//
// ts_tsTrafficEnum.h
// torn stars traffic script Traffic Enumeration
//
// This enumeration lists the possible traffic script types that can be started.
// This value needs to match the values in the INI setup files.
// 
// 
// 
// November 2005, jf
// 
//******************************************************************************************/

enum eTrafficScenario{
   etsInvalid = 0,
   // Cargo hauled from/to another system
   etsLongHaul = 1,
   // Cargo moved within the same system
   etsShortHaul = 2,
   etsStationGuard = 3,
   // Attack to destroy defenders
   etsRaid = 4
};


/*  
THIS MOD IS NOT MADE, DISTRIBUTED, OR SUPPORTED BY INFOGRAMES
OR PARTICLE SYSTEMS LTD. 

ELEMENTS TM & (C) INFOGRAMES AND PARTICLE SYSTEMS LTD.
*/

