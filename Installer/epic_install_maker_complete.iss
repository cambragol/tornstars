[Setup]
UseSetupLdr=true
OutputBaseFilename=unstable_space_11_6
;OutputDir=D:\Documents and Settings\Mourfin\My Documents\Unstable_Space_11_9
AppCopyright=Epic Team
AppName=Unstable Space
AppVerName=Unstable Space 11.6
DisableProgramGroupPage=true
UsePreviousGroup=false
AlwaysShowDirOnReadyPage=true
ShowLanguageDialog=false
Compression=lzma/ultra
EnableDirDoesntExistWarning=true
DefaultDirName={reg:HKLM\SOFTWARE\Particle Systems\Edge of Chaos\Settings,InstallPath|c:\EoC}
RestartIfNeededByRun=false
CreateAppDir=true
DisableDirPage=false
Uninstallable=false
DisableStartupPrompt=true
DirExistsWarning=no
SolidCompression=true
VersionInfoVersion=11.6
VersionInfoTextVersion=Epic 11.6
UsePreviousAppDir=false
WizardImageFile=.\Left_Install3.bmp
WizardSmallImageFile=.\install_small.bmp


[_ISTool]
Use7zip=true
[Dirs]
Name: {app}\movies
[Files]
; misc
Source: .\..\EpicSource\ExtraMods\no_launch_sequence.zip; DestDir: {app}\mods



; movies
Source: .\..\EpicArt\movies\*; DestDir: {app}\movies


; cluster models
Source: .\..\EpicSource\MS_Mod_ClusterModels\*; DestDir: {app}\mods\MS_Mod_Main; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\*; DestDir: {app}\mods\MS_Mod_Main\avatars; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\planets\*; DestDir: {app}\mods\MS_Mod_Main\avatars\planets; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\debris\*; DestDir: {app}\mods\MS_Mod_Main\avatars\debris; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\cutter\*; DestDir: {app}\mods\MS_Mod_Main\avatars\cutter; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\fueltransporter\*; DestDir: {app}\mods\MS_Mod_Main\avatars\fueltransporter; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\tug_hull\*; DestDir: {app}\mods\MS_Mod_Main\avatars\tug_hull; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\asteroids\*; DestDir: {app}\mods\MS_Mod_Main\avatars\asteroids; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\ModularStations\*; DestDir: {app}\mods\MS_Mod_Main\avatars\ModularStations; Flags: skipifsourcedoesntexist
;Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\ModularStations\chenyuang\*; DestDir: {app}\mods\MS_Mod_Main\avatars\ModularStations\chenyuang; Flags: skipifsourcedoesntexist
;Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\ModularStations\emerald\*; DestDir: {app}\mods\MS_Mod_Main\avatars\ModularStations\emerald; Flags: skipifsourcedoesntexist
;Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\ModularStations\tseng\*; DestDir: {app}\mods\MS_Mod_Main\avatars\ModularStations\tseng; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\*; DestDir: {app}\mods\MS_Mod_Main\avatars\epicasteroids; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\darkasteroids\*; DestDir: {app}\mods\MS_Mod_Main\avatars\epicasteroids\darkasteroids; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\exoticasteroids\*; DestDir: {app}\mods\MS_Mod_Main\avatars\epicasteroids\exoticasteroids; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\frostasteroids\*; DestDir: {app}\mods\MS_Mod_Main\avatars\epicasteroids\frostasteroids; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\hardasteroids\*; DestDir: {app}\mods\MS_Mod_Main\avatars\epicasteroids\hardasteroids; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\hotasteroids\*; DestDir: {app}\mods\MS_Mod_Main\avatars\epicasteroids\hotasteroids; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\iceasteroids\*; DestDir: {app}\mods\MS_Mod_Main\avatars\epicasteroids\iceasteroids; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\metalasteroids\*; DestDir: {app}\mods\MS_Mod_Main\avatars\epicasteroids\metalasteroids; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\neutroniumasteroids\*; DestDir: {app}\mods\MS_Mod_Main\avatars\epicasteroids\neutroniumasteroids; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\redasteroids\*; DestDir: {app}\mods\MS_Mod_Main\avatars\epicasteroids\redasteroids; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\softasteroids\*; DestDir: {app}\mods\MS_Mod_Main\avatars\epicasteroids\softasteroids; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\avatars\freighter\*; DestDir: {app}\mods\MS_Mod_Main\avatars\freighter; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\collisionhulls\*; DestDir: {app}\mods\MS_Mod_Main\collisionhulls; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\sims\stations\*; DestDir: {app}\mods\MS_Mod_Main\sims\stations; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\sims\epicasteroids\*; DestDir: {app}\mods\MS_Mod_Main\sims\epicasteroids; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\sims\epicfieldasteroids\*; DestDir: {app}\mods\MS_Mod_Main\sims\epicfieldasteroids; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\sims\regions\*; DestDir: {app}\mods\MS_Mod_Main\sims\regions; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\sims\shipfields\*; DestDir: {app}\mods\MS_Mod_Main\sims\shipfields; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\fields\*; DestDir: {app}\mods\MS_Mod_Main\fields; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\sfx\*; DestDir: {app}\mods\MS_Mod_Main\sfx; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\sfx\asteroid_impact\*; DestDir: {app}\mods\MS_Mod_Main\sfx\asteroid_impact; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_ClusterModels\sfx\kibble\*; DestDir: {app}\mods\MS_Mod_Main\sfx\kibble; Flags: skipifsourcedoesntexist


