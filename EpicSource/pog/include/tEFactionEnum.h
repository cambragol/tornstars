//*******************************************************************************************/
//
// tEFactionEnum.h
//
// This file contains the faction related enumerations and level setting values.
// 
//
// May 2005, Jon Freise
//******************************************************************************************/


enum eFactionType {
   FCT_Invalid = 0,
   FCT_Independent = 1,
   FCT_Navy = 2,
   FCT_Pirate = 4,
   FCT_Mercenary = 8,
   FCT_Rebel = 16,
   FCT_Spy = 32,
   FCT_MegaCorp = 64,
   FCT_BaseCulture = 128,

   FCT_Public = FCT_MegaCorp|FCT_Navy,
   FCT_Hidden = FCT_Pirate|FCT_Rebel|FCT_Spy,
   FCT_Legal = FCT_MegaCorp|FCT_Navy,
   FCT_Authority = FCT_Navy
};



