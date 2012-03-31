//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tsPodUtil.h
//
// Compiler-generated export header for package "tsPodUtil"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype hsim tsPodUtil.CreateCargoPod( int cargo_enum, string owner_faction, string cargo_faction );

prototype hsim tsPodUtil.CreatePodShipper( int cargo_enum, string owner_faction, int shipper_allegiance );

prototype hship tsPodUtil.CreateCargoPodCustom( int cargo_enum, string owner_faction, string cargo_faction, string pod_template );

prototype hcargo tsPodUtil.PodCargo( hisim pod );

prototype set tsPodUtil.PlayerPodCargoSet( hisim center, float dist );

prototype set tsPodUtil.PlayerPods( hisim center, float distance );

prototype set tsPodUtil.LegalPods( set all_pods );

prototype set tsPodUtil.IllegalPods( set all_pods );

prototype list tsPodUtil.UndockedPodList( hisim center, float dist );

prototype list tsPodUtil.TaggedPodList( hisim center, float dist );

prototype int tsPodUtil.NumberOfCargoType( hisim center, float radius, int type, bool legit );

prototype int tsPodUtil.RemoveType( hisim center, float radius, int type, int number, bool legit );

prototype bool tsPodUtil.AnyPlayerPodsIllegal( hisim center, float radius );

prototype set tsPodUtil.ShipPods( hship ship );

prototype tsPodUtil.DropCargo( hship freighter );

prototype tsPodUtil.AutodockPod( hship pod, hsim ship, hdockport target );

prototype set tsPodUtil.DockPorts( hship ship );

prototype set tsPodUtil.AsteroidDockPorts( hhabitat ship );

prototype set tsPodUtil.UniversalDockPorts( hhabitat ship );

prototype set tsPodUtil.UnloadDockPorts( hhabitat ship );

prototype set tsPodUtil.ClaimPods( hship ship, set pods );

prototype bool tsPodUtil.LoadDone( set cargo_pods );

prototype tsPodUtil.FreePods( set cargo_pods );

prototype int tsPodUtil.HackLevel( hship pod );

prototype tsPodUtil.SetHackLevel( hship pod, int level );

prototype bool tsPodUtil.IsHackAllowed( hship pod );

prototype tsPodUtil.RemoveHack( hship pod );

prototype tsPodUtil.HackTargetPod();

prototype tsPodUtil.HackNearbyPods();

prototype tsPodUtil.TogglePodTag();

prototype tsPodUtil.LoadPodsToPlayerShip();

prototype tsPodUtil.InitializeKeyBindings();

prototype tsPodUtil.PlayerShipDropCargo();

prototype tsPodUtil.DockTargetPodToPlayerShip();

// EOF /////////////////////////////////////////////////////////////////////////

