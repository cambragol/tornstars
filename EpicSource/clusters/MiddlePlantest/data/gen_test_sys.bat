@set PATH=c:\iwar2\bin\release;%path%

save_type test_systems.csv

	
geog test_sultan.csv	test_sultan.map	
geog test_junk.csv	test_junk.map	
geog test_pirate.csv	test_pirate.map
geog test_leung.csv	test_leung.map 


copy /b  test_sultan.map     c:\projects\epic\clusters\MiddlePlantest\geog\middle
copy /b  test_junk.map       c:\projects\epic\clusters\MiddlePlantest\geog\middle
copy /b  test_pirate.map     c:\projects\epic\clusters\MiddlePlantest\geog\middle
copy /b  test_leung.map    c:\projects\epic\clusters\MiddlePlantest\geog\middle


copy /b  test_sultan.ini     c:\projects\epic\clusters\MiddlePlantest\geog\middle
copy /b  test_junk.ini       c:\projects\epic\clusters\MiddlePlantest\geog\middle
copy /b  test_pirate.ini     c:\projects\epic\clusters\MiddlePlantest\geog\middle
copy /b  test_leung.ini    c:\projects\epic\clusters\MiddlePlantest\geog\middle


copy /b  test_sultan.txt     c:\projects\epic\clusters\MiddlePlantest\TEXT\geog\test_sultan.csv
copy /b  test_junk.txt       c:\projects\epic\clusters\MiddlePlantest\TEXT\geog\test_junk.csv
copy /b  test_pirate.txt     c:\projects\epic\clusters\MiddlePlantest\TEXT\geog\test_pirate.csv
copy /b  test_leung.txt    c:\projects\epic\clusters\MiddlePlantest\TEXT\geog\test_leung.csv



