
//*******************************************************************************************/
//
// tRepEnum.h
//
// Lists the Skill and Status types used in Epic.
// 
//
// 
//
// October 2002, Jon Freise
//******************************************************************************************/


enum eSkillRep {
   SR_Invalid = 0,
   SR_Commercial = 1,
   SR_Command = 2,
   SR_Smuggling = 4,
   SR_Pirate = 8,
   SR_Police = 16,
   SR_Hacker = 32
};


enum eStatusRep {
   STR_Invalid = 0,
   STR_Heroic = 1,
   STR_Infamy = 2,
   STR_Fame = 4,
   STR_Status = 8
};


// Enum shows the level of damage the player has caused the faction.
// Used to control response to player attacks.

enum ePlayerDamage {
   epdNone,
   epdTheft,             //theft of cargo pods, or cyber raiding
   epdAttack,            //attack on ships, pirating transports
   epdCivilianKilled,    //actually destroying civilian shipping
   epdStationAttack,     //attacking a station, endagering civilians
   epdStationDestroyed,  //destroying a station. A declaration of war
   epdHabitatDestroyed   //killing thousands of innocents. Sure to provoke wide response.
};
