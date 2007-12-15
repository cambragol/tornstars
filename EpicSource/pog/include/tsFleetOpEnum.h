
/* Underworld Operations */
enum eUnderworldOp {
   UO_Invalid = 0,
   UO_MasterOp = 1,
   UO_HQOp = 2,
   UO_SupplyOp = 4,
   UO_ViceDenOp = 8,
   UO_MedicalOp = 16,
   UO_EmbezzleOp = 32,
   UO_SafeHouse = 64,
   UO_WeaponsSupply = 128,
   UO_RefugeeBuyer = 256,
   UO_RefugeeSupply = 512,
   UO_DrugSupply = 1024,
   UO_ShipBuyer = 2048,
   UO_PirateBase = 4096,
   UO_Legal = 8192
};

/* 
Operations are the bases outlaws use to make money. They are hidden in 
normal stations. They typically need some kind of supply to generate 
funds. They also generate missions for players.

Legal is the operation that owns and operates the station. It is included 
here to allow informers to infiltrate. It gets added to the station at 
start up.

MasterOp is the controlling base of a whole outlaw faction. It can 
span several systems.

HQ is a controlling base of a whole planet and nearby moons.

Supply operation is built on waystations, repair stations or drydocks. 
Allows supply to a pirate cove.

ViceDen is built on a casino, entertainment station, resort or settlement. 
Requires drugs and/or prostitues to operate. High profits at luxury 
operations. Half profits at settlements and higher alarm rate.

Medical sources illegal medical procedures. Must have medical drugs and 
clone parts to operate. Allows identity changes. It can be used to improve 
informer skill level. Built on any medical station. Hard to find corrupt 
entity for start.
    
Embezzle is built on any processing or non-weapons manufacturing plant. 
Allows starting up a fence. Gives profit source. Hard to find corrupt 
entity to start.
    
[removed, now a base: Pirate Cove is a hidden base for illegal warships. 
Typically a disused station or abandond mine. May be a hollow asteroid. 
Allows owning warships and outfitting ships with weapons. The cove must be 
supplied by a supply operation. Expensive.]
    
Pirate Base is built on any settlement or habitat. The pirate base is the 
ultimate outlaw base. The pirate forces replace  the base defenders. 
Allows open owning of warships. Avoids police attacks. Two types of 
operation: 
1. pay large tribute to settlement. As long as settlement is happy, base stays. 
2. Take over leadership of settlement. Half cost, but danger of navy 
rescue without political backing.
    
Safe House can be created quickly by a fleeing agent. It represents a 
hiding place in a station. When looking for someone you need to be able to 
find the safe house. Typically a very high hide value.

[October 2003, moved from resources below and modified.

WeaponsSuppy is built on a weapons plant, or navy depot. Sources the 
weapons of that station. (replaces smuggler op)

ShipBuyer is built on a shipyard in a zero law level zone. They will 
reconstruct ships to hide the prior owners.

PersonSupply is built on poor habitats and refugee centers. These people 
will pay to be moved to somewhere better. They can also be sold to vice 
dens as slaves.
 
RefugeeBuyer represents those who pay for transport to better living 
conditions. These are always built on settlements in wealthy high law 
level systems. It can be quite hard to get people to these locations.

DrugSupply is a source of illegal drugs. These are built on agricultural 
settlements and medical factories. (replaces smuggler op)

*/


/* Resources and Attributes */

enum eUnderworldAttrib {
   UA_SlaveSupply,
   UA_SlaveBuyer,
   UA_RefugeeResource,
   UA_IllegalSupply,
   UA_WeaponsSupply,
   UA_ShipBuyer,
   UA_TaxedGoodBuyer
};

/* 
October 2003 note: Moving resources into operations. They are now totally 
based on station type (revised station types). Resources represent links 
to off game supplies. Some operations must be set up on a resource. 
Finding and controlling outlaw resources is a key activity of outlaw 
factions and the police.

Smuggle typically has supplier point fixed by resource attached to a 
station, with attendant smuggle operation. The selling point is typically  
a fence or direct contact to a consuming operation.


Slave Supply: is a source point for slaves and prostitutes.

Slave Buyer: is a selling point for slaves. Some operations use slaves as well. 

Refugee Supply: is a place where refugees are trying to flee. They always 
have a destination, it is likely illegal. They are willing to pay high 
prices for the trip.
    
Illegal Supply: is a link to illegal goods, equipment or drugs. Purchase 
goods here for smuggling to fences or ViceDens. Smuggle operations are 
built on these resource links.
    
Weapons Supply: is a specialized illegal supply. Typically an inside link 
at a government facility. These links cannot be controlled. They start 
with a controlling operation. Weapons are in high demand at all other 
operations and good for high profits.
    
Ship Buyer: this specialized fence can handle reselling whole star ships. 
A major money supplier for pirate operations. Again it cannot be controlled.
    
TaxedGood Buyer: this purchaser is willing to fence legal goods that have 
been slipped past customs. Typically located on opposite sides of a nation  
boundry, these buyers have funded most smuggling operations since time 
immemorial.

*/



