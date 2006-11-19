//
// (c) 1998-9 Particle Systems Ltd. All Rights Reserved
//
// tPodUtil.h
//
// Compiler-generated export header for package "tPodUtil"
//
// Revision control information:
//
// $Header: /flux/src/compiler/TypeChecker.cpp 31    27/03/01 14:31 Will $
//

// Dependencies ////////////////////////////////////////////////////////////////

// Enumerated types ////////////////////////////////////////////////////////////

// Functions ///////////////////////////////////////////////////////////////////

prototype hsim tPodUtil.CreateCargoPod( int cargo_enum, string owner_faction, string cargo_faction );

prototype hsim tPodUtil.CreatePodShipper( int cargo_enum, string owner_faction, int shipper_allegiance );

prototype hship tPodUtil.CreateCargoPodCustom( int cargo_enum, string owner_faction, string cargo_faction, string pod_template );

prototype hcargo tPodUtil.PodCargo( hisim pod );

prototype set tPodUtil.PlayerPodCargoSet( hisim center, float dist );

prototype set tPodUtil.PlayerPods( hisim center, float distance );

prototype set tPodUtil.LegalPods( set all_pods );

prototype set tPodUtil.IllegalPods( set all_pods );

prototype list tPodUtil.UndockedPodList( hisim center, float dist );

prototype list tPodUtil.TaggedPodList( hisim center, float dist );

prototype int tPodUtil.NumberOfCargoType( hisim center, float radius, int type, bool legit );

prototype int tPodUtil.RemoveType( hisim center, float radius, int type, int number, bool legit );

prototype bool tPodUtil.AnyPlayerPodsIllegal( hisim center, float radius );

prototype set tPodUtil.ShipPods( hship ship );

prototype tPodUtil.DropCargo( hship freighter );

prototype tPodUtil.AutodockPod( hship pod, hsim ship, hdockport target );

prototype set tPodUtil.DockPorts( hship ship );

prototype set tPodUtil.ClaimPods( hship ship, set pods );

prototype bool tPodUtil.LoadDone( set cargo_pods );

prototype tPodUtil.FreePods( set cargo_pods );

prototype int tPodUtil.HackLevel( hship pod );

prototype tPodUtil.SetHackLevel( hship pod, int level );

prototype bool tPodUtil.IsHackAllowed( hship pod );

prototype tPodUtil.RemoveHack( hship pod );

prototype tPodUtil.HackTargetPod();

prototype tPodUtil.HackNearbyPods();

prototype tPodUtil.TogglePodTag();

// EOF /////////////////////////////////////////////////////////////////////////

