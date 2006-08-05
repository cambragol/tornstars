[Setup]
UseSetupLdr=true
OutputBaseFilename=unstable_space_setup_10_0_core
OutputDir=C:\Epic\EpicRelease\USpace10_0
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
UsePreviousAppDir=false
WizardImageFile=.\EpicSource\Installer\install_left_2.bmp
WizardSmallImageFile=.\EpicSource\Installer\install_small_2.bmp
[_ISTool]
Use7zip=true
[Dirs]
Name: {app}\movies
[Files]
; misc
Source: .\EpicSource\ExtraMods\no_launch_sequence.zip; DestDir: {app}\mods


; debug
Source: .\EpicSource\MS_Mod_Debug\*; DestDir: {app}\mods\MS_Mod_Debug
Source: .\EpicSource\MS_Mod_Debug\html\*; DestDir: {app}\mods\MS_Mod_Debug\html

; autowatch
Source: .\EpicSource\MS_Mod_Auto\*; DestDir: {app}\mods\MS_Mod_Auto

; econ
Source: .\EpicSource\MS_Mod_Econ\*; DestDir: {app}\mods\MS_Mod_Econ; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_Econ\TEXT\*; DestDir: {app}\mods\MS_Mod_Econ\TEXT; Flags: skipifsourcedoesntexist

; environ
Source: .\EpicSource\MS_Mod_Environ\*; DestDir: {app}\mods\MS_Mod_Environ; Flags: skipifsourcedoesntexist

; geog
Source: .\EpicSource\clusters\US_Mod_Geog\*; DestDir: {app}\mods\US_Mod_Geog
Source: .\EpicSource\clusters\US_Mod_Geog\data\*; DestDir: {app}\mods\US_Mod_Geog\data
Source: .\EpicSource\clusters\US_Mod_Geog\geog\*; DestDir: {app}\mods\US_Mod_Geog\geog
Source: .\EpicSource\clusters\US_Mod_Geog\geog\middle\*; DestDir: {app}\mods\US_Mod_Geog\geog\middle
;Source: .\EpicSource\clusters\US_Mod_Geog\sims\*; DestDir: {app}\mods\US_Mod_Geog\sims; Flags: skipifsourcedoesntexist
;Source: .\EpicSource\clusters\US_Mod_Geog\sims\stations\*; DestDir: {app}\mods\US_Mod_Geog\sims\stations
Source: .\EpicSource\clusters\US_Mod_Geog\source\*; DestDir: {app}\mods\US_Mod_Geog\source; Flags: skipifsourcedoesntexist
Source: .\EpicSource\clusters\US_Mod_Geog\TEXT\*; DestDir: {app}\mods\US_Mod_Geog\TEXT
Source: .\EpicSource\clusters\US_Mod_Geog\TEXT\geog\*; DestDir: {app}\mods\US_Mod_Geog\TEXT\geog

; main
Source: .\EpicSource\MS_Mod_Main\*; DestDir: {app}\mods\MS_Mod_Main
Source: .\EpicSource\MS_Mod_Main\html\*; DestDir: {app}\mods\MS_Mod_Main\html
Source: .\EpicSource\MS_Mod_Main\html\news\*; DestDir: {app}\mods\MS_Mod_Main\html\news
Source: .\EpicSource\MS_Mod_Main\images\*; DestDir: {app}\mods\MS_Mod_Main\images; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_Main\images\gui\*; DestDir: {app}\mods\MS_Mod_Main\images\gui
Source: .\EpicSource\pog\include\*; DestDir: {app}\mods\MS_Mod_Main\include; Flags: skipifsourcedoesntexist
Source: .\EpicSource\pog\include_pkg\*; DestDir: {app}\mods\MS_Mod_Main\include_pkg; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_Main\packages\*; DestDir: {app}\mods\MS_Mod_Main\packages
Source: .\EpicSource\MS_Mod_Main\source\*; DestDir: {app}\mods\MS_Mod_Main\source
Source: .\EpicSource\MS_Mod_Main\TEXT\*; DestDir: {app}\mods\MS_Mod_Main\TEXT
Source: .\EpicSource\MS_Mod_Main\cfg\*; DestDir: {app}\mods\MS_Mod_Main\cfg

