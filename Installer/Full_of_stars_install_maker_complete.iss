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



; nebula
Source: .\..\EpicArt\MS_Mod_Nebula\models\farnorth\*; DestDir: {app}\mods\MS_Mod_Main\models\farnorth; Flags: skipifsourcedoesntexist






[INI]

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

