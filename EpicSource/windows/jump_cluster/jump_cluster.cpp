// jump_cluster.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include "MapEnumerations.h"


struct {
	char name [2048];
	int model;
} model_table[256];


struct {
	char name [2048];
	int habitat_enum;
} habitat_type_table[1024];

struct {
	char name [2048];
	int faction_enum;
} faction_table[256];

void ParseName(char *name);

double PrintGiant(FILE * out, char *name, char *parent, double orbit, double rot);
double PrintMoon(FILE * out, char *name, char *parent, double orbit, double rot, double radius);
double PrintPlanet(FILE * out, char *name, char *parent, double orbit, double rot, int texture, int bump_map);
void PrintSpecialPlanet(FILE * out, char *name, char *parent, double orbit, double rot, 
						double radius, int model, FILE * finiout, int count);

void PrintStation(FILE * out, char *name, char *parent, 
				  double orbit, double rot, int faction, 
				  int type, int model, FILE * finiout, int count, 
				  char * fac_name, int status, int richness);

void PrintOperation( char *parent,
				  int type,  FILE * finiout, int count, 
				  char * fac_name);

void PrintStar(FILE * out, char *name, char *parent, double orbit, double rot, int magnitude);
double PrintCore(FILE * out, char *name, char *parent, double orbit, double rot);

void PrintBelt(FILE * out, char *name, char *parent, double orbit, double rot, double field_size);
void PrintRing(FILE * out, char *name, char *parent, double orbit, double rot, double field_size);
void PrintNebula(FILE * out, char *name, char *parent, double orbit, double rot, double field_size);

void PrintCenter(FILE * out, char *name);
double rand_size(double lower, double upper);
int rand_int( int upper);

int NameToFaction(char * name);
int NameToStation(char * name);
int NameToModel(char * name);

int NameToStationType(char * name);
int NameToStatus(char * name);

int NameToOpType(char * name);

int HabTypeToDefType(int type);
int HabTypeToDef(int type);

int SupportedStation(char * name, char * station_name);

void clear_table ();


double cstar_orbit_base = 1.0e9;
double cmoon_orbit_base = 1.0e8;
double cmoon_orbit_start = 4.0;
double cmoon_orbit_increment = 1.2;

double cplanet_radii_min = 1.0e6;
double cplanet_radii_max = 9.0e6;
double cplanet_orbit_base = 1.0e9;
double cplanet_orbit_start = 3.0;
double cplanet_orbit_increment = 1.5;

double cgiant_radii_min = 2.0e7;
double cgiant_radii_max = 9.0e7;

double cstation_orbit_mult = 2.0;

//Default texture values from EoC standard code.
int crocky1_texture_count = 4;
int crocky2_texture_count = 4;

int cgassy_texture_count = 10;

int cbump_texture = 9;

int model_entries = 0;
int faction_entries = 0;
int habitat_entries = 0;

FILE *error_log;