; debug
Source: .\..\EpicSource\MS_Mod_Debug\*; DestDir: {app}\mods\MS_Mod_Debug
Source: .\..\EpicSource\MS_Mod_Debug\html\*; DestDir: {app}\mods\MS_Mod_Debug\html


; econ
Source: .\..\EpicSource\MS_Mod_Econ\*; DestDir: {app}\mods\MS_Mod_Main; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Econ\TEXT\*; DestDir: {app}\mods\MS_Mod_Main\TEXT; Flags: skipifsourcedoesntexist


; environ
Source: .\..\EpicSource\MS_Mod_Environ\*; DestDir: {app}\mods\MS_Mod_Main; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_EnvPog\*; DestDir: {app}\mods\MS_Mod_Main; Flags: skipifsourcedoesntexist


; geog
Source: .\..\EpicSource\clusters\US_Mod_Geog\*; DestDir: {app}\mods\US_Mod_Geog
Source: .\..\EpicSource\clusters\US_Mod_Geog\data\*; DestDir: {app}\mods\US_Mod_Geog\data
Source: .\..\EpicSource\clusters\US_Mod_Geog\geog\*; DestDir: {app}\mods\US_Mod_Geog\geog
Source: .\..\EpicSource\clusters\US_Mod_Geog\geog\middle\*; DestDir: {app}\mods\US_Mod_Geog\geog\middle
Source: .\..\EpicSource\clusters\US_Mod_Geog\source\*; DestDir: {app}\mods\US_Mod_Geog\source; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\clusters\US_Mod_Geog\TEXT\*; DestDir: {app}\mods\US_Mod_Geog\TEXT
Source: .\..\EpicSource\clusters\US_Mod_Geog\TEXT\geog\*; DestDir: {app}\mods\US_Mod_Geog\TEXT\geog


; main
Source: .\..\EpicSource\MS_Mod_Main\*; DestDir: {app}\mods\MS_Mod_Main
Source: .\..\EpicSource\MS_Mod_Main\html\*; DestDir: {app}\mods\MS_Mod_Main\html
Source: .\..\EpicSource\MS_Mod_Main\html\news\*; DestDir: {app}\mods\MS_Mod_Main\html\news
Source: .\..\EpicSource\MS_Mod_Main\images\*; DestDir: {app}\mods\MS_Mod_Main\images; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Main\images\gui\*; DestDir: {app}\mods\MS_Mod_Main\images\gui
Source: .\..\EpicSource\pog\include\*; DestDir: {app}\mods\MS_Mod_Main\include; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\pog\include_pkg\*; DestDir: {app}\mods\MS_Mod_Main\include_pkg; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Main\packages\*; DestDir: {app}\mods\MS_Mod_Main\packages
Source: .\..\EpicSource\MS_Mod_Main\source\*; DestDir: {app}\mods\MS_Mod_Main\source
Source: .\..\EpicSource\MS_Mod_Main\TEXT\*; DestDir: {app}\mods\MS_Mod_Main\TEXT
Source: .\..\EpicSource\MS_Mod_Main\cfg\*; DestDir: {app}\mods\MS_Mod_Main\cfg


