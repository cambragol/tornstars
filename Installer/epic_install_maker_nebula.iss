[Setup]
UseSetupLdr=true
OutputBaseFilename=unstable_space_10_0_nebula
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
[Files]
; nebula
Source: .\EpicArt\MS_Mod_Nebula\*; DestDir: {app}\mods\MS_Mod_Nebula; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\images\sfx\*; DestDir: {app}\mods\MS_Mod_Nebula\images\sfx
Source: .\EpicArt\MS_Mod_Nebula\models\al43551\*; DestDir: {app}\mods\MS_Mod_Nebula\models\al43551; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\bumpys_star\*; DestDir: {app}\mods\MS_Mod_Nebula\models\bumpys_star; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\emerald\*; DestDir: {app}\mods\MS_Mod_Nebula\models\emerald; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\epitaph\*; DestDir: {app}\mods\MS_Mod_Nebula\models\epitaph; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\farnorth\*; DestDir: {app}\mods\MS_Mod_Nebula\models\farnorth; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\farsouth\*; DestDir: {app}\mods\MS_Mod_Nebula\models\farsouth; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\hd3887\*; DestDir: {app}\mods\MS_Mod_Nebula\models\hd3887; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\hd4045\*; DestDir: {app}\mods\MS_Mod_Nebula\models\hd4045; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\li_po\*; DestDir: {app}\mods\MS_Mod_Nebula\models\li_po; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\lombard\*; DestDir: {app}\mods\MS_Mod_Nebula\models\lombard; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\multiplayer\*; DestDir: {app}\mods\MS_Mod_Nebula\models\multiplayer; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\new_const\*; DestDir: {app}\mods\MS_Mod_Nebula\models\new_const; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\north\*; DestDir: {app}\mods\MS_Mod_Nebula\models\north; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\penda\*; DestDir: {app}\mods\MS_Mod_Nebula\models\penda; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\providence\*; DestDir: {app}\mods\MS_Mod_Nebula\models\providence; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\ripon\*; DestDir: {app}\mods\MS_Mod_Nebula\models\ripon; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\south\*; DestDir: {app}\mods\MS_Mod_Nebula\models\south; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\x472\*; DestDir: {app}\mods\MS_Mod_Nebula\models\x472; Flags: skipifsourcedoesntexist
Source: .\EpicArt\MS_Mod_Nebula\models\xu_xuan\*; DestDir: {app}\mods\MS_Mod_Nebula\models\xu_xuan; Flags: skipifsourcedoesntexist

[Code]
#include "core_needed.pas"
