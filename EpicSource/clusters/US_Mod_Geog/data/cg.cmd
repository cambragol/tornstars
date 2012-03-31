ECHO off
(SET src_data=ND)
(SET bingeog=ND)
(SET binjump=ND)
(SET drvltr=ND)
(SET choix=Y)

(SET /P src_data=Path to all_systems.csv file ^[e:\iwar2\bin\^]: )
IF %src_data% == ND SET src_data=e:\iwar2\bin\
ECHO %src_data%
IF not exist %src_data%\all_systems.csv (GOTO :Exit1)

(SET /P bingeog=Path to the geog executable ^[e:\iwar2\bin\^]: )
IF %bingeog% == ND SET bingeog=e:\iwar2\bin\
ECHO %bingeog%
IF not exist %bingeog%\geog.exe (GOTO :Exit1)

(SET /P binjump=Path to the jump_cluster executable ^[e:\iwar2\bin\^]: )
IF %binjump% == ND SET binjump=e:\iwar2\bin\
ECHO %binjump%
IF not exist %binjump%\jump_cluster.exe (GOTO :Exit1)

(SET /P choix=Are you writting to EPIC svn Trunk ^[Y^]: )
IF /i %choix% == Y (GOTO :defaut)
SET /P DestMAP=Path where .map files will be saved: 
SET /P DestINI=Path where .ini files will be saved: 
SET /P DestCSV=Path where .csv files will be saved: 
SET /P DestTXT=Path where .txt files will be saved: 
(GOTO :generation)

:defaut
(SET /P drvltr=Path to EPIC SVN trunk ^[C:\DATA_VAULT\Referentiels\EoC^]: )
IF %drvltr% == ND SET drvltr=C:\DATA_VAULT\Referentiels\EoC

ECHO all .map, .csv and .ini files will be written into folder

ECHO %drvltr%\trunk\EpicSource\clusters\US_Mod_Geog\geog\middle\
(SET DestMAP=%drvltr%\trunk\EpicSource\clusters\US_Mod_Geog\geog\middle\)
(SET DestINI=%drvltr%\trunk\EpicSource\clusters\US_Mod_Geog\geog\middle\)
(SET DestCSV=%drvltr%\trunk\EpicSource\clusters\US_Mod_Geog\geog\middle\)

ECHO all .txt files will be written into folder
ECHO %drvltr%\trunk\EpicSource\clusters\US_Mod_Geog\TEXT\geog\
(SET DestTXT=%drvltr%\trunk\EpicSource\clusters\US_Mod_Geog\TEXT\geog\)

:generation
ECHO Let's Go!
ECHO Step 1- generating files from all_clusters.csv
jump_cluster %src_data%\all_systems.csv 

copy %src_data%\all_systems.csv %drvltr%\trunk\EpicSource\clusters\US_Mod_Geog\data\all_systems.csv


ECHO Step 2- generating geog files
%bingeog%geog aleppo.csv     aleppo.map     
%bingeog%geog al_wadi.csv    al_wadi.map     
%bingeog%geog al_quaan.csv   al_quaan.map 
%bingeog%geog tulunid.csv    tulunid.map   
%bingeog%geog saladin.csv    saladin.map     
%bingeog%geog nureddin.csv      nureddin.map    
%bingeog%geog hant.csv          hant.map        
%bingeog%geog akra.csv          akra.map        
%bingeog%geog epitaph.csv       epitaph.map     
%bingeog%geog lombard.csv       lombard.map     
%bingeog%geog ripon.csv         ripon.map       
%bingeog%geog nisami.csv        nisami.map      
%bingeog%geog corliss.csv       corliss.map     
%bingeog%geog watts.csv         watts.map       
%bingeog%geog kronholm.csv      kronholm.map    
%bingeog%geog li_po.csv         li_po.map       
%bingeog%geog tau_tsun.csv      tau_tsun.map    
%bingeog%geog xu_xuan.csv       xu_xuan.map     
%bingeog%geog providence.csv    providence.map  
%bingeog%geog emerald_sys.csv   emerald_sys.map 
%bingeog%geog penda.csv         penda.map       
%bingeog%geog huang.csv         huang.map       
%bingeog%geog bumpys_star.csv   bumpys_star.map 
%bingeog%geog alcuin.csv        alcuin.map      
%bingeog%geog bedalov.csv       bedalov.map     
%bingeog%geog powys.csv         powys.map       
%bingeog%geog t_ang.csv         t_ang.map 
%bingeog%geog x472.csv          x472.map    
%bingeog%geog hd3479.csv        hd3479.map    
%bingeog%geog hd3887.csv        hd3887.map   
%bingeog%geog hd2271.csv        hd2271.map    
%bingeog%geog al42217.csv       al42217.map
%bingeog%geog al43844.csv       al43844.map    
%bingeog%geog hd4045.csv        hd4045.map 
%bingeog%geog x788.csv          x788.map    
%bingeog%geog al40064.csv       al40064.map   
%bingeog%geog al43551.csv       al43551.map   
%bingeog%geog al43665.csv       al43665.map     
%bingeog%geog capsule_space.csv capsule_space.map

ECHO Step 3- Moving .map files to repository
move *.map %DestMAP%
ECHO Step 4- Moving .ini files to repository
move *.ini %DestINI%
ECHO Step 5- Moving .csv files to repository
move *.csv %DestCSV%
ECHO Step 6- Moving .txt files to repository
move *.txt %DestTXT%

ECHO The End!
GOTO :EOF
:Exit1
ECHO Unable to read all_systems.csv, or necessary exe
:EOF