; jump sim
Source: .\..\EpicSource\US_Mod_JumpTube\*; DestDir: {app}\mods\MS_Mod_Main
Source: .\..\EpicSource\US_Mod_JumpTube\avatars\*; DestDir: {app}\mods\MS_Mod_Main\avatars; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\US_Mod_JumpTube\avatars\jumptube\*; DestDir: {app}\mods\MS_Mod_Main\avatars\jumptube
Source: .\..\EpicSource\US_Mod_JumpTube\collisionhulls\*; DestDir: {app}\mods\MS_Mod_Main\collisionhulls
Source: .\..\EpicSource\US_Mod_JumpTube\sims\*; DestDir: {app}\mods\MS_Mod_Main\sims; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\US_Mod_JumpTube\sims\ships\*; DestDir: {app}\mods\MS_Mod_Main\sims\ships
Source: .\..\EpicSource\US_Mod_JumpTube\sims\regions\*; DestDir: {app}\mods\MS_Mod_Main\sims\regions
Source: .\..\EpicSource\US_Mod_JumpTube\subsims\*; DestDir: {app}\mods\MS_Mod_Main\subsims; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\US_Mod_JumpTube\subsims\dockports\*; DestDir: {app}\mods\MS_Mod_Main\subsims\dockports
Source: .\..\EpicSource\US_Mod_JumpTube\subsims\systems\*; DestDir: {app}\mods\MS_Mod_Main\subsims\systems; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\US_Mod_JumpTube\subsims\systems\nonplayer\*; DestDir: {app}\mods\MS_Mod_Main\subsims\systems\nonplayer


; music
Source: .\..\EpicArt\MS_Mod_Music\*; DestDir: {app}\mods\MS_Mod_Main; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\audio\*; DestDir: {app}\mods\MS_Mod_Main\audio; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\audio\music\*; DestDir: {app}\mods\MS_Mod_Main\audio\music; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\audio\sfx\*; DestDir: {app}\mods\MS_Mod_Main\audio\sfx; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\avatars\*; DestDir: {app}\mods\MS_Mod_Main\avatars; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\avatars\admin_station_sound\*; DestDir: {app}\mods\MS_Mod_Main\avatars\admin_station_sound; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\avatars\fortress_station_sound\*; DestDir: {app}\mods\MS_Mod_Main\avatars\fortress_station_sound; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\avatars\giant_sound\*; DestDir: {app}\mods\MS_Mod_Main\avatars\giant_sound; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\avatars\habitat_station_sound\*; DestDir: {app}\mods\MS_Mod_Main\avatars\habitat_station_sound; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\avatars\leung_sound\*; DestDir: {app}\mods\MS_Mod_Main\avatars\leung_sound; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\avatars\moon_sound\*; DestDir: {app}\mods\MS_Mod_Main\avatars\moon_sound; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\avatars\old_corvette\*; DestDir: {app}\mods\MS_Mod_Main\avatars\old_corvette; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\avatars\patcom\*; DestDir: {app}\mods\MS_Mod_Main\avatars\patcom; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\avatars\pirate_station_sound\*; DestDir: {app}\mods\MS_Mod_Main\avatars\pirate_station_sound; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\avatars\planet_sound\*; DestDir: {app}\mods\MS_Mod_Main\avatars\planet_sound; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\avatars\production_station_sound\*; DestDir: {app}\mods\MS_Mod_Main\avatars\production_station_sound; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\avatars\station_sound\*; DestDir: {app}\mods\MS_Mod_Main\avatars\station_sound; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\avatars\sultan_sound\*; DestDir: {app}\mods\MS_Mod_Main\avatars\sultan_sound; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\avatars\sun_sound\*; DestDir: {app}\mods\MS_Mod_Main\avatars\sun_sound; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Music\sims\*; DestDir: {app}\mods\MS_Mod_Main\sims; Flags: skipifsourcedoesntexist


