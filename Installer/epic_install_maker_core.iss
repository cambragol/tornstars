[Setup]
UseSetupLdr=true
OutputBaseFilename=epic_setup_7_5_1_core
OutputDir=C:\games\EoC_EPIC\EpicInstaller
AppCopyright=Epic Team
AppName=Epic
AppVerName=Epic 7.5.1
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
VersionInfoVersion=7.5
VersionInfoTextVersion=Epic 7.5.1
WizardImageFile=C:\games\EoC_EPIC\EpicInstaller\install_left_2.bmp
WizardSmallImageFile=C:\games\EoC_EPIC\EpicInstaller\install_small_2.bmp
[_ISTool]
Use7zip=true
[Dirs]
Name: {app}\movies
[Files]
; misc
Source: ..\mods\no_launch_sequence.zip; DestDir: {app}\mods
Source: Epic User Manual.rtf; DestDir: {app}\mods
;Source: ..\mods\HighPolyPlanets.zip; DestDir: {app}\mods

; debug
Source: ..\mods\MS_Mod_Debug\*; DestDir: {app}\mods\MS_Mod_Debug
Source: ..\mods\MS_Mod_Debug\html\*; DestDir: {app}\mods\MS_Mod_Debug\html

; econ
Source: ..\mods\MS_Mod_Econ\*; DestDir: {app}\mods\MS_Mod_Econ; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_Econ\TEXT\*; DestDir: {app}\mods\MS_Mod_Econ\TEXT; Flags: skipifsourcedoesntexist

; environ
Source: ..\mods\MS_Mod_Environ\*; DestDir: {app}\mods\MS_Mod_Environ; Flags: skipifsourcedoesntexist

; geog
Source: ..\mods\MS_Mod_Geog\*; DestDir: {app}\mods\MS_Mod_Geog
Source: ..\mods\MS_Mod_Geog\data\*; DestDir: {app}\mods\MS_Mod_Geog\data
Source: ..\mods\MS_Mod_Geog\geog\*; DestDir: {app}\mods\MS_Mod_Geog\geog
Source: ..\mods\MS_Mod_Geog\geog\middle\*; DestDir: {app}\mods\MS_Mod_Geog\geog\middle
Source: ..\mods\MS_Mod_Geog\sims\*; DestDir: {app}\mods\MS_Mod_Geog\sims; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_Geog\sims\stations\*; DestDir: {app}\mods\MS_Mod_Geog\sims\stations
Source: ..\mods\MS_Mod_Geog\source\*; DestDir: {app}\mods\MS_Mod_Geog\source; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_Geog\TEXT\*; DestDir: {app}\mods\MS_Mod_Geog\TEXT
Source: ..\mods\MS_Mod_Geog\TEXT\geog\*; DestDir: {app}\mods\MS_Mod_Geog\TEXT\geog

; main
Source: ..\mods\MS_Mod_Main\*; DestDir: {app}\mods\MS_Mod_Main
Source: ..\mods\MS_Mod_Main\html\*; DestDir: {app}\mods\MS_Mod_Main\html
Source: ..\mods\MS_Mod_Main\images\*; DestDir: {app}\mods\MS_Mod_Main\images; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_Main\images\gui\*; DestDir: {app}\mods\MS_Mod_Main\images\gui
Source: ..\mods\MS_Mod_Main\include\*; DestDir: {app}\mods\MS_Mod_Main\include; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_Main\packages\*; DestDir: {app}\mods\MS_Mod_Main\packages
Source: ..\mods\MS_Mod_Main\source\*; DestDir: {app}\mods\MS_Mod_Main\source
Source: ..\mods\MS_Mod_Main\TEXT\*; DestDir: {app}\mods\MS_Mod_Main\TEXT

; pog
Source: ..\mods\MS_Mod_Pog\*; DestDir: {app}\mods\MS_Mod_Pog; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_Pog\html\*; DestDir: {app}\mods\MS_Mod_Pog\html; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_Pog\packages\*; DestDir: {app}\mods\MS_Mod_Pog\packages; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_Pog\source\*; DestDir: {app}\mods\MS_Mod_Pog\source; Flags: skipifsourcedoesntexist

; reference
Source: ..\mods\MS_Mod_Reference\*; DestDir: {app}\mods\MS_Mod_Reference; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_Reference\html\*; DestDir: {app}\mods\MS_Mod_Reference\html; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_Reference\html\encyclopedia\politics\*; DestDir: {app}\mods\MS_Mod_Reference\html\encyclopedia\politics; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_Reference\html\prison\*; DestDir: {app}\mods\MS_Mod_Reference\html\prison; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_Reference\TEXT\*; DestDir: {app}\mods\MS_Mod_Reference\TEXT; Flags: skipifsourcedoesntexist