int main(int argc, char* argv[])
{ 
	FILE *finput;
	FILE *foutput;
	FILE *fouttext;
	FILE *foutini;


	char line [2048];
	char * ptoken;

	char name[1024];
	char station[1024];
	char station_model[1024];
	char faction[1024];
	char lpoint[1024];
	char system[1024];

	char planet[1024];
	char moon[1024];
	char file_name[1024];

	char station_status[1024];
	char operation_type[1024];
	char system_visible[1024];

	double station_orbit = 0.25;
	double station_rot = 30.0;

	double planet_orbit = 0.25;
	double planet_rot = 30.0;
	double planet_radius = 12e6;
	double station_radius = 1e7;

	double moon_orbit = 0.25;
	double moon_rot = 30.0;

	char operation_parent[1024];
	char station_parent[1024];
	char planet_parent[1024];
	char moon_parent[1024];
	char center_name[1024];

	int i, entries;
	int fac, type, model, status, planet_model;
	int magnitude;
	int int_value;
	int specific_texture = 0;
	int richness;

	double adjustment;

	int station_count = 0;
	int operation_count = 0;

	int period;
	int difficulty;
	int offset;

    int habitat_type;
    int faction_enum;


	// counter for number of lpoint jump routes
	// used in creating the system ini file.
	int gLpointRoutes = 0;

	if (argc != 2){ 
		fprintf(error_log,"Usage: jump_cluster <input spreadsheet name>\n");
		return 1;
	}

	// Open the input file
	finput = fopen(argv[1],"r");

	if (NULL == finput){ 
		fprintf(error_log,"Error: trying to open input file %s\n",argv[1]);
		return 1;
	}


	error_log = fopen("error.txt","w");

	if (NULL == error_log){ 
		fprintf(error_log,"Error: trying to open error log file\n");
		return 1;
	}

	foutput = NULL;
	fouttext = NULL;

	srand(1);

	clear_table();


	// While not out of lines
	while (NULL != fgets(line,2048,finput)){ 

		ptoken = strtok(line, " \t,");

		if (strlen(ptoken) <=1){
			// This is an empty line, just ignore it.	
		}else if (';' == ptoken[0]){
			// This is a comment line, just ignore it.
		}else if (0 == strcmp("Giant",ptoken)){ 
			ParseName(name);

			planet_radius = PrintGiant(foutput, name, planet_parent, planet_orbit, planet_rot);
			station_radius = planet_radius;

			// reset the moon orbit rotation
			// reset the moon orbit distance
			// reset the moon parent
			moon_orbit = cmoon_orbit_start;
			moon_rot = planet_rot;
			strcpy(moon_parent,name);

			// reset the station parent
			// reset the station distance
			// reset the station rotation

			station_orbit = cstation_orbit_mult;
			station_rot = 0.0;
			strcpy(station_parent,name);

			// increment planet distance and rotation
			planet_orbit *= cplanet_orbit_increment;
			planet_rot += 30.0;
			if (planet_rot >= 360)
				planet_rot = 0;

			fprintf(fouttext,"%s,\"%s\"\n",name,name);

		}else if (0 == strcmp("Model",ptoken)){ 
			// This entry lets us build a symbol table converting from string names
			// to model numbers. This makes life easy on the cluster builder and
			// allows changes without need of recompiling the jump_cluster program.

			ParseName(name);
			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%d",&int_value);
			model = int_value;
			
			strncpy(model_table[model_entries].name, name, 1000);
			model_table[model_entries].model = model;

			++model_entries;

		}else if (0 == strcmp("Habitat",ptoken)){ 
			// This entry lets us build a symbol table converting from string names
			// to model numbers. This makes life easy on the cluster builder and
			// allows changes without need of recompiling the jump_cluster program.

			ParseName(name);
			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%d",&int_value);
			habitat_type = int_value;
			
			strncpy(habitat_type_table[habitat_entries].name, name, 1000);
			habitat_type_table[habitat_entries].habitat_enum = habitat_type;

			++habitat_entries;

		}else if (0 == strcmp("Faction",ptoken)){ 
			// This entry lets us build a symbol table converting from string names
			// to model numbers. This makes life easy on the cluster builder and
			// allows changes without need of recompiling the jump_cluster program.

			ParseName(name);
			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%d",&int_value);
			faction_enum = int_value;
			
			strncpy(faction_table[faction_entries].name, name, 1000);
			faction_table[faction_entries].faction_enum = faction_enum;

			++faction_entries;

		}else if (0 == strcmp("Station",ptoken)){ 
			ParseName(name);

			ParseName(station);

			ParseName(station_model);

			ParseName(faction);

			ParseName(station_status);

			fac = NameToFaction(faction);

			type = NameToStationType(station);

			model = NameToModel(station_model);

			status = NameToStatus(station_status);

			SupportedStation(station, name);

			PrintStation(foutput, name, station_parent, station_orbit*station_radius, 
					station_rot, fac, type, model, foutini, station_count, faction, status, 0);

			// increment puts stations in tri balance. stations end up
			// on near opposite sides of planet. with uneven
			// value, they should never overlap.
			station_rot += 127.0;
			station_rot = fmod(station_rot, 360.0);

			station_count++;

			fprintf(fouttext,"%s,\"%s\"\n",name,name);
			
			// remember this station as a parent of future operations.
			strcpy(operation_parent,name);
		}else if (0 == strcmp("Mine",ptoken)){ 
			ParseName(name);

			ParseName(station);

			ParseName(station_model);

			ParseName(faction);

			ParseName(station_status);

			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%d",&int_value);
			richness = int_value;

			if (richness < 0) {
				richness = 0;
			}else if (richness > 3) {
				richness = 3;
			}

			fac = NameToFaction(faction);

			type = NameToStationType(station);
			model = NameToModel(station_model);
			//model = NameToStation(station);

			status = NameToStatus(station_status);

			SupportedStation(station, name);

			PrintStation(foutput, name, station_parent, station_orbit*station_radius, 
					station_rot, fac, type, model, foutini, station_count, faction, 
					status, richness);

			// increment puts stations in tri balance. stations end up
			// on near opposite sides of planet. with uneven
			// value, they should never overlap.
			station_rot += 127.0;
			station_rot = fmod(station_rot, 360.0);

			station_count++;

			fprintf(fouttext,"%s,\"%s\"\n",name,name);
			
			// remember this station as a parent of future operations.
			strcpy(operation_parent,name);
		}else if (0 == strcmp("Operation",ptoken)){ 
			//operation type
			ParseName(operation_type);
			ParseName(faction);
			type = NameToOpType(operation_type);

			PrintOperation( operation_parent, type, 
					      foutini, operation_count, faction);

			operation_count++;

			fprintf(fouttext,"%s,\"%s\"\n",name,name);
		}else if (0 == strcmp("Planet",ptoken)){ 
			ParseName(name);

			planet_radius = PrintPlanet(foutput, name, planet_parent, 
				planet_orbit, planet_rot, specific_texture, cbump_texture);
			station_radius = planet_radius;

			// reset the special texture value
			specific_texture = 0;
			cbump_texture = 0;

			// reset the moon orbit rotation
			// reset the moon orbit distance
			// reset the moon parent
			moon_orbit = cmoon_orbit_start;
			moon_rot = planet_rot;
			strcpy(moon_parent,name);

			// reset the station parent
			// reset the station distance
			// reset the station rotation
			station_orbit = cstation_orbit_mult;
			station_rot = 0.0;
			strcpy(station_parent,name);

			// increment planet distance and rotation
			planet_orbit *=cplanet_orbit_increment;
			planet_rot += 30.0;
			planet_rot = fmod(planet_rot, 360.0);

			fprintf(fouttext,"%s,\"%s\"\n",name,name);
		
		}else if (0 == strcmp("SpecialPlanet",ptoken)){ 
			ParseName(name);

			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%d",&int_value);
			planet_radius = int_value;
			planet_radius = planet_radius * 1e3;

			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%d",&int_value);
			planet_model = int_value;

			PrintSpecialPlanet(foutput, name, planet_parent, planet_orbit, planet_rot, 
							   planet_radius, planet_model, foutini, station_count);
			
			++station_count;

			station_radius = planet_radius;

			// reset the special texture value
			specific_texture = 0;
			cbump_texture = 0;

			// reset the moon orbit rotation
			// reset the moon orbit distance
			// reset the moon parent
			moon_orbit = cmoon_orbit_start;
			moon_rot = planet_rot;
			strcpy(moon_parent,name);

			// reset the station parent
			// reset the station distance
			// reset the station rotation
			station_orbit = cstation_orbit_mult;
			station_rot = 0.0;
			strcpy(station_parent,name);

			// increment planet distance and rotation
			planet_orbit *=cplanet_orbit_increment;
			planet_rot += 30.0;
			planet_rot = fmod(planet_rot, 360.0);

			fprintf(fouttext,"%s,\"%s\"\n",name,name);

		}else if (0 == strcmp("Belt", ptoken)){ 
			ParseName(name);

			PrintBelt(foutput, name, planet_parent, planet_orbit,planet_rot, planet_orbit/1000.0);
			// 10,000,000 meters seperation between stations.
			planet_radius = cplanet_radii_max;
			station_radius = cplanet_radii_max;
			// reset the moon orbit rotation
			// reset the moon orbit distance
			// reset the moon parent
			moon_orbit = cmoon_orbit_start;
			moon_rot = planet_rot;
			strcpy(moon_parent,name);

			// reset the station parent
			// reset the station distance
			// reset the station rotation
			station_orbit = cstation_orbit_mult;
			station_rot = planet_rot;
			strcpy(station_parent,name);

			// increment planet distance and rotation
			planet_orbit *= cplanet_orbit_increment;
			planet_rot += 30.0;
			if (planet_rot >= 360)
				planet_rot = 0;

			fprintf(fouttext,"%s,\"%s\"\n",name,name);
		}else if (0 == strcmp("Ring", ptoken)){ 
			ParseName(name);

			PrintRing(foutput, name, moon_parent, moon_orbit, moon_rot, moon_orbit/1000.0);

			station_radius = cplanet_radii_min;

			// reset the station parent
			// reset the station distance
			// reset the station rotation
			station_orbit = cstation_orbit_mult;
			station_rot = 0.0;
			strcpy(station_parent,name);

			// increment planet distance and rotation
			moon_orbit *=cmoon_orbit_increment;
			moon_rot += 30.0;
			if (moon_rot>= 360)
				moon_rot = 0;

			fprintf(fouttext,"%s,\"%s\"\n",name,name);
		}else if (0 == strcmp("Nebula", ptoken)){ 
			ParseName(name);

			PrintNebula(foutput, name, planet_parent, planet_orbit, planet_rot, planet_orbit/1000.0);
			// 10,000,000 meters seperation between stations.
			planet_radius = cplanet_radii_max;
			station_radius = cplanet_radii_max;
			// reset the moon orbit rotation
			// reset the moon orbit distance
			// reset the moon parent
			moon_orbit = cmoon_orbit_start;
			moon_rot = planet_rot;
			strcpy(moon_parent,name);

			// reset the station parent
			// reset the station distance
			// reset the station rotation
			station_orbit = cstation_orbit_mult;
			station_rot = planet_rot;
			strcpy(station_parent,name);

			// increment planet distance and rotation
			planet_orbit *=cplanet_orbit_increment;
			planet_rot += 30.0;
			if (planet_rot >= 360)
				planet_rot = 0;

			fprintf(fouttext,"%s,\"%s\"\n",name,name);

		}else if (0 == strcmp("Star", ptoken)){ 
			ParseName(name);

			// Read texture 2 color triple
			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%d",&magnitude);

			if (magnitude < 0)
				magnitude = 0;
			else if (magnitude > 100)
				magnitude = 100;

			//ptoken = strtok(NULL," \t,");
			//sscanf(ptoken,"%f",&star_distance);
			
			//fprintf(error_log,ptoken);
			//fprintf(error_log," %f star distance\n", star_distance);
			

			PrintStar(foutput, name, center_name, 0.0, 0.0, magnitude);
			
			planet_radius = cplanet_radii_max;
			station_radius = cplanet_radii_max;
			// reset the moon orbit rotation
			// reset the moon orbit distance
			// reset the moon parent
			moon_orbit = cmoon_orbit_start;
			moon_rot = 0.0;
			strcpy(moon_parent,name);

			// reset the station parent
			// reset the station distance
			// reset the station rotation
			station_orbit = cstation_orbit_mult;
			station_rot = 0.0;
			strcpy(station_parent,name);

			// reset planet parent
			// reset planet orbits
			// reset planet rotation
			planet_orbit = cplanet_orbit_start;
			planet_rot = 0.0;
			strcpy(planet_parent, name);			

			fprintf(fouttext,"%s,\"%s\"\n",name,name);

		}else if (0 == strcmp("Core", ptoken)){ 
			// failed core star of a system. It can have orbiting planets.
			ParseName(name);

			PrintCore(foutput, name, center_name, 0, 0);

			//PrintCore(foutput, name, center_name);
			
			planet_radius = cplanet_radii_max;
			station_radius = cplanet_radii_max;
			// reset the moon orbit rotation
			// reset the moon orbit distance
			// reset the moon parent
			moon_orbit = cmoon_orbit_start;
			moon_rot = 0.0;
			strcpy(moon_parent,name);

			// reset the station parent
			// reset the station distance
			// reset the station rotation
			station_orbit = cstation_orbit_mult;
			station_rot = 0.0;
			strcpy(station_parent,name);

			// reset planet parent
			// reset planet orbits
			// reset planet rotation
			planet_orbit = cplanet_orbit_start;
			planet_rot = 0.0;
			strcpy(planet_parent, name);			

			fprintf(fouttext,"%s,\"%s\"\n",name,name);

		}else if (0 == strcmp("Moon", ptoken)){ 
			ParseName(name);

			station_radius = PrintMoon(foutput, name, moon_parent, moon_orbit, moon_rot, planet_radius);
			

			// reset the station parent
			// reset the station distance
			// reset the station rotation
			station_orbit = cstation_orbit_mult;
			station_rot = 0.0;
			strcpy(station_parent,name);

			// increment planet distance and rotation
			moon_orbit *=cmoon_orbit_increment;
			moon_rot += 30.0;
			if (moon_rot>= 360)
				moon_rot = 0;

			fprintf(fouttext,"%s,\"%s\"\n",name,name);

		}else if (0 == strcmp("Center", ptoken)){
			ParseName(name);
			ParseName(system_visible);

			fprintf(error_log,"New System :%s:\n",name);
			// Open a new output file.
			// Close the current output file

			if (NULL != foutput){ 
				fclose(foutput);
				fclose(fouttext);
				fclose(foutini);
			}

			strcpy(file_name,name);
			strcat(file_name,".csv");

			foutput = fopen(file_name,"w");

			if (NULL == foutput){ 
				fprintf(error_log,"Error: trying to open output file %s\n",file_name);
				return 1;
			}
			
			strcpy(file_name,name);
			strcat(file_name,".txt");

			fouttext = fopen(file_name,"w");

			if (NULL == foutput){ 
				fprintf(error_log,"Error: trying to open output text file %s\n",file_name);
				return 1;
			}

			strcpy(file_name,name);
			strcat(file_name,".ini");

			foutini = fopen(file_name,"w");

			if (NULL == foutini){ 
				fprintf(error_log,"Error: trying to open output ini file %s\n",file_name);
				return 1;
			}
			
			
			fprintf(foutini,"\n\n[SystemProperties]\nvisibility=%s\n", system_visible);

			fprintf(foutini,"\n\n[starting_stations]\n\n");

			// every system restarts the station count for ini file.
			station_count = 0;
			operation_count = 0;
			gLpointRoutes = 0;


			strcpy(file_name,name);
			strcat(file_name,"_center");

			fprintf(foutput,"Center,%s,0,0,0,1,0,0,0,0,,,end,\n",file_name);
			strcpy(center_name,file_name);

			// Just because there might not be a new star, we reset
			// everything here. The star will recreate, if 
			// it needs to.

			planet_radius = cplanet_radii_max;
			station_radius = cplanet_radii_max;

			// reset the moon orbit rotation
			// reset the moon orbit distance
			// reset the moon parent
			moon_orbit = cmoon_orbit_start;
			moon_rot = 0.0;
			strcpy(moon_parent,name);

			// reset the station parent
			// reset the station distance
			// reset the station rotation
		
			station_orbit = cstation_orbit_mult;
			station_rot = 0.0;
			strcpy(station_parent,name);

			// reset planet parent
			// reset planet orbits
			// reset planet rotation
			planet_orbit = cplanet_orbit_start;
			planet_rot = 0.0;
			strcpy(planet_parent, name);

			fprintf(fouttext,"%s,\"%s\"\n",center_name,name);

		}else if (0 == strcmp("Lpoint", ptoken)){ 
			ParseName(name);

			// remember this Lpoint as a parent of future operations.
			strcpy(operation_parent,name);

			fprintf(fouttext,"%s,\"%s\"\n",name,name);

			ParseName(planet);

			ParseName(moon);

			// Read the number of entries
			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%d",&entries);


			// The jump_cluster does not allow system to system jumps lpoint
			// using the PS jump code. We do this by having each lpoint have no
			// entries. This way, local jumps are still supported normally,
			// capsule drive subsystems still work, and yet we get to customize 
			// lpoint jumping.
			//fprintf(foutput,"Lpoint,%s,%s,%s,%f,%d,",name,planet,moon,0.50,entries);
			fprintf(foutput,"Lpoint,%s,%s,%s,%f,%d,",name,planet,moon,0.50,0);
// Each jump point gets an entry in the system INI file.
// One set of entries for every route from this jump point.
// The data tells the jump code where to send the player, and how hard to get there.
//start_lpoint[0]=lpoint name
//difficulty[0]= 1 for mil, 2 for scout
//period[0]
//end_system[0]=
//end_lpoint[0]

			// Start the series of entries in the cluster data file.
			fprintf(foutini,"\n;%s Route Entries\n", name);

			for (i=0;i<entries;++i){
				// Parse the system, but we output nothing to the geog for jump_cluster.
				ParseName(system);
				//fprintf(foutput,"%s,",system);
				// Parse the lpoint target
				ParseName(lpoint);
				
				// Parse the difficulty
				ptoken = strtok(NULL," \t,");
				sscanf(ptoken,"%d",&difficulty);
				
				// Parse the period
				ptoken = strtok(NULL," \t,");
				sscanf(ptoken,"%d",&period);
				
				// Parse the offset 
				ptoken = strtok(NULL," \t,");
				sscanf(ptoken,"%d",&offset);
			
				fprintf(foutini,"\nstart_lpoint[%d]=\"%s\"\n", gLpointRoutes, name);
				fprintf(foutini,"difficulty[%d]=%d\n", gLpointRoutes, difficulty);
				fprintf(foutini,"period[%d]=%d\n", gLpointRoutes, period);
				fprintf(foutini,"offset[%d]=%d\n", gLpointRoutes, offset);
				fprintf(foutini,"end_system[%d]=\"%s\"\n", gLpointRoutes, system);
				fprintf(foutini,"end_lpoint[%d]=\"%s\"\n\n", gLpointRoutes, lpoint);
				gLpointRoutes++;
			}

			fprintf(foutput,"end,\n");

		}else if (0 == strcmp("PlanetRadiusMin", ptoken)){ 

			// Read in the new minimum planet size.
			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%f",&adjustment);
			cplanet_radii_min = adjustment;

		}else if (0 == strcmp("PlanetRadiusMax", ptoken)){ 
			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%f",&adjustment);
			cplanet_radii_max = adjustment;
		}else if (0 == strcmp("GiantRadiusMin", ptoken)){ 
			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%f",&adjustment);
			cgiant_radii_min = adjustment;
		}else if (0 == strcmp("GaintRadiusMax", ptoken)){ 
			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%f",&adjustment);
			cgiant_radii_max = adjustment;
		}else if (0 == strcmp("PlanetOrbitBase", ptoken)){ 
			// All planet orbit increases are multiplied by this number.
			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%f",&adjustment);
			cplanet_orbit_base = adjustment;
		}else if (0 == strcmp("PlanetOrbit", ptoken)){ 
			// This is the starting distance for planets (times base number).
			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%f",&adjustment);
			planet_orbit = adjustment;
		}else if (0 == strcmp("PlanetOrbitIncrement", ptoken)){ 
			// This is the amount each orbit increases the orbit radius.
			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%f",&adjustment);
			cplanet_orbit_increment = adjustment;
		} else if (0 == strcmp("RockyTextureCount", ptoken)){ 
			// This is the number of texture 1 values availiable for rocky textures
			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%d",&int_value);
			crocky1_texture_count = int_value;
		} else if (0 == strcmp("RockyTwoTextureCount", ptoken)){ 
			// This is the number of texture 2 values availiable for rocky textures
			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%d",&int_value);
			crocky2_texture_count = int_value;
		} else if (0 == strcmp("GiantTextureCount", ptoken)){ 
			// This is the number of gas giant texture availiable.
			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%d",&int_value);
			cgassy_texture_count = int_value;
		} else if (0 == strcmp("SpecialPlanetTexture", ptoken)){ 
			// Allows the user to specifiy a special value to use for 
			// texture 1 of a planet. needed for Emerald and others.
			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%d",&int_value);
			specific_texture = int_value;
		} else if (0 == strcmp("SpecialPlanetBump", ptoken)){ 
			// Allows the user to specify which texture is the bump map texture
			// used with special planets.
			ptoken = strtok(NULL," \t,");
			sscanf(ptoken,"%d",&int_value);
			cbump_texture = int_value;
		} else {
			fprintf(error_log,"Error :%s:\n",ptoken);
		}
	}
	// Close input
	fclose(finput);

	// Close output
	fclose(foutput);

	return 0;
}



