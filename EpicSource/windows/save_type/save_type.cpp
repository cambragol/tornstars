// save_type.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include "MapEnumerations.h"


void ParseName(char *name);

double PrintGiant(FILE * out, char *name, char *parent, double orbit, double rot);
double PrintMoon(FILE * out, char *name, char *parent, double orbit, double rot, double radius);
double PrintPlanet(FILE * out, char *name, char *parent, double orbit, double rot, int texture, int bump_map);
void PrintSpecialPlanet(FILE * out, char *name, char *parent, double orbit, double rot, 
						double radius, int model, FILE * finiout, int count);

void PrintStation(FILE * out, char *name, char *parent, 
				  double orbit, double rot, int faction, 
				  int type, int model, FILE * finiout, int count, 
				  char * fac_name, int status);

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
int NameToStationType(char * name);
int NameToStatus(char * name);

int NameToOpType(char * name);

int HabTypeToDefType(int type);
int HabTypeToDef(int type);

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

//These are named to match the models, 
// not the intended purpose.
enum {
	MT_MiningStation = 0,
	MT_ProcessingPlant = 1,
	MT_OrbitalGarden = 2,
	MT_RichSettlement =3,
	MT_PoorSettlement =4,
	MT_ManufacturePlant = 5,
	MT_ResearchStation = 6,
	MT_ShipYardStation = 7,
	MT_TransferStation = 8,
	MT_AdminStation = 9,
	MT_SecurityStation = 10,

	MT_CasinoStation = 11,
	MT_STC = 12,
	MT_MarauderBase = 13,
	MT_FortressStation = 14,
	MT_NavalBaseStation = 15,
	MT_PirateStation = 16,
	MT_CorporateHQ = 17,

	MT_Communications =18,
	MT_Prison=19,
	MT_AsteroidSmall = 20,
	MT_AsteroidMedium = 22,
	MT_AsteroidLarge = 23,
	MT_AsteroidPlain = 26,
	MT_JumpAccel = 29,
	MT_Biobomber = 32,
	MT_PoliceStation = 36,
	MT_SmallPirate = 37,
	MT_CurvedStation = 38,
	MT_NewAsteroid01 = 39, 
	MT_NewAsteroid03 = 40,
	MT_NewAsteroid05 = 41,
	MT_NewAsteroid06 = 42
};




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
	char faction[1024];

	char planet[1024];
	char moon[1024];
	char file_name[1024];

	char station_status[1024];
	char operation_type[1024];

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

	double star_distance;
	double adjustment;

	int station_count = 0;
	int operation_count = 0;

	if (argc != 2){ 
		printf("Usage: save_type <input spreadsheet name>\n");
		return 1;
	}

	// Open the input file
	finput = fopen(argv[1],"r");

	if (NULL == finput){ 
		printf("Error: trying to open input file %s\n",argv[1]);
		return 1;
	}

	foutput = NULL;
	fouttext = NULL;

	srand(1);

	// While not out of lines
	while (NULL != fgets(line,2048,finput)){ 

		ptoken = strtok(line, " \t,");
		//printf("token :%s:\n",ptoken);

		if (0 == strcmp("Giant",ptoken)){ 
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

		}else if (0 == strcmp("Station",ptoken)){ 
			ParseName(name);

			ParseName(station);

			ParseName(faction);

			ParseName(station_status);

			fac = NameToFaction(faction);

			type = NameToStationType(station);

			model = NameToStation(station);

			status = NameToStatus(station_status);

			PrintStation(foutput, name, station_parent, station_orbit*station_radius, 
					station_rot, fac, type, model, foutini, station_count, faction, status);

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
			
			//printf(ptoken);
			//printf(" %f star distance\n", star_distance);
			

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

			printf("New System :%s:\n",name);
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
				printf("Error: trying to open output file %s\n",file_name);
				return 1;
			}
			
			strcpy(file_name,name);
			strcat(file_name,".txt");

			fouttext = fopen(file_name,"w");

			if (NULL == foutput){ 
				printf("Error: trying to open output text file %s\n",file_name);
				return 1;
			}

			strcpy(file_name,name);
			strcat(file_name,".ini");

			foutini = fopen(file_name,"w");

			if (NULL == foutini){ 
				printf("Error: trying to open output ini file %s\n",file_name);
				return 1;
			}

			fprintf(foutini,"\n\n[starting_stations]\n\n");

			// every system restarts the station count for ini file.
			station_count = 0;
			operation_count = 0;

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

			fprintf(foutput,"Lpoint,%s,%s,%s,%f,%d,",name,planet,moon,0.50,entries);

			for (i=0;i<entries;++i){ 
				ParseName(name);
				fprintf(foutput,"%s,",name);
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
			//printf("Name :%s: %d\n",name,i);
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

	return radius;
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

	return moon;
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

	return radius;
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
			model, HT_Disused, A_Aliens );

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
				  char * fac_name, int status)
{
	fprintf(out, ";Station, name, parent, distance, rotation, elevation, orientation x, y, z, station model, hab type, faction, populatin, end,\n");

	fprintf(out, "Station,%s,%s,%f,%f,0,1,0,0,%d,%d,%d,10,end,\n",
			name, parent, 
			orbit, rot, 
			model, type, faction);

	fprintf(finiout,"\n\n\n\n");
	fprintf(finiout,"name[%d]=\"%s\"\n", count, name);
	fprintf(finiout,"parent_body[%d]=\"%s\"\n", count, parent);
	fprintf(finiout,"template[%d]=%d\n", count, model);
	fprintf(finiout,"orbital_distance[%d]=%f\n",count,orbit);
	fprintf(finiout,"orbital_angle_around[%d]=%f\n",count,rot);
	fprintf(finiout,"orbital_angle_above[%d]=%f\n",count,0);
	fprintf(finiout,"type[%d]=%d\n", count, type);

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

	return radius;
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
			name, parent, orbit*cplanet_orbit_base, rot, 2.5e6);
}