; jump
Source: .\EpicSource\MS_Mod_Jump\*; DestDir: {app}\mods\MS_Mod_Jump
Source: .\EpicSource\MS_Mod_Jump\html\*; DestDir: {app}\mods\MS_Mod_Jump\html
Source: .\EpicSource\MS_Mod_Jump\packages\*; DestDir: {app}\mods\MS_Mod_Jump\packages
Source: .\EpicSource\MS_Mod_Jump\source\*; DestDir: {app}\mods\MS_Mod_Jump\source
Source: .\EpicSource\MS_Mod_Jump\TEXT\*; DestDir: {app}\mods\MS_Mod_Jump\TEXT



; pog
Source: .\EpicSource\MS_Mod_Pog\*; DestDir: {app}\mods\MS_Mod_Pog; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_Pog\html\*; DestDir: {app}\mods\MS_Mod_Pog\html; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_Pog\packages\*; DestDir: {app}\mods\MS_Mod_Pog\packages; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_Pog\source\*; DestDir: {app}\mods\MS_Mod_Pog\source; Flags: skipifsourcedoesntexist

; reference
Source: .\EpicSource\MS_Mod_Reference\*; DestDir: {app}\mods\MS_Mod_Reference; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_Reference\html\*; DestDir: {app}\mods\MS_Mod_Reference\html; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_Reference\html\prison\*; DestDir: {app}\mods\MS_Mod_Reference\html\prison; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_Reference\html\encyclopedia\*; DestDir: {app}\mods\MS_Mod_Reference\html\encyclopedia; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_Reference\html\encyclopedia\politics\*; DestDir: {app}\mods\MS_Mod_Reference\html\encyclopedia\politics; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_Reference\html\encyclopedia\geography\*; DestDir: {app}\mods\MS_Mod_Reference\html\encyclopedia\geography; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_Reference\TEXT\*; DestDir: {app}\mods\MS_Mod_Reference\TEXT; Flags: skipifsourcedoesntexist

; ships
Source: .\EpicSource\MS_Mod_Ships\*; DestDir: {app}\mods\MS_Mod_Ships; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_Ships\sims\*; DestDir: {app}\mods\MS_Mod_Ships\sims; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_Ships\sims\ships\*; DestDir: {app}\mods\MS_Mod_Ships\sims\ships; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_Ships\sims\ships\player\*; DestDir: {app}\mods\MS_Mod_Ships\sims\ships\player; Flags: skipifsourcedoesntexist
Source: .\EpicSource\MS_Mod_Ships\sims\ships\utility\*; DestDir: {app}\mods\MS_Mod_Ships\sims\ships\utility; Flags: skipifsourcedoesntexist
; station test
Source: .\EpicSource\clusters\MS_Mod_StationTest\*; DestDir: {app}\mods\MS_Mod_StationTest; Flags: skipifsourcedoesntexist
Source: .\EpicSource\clusters\MS_Mod_StationTest\data\*; DestDir: {app}\mods\MS_Mod_StationTest\data; Flags: skipifsourcedoesntexist
Source: .\EpicSource\clusters\MS_Mod_StationTest\geog\*; DestDir: {app}\mods\MS_Mod_StationTest\geog; Flags: skipifsourcedoesntexist
Source: .\EpicSource\clusters\MS_Mod_StationTest\geog\middle\*; DestDir: {app}\mods\MS_Mod_StationTest\geog\middle; Flags: skipifsourcedoesntexist
Source: .\EpicSource\clusters\MS_Mod_StationTest\sims\*; DestDir: {app}\mods\MS_Mod_StationTest\sims; Flags: skipifsourcedoesntexist
Source: .\EpicSource\clusters\MS_Mod_StationTest\sims\stations\*; DestDir: {app}\mods\MS_Mod_StationTest\sims\stations; Flags: skipifsourcedoesntexist
Source: .\EpicSource\clusters\MS_Mod_StationTest\TEXT\*; DestDir: {app}\mods\MS_Mod_StationTest\TEXT; Flags: skipifsourcedoesntexist
Source: .\EpicSource\clusters\MS_Mod_StationTest\TEXT\geog\*; DestDir: {app}\mods\MS_Mod_StationTest\TEXT\geog; Flags: skipifsourcedoesntexist