void ParseName(char * name)
{ 
	char temp[1024];
	char * ptoken;
	int length, i;

	// finds name, but has white space lead and trail.
	ptoken = strtok(NULL, ",");

	// get the tokenizer out of the equation.
	strcpy(temp,ptoken);
	ptoken = temp;

	// find lead without space, and skip
	//lead = strspn(ptoken," ");
	//ptoken += lead;

	length = strlen(ptoken);
	for (i=0;i<length;i++,ptoken++)
	{ 
		if (!isspace(*ptoken)){ 
			break;
		}
	}
	
	length = strlen(ptoken);

	for (i=length-1;i>0;--i){ 
		if (!isspace(ptoken[i])){ 
			strncpy(name,ptoken,i+1);
			name[i+1]=0;
			//fprintf(error_log,"Name :%s: %d\n",name,i);
			return;
		}
	}

	name[0]=0;
}

//type body	name	parent	dist	lat	long	roll	pitch	yaw	y_scale	radius	body type	pop	texture	tex 1	tex 2	red1	green	blue 	red2	green 	blue	red 3	green 	blue	cloud tex	rings	cloud opacity
//Body	Al Qilaal	Aleppo	7.00E+10	0	0	0	0	0	1	6.00E+07	4	0	2	1	1	127	116	96	127	111	82	127	116	96	0	5	255

double PrintGiant(FILE * out, char *name, char *parent, double orbit, double rot)
{ 
	int tex1, tex2;
	double radius;

	// Calculate the giant size
	radius = rand_size(cgiant_radii_min,cgiant_radii_max);
	//radius = cgiant_radii_min;

	// Gas giants take one texture from the gas giants texture and the second
	// one from the clouds texture. We are ignoring the second value and putting
	// a special black texture in the first clouds position so our pretty
	// gas giant textures are not messed up.
	tex1 = rand_int(cgassy_texture_count);
	tex2 = 0;

	fprintf(out,"\n;Body, Name, Parent, Distance, Rotation, Elevation, Orientation X, Y, Z, Y Scale");
	fprintf(out,", Body Radius, Body Type (giant),	Texture Type, Texture Map 1, Texture Map 2,");
	fprintf(out,"Red Low, Blue Low, Green Low, Red High, Green High, Blue High, ");
	fprintf(out,"Red Unk, Green Unk, Blue Unk, Cloud Texture Map, Number Rings, Cloud Opacity, end,\n");
	fprintf(out,"Body,%s,%s,%f,%f,0,1,0,0,0,%f,4,2,%d,%d,200,200,200,149,138,114,127,116,96,0,5,255,end,\n",
			name, parent,orbit*cplanet_orbit_base,rot, radius, tex1, tex2);

	return 2.0*radius;
}

double PrintMoon(FILE * out, char *name, char *parent, double orbit, double rot, double radius)
{ 
	double moon;
	int tex1, tex2, low1, low2, low3;

	// Calculate the moon max size, clamp at quarter planet, or 2 earths.
	// allows really big gas gaint moons, but littler planet moons.

	moon = radius/4.0;
	if (moon>12e6)
		moon = 12e6;
	else if (moon < 2.7e5)
		moon = 2.7e5;

	moon = rand_size(2.5e5,moon);
	//moon = cplanet_radii_min/4.0;

	// Moons mix one color texture and one surface bump map texture to 
	// get a nice cratered and broken appearence.
	tex1 = rand_int(crocky1_texture_count);
	tex2 = crocky1_texture_count + rand_int(crocky2_texture_count);
	
	low1 = rand_int(50)+100;
	low2 = rand_int(50)+100;
	low3 = rand_int(50)+100;

	fprintf(out,";Body, Name, Parent, Distance, Rotation, Elevation, Orientation X, Y, Z, Y Scale");
	fprintf(out,", Body Radius, Body Type (moon),	Texture Type, Texture Map 1, Texture Map 2,");
	fprintf(out,"Red Low, Blue Low, Green Low, Red High, Green High, Blue High, ");
	fprintf(out,"Red Unk, Green Unk, Blue Unk, Cloud Texture Map, Number Rings, Cloud Opacity, end,\n");
	// Set a cloud texture if the planet is 70% of earth or larger.

	fprintf(out, "Body,%s,%s,%f,%f,0,1,0,0,0,%f,3,1,%d,%d,%d,%d,%d,15,15,15,127,44,34,255,0,0,end,\n",
		name, parent, orbit*cmoon_orbit_base, rot, moon, tex1, tex2, low1, low2, low3);

	return 2.0*moon;
}