void PrintRing(FILE * out, char *name, char *parent, double orbit, double rot, double field_size)
{ 
	fprintf(out, ";Belt, name, parent, distance, rotation, elevation, field size, end,\n");

	fprintf(out, "Belt,%s,%s,%f,%f,0,%f,end,\n",
			name, parent, orbit*cmoon_orbit_base, rot, 2.5e6);
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
	printf("Error: invalid station status n->s: %s\n",name);
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

	printf("Error: invalid operation type n->s: %s\n",name);
	return 0;
}
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

	printf("Error: invalid faction name n->s: %s\n",name);
	return A_Aliens; // The empty faction.
}

int NameToStation(char * name)

{ 


	if (0==strcmp(name,"WaterMine")){return MT_AsteroidLarge;
	}else if (0==strcmp(name,"OrganicsMine")){return MT_NewAsteroid01;
	}else if (0==strcmp(name,"InorganicsMine")){return MT_NewAsteroid01;
	}else if (0==strcmp(name,"BiomassMine")){return MT_NewAsteroid01;
	}else if (0==strcmp(name,"CommonMetalsMine")){return MT_NewAsteroid05;
	}else if (0==strcmp(name,"RareMetalsMine")){return MT_NewAsteroid05;
	}else if (0==strcmp(name,"ExoticMetalsMine")){return MT_NewAsteroid05;
	}else if (0==strcmp(name,"RadioactivesMine")){return MT_AsteroidMedium;
	}else if (0==strcmp(name,"FusionableGasesMine")){return MT_MiningStation;
	}else if (0==strcmp(name,"NeutroniumMine")){return MT_AsteroidLarge;
        
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
	}else if (0==strcmp(name,"Fortress")){return MT_MarauderBase;
        
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
        
	}else if (0==strcmp(name,"Transfer")){return MT_MiningStation;
	}

	printf("Error: invalid station type n->s: %s\n",name);
	return 34;
}


int NameToStationType(char * name)