; nebula
Source: .\..\EpicArt\MS_Mod_Nebula\*; DestDir: {app}\mods\MS_Mod_Main; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Nebula\images\sfx\*; DestDir: {app}\mods\MS_Mod_Main\images\sfx
Source: .\..\EpicArt\MS_Mod_Nebula\models\al43551\*; DestDir: {app}\mods\MS_Mod_Main\models\al43551; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Nebula\models\bumpys_star\*; DestDir: {app}\mods\MS_Mod_Main\models\bumpys_star; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Nebula\models\emerald\*; DestDir: {app}\mods\MS_Mod_Main\models\emerald; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Nebula\models\epitaph\*; DestDir: {app}\mods\MS_Mod_Main\models\epitaph; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Nebula\models\farnorth\*; DestDir: {app}\mods\MS_Mod_Main\models\farnorth; Flags: skipifsourcedoesntexist
;Source: .\..\EpicArt\MS_Mod_Nebula\models\farsouth\*; DestDir: {app}\mods\MS_Mod_Main\models\farsouth; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Nebula\models\hd3887\*; DestDir: {app}\mods\MS_Mod_Main\models\hd3887; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Nebula\models\hd4045\*; DestDir: {app}\mods\MS_Mod_Main\models\hd4045; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Nebula\models\li_po\*; DestDir: {app}\mods\MS_Mod_Main\models\li_po; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Nebula\models\lombard\*; DestDir: {app}\mods\MS_Mod_Main\models\lombard; Flags: skipifsourcedoesntexist
;Source: .\..\EpicArt\MS_Mod_Nebula\models\multiplayer\*; DestDir: {app}\mods\MS_Mod_Main\models\multiplayer; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Nebula\models\new_const\*; DestDir: {app}\mods\MS_Mod_Main\models\new_const; Flags: skipifsourcedoesntexist
;Source: .\..\EpicArt\MS_Mod_Nebula\models\north\*; DestDir: {app}\mods\MS_Mod_Main\models\north; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Nebula\models\penda\*; DestDir: {app}\mods\MS_Mod_Main\models\penda; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Nebula\models\providence\*; DestDir: {app}\mods\MS_Mod_Main\models\providence; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Nebula\models\ripon\*; DestDir: {app}\mods\MS_Mod_Main\models\ripon; Flags: skipifsourcedoesntexist
;Source: .\..\EpicArt\MS_Mod_Nebula\models\south\*; DestDir: {app}\mods\MS_Mod_Main\models\south; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Nebula\models\x472\*; DestDir: {app}\mods\MS_Mod_Main\models\x472; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Nebula\models\xu_xuan\*; DestDir: {app}\mods\MS_Mod_Main\models\xu_xuan; Flags: skipifsourcedoesntexist


; planets
Source: .\..\EpicArt\MS_Mod_Planets\*; DestDir: {app}\mods\MS_Mod_Main; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Planets\images\*; DestDir: {app}\mods\MS_Mod_Main\images; Flags: skipifsourcedoesntexist
Source: .\..\EpicArt\MS_Mod_Planets\images\planets\*; DestDir: {app}\mods\MS_Mod_Main\images\planets; Flags: skipifsourcedoesntexist


