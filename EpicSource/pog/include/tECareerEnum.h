//*******************************************************************************************/
//
// tECareerEnum.h
//
// This package creates and manages career objects.
// 
//
// 
//
// March 2004, Jon Freise
//******************************************************************************************/


enum eCareerType {
   ectNone = 0,
   ectFleetOfficer = 1,
   ectFleetInt = 2,
   ectMercOfficer = 4,
   ectMercInt = 8,
   ectPirateEnforcer = 16,
   ectPirateAgent = 32,
   ectCorpOfficer = 64
};


enum eCareerChange {
   eccNone = 0,
   eccJoin = 1,
   eccTransfer = 2,
   eccBetray = 4
};


/*  
THIS MOD IS NOT MADE, DISTRIBUTED, OR SUPPORTED BY INFOGRAMES
OR PARTICLE SYSTEMS LTD. 

ELEMENTS TM & (C) INFOGRAMES AND PARTICLE SYSTEMS LTD.
*/