{ 
	if (0==strcmp(name,"WaterMine")){return 2;
	}else if (0==strcmp(name,"OrganicsMine")){return 3;
	}else if (0==strcmp(name,"InorganicsMine")){return 4;
	}else if (0==strcmp(name,"BiomassMine")){return 5;
	}else if (0==strcmp(name,"CommonMetalsMine")){return 6;
	}else if (0==strcmp(name,"RareMetalsMine")){return 7;
	}else if (0==strcmp(name,"ExoticMetalsMine")){return 8;
	}else if (0==strcmp(name,"RadioactivesMine")){return 9;
	}else if (0==strcmp(name,"FusionableGasesMine")){return 10;
	}else if (0==strcmp(name,"NeutroniumMine")){return 53;
        
	}else if (0==strcmp(name,"WaterProc")){return 11;
	}else if (0==strcmp(name,"OrganicsProc")){return 12;
	}else if (0==strcmp(name,"InorganicsProc")){return 13;
	}else if (0==strcmp(name,"BiomassProc")){return 14;
	}else if (0==strcmp(name,"CommonMetalsProc")){return 15;
	}else if (0==strcmp(name,"RareMetalsProc")){return 16;
	}else if (0==strcmp(name,"ExoticMetalsProc")){return 17;
	}else if (0==strcmp(name,"RadioactivesProc")){return 18;
	}else if (0==strcmp(name,"FusionableGasesProc")){return 19;
	}else if (0==strcmp(name,"NeutroniumProc")){return 20;
        

	}else if (0==strcmp(name,"HeavyMan")){return 22;
	}else if (0==strcmp(name,"BiologicalMan")){return 23;
	}else if (0==strcmp(name,"WetwareMan")){return 24;
	}else if (0==strcmp(name,"HiTechMan")){return 25;
	}else if (0==strcmp(name,"ElectronicsMan")){return 26;
	}else if (0==strcmp(name,"WeaponsMan")){return 27;
	}else if (0==strcmp(name,"PharmaceuticalsMan")){return 28;
	}else if (0==strcmp(name,"PlasticsMan")){return 29;
	}else if (0==strcmp(name,"FusionReactorsMan")){return 30;
	}else if (0==strcmp(name,"EnergyCellsMan")){return 31;
	}else if (0==strcmp(name,"StationFabricationMan")){return 32;
	}else if (0==strcmp(name,"LuxuriesMan")){return 33;
        
	}else if (0==strcmp(name,"BioBomber")){return 35;
        
	}else if (0==strcmp(name,"Shipyard")){return 21;        
	}else if (0==strcmp(name,"Waystation")){return 36;

	}else if (0==strcmp(name,"Research")){return 40;
	}else if (0==strcmp(name,"MedicalResearch")){return 41;
	}else if (0==strcmp(name,"BlackResearch")){return 42;
	}else if (0==strcmp(name,"SensitiveResearch")){return 43;

	}else if (0==strcmp(name,"CentralHQ")){return 47;
        
	}else if (0==strcmp(name,"AgSettlement")){return 48;

	}else if (0==strcmp(name,"Resort")){return 49;
	}else if (0==strcmp(name,"LuxuryResort")){return 50;
        
	}else if (0==strcmp(name,"Medical")){return 51;

	}else if (0==strcmp(name,"SecurityStation")){return 54;
 	}else if (0==strcmp(name,"Fortress")){return 55;       
	}else if (0==strcmp(name,"MercenaryBase")){return 60;
        
	}else if (0==strcmp(name,"Warehousing")){return 62;
	}else if (0==strcmp(name,"Entertainment")){return 66;
        
	}else if (0==strcmp(name,"Settlement")){return 67;
	}else if (0==strcmp(name,"PoliceBase")){return 68;


	}else if (0==strcmp(name,"DefenseDock")){return 71;
        
	}else if (0==strcmp(name,"NavalAcademy")){return 72;

	}else if (0==strcmp(name,"NavalTraining")){return 73;

	// Small population government
	}else if (0==strcmp(name,"Outpost")){return 74;

	}else if (0==strcmp(name,"MarineBarracks")){return 78;
        
	}else if (0==strcmp(name,"NavalResearch")){return 81;
        
	}else if (0==strcmp(name,"SupplyDepot")){return 84;


	//}else if (0==strcmp(name,"STC")){return 87;
        
	}else if (0==strcmp(name,"FTLArray")){return 88;

	}else if (0==strcmp(name,"STLTran")){return 90;

	// System Senator
	}else if (0==strcmp(name,"SystemAdmin")){return 93;
	// National government
	}else if (0==strcmp(name,"ClusterAdmin")){return 94;
	// Local Governor
	}else if (0==strcmp(name,"RegionAdmin")){return 95;

	}else if (0==strcmp(name,"University")){return 96;


	}else if (0==strcmp(name,"PirateBase")){return 101;

	}else if (0==strcmp(name,"PirateCove")){return 102;

	}else if (0==strcmp(name,"PirateOutpost")){return 103;


	}else if (0==strcmp(name,"Casino")){return 106;

	}else if (0==strcmp(name,"Religious")){return 109;


	}else if (0==strcmp(name,"Habitat")){return 112;

	}else if (0==strcmp(name,"BoxTown")){return 114;

	}else if (0==strcmp(name,"Asteroid1")){return 115;
	}else if (0==strcmp(name,"Asteroid2")){return 115;
	}else if (0==strcmp(name,"Asteroid3")){return 115;
	}else if (0==strcmp(name,"Asteroid4")){return 115;

	}else if (0==strcmp(name,"JumpAccel")){return 118;
        
	}else if (0==strcmp(name,"Transfer")){return 122;
	}



	printf("Error: invalid station name n->t: %s\n",name);

	return 116;
}


int NameToStarType(char * name)

{ 
	if (0==strcmp(name,"ok")){return 0;
	}else if (0==strcmp(name,"destroyed")){return 1;
	}else if (0==strcmp(name,"never")){return 2;
	}else if (0==strcmp(name,"building")){return 3;
	}else if (0==strcmp(name,"empty")){return 4;
	}
	printf("Error: invalid station status n->s: %s\n",name);
	return 0;
	
}



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