double PrintPlanet(FILE * out, char *name, char *parent, double orbit, double rot, int texture, int bump_map)
{ 
//Body	Qataar	Aleppo	1.00E+11	30	0	0	0	0	1	5.00E+06	3	0	1	1	1	99	46	40	120	145	14	127	44	34	255	0	0

	double radius;
	int tex1, tex2;

	// Calculate the planet size. 
	radius = rand_size(cplanet_radii_min, cplanet_radii_max);
	//radius = cplanet_radii_min;
	
	// Normally, planets take two textures from the first rocky texture group.
	// that gives lots of interesting color, but not so much surface roughness.
	if (0 == texture) {
		tex1 = rand_int(crocky1_texture_count);
		tex2 = rand_int(crocky1_texture_count);
	}else {
		// Special planets are the ones like Emerald that use unique textures
		// and bump maps. The designer sets those up uniquely.
		tex1 = texture;
		tex2 = bump_map;
	}


	// Set a cloud texture if the planet is 70% of earth or larger.

	//Output the help info for this entry.
	fprintf(out,"\n;Body, Name, Parent, Distance, Rotation, Elevation, Orientation X, Y, Z, Y Scale");
	fprintf(out,", Body Radius, Body Type (planet),	Texture Type, Texture Map 1, Texture Map 2,");
	fprintf(out,"Red Low, Blue Low, Green Low, Red High, Green High, Blue High, ");
	fprintf(out,"Red Unk, Green Unk, Blue Unk, Cloud Texture Map, Number Rings, Cloud Opacity, end,\n");


	fprintf(out, "Body,%s,%s,%f,%f,0,1,0,0,0,", 
			name, parent, orbit*cplanet_orbit_base, rot);
	fprintf(out, "%f,2,1,%d,%d,200,200,200,55,55,55,127,44,34,255,0,0,end,\n",
			radius, tex1, tex2);

	return 2.0*radius;
}

/*
	A special planet is a planet sized station wrapped around a standard planet. 

*/
void PrintSpecialPlanet(FILE * out, char *name, char *parent, double orbit, double rot, 
						double radius, int model, FILE * finiout, int count)
{ 
//Body	Qataar	Aleppo	1.00E+11	30	0	0	0	0	1	5.00E+06	3	0	1	1	1	99	46	40	120	145	14	127	44	34	255	0	0

	//double radius;
	int tex1, tex2;
	
	tex1 = 0;
	tex2 = 0;

	// Set a cloud texture if the planet is 70% of earth or larger.


	fprintf(out, "Body,%s,%s,%f,%f,0,1,0,0,0,", 
			name, parent, orbit*cplanet_orbit_base, rot);

	fprintf(out, "%f,2,1,%d,%d,200,200,200,55,55,55,127,44,34,255,0,0,end,\n",
			radius, tex1, tex2);

	fprintf(out, ";SpecialP, name, parent, distance, rotation, elevation, orientation x, y, z, station model, hab type, faction, populatin, end,\n");

	fprintf(out, "Station,%s_station,%s,%f,%f,0,1,0,0,%d,%d,%d,10,end,\n",
			name, parent, 
			orbit*cplanet_orbit_base, rot, 
			model, HT_Disused, A_Neutral );

	fprintf(finiout,"\n\n\n\n");
	fprintf(finiout,"name[%d]=\"%s_station\"\n", count, name);
	fprintf(finiout,"parent_body[%d]=\"%s\"\n", count, parent);
	fprintf(finiout,"template[%d]=%d\n", count, model);
	fprintf(finiout,"orbital_distance[%d]=%f\n",count,orbit);
	fprintf(finiout,"orbital_angle_around[%d]=%f\n",count,rot);
	fprintf(finiout,"orbital_angle_above[%d]=%f\n",count,0);
	fprintf(finiout,"type[%d]=%d\n", count, HT_Disused);
	fprintf(finiout,"faction[%d]=\"F_Empty\"\n", count);

}



/*
[starting_stations]
name[0]="Fonseka Foundation HQ"
parent_body[0]="Brentano"
orbital_distance[0]=15000000.000000
orbital_angle_around[0]=0.000000
orbital_angle_above[0]=0.000000
type[0]=45
;template[0]=17
faction[0]="Fonsenka"
defense[0]="4"
defense_type[0]="5"
*/

void PrintStation(FILE * out, char *name, char *parent, 
				  double orbit, double rot, int faction, 
				  int type, int model, FILE * finiout, int count, 
				  char * fac_name, int status, int richness)
{
	int station_type;
	int population;



	// If the station is empty, then the faction must be neutral.
	if (4 == status) {
		faction = A_Neutral;
		population = 0;
	}

	// if the station has an empty faction, it must be empty.
	if (A_Neutral == faction) {
		population = 0;
		//station_type = HT_Disused;
		station_type = type;
		status = 4;
	}else {
		population = 4;
		station_type = type;
	}

	fprintf(out, ";Station, name, parent, distance, rotation, elevation, orientation x, y, z, station model, hab type, faction, populatin, end,\n");

	fprintf(out, "Station,%s,%s,%f,%f,0,1,0,0,%d,%d,%d,%d,end,\n",
			name, parent, 
			orbit, rot, 
			model, station_type, faction, population);

	fprintf(finiout,"\n\n\n\n");
	fprintf(finiout,"name[%d]=\"%s\"\n", count, name);
	fprintf(finiout,"parent_body[%d]=\"%s\"\n", count, parent);
	fprintf(finiout,"template[%d]=%d\n", count, model);
	fprintf(finiout,"orbital_distance[%d]=%f\n",count,orbit);
	fprintf(finiout,"orbital_angle_around[%d]=%f\n",count,rot);
	fprintf(finiout,"orbital_angle_above[%d]=%f\n",count,0);
	fprintf(finiout,"type[%d]=%d\n", count, type);
	fprintf(finiout,"richness[%d]=%d\n", count, richness);

	fprintf(finiout,"faction[%d]=\"F_%s\"\n", count, fac_name);

	//fprintf(finiout,"defense[%d]=%d\n", count,HabTypeToDef(type));
	//fprintf(finiout,"defense_type[%d]=%d\n", count,HabTypeToDefType(type));
	if (0 == status){//normal
		fprintf(finiout,"status[%d]=\"Normal\"\n", count);
		//fprintf(finiout,"hidden[%d]=0\n", count);
		//fprintf(finiout,"destroyed[%d]=0\n", count);
		//fprintf(finiout,"visible[%d]=1\n", count);
		//fprintf(finiout,"build[%d]=0\n", count);
	}else if (1 == status){//destroyed
		fprintf(finiout,"status[%d]=\"Destroyed\"\n", count);
		//fprintf(finiout,"hidden[%d]=0\n", count);
		//fprintf(finiout,"destroyed[%d]=1\n", count);
		//fprintf(finiout,"visible[%d]=0\n", count);
		//fprintf(finiout,"build[%d]=0\n", count);
	}else if (2 == status){//NeverBuilt
		fprintf(finiout,"status[%d]=\"NeverBuilt\"\n", count);
		//fprintf(finiout,"hidden[%d]=0\n", count);
		//fprintf(finiout,"destroyed[%d]=0\n", count);
		//fprintf(finiout,"visible[%d]=0\n", count);
		//fprintf(finiout,"build[%d]=0\n", count);
	}else if (3 == status) {//station under construction
		fprintf(finiout,"status[%d]=\"Building\"\n", count);
		//fprintf(finiout,"hidden[%d]=0\n", count);
		//fprintf(finiout,"destroyed[%d]=0\n", count);
		//fprintf(finiout,"visible[%d]=1\n", count);
		//fprintf(finiout,"build[%d]=1\n", count);
	}else {
		fprintf(finiout,"status[%d]=\"Empty\"\n", count);
	}
}


/*
[starting_stations]
op_parent[0]="Brentano"
op_type[0]=45
op_faction[0]="Fonsenka"
*/
void PrintOperation(char *parent,
				  int type,  FILE * finiout, int count, 
				  char * fac_name)
{
	fprintf(finiout,"\n\n");

	fprintf(finiout,"op_parent[%d]=\"%s\"\n", count, parent);
	fprintf(finiout,"op_type[%d]=%d\n", count, type);
	fprintf(finiout,"op_faction[%d]=\"F_%s\"\n", count, fac_name);


}

// Failed gas giant core?
double PrintCore(FILE * out, char *name, char *parent, double orbit, double rot)
{ 
	int tex1, tex2;
	double radius;

	// Calculate the giant size
	radius = rand_size(cgiant_radii_min,cgiant_radii_max);
	//radius = cgiant_radii_min;

	tex1 = rand_int(cgassy_texture_count);
	tex2 = rand_int(cgassy_texture_count);

	fprintf(out,"\n;Body, Name, Parent, Distance, Rotation, Elevation, Orientation X, Y, Z, Y Scale");
	fprintf(out,", Body Radius, Body Type (failed core),	Texture Type, Texture Map 1, Texture Map 2,");
	fprintf(out,"Red Low, Blue Low, Green Low, Red High, Green High, Blue High, ");
	fprintf(out,"Red Unk, Green Unk, Blue Unk, Cloud Texture Map, Number Rings, Cloud Opacity, end,\n");

	fprintf(out,"\nBody,%s,%s,%f,%f,0,1,0,0,0,%f,4,2,%d,%d,200,200,200,139,148,114,127,116,96,0,5,255,end,\n",
			name, parent,orbit*cplanet_orbit_base,rot, radius, tex1, tex2);

	return 2.0 * radius;
}




void PrintStar(FILE * out, char *name, char *parent, double orbit, double rot, int magnitude)
{ 
	fprintf(out, "\n;Star, name, parent, distance, rotation, elevation, magnitude, end,\n");
	fprintf(out, "Star,%s,%s,%g,%g,0,%d,end,\n",
			name, parent, orbit, rot, magnitude);

}