; reference
Source: .\..\EpicSource\MS_Mod_Reference\*; DestDir: {app}\mods\MS_Mod_Main; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Reference\html\*; DestDir: {app}\mods\MS_Mod_Main\html; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Reference\html\prison\*; DestDir: {app}\mods\MS_Mod_Main\html\prison; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Reference\html\encyclopedia\*; DestDir: {app}\mods\MS_Mod_Main\html\encyclopedia; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Reference\html\encyclopedia\politics\*; DestDir: {app}\mods\MS_Mod_Main\html\encyclopedia\politics; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Reference\html\encyclopedia\geography\*; DestDir: {app}\mods\MS_Mod_Main\html\encyclopedia\geography; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Reference\html\encyclopedia\images\*; DestDir: {app}\mods\MS_Mod_Main\html\encyclopedia\images; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Reference\html\encyclopedia\images\maps\*; DestDir: {app}\mods\MS_Mod_Main\html\encyclopedia\images\maps; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Reference\TEXT\*; DestDir: {app}\mods\MS_Mod_Main\TEXT; Flags: skipifsourcedoesntexist


; ships
Source: .\..\EpicSource\MS_Mod_Ships\*; DestDir: {app}\mods\MS_Mod_Ships
Source: .\..\EpicSource\MS_Mod_Ships\collisionhulls\*; DestDir: {app}\mods\MS_Mod_Ships\collisionhulls
Source: .\..\EpicSource\MS_Mod_Ships\audio\sfx\*; DestDir: {app}\mods\MS_Mod_Ships\audio\sfx
Source: .\..\EpicSource\MS_Mod_Ships\avatars\assault_cannon\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\assault_cannon
Source: .\..\EpicSource\MS_Mod_Ships\avatars\assault_cannon_bolt\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\assault_cannon_bolt
Source: .\..\EpicSource\MS_Mod_Ships\avatars\cutting_beam\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\cutting_beam
Source: .\..\EpicSource\MS_Mod_Ships\avatars\beam\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\beam
Source: .\..\EpicSource\MS_Mod_Ships\avatars\capital_beam_bolt\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\capital_beam_bolt
Source: .\..\EpicSource\MS_Mod_Ships\avatars\cutting_beam_bolt\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\cutting_beam_bolt
Source: .\..\EpicSource\MS_Mod_Ships\avatars\cutting_beam_projector\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\cutting_beam_projector
Source: .\..\EpicSource\MS_Mod_Ships\avatars\mining_beam\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\mining_beam
Source: .\..\EpicSource\MS_Mod_Ships\avatars\disruptor\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\disruptor
Source: .\..\EpicSource\MS_Mod_Ships\avatars\eamp\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\eamp
Source: .\..\EpicSource\MS_Mod_Ships\avatars\edrone\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\edrone
Source: .\..\EpicSource\MS_Mod_Ships\avatars\heavy_pbc_bolt\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\heavy_pbc_bolt
Source: .\..\EpicSource\MS_Mod_Ships\avatars\light_pbc\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\light_pbc
Source: .\..\EpicSource\MS_Mod_Ships\avatars\light_pbc_bolt\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\light_pbc_bolt
Source: .\..\EpicSource\MS_Mod_Ships\avatars\missile_magazine\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\missile_magazine
Source: .\..\EpicSource\MS_Mod_Ships\avatars\neutron_pbc\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\neutron_pbc
Source: .\..\EpicSource\MS_Mod_Ships\avatars\old_corvette\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\old_corvette
Source: .\..\EpicSource\MS_Mod_Ships\avatars\heavy_corvette\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\heavy_corvette
Source: .\..\EpicSource\MS_Mod_Ships\avatars\pbc_bolt\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\pbc_bolt
Source: .\..\EpicSource\MS_Mod_Ships\avatars\pbc_bolt_neutron\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\pbc_bolt_neutron
Source: .\..\EpicSource\MS_Mod_Ships\avatars\quad_pbc\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\quad_pbc
Source: .\..\EpicSource\MS_Mod_Ships\avatars\standard_pbc\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\standard_pbc
Source: .\..\EpicSource\MS_Mod_Ships\avatars\standard_pbc_bolt\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\standard_pbc_bolt
Source: .\..\EpicSource\MS_Mod_Ships\avatars\turret_e\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\turret_e
Source: .\..\EpicSource\MS_Mod_Ships\avatars\pulsar\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\pulsar
Source: .\..\EpicSource\MS_Mod_Ships\avatars\tug_hull\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\tug_hull
Source: .\..\EpicSource\MS_Mod_Ships\avatars\us_capital_beam_turret\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\us_capital_beam_turret
Source: .\..\EpicSource\MS_Mod_Ships\avatars\us_mining_beam_turret\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\us_mining_beam_turret
Source: .\..\EpicSource\MS_Mod_Ships\avatars\interceptor\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\interceptor
Source: .\..\EpicSource\MS_Mod_Ships\avatars\marauderfighter\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\marauderfighter
Source: .\..\EpicSource\MS_Mod_Ships\avatars\old_destroyer\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\old_destroyer
Source: .\..\EpicSource\MS_Mod_Ships\avatars\stormpetrel\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\stormpetrel
Source: .\..\EpicSource\MS_Mod_Ships\avatars\truck\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\truck
Source: .\..\EpicSource\MS_Mod_Ships\avatars\turret_a\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\turret_a
Source: .\..\EpicSource\MS_Mod_Ships\avatars\turret_b\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\turret_b
Source: .\..\EpicSource\MS_Mod_Ships\avatars\turret_c\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\turret_c
Source: .\..\EpicSource\MS_Mod_Ships\avatars\turret_d\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\turret_d
Source: .\..\EpicSource\MS_Mod_Ships\avatars\freighter\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\freighter
Source: .\..\EpicSource\MS_Mod_Ships\avatars\command_section\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\command_section
Source: .\..\EpicSource\MS_Mod_Ships\avatars\flitter\*; DestDir: {app}\mods\MS_Mod_Ships\avatars\flitter

