function InitializeSetup(): Boolean;
var
	epic_version: Longint;
	eoc_version: Cardinal;
	ini_file: String;
	ini_path: String;
begin
	// Has the correct version of Core been installed
	RegQueryStringValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\Particle Systems\Edge of Chaos\Settings', 'InstallPath', ini_path);
	ini_file := ini_path + '\epic_version.ini';
	epic_version := GetIniInt('Version', 'value', 0,0,0, ini_file);
	
	//MsgBox('Inifile= ' + ini_file, mbInformation, MB_OK);
	if  epic_version >= 705 then
		Result := True
	else begin
		MsgBox('Correct version of Epic Core has not been installed first.', mbInformation, MB_OK);
		Result := False;
	end;

	// check eoc version	
	RegQueryDWordValue(HKEY_LOCAL_MACHINE, 'SOFTWARE\Particle Systems\Edge of Chaos\Settings', 'Version', eoc_version);
	if  eoc_version = 14 then
		Result := True
	else begin
		MsgBox('Edge of Chaos v14.x has not been installed first.', mbInformation, MB_OK);
		Result := False;
	end;
	
	// do some key files exists tests that indicate a real EoC install location
	if not FileExists(ini_path+'\flux.ini') then Result:= false;
	if not FileExists(ini_path+'\EdgeOfChaos.exe') then	Result:= false;
	if not FileExists(ini_path+'\bin\release\loader.exe') then Result:= false;
end;