void PrintBelt(FILE * out, char *name, char *parent, double orbit, double rot, double field_size)
{ 
	fprintf(out, ";Belt, name, parent, distance, rotation, elevation, field size, end,\n");

	fprintf(out, "Belt,%s,%s,%f,%f,0,%f,end,\n",
			name, parent, orbit*cplanet_orbit_base, rot, 40e6);
}

void PrintRing(FILE * out, char *name, char *parent, double orbit, double rot, double field_size)
{ 
	fprintf(out, ";Belt, name, parent, distance, rotation, elevation, field size, end,\n");

	fprintf(out, "Belt,%s,%s,%f,%f,0,%f,end,\n",
			name, parent, orbit*cmoon_orbit_base, rot, 40e6);
}

void PrintNebula(FILE * out, char *name, char *parent, double orbit, double rot, double field_size)
{ 
	fprintf(out, ";Belt, name, parent, distance, rotation, elevation, field size, end,\n");

	fprintf(out, "Belt,%s,%s,%f,%f,0,%f,end,\n",
			name, parent, orbit*cplanet_orbit_base, rot, 2.5e6);
}

void PrintCenter(FILE * out, char *name)
{ 
	fprintf(out, "\n;Center, name,end,\n");
	fprintf(out,"Center,%s,end,\n",name);
}


double rand_size(double lower, double upper)
{ 
	int temp;
	double value;

	temp = rand();

	value = (temp*(upper-lower))/(double)RAND_MAX;
	value += lower;

	return value;
}

int rand_int( int upper)
{
	int temp;

	temp = rand();
	temp = (temp*upper)/RAND_MAX;

	return temp;
}

int NameToStatus(char * name)

{ 
	if (0==strcmp(name,"ok")){return 0;
	}else if (0==strcmp(name,"destroyed")){return 1;
	}else if (0==strcmp(name,"never")){return 2;
	}else if (0==strcmp(name,"building")){return 3;
	}else if (0==strcmp(name,"empty")){return 4;
	}
	fprintf(error_log,"Error: invalid station status n->s: %s\n",name);
	return 0;
	
}


int NameToOpType(char * name)
{ 
	if (0==strcmp(name,"Piratehq")) { return 123;
	}else if (0==strcmp(name,"Embezzle")) { return 124;
	}else if (0==strcmp(name,"Viceden")) { return 125; 
	}else if (0==strcmp(name,"Hacker")) { return 126; 
	}else if (0==strcmp(name,"Cyber")) { return 127; 
	}else if (0==strcmp(name,"Protection")) { return 128;
	}else if (0==strcmp(name,"Fleetattack")) { return 129;
	}else if (0==strcmp(name,"Fleetdefense")) { return 130;
	}else if (0==strcmp(name,"Spyattack")) { return 131;
	}else if (0==strcmp(name,"Spydefense")) { return 132;
	}else if (0==strcmp(name,"Spyneutral")) { return 133;
	}else if (0==strcmp(name,"Invasion")) { return 134;
	}else if (0==strcmp(name,"Rebelsupport")) { return 135;
	}else if (0==strcmp(name,"Blackmarket")) { return 136;
	}else if (0==strcmp(name,"Rebelhq")) { return 137;
	}else if (0==strcmp(name,"CustomsToll")) { return 139;
	}else if (0==strcmp(name,"PirateToll")) { return 140;
	}

	fprintf(error_log,"Error: invalid operation type n->s: %s\n",name);
	return 0;
}

int NameToFaction(char * name)
{ 

	int i;

	for (i=0;i<faction_entries;++i)
	{
		if (strcmp(name, faction_table[i].name) == 0){
			return faction_table[i].faction_enum;
		}
	}

	// This in an invalid value, return faction 0 (neutral)
	fprintf(error_log,"Error: invalid faction name n->s:%s:\n",name);
	return 0;
}
/*
int NameToFaction(char * name)
{ 
	
//Governments
if (0==strcmp(name,"AllianceNavy")) { return A_Military;
}else if (0==strcmp(name,"ImperialNavy")) { return A_Government; 
}else if (0==strcmp(name,"RoyalGuard")) { return A_MAASCorporation; 
}else if (0==strcmp(name,"YezhidNavy")) { return A_KIMOShipping; 
}else if (0==strcmp(name,"CDF")) { return A_Police; 
}else if (0==strcmp(name,"CMCSS")) { return A_AdvancedSecurityCorp;

//Crime houses
}else if (0==strcmp(name,"Lindevaal")) { return A_Underworld;
}else if (0==strcmp(name,"Pimental")) { return A_CarvaCartel;
}else if (0==strcmp(name,"Gargoyles")) { return A_Marauders;
}else if (0==strcmp(name,"TakananRaiders")) { return A_Angels;
}else if (0==strcmp(name,"Droznic")) { return A_TheOman;
}else if (0==strcmp(name,"GoldenLotus")) { return A_DesterCorporation;
}else if (0==strcmp(name,"Forty")) { return A_Infonet;

//Independent peoples
}else if (0==strcmp(name,"Aikenites")) { return A_WordsworthTechnology;
}else if (0==strcmp(name,"Transients")) { return A_Transient;
}else if (0==strcmp(name,"Junkers")) { return A_Junkers;
}else if (0==strcmp(name,"EmeraldCitizens")) { return A_TheThirdWay;
}else if (0==strcmp(name,"LeungCitizens")) { return A_AshantiInvestment;
}else if (0==strcmp(name,"SultanateCitizens")) { return A_ChonBodifule;
}else if (0==strcmp(name,"CaliphateCitizens")) { return A_HibatshPMC;
}else if (0==strcmp(name,"CorlissCitizens")) { return A_LowOrbitRecovery;

// Independent criminals
}else if (0==strcmp(name,"Scavengers")) { return A_Kong;
}else if (0==strcmp(name,"Uncleansed")) { return A_League;
}else if (0==strcmp(name,"Faceless")) { return A_MCA;

// Mega Corporations
}else if (0==strcmp(name,"Azran")) { return A_NOMEXCorporation;
}else if (0==strcmp(name,"Chavez")) { return A_Society;
}else if (0==strcmp(name,"CMCMining")) { return A_HeliosMining;
}else if (0==strcmp(name,"Corliss")) { return A_CrosspointMinerals;
}else if (0==strcmp(name,"DAMN")) { return A_Exile;
}else if (0==strcmp(name,"EtCom")) { return A_Network54;
}else if (0==strcmp(name,"Grinnel")) { return A_TrimannShipping;
}else if (0==strcmp(name,"ImperialMining")) { return A_VonShellingIndustries;
}else if (0==strcmp(name,"Kronholm")) { return A_MegalithCorp;
}else if (0==strcmp(name,"Lomax")) { return A_LOMAXTechnologies;
}else if (0==strcmp(name,"Markus")) { return A_StellarNet;
}else if (0==strcmp(name,"Mesa")) { return A_OrionProducts;
}else if (0==strcmp(name,"NSOLaplace")) { return A_NSOLaplace;
}else if (0==strcmp(name,"Saffron")) { return A_RhondusGasMining;
}else if (0==strcmp(name,"StellarParamed")) { return A_HighlifeProducts;
}else if (0==strcmp(name,"UCP")) { return A_UniversalConsumerProducts;
}else if (0==strcmp(name,"Jardin")) { return A_JardinTerraforming;

// Rebel groups that are working to form new governments.
}else if (0==strcmp(name,"Fonseka")) { return A_WhindWeaponsSystems;
}else if (0==strcmp(name,"Eastern")) { return A_CoventryEngineeringResearch;

// Extra and unused not entered.

// Mercenaries
}else if (0==strcmp(name,"Golligers")) { return A_Stepson;
}else if (0==strcmp(name,"Dragons")) { return A_NumikoProducts;
}else if (0==strcmp(name,"Angels")) { return A_LOMAXEngines;
}else if (0==strcmp(name,"Fist")) { return A_NetcomSA;

// Special Factions
}else if (0==strcmp(name,"Brethren")) { return A_DatagonTechnologies;
}else if (0==strcmp(name,"Machines")) { return A_MicoriaCommunications;
}else if (0==strcmp(name,"Empty")) { return A_Neutral;
}

	fprintf(error_log,"Error: invalid faction name n->s: %s\n",name);
	return A_Neutral; // The empty faction.
}

*/
int NameToModel(char * name)
{ 

	int i;

	for (i=0;i<model_entries;++i)
	{
		if (strcmp(name, model_table[i].name) == 0){
			return model_table[i].model;
		}
	}

	// This in an invalid value, and should lead to a station
	// that is clearly not correct.
	fprintf(error_log,"Error: invalid station model name n->s:%s:\n",name);
	return 0;
}