Source: .\..\EpicSource\MS_Mod_Ships\images\sfx\*; DestDir: {app}\mods\MS_Mod_Ships\images\sfx; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Ships\sfx\*; DestDir: {app}\mods\MS_Mod_Ships\sfx; Flags: skipifsourcedoesntexist

Source: .\..\EpicSource\MS_Mod_Ships\sims\*; DestDir: {app}\mods\MS_Mod_Ships\sims; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Ships\sims\explosions\*; DestDir: {app}\mods\MS_Mod_Ships\sims\explosions; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Ships\sims\ships\*; DestDir: {app}\mods\MS_Mod_Ships\sims\ships; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Ships\sims\ships\default\*; DestDir: {app}\mods\MS_Mod_Ships\sims\ships\default; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Ships\sims\ships\player\*; DestDir: {app}\mods\MS_Mod_Ships\sims\ships\player; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Ships\sims\ships\utility\*; DestDir: {app}\mods\MS_Mod_Ships\sims\ships\utility; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Ships\sims\ships\default\emerald\*; DestDir: {app}\mods\MS_Mod_Ships\sims\ships\default\emerald; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Ships\sims\ships\default\leung\*; DestDir: {app}\mods\MS_Mod_Ships\sims\ships\default\leung; Flags: skipifsourcedoesntexist

Source: .\..\EpicSource\MS_Mod_Ships\sims\weapons\*; DestDir: {app}\mods\MS_Mod_Ships\sims\weapons; Flags: skipifsourcedoesntexist

Source: .\..\EpicSource\MS_Mod_Ships\subsims\*; DestDir: {app}\mods\MS_Mod_Ships\subsims; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Ships\subsims\systems\*; DestDir: {app}\mods\MS_Mod_Ships\subsims\systems; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Ships\subsims\systems\nonplayer\*; DestDir: {app}\mods\MS_Mod_Ships\subsims\systems\nonplayer; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Ships\subsims\systems\nonplayer\external\*; DestDir: {app}\mods\MS_Mod_Ships\subsims\systems\nonplayer\external; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Ships\subsims\systems\player\*; DestDir: {app}\mods\MS_Mod_Ships\subsims\systems\player; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Ships\subsims\systems\player\programs\*; DestDir: {app}\mods\MS_Mod_Ships\subsims\systems\player\programs; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\MS_Mod_Ships\subsims\systems\player\subsystems\*; DestDir: {app}\mods\MS_Mod_Ships\subsims\systems\player\subsystems; Flags: skipifsourcedoesntexist