; config and other files
;Source: .\EpicSource\docs\Epic User Manual.rtf; DestDir: {app}\mods
Source: .\EpicSource\docs\epic_*_config.ini; DestDir: {app}\configs
;Source: .\EpicSource\docs\InstallInstructions.rtf; DestDir: {app}\epic_docs; Flags: skipifsourcedoesntexist
Source: .\EpicSource\docs\keybind.txt; DestDir: {app}\epic_docs; Flags: skipifsourcedoesntexist
Source: .\EpicSource\docs\credits.rtf; DestDir: {app}\epic_docs; Flags: skipifsourcedoesntexist
Source: .\EpicSource\Installer\epic5.ico; DestDir: {app}
Source: .\EpicSource\Installer\epic6.ico; DestDir: {app}


[INI]
;Filename: {app}\flux.ini; Section: icSolarSystem; Key: far_clip; String: 3e+0014
Filename: {app}\flux.ini; Section: icSolarSystem; Key: far_clip; String: 2e5
Filename: {app}\flux.ini; Section: FcInputMapper; Key: input_scheme_ini; String: configs/epic_joy_config.ini
Filename: {app}\flux.ini; Section: icGUIMovie; Key: az; String: 0
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
;pre set up the mods
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_ClusterModels; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Debug; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Econ; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Emerald; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Environ; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: US_Mod_Geog; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Main; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Jump; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Music; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Nebula; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Planets; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Pog; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Reference; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Ships; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: no_launch_sequence; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Auto; String: 1
; rolled high poly into cluster models
;Filename: {app}\flux.ini; Section: Mods; Key: HighPolyPlanets; String: 1
; set Epic version
Filename: {app}\epic_version.ini; Section: Version; Key: value; String: 800


;Filename: {app}\flux.ini; Section: Mods; Key: multimod; String: 1;
;Filename: {app}\flux.ini; Section: Mods; Key: zzUniGUI; String: 1;

[Icons]
Name: {userdesktop}\Epic; Filename: {app}\EdgeOfChaos.exe; WorkingDir: {app}; IconFilename: {app}\epic5.ico; Comment: EoC Launcher for Epic; IconIndex: 0

[Code]
procedure CurStepChanged(CurStep: TSetupStep);
var
  ResultCode: Integer;
  copy_str: String;
begin
	// determine if at step just before the install starts
	if CurStep=ssInstall then
		begin

		//MsgBox(ExpandConstant('{app}'), mbInformation, MB_OK);

		// backup the mods dir
		copy_str := ExpandConstant('/Y /E /I "{app}\mods" "{app}\mods-backup_') + GetDateTimeString('yyyy/mm/dd_hh:nn:ss', '-', '-') + '"';
		//MsgBox(copy_str, mbInformation, MB_OK);
		Exec(ExpandConstant('{win}\system32\xcopy.exe'), copy_str, '', SW_SHOW, ewWaitUntilTerminated, ResultCode);

		// backup a movies dir if there
		copy_str := ExpandConstant('/Y /E /I "{app}\movies" "{app}\movies-backup_') + GetDateTimeString('yyyy/mm/dd_hh:nn:ss', '-', '-') + '"';
		//MsgBox(copy_str, mbInformation, MB_OK);
		Exec(ExpandConstant('{win}\system32\xcopy.exe'), copy_str, '', SW_SHOW, ewWaitUntilTerminated, ResultCode);

		// backup the planet texture dir in resources
		copy_str := ExpandConstant('/Y /E /I "{app}\resource\images\planets" "{app}\resource\images\planets-backup_') + GetDateTimeString('yyyy/mm/dd_hh:nn:ss', '-', '-') + '"';
		Exec(ExpandConstant('{win}\system32\xcopy.exe'), copy_str, '', SW_SHOW, ewWaitUntilTerminated, ResultCode);
		// delete all files inside this resource dir but leave the dir
		DelTree(ExpandConstant('{app}\resource\images\planets\*'), False, True, True);

		// backup flux ini
		FileCopy(ExpandConstant('{app}\flux.ini'), ExpandConstant('{app}\flux_') + GetDateTimeString('yyyy/mm/dd_hh:nn:ss', '-', '-')+'.ini', False);
		// Delete all files and directories inside mods\
		// but leave the directory itself
		DelTree(ExpandConstant('{app}\mods\*'), False, True, True);
		end;
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