/*
int NameToStation(char * name)
{ 
	if (0==strcmp(name,"WaterMine")){return MT_SmallWaterMine;
	}else if (0==strcmp(name,"OrganicsMine")){return MT_SmallOrganicsMine;
	}else if (0==strcmp(name,"InorganicsMine")){return MT_SmallInorganicsMine;
	}else if (0==strcmp(name,"BiomassMine")){return MT_SmallBiomassMine;
	}else if (0==strcmp(name,"CommonMetalsMine")){return MT_SmallCommonMetalsMine;
	}else if (0==strcmp(name,"RareMetalsMine")){return MT_SmallRareMetalsMine;
	}else if (0==strcmp(name,"ExoticMetalsMine")){return MT_SmallExoticMetalsMine;
	}else if (0==strcmp(name,"RadioactivesMine")){return MT_SmallRadioactivesMine;
	}else if (0==strcmp(name,"FusionableGasesMine")){return MT_SmallFusionableGassesMine;
	}else if (0==strcmp(name,"NeutroniumMine")){return MT_SmallNeutroniumMine;
        
	}else if (0==strcmp(name,"LargeWaterMine")){return MT_LargeWaterMine;
	}else if (0==strcmp(name,"LargeOrganicsMine")){return MT_LargeOrganicsMine;
	}else if (0==strcmp(name,"LargeInorganicsMine")){return MT_LargeInorganicsMine;
	}else if (0==strcmp(name,"LargeBiomassMine")){return MT_LargeBiomassMine;
	}else if (0==strcmp(name,"LargeCommonMetalsMine")){return MT_LargeCommonMetalsMine;
	}else if (0==strcmp(name,"LargeRareMetalsMine")){return MT_LargeRareMetalsMine;
	}else if (0==strcmp(name,"LargeExoticMetalsMine")){return MT_LargeExoticMetalsMine;
	}else if (0==strcmp(name,"LargeRadioactivesMine")){return MT_LargeRadioactivesMine;
	}else if (0==strcmp(name,"LargeFusionableGasesMine")){return MT_LargeFusionableGassesMine;
	}else if (0==strcmp(name,"LargeNeutroniumMine")){return MT_LargeNeutroniumMine;

	}else if (0==strcmp(name,"WaterProc")){return MT_ProcessingPlant;
	}else if (0==strcmp(name,"OrganicsProc")){return MT_ProcessingPlant;
	}else if (0==strcmp(name,"InorganicsProc")){return MT_ProcessingPlant;
	}else if (0==strcmp(name,"BiomassProc")){return MT_ProcessingPlant;
	}else if (0==strcmp(name,"CommonMetalsProc")){return MT_ProcessingPlant;
	}else if (0==strcmp(name,"RareMetalsProc")){return MT_CurvedStation;
	}else if (0==strcmp(name,"ExoticMetalsProc")){return MT_CurvedStation;
	}else if (0==strcmp(name,"RadioactivesProc")){return MT_CurvedStation;
	}else if (0==strcmp(name,"FusionableGasesProc")){return MT_CurvedStation;
	}else if (0==strcmp(name,"NeutroniumProc")){return MT_CurvedStation;
        

	}else if (0==strcmp(name,"HeavyMan")){return 5;
	}else if (0==strcmp(name,"BiologicalMan")){return MT_ManufacturePlant;
	}else if (0==strcmp(name,"WetwareMan")){return MT_ManufacturePlant;
	}else if (0==strcmp(name,"HiTechMan")){return MT_ManufacturePlant;
	}else if (0==strcmp(name,"ElectronicsMan")){return MT_ManufacturePlant;
	}else if (0==strcmp(name,"WeaponsMan")){return MT_ManufacturePlant;
	}else if (0==strcmp(name,"PharmaceuticalsMan")){return MT_ManufacturePlant;
	}else if (0==strcmp(name,"PlasticsMan")){return MT_ManufacturePlant;
	}else if (0==strcmp(name,"FusionReactorsMan")){return MT_ManufacturePlant;
	}else if (0==strcmp(name,"EnergyCellsMan")){return MT_ManufacturePlant;
	}else if (0==strcmp(name,"StationFabricationMan")){return MT_ManufacturePlant;
	}else if (0==strcmp(name,"LuxuriesMan")){return MT_ManufacturePlant;
        
	}else if (0==strcmp(name,"BioBomber")){return MT_Biobomber;
        
	}else if (0==strcmp(name,"Shipyard")){return MT_ShipYardStation;        
	}else if (0==strcmp(name,"Waystation")){return MT_ShipYardStation;

	}else if (0==strcmp(name,"Research")){return MT_CurvedStation;
	}else if (0==strcmp(name,"MedicalResearch")){return MT_ResearchStation;
	}else if (0==strcmp(name,"BlackResearch")){return MT_ResearchStation;
	}else if (0==strcmp(name,"SensitiveResearch")){return MT_ResearchStation;

	}else if (0==strcmp(name,"CentralHQ")){return MT_CorporateHQ;
        
	}else if (0==strcmp(name,"AgSettlement")){return MT_OrbitalGarden;
	}else if (0==strcmp(name,"Resort")){return MT_OrbitalGarden;
	}else if (0==strcmp(name,"LuxuryResort")){return MT_OrbitalGarden;
        
	}else if (0==strcmp(name,"Medical")){return MT_RichSettlement;

	}else if (0==strcmp(name,"SecurityStation")){return MT_SecurityStation;
	}else if (0==strcmp(name,"Fortress")){return MT_AsteroidPlain;
        
	}else if (0==strcmp(name,"MercenaryBase")){return MT_MarauderBase;
        
	}else if (0==strcmp(name,"Warehousing")){return MT_MiningStation;
	}else if (0==strcmp(name,"Entertainment")){return MT_CasinoStation;
        
	}else if (0==strcmp(name,"Settlement")){return MT_RichSettlement;
	}else if (0==strcmp(name,"PoliceBase")){return MT_SecurityStation;


	}else if (0==strcmp(name,"DefenseDock")){return MT_NavalBaseStation;
        
	}else if (0==strcmp(name,"NavalAcademy")){return MT_ResearchStation;
	}else if (0==strcmp(name,"NavalTraining")){return MT_ResearchStation;

	// Smallest government station
	}else if (0==strcmp(name,"Outpost")){return MT_PirateStation;
	}else if (0==strcmp(name,"MarineBarracks")){return MT_ResearchStation;
        
	}else if (0==strcmp(name,"NavalResearch")){return MT_ResearchStation;
        
	}else if (0==strcmp(name,"SupplyDepot")){return MT_NavalBaseStation;


        // Wierd, because using winged base as FTL instead of police.
	}else if (0==strcmp(name,"FTLArray")){return MT_PoliceStation;

	}else if (0==strcmp(name,"STLTran")){return MT_Communications;

	// System Senator
	}else if (0==strcmp(name,"SystemAdmin")){return MT_AdminStation;
	// National government
	}else if (0==strcmp(name,"ClusterAdmin")){return MT_AdminStation;
	// Area governor
	}else if (0==strcmp(name,"RegionAdmin")){return MT_AdminStation;

	}else if (0==strcmp(name,"University")){return MT_ResearchStation;

	}else if (0==strcmp(name,"PirateBase")){return MT_PirateStation;

	// just an asteroid, where operations can be based.
	}else if (0==strcmp(name,"PirateCove")){return MT_AsteroidPlain;

	}else if (0==strcmp(name,"PirateOutpost")){return MT_SmallPirate;

	}else if (0==strcmp(name,"Casino")){return MT_CasinoStation;

	}else if (0==strcmp(name,"Religious")){return MT_OrbitalGarden;


	}else if (0==strcmp(name,"Habitat")){return MT_RichSettlement;

	}else if (0==strcmp(name,"BoxTown")){return MT_PoorSettlement;

	}else if (0==strcmp(name,"JumpAccel")){return MT_JumpAccel;
        
	}else if (0==strcmp(name,"Transfer")){return MT_Beanstalk;
	}else if (0==strcmp(name,"Beanstalk")){return MT_Beanstalk;
	}

	fprintf(error_log,"Error: invalid station type n->s: %s\n",name);
	return MT_HavenStation;
}
*/
int NameToStationType(char * name)
{ 

	int i;

	for (i=0;i<habitat_entries;++i)
	{
		if (strcmp(name, habitat_type_table[i].name) == 0){
			return habitat_type_table[i].habitat_enum;
		}
	}

	// This in an invalid value, and should lead to a station
	// that is clearly not correct.
	fprintf(error_log,"Error: invalid habitat type name n->s:%s:\n",name);
	return 0;
}