enum eOpChoiceLevel {
   OCL_TradeOnly = 1,
   OCL_NewSubs = 2,
   OCL_Diplomacy = 3
};

/*
    Trade only: This Boss may only offer standard trade deals. Must be with factions not hostile.
    
    New Subs: This Boss may create new operations as they see fit. Typically to strengthen position
    current operation.
    
    Diplomacy: This top level Boss may offer diplomatic deals with other factions. Typically alliances,
    no compete agreements, and threats. Only one top level per faction.
*/

enum eOpDiplomacyLink {
   ODL_None =      0,
   ODL_Trade =     1,
   ODL_NoCompete = 2,
   ODL_Defense =  3,
   ODL_ShareStation = 4
};

/*

    Trade: trust based trade deal. The requirement for smuggling or other trade missions.
    
    NoCompete: Agreement to not fight one another. Typically aimed at fighting third party.
    
    Defense: Alliance for self protection. Small parties join with strong parties for defense.
    
    ShareStation: Agreement to not try to take over a neutral operation. Two outlaws
    may choose to share a drug supply rather than fight it out. This may be proposed by
    the drug supply operation.

*/



/* 
   Informer states
   An order or drop command puts an informer on station.
   A stop command ends an order and makes the state idle.
   A pickup command moves an idle informer onto the player ship.
   A trapped informer may also be picked up. 
*/
/*
enum eInformAction {
   InA_OnShip = 0,          // on player ship, waiting for orders
   InA_Search = 1,        // searching
   InA_Infiltrate = 2,    // infiltrating operation
   InA_Setup = 3,         // starting a new operation
   InA_Trapped = 4,       // discovered by enemy
   InA_FreeAgent = 5,     // not hired by player
   InA_Idle = 6         // on station, waiting for orders
};
*/

enum eInformerState {
   INS_OnShip,
   INS_Idle,
   INS_Planted,
   INS_Infiltrate,
   INS_WaitAction,
   INS_Fleeing,
   INS_Searching,
   INS_Recruiting,
   INS_FreeAgent
};

/* 

Send Informer
Infiltrate -> Known Operations
Search     -> for Operations
Diplomacy  -> Faction
    Trade
    Alliance
    No Compete
    Join
    Protection
    Agree leave station Neutral


Zones:
Outlaw - Casino, Resort, Settlement, Habitat, Entertainment
Transport/Mining - Rough and tumble world of mines and docks, these people know ships.
Corporate/Manufacture - All corporate stations and manufacturing bases.
Police/Navy - Police bases, Navy bases, Defense stations
Government/Political - HQs, Departments, (Settlements, Villas)
Science/Medical - Medical, Research, University

*/

/* 
   
Search:
Requires getting an informer into the station. (Some stations prohibit docking without permit).

Select an informer.
Select Search. The informer leaves the ship and begins to look for operations.
Will continue until stopped by player. Status checked with informer screen.
Search costs.

Some political position have a special ability: Search. May use police or troops to conduct a sweep.

Uses Informer Zone Skill. Any Bonus Clues. Compare with hide of Operation to determine if revealed.

*/

/* 

Infiltration:
Requires getting an informer into a station.

Mission is needed to increase an informer 'depth'. The greater the depth, the better the 
information. Start at depth zero, no information. The level of security determines what 
kind of mission is needed to increase the informer depth. There is a delay time between
advancements, of a few days at least.

The Discovery risk is determined by security level, informer skill, and depth. Also modified
by current use of information supplied by informer, and counter-spy operations being done
by operation. The player may choose to rescue or pull out a high risk informer.

Each operation day, the informer task checks for information and sends it to the player. 
It decrements the time needed to wait for depth increase. The informer checks for discovery.

Other events happen when the player invokes them from menu.

Depth 0, no info. - Start here.
Depth 1, Outsider. - Knowledge of major operation that move ships and material, as it happens.
Depth 2, Inside data. - Knowledge of major operations before they happen.
Depth 3, Secure. - Knowledge of diplomacy and agent operations.

Informer may Cash Out when they leave a station. Depending on depth of informer, they can 
collect a key clue or proof. This is a high risk operation option that may create a 
special rescue mission.

Some station require rescue. All high security stations, military bases, R+D, Hideouts.

*/ 