; station test
Source: .\..\EpicSource\clusters\MS_Mod_StationTest\*; DestDir: {app}\mods\MS_Mod_StationTest; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\clusters\MS_Mod_StationTest\data\*; DestDir: {app}\mods\MS_Mod_StationTest\data; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\clusters\MS_Mod_StationTest\geog\*; DestDir: {app}\mods\MS_Mod_StationTest\geog; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\clusters\MS_Mod_StationTest\geog\middle\*; DestDir: {app}\mods\MS_Mod_StationTest\geog\middle; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\clusters\MS_Mod_StationTest\TEXT\*; DestDir: {app}\mods\MS_Mod_StationTest\TEXT; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\clusters\MS_Mod_StationTest\TEXT\geog\*; DestDir: {app}\mods\MS_Mod_StationTest\TEXT\geog; Flags: skipifsourcedoesntexist





; config and other files
;Source: .\..\EpicSource\docs\Epic User Manual.rtf; DestDir: {app}\mods
Source: .\..\EpicSource\docs\ts_*_config.ini; DestDir: {app}\configs
;Source: .\..\EpicSource\docs\InstallInstructions.rtf; DestDir: {app}\epic_docs; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\docs\keybind.txt; DestDir: {app}\epic_docs; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\docs\credits.rtf; DestDir: {app}\epic_docs; Flags: skipifsourcedoesntexist
Source: .\..\EpicSource\docs\unstable_space_bugs.xls; DestDir: {app}\epic_docs; Flags: skipifsourcedoesntexist
Source: .\tornstars.ico; DestDir: {app}
Source: .\epic5.ico; DestDir: {app}
Source: .\epic6.ico; DestDir: {app}


[INI]
;Filename: {app}\flux.ini; Section: icSolarSystem; Key: far_clip; String: 3e+0014
Filename: {app}\flux.ini; Section: icSolarSystem; Key: far_clip; String: 2e5
Filename: {app}\flux.ini; Section: FcInputMapper; Key: input_scheme_ini; String: configs/ts_dev_config.ini
Filename: {app}\flux.ini; Section: icGUIMovie; Key: az; String: 1
Filename: {app}\flux.ini; Section: icGUIMovie; Key: ocal; String: 1
Filename: {app}\flux.ini; Section: icGUIMovie; Key: ycal; String: 1
Filename: {app}\flux.ini; Section: icGUIMovie; Key: jaffs; String: 1
Filename: {app}\flux.ini; Section: icGUIMovie; Key: lori; String: 1
Filename: {app}\flux.ini; Section: icGUIMovie; Key: smith; String: 1
Filename: {app}\flux.ini; Section: icShip; Key: critical_damage_scale; String: 0.5
Filename: {app}\flux.ini; Section: icShip; Key: criticals_per_impact; String: 0.5
Filename: {app}\flux.ini; Section: FcResourceManager; Key: search_paths[0]; String: .\resource
Filename: {app}\flux.ini; Section: FcResourceManager; Key: search_paths[1]; String: .\streams
Filename: {app}\flux.ini; Section: FcResourceManager; Key: search_paths[2]; String: .\movies
Filename: {app}\flux.ini; Section: FcResourceManager; Key: search_cd; String: 0
; Developer setup section. Disable for public releases
Filename: {app}\flux.ini; Section: Debug; Key: developer_mode; String: 1
Filename: {app}\flux.ini; Section: Debug; Key: trace_level; String: 3
Filename: {app}\flux.ini; Section: Debug; Key: trace_to_console; String: 1
Filename: {app}\flux.ini; Section: Debug; Key: trace_to_log; String: 1
Filename: {app}\flux.ini; Section: FcGame; Key: full_screen; String: 0
Filename: {app}\flux.ini; Section: FcGame; Key: width; String: 1024
Filename: {app}\flux.ini; Section: FcGame; Key: height; String: 768