/*
int NameToStationType(char * name)
{ 
  if ( 0==strcmp(name,"HT_Invalid" )) {
      return HT_Invalid; 
   }
   if ( 0==strcmp(name,"HT_Disused" )) {
      return HT_Disused; 
   }
   if ( 0==strcmp(name,"HT_WaterMine" )) {
      return HT_WaterMine; 
   }
   if ( 0==strcmp(name,"HT_OrganicsMine" )) {
      return HT_OrganicsMine; 
   }
   if ( 0==strcmp(name,"HT_InorganicsMine" )) {
      return HT_InorganicsMine; 
   }
   if ( 0==strcmp(name,"HT_BiomassMine" )) {
      return HT_BiomassMine; 
   }
   if ( 0==strcmp(name,"HT_CommonMetalsMine" )) {
      return HT_CommonMetalsMine; 
   }
   if ( 0==strcmp(name,"HT_RareMetalsMine" )) {
      return HT_RareMetalsMine; 
   }
   if ( 0==strcmp(name,"HT_ExoticMetalsMine" )) {
      return HT_ExoticMetalsMine; 
   }
   if ( 0==strcmp(name,"HT_RadioactivesMine" )) {
      return HT_RadioactivesMine; 
   }
   if ( 0==strcmp(name,"HT_FusionableGasesMine" )) {
      return HT_FusionableGasesMine; 
   }
   if ( 0==strcmp(name,"HT_WaterProcessingPlant" )) {
      return HT_WaterProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_OrganicsProcessingPlant" )) {
      return HT_OrganicsProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_InorganicsProcessingPlant" )) {
      return HT_InorganicsProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_BiomassProcessingPlant" )) {
      return HT_BiomassProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_CommonMetalsProcessingPlant" )) {
      return HT_CommonMetalsProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_RareMetalsProcessingPlant" )) {
      return HT_RareMetalsProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_ExoticMetalsProcessingPlant" )) {
      return HT_ExoticMetalsProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_RadioactivesProcessingPlant" )) {
      return HT_RadioactivesProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_FusionableGasesProcessingPlant" )) {
      return HT_FusionableGasesProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_NeutroniumProcessingPlant" )) {
      return HT_NeutroniumProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_Shipyard" )) {
      return HT_Shipyard; 
   }
   if ( 0==strcmp(name,"HT_HeavyManufacturingPlant" )) {
      return HT_HeavyManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_BiologicalManufacturingPlant" )) {
      return HT_BiologicalManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_WetwareManufacturingPlant" )) {
      return HT_WetwareManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_HiTechManufacturingPlant" )) {
      return HT_HiTechManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_ElectronicsManufacturingPlant" )) {
      return HT_ElectronicsManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_WeaponsManufacturingPlant" )) {
      return HT_WeaponsManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_PharmaceuticalsManufacturingPlant" )) {
      return HT_PharmaceuticalsManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_PlasticsManufacturingPlant" )) {
      return HT_PlasticsManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_FusionReactorsManufacturingPlant" )) {
      return HT_FusionReactorsManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_EnergyCellsManufacturingPlant" )) {
      return HT_EnergyCellsManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_StationFabricationManufacturingPlant" )) {
      return HT_StationFabricationManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_LuxuriesManufacturingPlant" )) {
      return HT_LuxuriesManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_TerraformingStation" )) {
      return HT_TerraformingStation; 
   }
   if ( 0==strcmp(name,"HT_BioBomber" )) {
      return HT_BioBomber; 
   }
   if ( 0==strcmp(name,"HT_Waystation" )) {
      return HT_Waystation; 
   }
   if ( 0==strcmp(name,"HT_RepairStation" )) {
      return HT_RepairStation; 
   }
   if ( 0==strcmp(name,"HT_OreTransferStation" )) {
      return HT_OreTransferStation; 
   }
   if ( 0==strcmp(name,"HT_ResearchAndDevelopmentLab" )) {
      return HT_ResearchAndDevelopmentLab; 
   }
   if ( 0==strcmp(name,"HT_ResearchStation" )) {
      return HT_ResearchStation; 
   }
   if ( 0==strcmp(name,"HT_MedicalResearchCentre" )) {
      return HT_MedicalResearchCentre; 
   }
   if ( 0==strcmp(name,"HT_BlackBudgetResearchStation" )) {
      return HT_BlackBudgetResearchStation; 
   }
   if ( 0==strcmp(name,"HT_SensitiveResearchStation" )) {
      return HT_SensitiveResearchStation; 
   }
   if ( 0==strcmp(name,"HT_FinancialCentre" )) {
      return HT_FinancialCentre; 
   }
   if ( 0==strcmp(name,"HT_RegionalHQ" )) {
      return HT_RegionalHQ; 
   }
   if ( 0==strcmp(name,"HT_Villa" )) {
      return HT_Villa; 
   }
   if ( 0==strcmp(name,"HT_CentralHQ" )) {
      return HT_CentralHQ; 
   }
   if ( 0==strcmp(name,"HT_AgriculturalSettlement" )) {
      return HT_AgriculturalSettlement; 
   }
   if ( 0==strcmp(name,"HT_Resort" )) {
      return HT_Resort; 
   }
   if ( 0==strcmp(name,"HT_LuxuryResort" )) {
      return HT_LuxuryResort; 
   }
   if ( 0==strcmp(name,"HT_MedicalFacility" )) {
      return HT_MedicalFacility; 
   }
   if ( 0==strcmp(name,"HT_LeisureComplex" )) {
      return HT_LeisureComplex; 
   }
   if ( 0==strcmp(name,"HT_NeutroniumMine" )) {
      return HT_NeutroniumMine; 
   }
   if ( 0==strcmp(name,"HT_SecurityStation" )) {
      return HT_SecurityStation; 
   }
   if ( 0==strcmp(name,"HT_Fortress" )) {
      return HT_Fortress; 
   }
   if ( 0==strcmp(name,"HT_HighSecurityPrison" )) {
      return HT_HighSecurityPrison; 
   }
   if ( 0==strcmp(name,"HT_LowSecurityPrison" )) {
      return HT_LowSecurityPrison; 
   }
   if ( 0==strcmp(name,"HT_HardLabourPrison" )) {
      return HT_HardLabourPrison; 
   }
   if ( 0==strcmp(name,"HT_Homestead" )) {
      return HT_Homestead; 
   }
   if ( 0==strcmp(name,"HT_MercenaryBase" )) {
      return HT_MercenaryBase; 
   }
   if ( 0==strcmp(name,"HT_TradingPost" )) {
      return HT_TradingPost; 
   }
   if ( 0==strcmp(name,"HT_Warehousing" )) {
      return HT_Warehousing; 
   }
   if ( 0==strcmp(name,"HT_BlackMarket" )) {
      return HT_BlackMarket; 
   }
   if ( 0==strcmp(name,"HT_DryDock" )) {
      return HT_DryDock; 
   }
   if ( 0==strcmp(name,"HT_DockingStation" )) {
      return HT_DockingStation; 
   }
   if ( 0==strcmp(name,"HT_EntertainmentStation" )) {
      return HT_EntertainmentStation; 
   }
   if ( 0==strcmp(name,"HT_Settlement" )) {
      return HT_Settlement; 
   }
   if ( 0==strcmp(name,"HT_PoliceBase" )) {
      return HT_PoliceBase; 
   }
   if ( 0==strcmp(name,"HT_PoliceOutpost" )) {
      return HT_PoliceOutpost; 
   }
   if ( 0==strcmp(name,"HT_SystemDefenceStation" )) {
      return HT_SystemDefenceStation; 
   }
   if ( 0==strcmp(name,"HT_SystemDefenceDock" )) {
      return HT_SystemDefenceDock; 
   }
   if ( 0==strcmp(name,"HT_NavalAcademy" )) {
      return HT_NavalAcademy; 
   }
   if ( 0==strcmp(name,"HT_NavalTrainingBase" )) {
      return HT_NavalTrainingBase; 
   }
   if ( 0==strcmp(name,"HT_Outpost" )) {
      return HT_Outpost; 
   }
   if ( 0==strcmp(name,"HT_Base" )) {
      return HT_Base; 
   }
   if ( 0==strcmp(name,"HT_RepairDock" )) {
      return HT_RepairDock; 
   }
   if ( 0==strcmp(name,"HT_MarineBarracks" )) {
      return HT_MarineBarracks; 
   }
   if ( 0==strcmp(name,"HT_PerimeterDefences" )) {
      return HT_PerimeterDefences; 
   }
   if ( 0==strcmp(name,"HT_NavalTestingSite" )) {
      return HT_NavalTestingSite; 
   }
   if ( 0==strcmp(name,"HT_NavalResearchFacility" )) {
      return HT_NavalResearchFacility; 
   }
   if ( 0==strcmp(name,"HT_JumpFortress" )) {
      return HT_JumpFortress; 
   }
   if ( 0==strcmp(name,"HT_SupplyDepot" )) {
      return HT_SupplyDepot; 
   }
   if ( 0==strcmp(name,"HT_DefenceStation" )) {
      return HT_DefenceStation; 
   }
   if ( 0==strcmp(name,"HT_STCPost" )) {
      return HT_STCPost; 
   }
   if ( 0==strcmp(name,"HT_STCHQ" )) {
      return HT_STCHQ; 
   }
   if ( 0==strcmp(name,"HT_FTLArray" )) {
      return HT_FTLArray; 
   }
   if ( 0==strcmp(name,"HT_FTLInterchange" )) {
      return HT_FTLInterchange; 
   }
   if ( 0==strcmp(name,"HT_STLTranceiver" )) {
      return HT_STLTranceiver; 
   }
   if ( 0==strcmp(name,"HT_STLInterchange" )) {
      return HT_STLInterchange; 
   }
   if ( 0==strcmp(name,"HT_PlanetaryAdministration" )) {
      return HT_PlanetaryAdministration; 
   }
   if ( 0==strcmp(name,"HT_SystemAdministration" )) {
      return HT_SystemAdministration; 
   }
   if ( 0==strcmp(name,"HT_ClusterAdministration" )) {
      return HT_ClusterAdministration; 
   }
   if ( 0==strcmp(name,"HT_RegionalDepartment" )) {
      return HT_RegionalDepartment; 
   }
   if ( 0==strcmp(name,"HT_University" )) {
      return HT_University; 
   }
   if ( 0==strcmp(name,"HT_Ark" )) {
      return HT_Ark; 
   }
   if ( 0==strcmp(name,"HT_Garden" )) {
      return HT_Garden; 
   }
   if ( 0==strcmp(name,"HT_Asylum" )) {
      return HT_Asylum; 
   }
   if ( 0==strcmp(name,"HT_Hospice" )) {
      return HT_Hospice; 
   }
   if ( 0==strcmp(name,"HT_PirateBase" )) {
      return HT_PirateBase; 
   }
   if ( 0==strcmp(name,"HT_PirateCove" )) {
      return HT_PirateCove; 
   }
   if ( 0==strcmp(name,"HT_PirateOutpost" )) {
      return HT_PirateOutpost; 
   }
   if ( 0==strcmp(name,"HT_GangsterHideout" )) {
      return HT_GangsterHideout; 
   }
   if ( 0==strcmp(name,"HT_ViceDen" )) {
      return HT_ViceDen; 
   }
   if ( 0==strcmp(name,"HT_Casino" )) {
      return HT_Casino; 
   }
   if ( 0==strcmp(name,"HT_CollectiveSettlement" )) {
      return HT_CollectiveSettlement; 
   }
   if ( 0==strcmp(name,"HT_Hermitage" )) {
      return HT_Hermitage; 
   }
   if ( 0==strcmp(name,"HT_ReligiousCentre" )) {
      return HT_ReligiousCentre; 
   }
   if ( 0==strcmp(name,"HT_MadScientistLab" )) {
      return HT_MadScientistLab; 
   }
   if ( 0==strcmp(name,"HT_Hideout" )) {
      return HT_Hideout; 
   }
   if ( 0==strcmp(name,"HT_Habitat" )) {
      return HT_Habitat; 
   }
   if ( 0==strcmp(name,"HT_Junkyard" )) {
      return HT_Junkyard; 
   }
   if ( 0==strcmp(name,"HT_BoxTown" )) {
      return HT_BoxTown; 
   }
   if ( 0==strcmp(name,"HT_AsteroidSculptures" )) {
      return HT_AsteroidSculptures; 
   }
   if ( 0==strcmp(name,"HT_PlayerBase" )) {
      return HT_PlayerBase; 
   }
   if ( 0==strcmp(name,"HT_GunstarArray" )) {
      return HT_GunstarArray; 
   }
   if ( 0==strcmp(name,"HT_JumpAccelerator" )) {
      return HT_JumpAccelerator; 
   }
   if ( 0==strcmp(name,"HT_HoffersGap" )) {
      return HT_HoffersGap; 
   }
   if ( 0==strcmp(name,"HT_HoffersHeel" )) {
      return HT_HoffersHeel; 
   }
   if ( 0==strcmp(name,"HT_Beanstalk" )) {
      return HT_Beanstalk; 
   }
   if ( 0==strcmp(name,"HT_TransferStation" )) {
      return HT_TransferStation; 
   }

fprintf(error_log,"Error: invalid station name n->t:%s:\n",name);
	return 116;
}
*/