; ships
Source: ..\mods\MS_Mod_Ships\*; DestDir: {app}\mods\MS_Mod_Ships; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_Ships\sims\*; DestDir: {app}\mods\MS_Mod_Ships\sims; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_Ships\sims\ships\*; DestDir: {app}\mods\MS_Mod_Ships\sims\ships; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_Ships\sims\ships\player\*; DestDir: {app}\mods\MS_Mod_Ships\sims\ships\player; Flags: skipifsourcedoesntexist

; station test
Source: ..\mods\MS_Mod_StationTest\*; DestDir: {app}\mods\MS_Mod_StationTest; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_StationTest\data\*; DestDir: {app}\mods\MS_Mod_StationTest\data; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_StationTest\geog\*; DestDir: {app}\mods\MS_Mod_StationTest\geog; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_StationTest\geog\middle\*; DestDir: {app}\mods\MS_Mod_StationTest\geog\middle; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_StationTest\sims\*; DestDir: {app}\mods\MS_Mod_StationTest\sims; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_StationTest\sims\stations\*; DestDir: {app}\mods\MS_Mod_StationTest\sims\stations; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_StationTest\TEXT\*; DestDir: {app}\mods\MS_Mod_StationTest\TEXT; Flags: skipifsourcedoesntexist
Source: ..\mods\MS_Mod_StationTest\TEXT\geog\*; DestDir: {app}\mods\MS_Mod_StationTest\TEXT\geog; Flags: skipifsourcedoesntexist

; config and other files
Source: epic_*_config.ini; DestDir: {app}\configs
Source: *.rtf; DestDir: {app}\epic_docs; Flags: skipifsourcedoesntexist
Source: keybind.txt; DestDir: {app}\epic_docs; Flags: skipifsourcedoesntexist
Source: epic5.ico; DestDir: {app}
Source: epic6.ico; DestDir: {app}


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
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Debug; String: 0
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Econ; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Environ; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Geog; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Main; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Music; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Nebula; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Planets; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Pog; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Reference; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_Ships; String: 1
Filename: {app}\flux.ini; Section: Mods; Key: MS_Mod_StationTest; String: 0
Filename: {app}\flux.ini; Section: Mods; Key: no_launch_sequence; String: 1

; set Epic version
Filename: {app}\epic_version.ini; Section: Version; Key: value; String: 705


;Filename: {app}\flux.ini; Section: Mods; Key: HighPolyPlanets; String: 1
;Filename: {app}\flux.ini; Section: Mods; Key: multimod; String: 1;
;Filename: {app}\flux.ini; Section: Mods; Key: zzUniGUI; String: 1;

[Icons]
Name: {userdesktop}\Epic; Filename: {app}\EdgeOfChaos.exe; WorkingDir: {app}; IconFilename: {app}\epic6.ico; Comment: EoC Launcher for Epic; IconIndex: 0

[Code]
procedure CurStepChanged(CurStep: TSetupStep);
var
  ResultCode: Integer;
  copy_str: String;
begin
	// determine if at step just before the install starts
	if CurStep=ssInstall then
		begin
		// backup the mods dir
		copy_str := ExpandConstant('/Y /E /I "{app}\mods" "{app}\mods-backup_') + GetDateTimeString('yyyy/mm/dd_hh:nn:ss', '-', '-') + '"';
		Exec(ExpandConstant('{win}\system32\xcopy.exe'), copy_str, '', SW_SHOW, ewWaitUntilTerminated, ResultCode);

		// backup the planet texture dir in resources
		copy_str := ExpandConstant('/Y /E /I "{app}\resource\images\planets" "{app}\resource\images\planets-backup_') + GetDateTimeString('yyyy/mm/dd_hh:nn:ss', '-', '-') + '"';
		Exec(ExpandConstant('{win}\system32\xcopy.exe'), copy_str, '', SW_SHOW, ewWaitUntilTerminated, ResultCode);
		// delete all files inside this resource dir but leave the dir
		DelTree(ExpandConstant('{app}\resource\images\planets\*'), False, True, True);

		// backup a movies dir if there
		//Exec(ExpandConstant('{win}\system32\xcopy.exe'),
		//	ExpandConstant('/Y /E /I {app}\movies {app}\movies-backup_') + GetDateTimeString('yyyy/mm/dd_hh:nn:ss', '-', '-'),
		//	'',
		//	SW_SHOW,
		//	ewWaitUntilTerminated,
		//	ResultCode);

		FileCopy(ExpandConstant('{app}\flux.ini'), ExpandConstant('{app}\flux_')+GetDateTimeString('yyyy/mm/dd_hh:nn:ss', '-', '-')+'.ini', False);
		// Delete all files and directories inside mods\
		// but leave the directory itself
		DelTree(ExpandConstant('{app}\mods\*'), False, True, True);
		end;
end;