;pre set up the mods
;Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_ClusterModels; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Debug; String: 1
;Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Econ; String: 1
;Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Environ; String: 1
;Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_EnvPog; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_StationTest; String: 0
Filename: {app}\flux.ini; Section: Mods; Key: US_Mod_Geog; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Main; String: 1
;Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Jump; String: 1
;Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Music; String: 1
;Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Nebula; String: 1
;Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Planets; String: 1
;Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Pog; String: 1
;Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Reference; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Ships; String: 1
;Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Test; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: no_launch_sequence; String: 1
;Filename: {app}\flux.ini; Section: Mods; Key: US_Mod_JumpTube; String: 1
; rolled high poly into cluster models
;Filename: {app}\flux.ini; Section: Mods; Key: HighPolyPlanets; String: 1
; set Epic version
Filename: {app}\epic_version.ini; Section: Version; Key: value; String: 800




[Icons]
Name: {userdesktop}\Torn Stars; Filename: {app}\EdgeOfChaos.exe; WorkingDir: {app}; IconFilename: {app}\tornstars.ico; Comment: EoC Launcher for Torn Stars; IconIndex: 0

[Code]
procedure CurStepChanged(CurStep: TSetupStep);
var
  ResultCode: Integer;
  copy_str: String;
begin
	// determine if at step just before the install starts
//	if CurStep=ssInstall then
//		begin
//
//		//MsgBox(ExpandConstant('{app}'), mbInformation, MB_OK);
//
//		// backup the mods dir
//		copy_str := ExpandConstant('/Y /E /I "{app}\mods" "{app}\mods-backup_') + GetDateTimeString('yyyy/mm/dd_hh:nn:ss', '-', '-') + '"';
//		//MsgBox(copy_str, mbInformation, MB_OK);
//		Exec(ExpandConstant('{win}\system32\xcopy.exe'), copy_str, '', SW_SHOW, ewWaitUntilTerminated, ResultCode);
//
//		// backup a movies dir if there
//		copy_str := ExpandConstant('/Y /E /I "{app}\movies" "{app}\movies-backup_') + GetDateTimeString('yyyy/mm/dd_hh:nn:ss', '-', '-') + '"';
//		//MsgBox(copy_str, mbInformation, MB_OK);
//		Exec(ExpandConstant('{win}\system32\xcopy.exe'), copy_str, '', SW_SHOW, ewWaitUntilTerminated, ResultCode);
//
//		// backup the planet texture dir in resources
//		copy_str := ExpandConstant('/Y /E /I "{app}\resource\images\planets" "{app}\resource\images\planets-backup_') + GetDateTimeString('yyyy/mm/dd_hh:nn:ss', '-', '-') + '"';
//		Exec(ExpandConstant('{win}\system32\xcopy.exe'), copy_str, '', SW_SHOW, ewWaitUntilTerminated, ResultCode);
//		// delete all files inside this resource dir but leave the dir
//		DelTree(ExpandConstant('{app}\resource\images\planets\*'), False, True, True);
//
//		// backup flux ini
//		FileCopy(ExpandConstant('{app}\flux.ini'), ExpandConstant('{app}\flux_') + GetDateTimeString('yyyy/mm/dd_hh:nn:ss', '-', '-')+'.ini', False);
//		// Delete all files and directories inside mods\
//		// but leave the directory itself
//		DelTree(ExpandConstant('{app}\mods\*'), False, True, True);
//    end;
end;

function InitializeSetup(): Boolean;
var
	version: Cardinal;
	ini_path: String;
begin
	// Has the correct version of EoC been installed
	RegQueryDWordValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\Particle Systems\Edge of Chaos\Settings', 'Version', version);
	RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\Particle Systems\Edge of Chaos\Settings', 'InstallPath', ini_path);

	if  version = 14 then
		Result := True
	else begin
		MsgBox('Edge of Chaos v14.x has not been installed first.', mbInformation, MB_OK);
		Result := False;
	end;

	// do some key files exists that indicate a real EoC install location
	if not FileExists(ini_path+'\flux.ini') then Result:= false;
	if not FileExists(ini_path+'\EdgeOfChaos.exe') then	Result:= false;
	if not FileExists(ini_path+'\bin\release\loader.exe') then Result:= false;

end;

