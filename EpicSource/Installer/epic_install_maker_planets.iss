[Setup]
UseSetupLdr=true
OutputBaseFilename=unstable_space_10_0_planets
OutputDir=C:\epic\epicrelease\USpace10_0
AppCopyright=Epic Team
AppName=Unstable Space
AppVerName=Unstable Space 10.0
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
VersionInfoVersion=10.0
VersionInfoTextVersion=Epic 10.0
WizardImageFile=.\EpicSource\Installer\install_left_2.bmp
WizardSmallImageFile=.\EpicSource\Installer\install_small_2.bmp

[_ISTool]
Use7zip=true
[Dirs]
Name: {app}\movies
[Files]
; planets
Source: .\EpicArt\MS_Mod_Planets\*; DestDir: {app}\mods\MS_Mod_Planets; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Planets\images\*; DestDir: {app}\mods\MS_Mod_Planets\images; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Planets\images\planets\*; DestDir: {app}\mods\MS_Mod_Planets\images\planets; Flags: skipifsourcedoesntexist

; movies
Source: movies\*; DestDir: {app}\movies

; cluster models
Source: .\EpicSource\MS_Mod_ClusterModels\*; DestDir: {app}\mods\MS_Mod_ClusterModels; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\planets\*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars\planets; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\asteroids\*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars\asteroids; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\ModularStations\*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars\ModularStations; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\ModularStations\chenyuang\*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars\ModularStations\chenyuang; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\ModularStations\emerald\*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars\ModularStations\emerald; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\ModularStations\tseng\*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars\ModularStations\tseng; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars\epicasteroids; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\darkasteroids*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars\epicasteroids\darkasteroids; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\exoticasteroids*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars\epicasteroids\exoticasteroids; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\frostasteroids*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars\epicasteroids\frostasteroids; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\hardasteroids*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars\epicasteroids\hardasteroids; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\hotasteroids*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars\epicasteroids\hotasteroids; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\iceasteroids*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars\epicasteroids\iceasteroids; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\metalasteroids*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars\epicasteroids\metalasteroids; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\neutroniumasteroids*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars\epicasteroids\neutroniumasteroids; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\redasteroids*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars\epicasteroids\redasteroids; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\avatars\epicasteroids\softasteroids*; DestDir: {app}\mods\MS_Mod_ClusterModels\avatars\epicasteroids\softasteroids; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\collisionhulls\*; DestDir: {app}\mods\MS_Mod_ClusterModels\collisionhulls; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_ClusterModels\sims\stations\*; DestDir: {app}\mods\MS_Mod_ClusterModels\sims\stations; Flags: skipifsourcedoesntexist

[INI]
Filename: {app}\flux.ini; Section: icGUIMovie; Key: az; String: 0
Filename: {app}\flux.ini; Section: icGUIMovie; Key: ocal; String: 1
Filename: {app}\flux.ini; Section: icGUIMovie; Key: ycal; String: 1
Filename: {app}\flux.ini; Section: icGUIMovie; Key: jaffs; String: 1
Filename: {app}\flux.ini; Section: icGUIMovie; Key: lori; String: 1
Filename: {app}\flux.ini; Section: icGUIMovie; Key: smith; String: 1

[Code]
#include "core_needed.pas"

procedure CurStepChanged(CurStep: TSetupStep);
var
  ResultCode: Integer;
  copy_str: String;
begin
	// determine if at step just before the install starts
	if CurStep=ssInstall then
		begin
		// backup a movies dir if there
		copy_str := ExpandConstant('/Y /E /I "{app}\movies" "{app}\movies-backup_') + GetDateTimeString('yyyy/mm/dd_hh:nn:ss', '-', '-') + '"';
		Exec(ExpandConstant('{win}\system32\xcopy.exe'), copy_str, '', SW_SHOW, ewWaitUntilTerminated, ResultCode);
		end;
end;