// Returns 0 if the station type is not supported by Torn Stars
// MetaGame.
int SupportedStation(char * name, char * station_name)
{ 

   if ( 0==strcmp(name,"HT_WaterMine" )) {
      return HT_WaterMine; 
   }
   if ( 0==strcmp(name,"HT_OrganicsMine" )) {
      return HT_OrganicsMine; 
   }
   if ( 0==strcmp(name,"HT_InorganicsMine" )) {
      return HT_InorganicsMine; 
   }
   if ( 0==strcmp(name,"HT_BiomassMine" )) {
      return HT_BiomassMine; 
   }
   if ( 0==strcmp(name,"HT_CommonMetalsMine" )) {
      return HT_CommonMetalsMine; 
   }
   if ( 0==strcmp(name,"HT_RareMetalsMine" )) {
      return HT_RareMetalsMine; 
   }
   if ( 0==strcmp(name,"HT_ExoticMetalsMine" )) {
      return HT_ExoticMetalsMine; 
   }
   if ( 0==strcmp(name,"HT_RadioactivesMine" )) {
      return HT_RadioactivesMine; 
   }
   if ( 0==strcmp(name,"HT_FusionableGasesMine" )) {
      return HT_FusionableGasesMine; 
   }
   if ( 0==strcmp(name,"HT_WaterProcessingPlant" )) {
      return HT_WaterProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_OrganicsProcessingPlant" )) {
      return HT_OrganicsProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_InorganicsProcessingPlant" )) {
      return HT_InorganicsProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_BiomassProcessingPlant" )) {
      return HT_BiomassProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_CommonMetalsProcessingPlant" )) {
      return HT_CommonMetalsProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_RareMetalsProcessingPlant" )) {
      return HT_RareMetalsProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_ExoticMetalsProcessingPlant" )) {
      return HT_ExoticMetalsProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_RadioactivesProcessingPlant" )) {
      return HT_RadioactivesProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_FusionableGasesProcessingPlant" )) {
      return HT_FusionableGasesProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_NeutroniumProcessingPlant" )) {
      return HT_NeutroniumProcessingPlant; 
   }
   if ( 0==strcmp(name,"HT_Shipyard" )) {
      return HT_Shipyard; 
   }
   if ( 0==strcmp(name,"HT_HeavyManufacturingPlant" )) {
      return HT_HeavyManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_BiologicalManufacturingPlant" )) {
      return HT_BiologicalManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_WetwareManufacturingPlant" )) {
      return HT_WetwareManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_HiTechManufacturingPlant" )) {
      return HT_HiTechManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_ElectronicsManufacturingPlant" )) {
      return HT_ElectronicsManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_WeaponsManufacturingPlant" )) {
      return HT_WeaponsManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_PharmaceuticalsManufacturingPlant" )) {
      return HT_PharmaceuticalsManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_PlasticsManufacturingPlant" )) {
      return HT_PlasticsManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_FusionReactorsManufacturingPlant" )) {
      return HT_FusionReactorsManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_EnergyCellsManufacturingPlant" )) {
      return HT_EnergyCellsManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_StationFabricationManufacturingPlant" )) {
      return HT_StationFabricationManufacturingPlant; 
   }
   if ( 0==strcmp(name,"HT_LuxuriesManufacturingPlant" )) {
      return HT_LuxuriesManufacturingPlant; 
   }

   if ( 0==strcmp(name,"HT_Waystation" )) {
      return HT_Waystation; 
   }

   if ( 0==strcmp(name,"HT_ResearchStation" )) {
      return HT_ResearchStation; 
   }

   if ( 0==strcmp(name,"HT_BlackBudgetResearchStation" )) {
      return HT_BlackBudgetResearchStation; 
   }

   if ( 0==strcmp(name,"HT_CentralHQ" )) {
      return HT_CentralHQ; 
   }
   if ( 0==strcmp(name,"HT_AgriculturalSettlement" )) {
      return HT_AgriculturalSettlement; 
   }
   if ( 0==strcmp(name,"HT_Resort" )) {
      return HT_Resort; 
   }

   if ( 0==strcmp(name,"HT_MedicalFacility" )) {
      return HT_MedicalFacility; 
   }

   if ( 0==strcmp(name,"HT_NeutroniumMine" )) {
      return HT_NeutroniumMine; 
   }
   if ( 0==strcmp(name,"HT_SecurityStation" )) {
      return HT_SecurityStation; 
   }
   if ( 0==strcmp(name,"HT_Fortress" )) {
      return HT_Fortress; 
   }

   if ( 0==strcmp(name,"HT_MercenaryBase" )) {
      return HT_MercenaryBase; 
   }

   if ( 0==strcmp(name,"HT_Warehousing" )) {
      return HT_Warehousing; 
   }
   if ( 0==strcmp(name,"HT_BlackMarket" )) {
      return HT_BlackMarket; 
   }

   if ( 0==strcmp(name,"HT_EntertainmentStation" )) {
      return HT_EntertainmentStation; 
   }
   if ( 0==strcmp(name,"HT_Settlement" )) {
      return HT_Settlement; 
   }
   if ( 0==strcmp(name,"HT_PoliceBase" )) {
      return HT_PoliceBase; 
   }

   if ( 0==strcmp(name,"HT_SystemDefenceDock" )) {
      return HT_SystemDefenceDock; 
   }

   if ( 0==strcmp(name,"HT_Outpost" )) {
      return HT_Outpost; 
   }


   if ( 0==strcmp(name,"HT_FTLArray" )) {
      return HT_FTLArray; 
   }

   if ( 0==strcmp(name,"HT_SystemAdministration" )) {
      return HT_SystemAdministration; 
   }
   if ( 0==strcmp(name,"HT_ClusterAdministration" )) {
      return HT_ClusterAdministration; 
   }
   if ( 0==strcmp(name,"HT_RegionalDepartment" )) {
      return HT_RegionalDepartment; 
   }

   if ( 0==strcmp(name,"HT_PirateBase" )) {
      return HT_PirateBase; 
   }
   if ( 0==strcmp(name,"HT_PirateCove" )) {
      return HT_PirateCove; 
   }
   if ( 0==strcmp(name,"HT_PirateOutpost" )) {
      return HT_PirateOutpost; 
   }
   if ( 0==strcmp(name,"HT_GangsterHideout" )) {
      return HT_GangsterHideout; 
   }

   if ( 0==strcmp(name,"HT_Casino" )) {
      return HT_Casino; 
   }

   if ( 0==strcmp(name,"HT_Hideout" )) {
      return HT_Hideout; 
   }
   if ( 0==strcmp(name,"HT_Habitat" )) {
      return HT_Habitat; 
   }

   if ( 0==strcmp(name,"HT_Beanstalk" )) {
      return HT_Beanstalk; 
   }
   if ( 0==strcmp(name,"HT_TransferStation" )) {
      return HT_TransferStation; 
   }

   if ( 0==strcmp(name,"HT_OreTransferStation" )) {
      return HT_OreTransferStation; 
   }

   fprintf(error_log,"Warning: Unsupported station type %s :%s:\n",station_name, name);
	return 0;
}



/*
int NameToStarType(char * name)

{ 
	if (0==strcmp(name,"ok")){return 0;
	}else if (0==strcmp(name,"destroyed")){return 1;
	}else if (0==strcmp(name,"never")){return 2;
	}else if (0==strcmp(name,"building")){return 3;
	}else if (0==strcmp(name,"empty")){return 4;
	}
	fprintf(error_log,"Error: invalid station status n->s: %s\n",name);
	return 0;
	
}
*/


int HabTypeToDef(int type)
{
	// one fighter wing
	int defense = 4;

	switch (type){
	case 54:
	case 87:
	case 101:
	case 102:
	case 68:
	case 40:
	case 41:
	case 74:
		// pair of patcoms
		defense = 2;
		break;
	case 55:
	case 60:
	case 71:
	case 42:
	case 43:
		// full wing of heavies
		defense = 4;
		break;
	}

	return defense;
}


int HabTypeToDefType(int type)
{
	// fighters by default
	int defense = 5;

	switch (type){
	case 54:
	case 87:
	case 101:
	case 102:
	case 68:
	case 40:
	case 41:
	case 74:
		// light combat stuff
		defense = 6;
		break;
	case 55:
	case 60:
	case 71:
	case 42:
	case 43:
		// heavy navy stuff
		defense = 7;
		break;
	}

	return defense;
}

void clear_table ()
{
	int i;

	for (i=0;i<256;++i)
	{
		model_table[i].name[0]=0;
		model_table[i].model=0;
	}
}
