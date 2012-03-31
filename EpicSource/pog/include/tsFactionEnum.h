//*******************************************************************************************/
//
// tsFactionEnum.h
//
// This file contains the faction related enumerations and level setting values.
// 
//
// May 2004, Jon Freise
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


// Just how severe is this action intended to be?
enum eFactionLevel {
   ACL_Invalid =0,
   ACL_Allied = 1,
   ACL_Friendly = 2,
   ACL_Peaceful = 4,
   ACL_Neutral = 8,
   ACL_Worried = 16,
   ACL_Dislike = 32,
   ACL_Hostile = 64
};


enum eFactionAlignment {
   FALN_None = 0,
   FALN_Hawk = 1,
   FALN_Dove = 2,
   FALN_Gray = 4,
   FALN_Illegal = 8,
   FALN_Lawful = 16,
   FALN_Treachery = 32
};

