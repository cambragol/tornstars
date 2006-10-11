[Setup]
UseSetupLdr=true
OutputBaseFilename=unstable_space_10_0_music
OutputDir=C:\epic\epicrelease\USpace10_0
AppCopyright=Epic Team
AppName=Unstable Space
AppVerName=Unstable Space 10.0
DisableProgramGroupPage=true
UsePreviousGroup=false
AlwaysShowDirOnReadyPage=true
ShowLanguageDialog=no
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
VersionInfoVersion=10.0
VersionInfoTextVersion=Epic 10.0
WizardImageFile=.\EpicSource\Installer\install_left_2.bmp
WizardSmallImageFile=.\EpicSource\Installer\install_small_2.bmp

[_ISTool]
Use7zip=true
[Files]
; music
Source: .\EpicArt\MS_Mod_Music\*; DestDir: {app}\mods\MS_Mod_Music; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\audio\*; DestDir: {app}\mods\MS_Mod_Music\audio; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\audio\music\*; DestDir: {app}\mods\MS_Mod_Music\audio\music; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\audio\sfx\*; DestDir: {app}\mods\MS_Mod_Music\audio\sfx; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\avatars\*; DestDir: {app}\mods\MS_Mod_Music\avatars; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\avatars\admin_station_sound\*; DestDir: {app}\mods\MS_Mod_Music\avatars\admin_station_sound; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\avatars\fortress_station_sound\*; DestDir: {app}\mods\MS_Mod_Music\avatars\fortress_station_sound; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\avatars\giant_sound\*; DestDir: {app}\mods\MS_Mod_Music\avatars\giant_sound; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\avatars\habitat_station_sound\*; DestDir: {app}\mods\MS_Mod_Music\avatars\habitat_station_sound; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\avatars\leung_sound\*; DestDir: {app}\mods\MS_Mod_Music\avatars\leung_sound; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\avatars\moon_sound\*; DestDir: {app}\mods\MS_Mod_Music\avatars\moon_sound; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\avatars\old_corvette\*; DestDir: {app}\mods\MS_Mod_Music\avatars\old_corvette; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\avatars\patcom\*; DestDir: {app}\mods\MS_Mod_Music\avatars\patcom; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\avatars\pirate_station_sound\*; DestDir: {app}\mods\MS_Mod_Music\avatars\pirate_station_sound; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\avatars\planet_sound\*; DestDir: {app}\mods\MS_Mod_Music\avatars\planet_sound; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\avatars\production_station_sound\*; DestDir: {app}\mods\MS_Mod_Music\avatars\production_station_sound; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\avatars\station_sound\*; DestDir: {app}\mods\MS_Mod_Music\avatars\station_sound; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\avatars\sultan_sound\*; DestDir: {app}\mods\MS_Mod_Music\avatars\sultan_sound; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\avatars\sun_sound\*; DestDir: {app}\mods\MS_Mod_Music\avatars\sun_sound; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Music\sims\*; DestDir: {app}\mods\MS_Mod_Music\sims; Flags: skipifsourcedoesntexist


[Code]
#include "core_needed.pas"
