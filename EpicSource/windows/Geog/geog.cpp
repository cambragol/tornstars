// g.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "GeogDef.h"

#define MAX_ENTRIES 1000
#define MAX_JUMPS 100
#define MAX_STRING 1024*4
#define MAX_NAME 260

typedef struct {
	unsigned char entity_type;
	char name[262];
	unsigned char seperator;
	double x_pos;
	double y_pos;
	double z_pos;
	float orient1;
	float orient2;
	float orient3;
	float y_scale;
	int parent_index;
	int	parent_index2;
	unsigned char pad [46];
} JumpPoint_T;




typedef struct {
	int lpoint;
	char route[MAX_STRING];

} JumpList_T;

void TokenLine(char * line);

void ParseCenter(Body_T * data);
 
void ParseBody(Body_T * data);
void ParseStar(Star_T * data);
void ParseStation(Station_T * data, FILE * finiout, int count);
void ParseNebula( Nebula_T * data);
void ParseBelt( Belt_T * data);

void ParseLpoint(Lpoint_T * data);
void ParseJumpRoute(JumpList_T * data);


void ParseName(char *name);
void ParseLocation(Entity_T * data, int parent);
void ParseOrientation(Entity_T * data);

int LookupParent(char * name);
void PlaceLpoint(Lpoint_T * data, float percentage);
void WriteJumpRoutes(FILE * foutput);
void ParseStationLocation(Station_T * data, int parent, FILE * finiout, int count);

int HabTypeToDef(int type);
int HabTypeToDefType(int type);


void InputMapFile(FILE * input);

void OutputCSVFile(FILE * output);
void OutputCenter(Body_T  body, FILE * output);
void OutputBody(Body_T  body, FILE * output);
void OutputStar(Star_T  body, FILE * output);
void OutputStation(Station_T  body, FILE * output);
void OutputNebula(Nebula_T  body, FILE * output);
void OutputBelt(Belt_T  body, FILE * output);
void OutputLpoint(Lpoint_T  lpoint, int index, FILE * output);

void OutputOffsets(FILE * output, Entity_T * child, Entity_T parent);

void InputLpointRoutes(FILE * finput, FILE * foutput, int total_records);


int find_lpoint(int index);


/* 
	This global entity acts as symbol table
	and intermediate form for all objects in
	geography. When the *.csv file is done
	being parsed, this array is written to file
	to form the *.map file.

  */


Entity_U geog_array[MAX_ENTRIES];
int geog_entries;

JumpList_T jumps[MAX_JUMPS];
int jump_entries;


char token_array[100][MAX_STRING];
int token_count;



int main(int argc, char* argv[])
{
	FILE *finput = NULL;
	FILE *foutput = NULL;
	FILE *finiout = NULL;

	char line [MAX_STRING];
	char * ptoken;
	char * cp;
	char value[4];
	int station_entries;


	//printf("Body Size %d Station Size %d Union %d\n",sizeof(Body_T),sizeof(Station_T),sizeof(Entity_U));

	// Clear entities
	memset(geog_array,0,MAX_ENTRIES*sizeof(Entity_U));
	geog_entries =0;
	
	memset(jumps,0,MAX_JUMPS*sizeof(JumpList_T));
	jump_entries =0;



	// Here we have been asked to decode a map file. Double check this is true, then
	// open the files for read and write.

	if (4 == argc){
		if (0 != strcmp("-decode",argv[1])) {
			printf("Usage: geog <input spreadsheet name> <output map file name> \n");
			printf("Usage: geog -decode <input map file name> <output csv file name>\n");	
			return 2;
		}
		// Open the input file
		finput = fopen(argv[2],"rb");

		if (NULL == finput){
			printf("Error: trying to open input map file %s\n",argv[2]);
			return 3;
		}

		// Open the input file
		foutput = fopen(argv[3],"w");

		if (NULL == foutput){
			printf("Error: trying to open ouput csv file %s\n",argv[3]);
			return 4;
		}

		InputMapFile(finput);

		InputLpointRoutes(finput, foutput, geog_entries);

		OutputCSVFile(foutput);


		fclose(finput);

		fclose(foutput);

		return 0;

	}else if (3 != argc){
		printf("Usage: geog <input spreadsheet name> <output map file name> \n");
		printf("Usage: geog -decode <input map file name> <output csv file name>\n");
		return 1;

	} 
	// Drop out the standard case where we translate csv files into
	// map files.

	// Open the input file csv file
	finput = fopen(argv[1],"rb");

	if (NULL == finput){
		printf("Error: trying to open input csv file %s\n",argv[1]);
		return 1;
	}
		
	foutput = fopen(argv[2],"w+b");

	if (NULL == foutput){
		printf("Error: trying to open output file %s\n",argv[2]);
		return 1;
	}

	station_entries = 0;
	geog_entries = 0;

	// While not out of lines
	while (NULL != fgets(line,MAX_STRING,finput)){

		// TokenLine(line);

		
		ptoken = strtok(line, " \t,\n");
		//printf("token :%s:\n",ptoken);

		if (0 == strcmp("Body",ptoken)){
			ParseBody(&geog_array[geog_entries].body);
			geog_entries++;
			
		}else if (0 == strcmp("Station",ptoken)){

			ParseStation(&geog_array[geog_entries].station, finiout, station_entries);

			geog_entries++;
			station_entries++;

		}else if (0 == strcmp("Lpoint",ptoken)){
			ParseLpoint(&geog_array[geog_entries].lpoint);

			jumps[jump_entries].lpoint = geog_entries;
			ParseJumpRoute(&jumps[jump_entries]);

			jump_entries++;
			geog_entries++;
			
		}else if (0 == strcmp("Belt", ptoken)){
			ParseBelt(&geog_array[geog_entries].belt);
			geog_entries++;

		}else if (0 == strcmp("Star", ptoken)){
			ParseStar(&geog_array[geog_entries].star);
			geog_entries++;

		}else if (0 == strcmp("Gunstar", ptoken)){
			//geog_entries++;

		}else if (0 == strcmp("Nebula", ptoken)){
			ParseNebula(&geog_array[geog_entries].nebula);

			geog_entries++;

		}else if (0 == strcmp("Center", ptoken)){
			ParseCenter(&geog_array[geog_entries].body);
			geog_entries++;

		}else if (0 == strcmp("JumpRoute",ptoken)){
			ParseJumpRoute(&jumps[jump_entries]);
			jump_entries++;
		}
		
	}
	// Close input
	fclose(finput);

	//printf("Entries %d\n",geog_entries);


	// Write the hex file.
	// write the total records in reverse format (motorola).

	cp = (char *)&(geog_entries);
	value[0] = *(cp+3);
	value[1] = *(cp+2);	
	value[2] = *(cp+1);
	value[3] = *(cp);
	
	fwrite(&value,4,1,foutput);

	// write the entities
	fseek(foutput,4,SEEK_SET);

	//printf("Geog Ent %d\n",geog_entries);

	fwrite(&geog_array,sizeof(Entity_U),geog_entries,foutput);

	WriteJumpRoutes(foutput);

	// Close output
	fclose(foutput);

	return 0;
}




void ParseCenter( Body_T * data)
{
	char name[MAX_STRING];
	// read the name, no whitespace.
	ParseName(name);
	strncpy(data->name,name,261);
	//printf("NTest b:%s: a:%s:\n",name, data->name);
	
	// only a few critical non-zero values
	data->x_pos = 0.0;
	data->y_pos = 0.0;
	data->z_pos = 0.0;

	data->orient1 = 1.0;
	data->orient2 = 0.0;
	data->orient3 = 0.0;

	// body entity type.
	data->entity_type= 0;
	data->body_type = 0;
	data->seperator = 0xd7;
}

void ParseStar( Star_T * data)
{
	char token[MAX_STRING];
	char * ptoken;
	int star_type;

	// Parse object name
	ParseName(token);
	strncpy(data->name,token,261);

	// Parse parent name
	ParseName(token);
	data->parent_index = LookupParent(token);

	// Parse and place object
	ParseLocation((Entity_T *)data, data->parent_index);

	// Parse star type
	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&star_type);

	//printf("Star: parent %s type %d\n",token,star_type);

	data->entity_type= 5; // Type star
	data->star_type = star_type;
	data->seperator = 0xd7;
}

void ParseBody( Body_T * data)
{
	char token[MAX_STRING];
	char * ptoken;
	int body_type, tex_type, tex1, tex2;
	int red, green, blue;
	int cloud_texture, cloud_opacity, rings;
	float y_scale, radius;


	// Parse object name
	ParseName(token);
	strncpy(data->name,token,261);

	//printf("Body :%s:\n",data->name);

	// Parse parent name
	ParseName(token);
	data->parent_index = LookupParent(token);

	// Parse and place object
	ParseLocation((Entity_T *)data, data->parent_index);

	ParseOrientation((Entity_T *)data);

	// pull out yscale and body radius.
	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%f",&y_scale);

	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%f",&radius);

	//	Body type
	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&body_type);

	data->body_radius = radius;
	data->y_scale = y_scale;
	data->body_type = body_type;

	// Texture type
	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&tex_type);

	// Texture 1
	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&tex1);

	// Texture 2
	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&tex2);

	data->texture_type = tex_type;
	data->planet_texture1 = tex1;
	data->planet_texture2 = tex2;

	// Read texture 1 color triple
	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&red);

	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&green);

	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&blue);

	data->texture1_red = (float)red;
	data->texture1_green = (float)green;
	data->texture1_blue = (float)blue;


	// Read texture 2 color triple
	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&red);

	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&green);

	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&blue);

	data->texture2_red = (float)red;
	data->texture2_green = (float)green;
	data->texture2_blue = (float)blue;


	// Read cloud color triple
	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&red);

	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&green);

	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&blue);

	data->texture3_red = (float)red;
	data->texture3_green = (float)green;
	data->texture3_blue = (float)blue;


	// Read cloud texture
	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&cloud_texture);

	// Read rings 
	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&rings);

	// Read cloud opacity
	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&cloud_opacity);

	data->cloud_texture = cloud_texture;
	data->ring_number = rings;
	data->cloud_opacity = cloud_opacity;

	data->entity_type = 0; // Type body
	data->seperator = 0xd7;

}


void ParseStation(Station_T * data,FILE* finiout, int count)
{
	char token[MAX_STRING];
	char * ptoken;
	int station_model, station_type, faction, population;


	// Parse object name
	ParseName(token);
	strncpy(data->name,token,261);

	//printf("Station :%s:\n",token);
	// Parse parent name
	ParseName(token);
	data->parent_index = LookupParent(token);



	// Parse and place object
	ParseLocation((Entity_T *)data, data->parent_index);

	ParseOrientation((Entity_T *)data);

	// Parse station model number
	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&station_model);

	// Parse station type
	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&station_type);

	// Parse faction number
	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&faction);

	// Parse population
	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%d",&population);


	data->entity_type= 1; // Type station
	data->station_model = station_model;
	data->habitat_type = station_type;
	data->faction_byte = faction;
	data->population = population;
	data->seperator = 0xd7;
}


void ParseBelt( Belt_T * data)
{
	char token[MAX_STRING];
	float radius;
	char * ptoken;

	// Parse object name
	ParseName(token);
	strncpy(data->name,token,261);

	//printf("Belt :%s:\n",data->name);

	// Parse parent name
	ParseName(token);
	data->parent_index = LookupParent(token);

	// Parse and place object
	ParseLocation((Entity_T *)data, data->parent_index);

	ptoken = strtok(NULL,",\n");
	sscanf(ptoken,"%f",&radius);

	data->field_size = radius;

	data->orient1 = 1.0;
	data->orient2 = 0.0;
	data->orient3 = 0.0;
	data->y_scale = 0.0;

	// we force this value to make the belt show up?
	data->y_pos = 0.0;

	// Always set the belt radius to be the distance from center of the belt.
	radius = (float)sqrt(pow(data->x_pos,2.0)+pow(data->y_pos,2.0)+pow(data->z_pos,2.0));
	data->belt_radius = radius;


	data->entity_type= 4; // Type belt
	data->seperator = 0xd7;
}




void ParseNebula( Nebula_T * data)
{
	char token[MAX_STRING];
	char * ptoken;
	Entity_T * entity;
	float radius;

	entity = (Entity_T *)data;

	// Parse object name
	ParseName(token);
	strncpy(data->name,token,261);

	//printf("Nebula :%s:\n",data->name);

	// Parse parent name
	ParseName(token);
	data->parent_index = LookupParent(token);

	// Parse and place object
	ParseLocation((Entity_T *)data, data->parent_index);

	ptoken = strtok(NULL," \t,\n");
	sscanf(ptoken,"%f",&radius);	

	data->nebula_radius = radius;

	data->entity_type = 7; // Type Nebula
	data->seperator = 0xd7;
}




void ParseLpoint(Lpoint_T * data)
{
	char token[MAX_STRING];
	char * ptoken;
	float percentage;
	
	data->entity_type = 2; // Type lpoint
	data->seperator = 0xd7;

	// Parse object name
	ParseName(token);
	strncpy(data->name,token,261);


	// Parse parent
	ParseName(token);
	data->center_index = LookupParent(token);

	// Parse moon
	ParseName(token);
	data->moon_index = LookupParent(token);

	ptoken = strtok(NULL,",\n");
	strcpy(token, ptoken);

	// Parse distance between moon and planet
	sscanf(ptoken,"%f",&percentage);

	PlaceLpoint(data, percentage);
}
/*
void ParseJumpRoute(JumpList_T * data)
{
	char * ptoken;
	int entries, len;
	char token[MAX_STRING];
	char * cp;
	int done;

	done = 0;
	entries = 0;
	cp = data->route;

	while (!done){
		ptoken = strtok(NULL,",\n");

		if (NULL == ptoken){
			done = 1;
		}else {
			sscanf(ptoken,"%s",token);

			if (strcmp("end",token)){
				done = 1;
			}else if (strcmp("local",token)) {
				done = 1;
			}else {
				len = strlen(token);
				memcpy(cp,token,len);
				cp[len]=';';
				cp += len+1;
				entries++;
			}
		}
	}

	// If there are no entries, then just append one space
	// as required by the EOC engine.
	if (0 == entries){
		strcpy(data->route," ");
	}
}
*/

void ParseJumpRoute(JumpList_T * data)
{
	char token[MAX_STRING];
	char * ptoken;
	int entries, i, len;
	char * cp;

	// Read the number of entries
	ptoken = strtok(NULL,"\t,\n");
	sscanf(ptoken,"%d",&entries);

	// Read each entry, append to string.
	cp = data->route;
	for (i=0;i<entries;++i){
		ParseName(token);
		len = strlen(token);
		memcpy(cp,token,len);
		cp[len]=';';
		cp += len+1;
	}

	// If there are no entries, then just append one space
	// as required by the EOC engine.
	if (0 == entries){
		strcpy(cp," ");
	
	}
	//printf("JumpRoute loc %d route :%s: \n",data->lpoint,data->route);
}




int LookupParent(char * name)
{
	int i;

	for (i=0;i<geog_entries;++i){
		//printf("Store Name :%s:\n",geog_array[i].entity.name);
		if (0==strcmp(name,geog_array[i].entity.name)){
			// found the name, return the index.
			//printf("Found: %d\n",i);
			return i;
		}
	}

	printf("\n\nError: Parent %s not found. Parents must be listed before children. Possible typo\n",
			name);
	return 0;
}


void ParseLocation(Entity_T * data, int parent)
{
	char * ptoken;
	float dist, rot_x, rot_y;
	double x, y, z, distxz, x_rad, y_rad;
	Entity_T * pparent;

	ptoken = strtok(NULL,"\t,\n");
	sscanf(ptoken,"%f",&dist);

	ptoken = strtok(NULL,"\t,\n");
	sscanf(ptoken,"%f",&rot_x);

	ptoken = strtok(NULL,"\t,\n");
	sscanf(ptoken,"%f",&rot_y);
/*
	ptoken = strtok(NULL,"\t,\n");
	sscanf(ptoken,"%f",&roll);

	ptoken = strtok(NULL,"\t,\n");
	sscanf(ptoken,"%f",&pitch);

	ptoken = strtok(NULL,"\t,\n");
	sscanf(ptoken,"%f",&yaw);

	ptoken = strtok(NULL,"\t,\n");
	sscanf(ptoken,"%f",&y_scale);

	ptoken = strtok(NULL,"\t,\n");
	sscanf(ptoken,"%f",&radius);
*/
	// Convert degrees to radians
	y_rad = ((rot_y * 2.0 * 3.14159)/360.0);
	x_rad = ((rot_x * 2.0 * 3.14159)/360.0);

	// Calculate out vectors from radians and distance
	y = sin(y_rad)*dist;
	distxz = cos(y_rad)*dist;
	x = cos(x_rad)*distxz;
	z = sin(x_rad)*distxz;

	pparent = &geog_array[parent].entity;

	// Add to parent position, to find final position.
	data->x_pos = x	+ pparent->x_pos;
	data->y_pos = y + pparent->y_pos;
	data->z_pos = z + pparent->z_pos;

	
	// calculate orientation
	/*
	data->orient1 = roll;
	data->orient2 = pitch;
	data->orient3 = yaw;
*/
	/*
	data->orient1 = 1.0;
	data->orient2 = 0.0;
	data->orient3 = 0.0;
*/
	// set radius and y scale factor
	//data->body_radius = radius;
	//data->y_scale = y_scale;

	//printf("Location d %f, xr %f, yr %f, r %f, p %f, y %f, sc %f, rad %f \n", dist, rot_x, rot_y, roll, pitch, yaw, y_scale, radius);

	//printf("Calc Loc x %f, y %f, z %f \n",data->x_pos, data->y_pos, data->z_pos);
}

void ParseOrientation(Entity_T * data)
{
	char * ptoken;
	float roll, pitch, yaw;

	ptoken = strtok(NULL,"\t,\n");
	sscanf(ptoken,"%f",&roll);

	ptoken = strtok(NULL,"\t,\n");
	sscanf(ptoken,"%f",&pitch);

	ptoken = strtok(NULL,"\t,\n");
	sscanf(ptoken,"%f",&yaw);

	// calculate orientation

	data->orient1 = roll;
	data->orient2 = pitch;
	data->orient3 = yaw;
}



/* 
// Old place point code, never quite correctly aligned lpoints with the moon
// or the planet.
void PlaceLpoint(JumpPoint_T * data)
{
	Entity_U * moon;
	Entity_U * planet;

	double vecx, vecy, vecz, dist, x, y, z, degree;

	moon = &geog_array[data->parent_index].entity;
	planet = &geog_array[data->parent_index2].entity;

	vecx = moon->x_pos - planet->x_pos;
	vecy = moon->y_pos - planet->y_pos;
	vecz = moon->z_pos - planet->z_pos;

	// find vector length.
	dist = sqrt(vecx*vecx+vecy*vecy+vecz*vecz);

	// find unit vector
	x = vecx/dist;
	y = vecy/dist;
	z = vecz/dist;

	// find the lpoint location, halfway between the two parents

	vecx = x*dist*0.5 + planet->x_pos;
	vecy = y*dist*0.5 + planet->y_pos;
	vecz = z*dist*0.5 + planet->z_pos;

	// fill the lpoint entries

	degree = (45.0 + (fabs(z)*15.0))*3.14159/180.0;


	// ccw rotation
	data->orient1 = (float)(x*cos(degree)-z*sin(degree));
	data->orient2 = (float)y;
	data->orient3 = (float)(x*sin(degree)+z*cos(degree));
	
	data->x_pos = vecx;
	data->y_pos = vecy;
	data->z_pos = vecz;

	//printf("Lpoint vector x %f, y %f, z %f\n",x, y, z);
	//printf("Lpoint orient x %f, y %f, z %f\n",data->orient1, data->orient2, data->orient3);
}
*/

// Thanks to mdvalley for figuring out how PS did the angle calculations.
void PlaceLpoint(Lpoint_T * data, float percentage)
{
	Entity_T * moon;
	Entity_T * planet;

	double vecx, vecy, vecz, dist, x, y, z, angle;

	if (percentage > 1.0) {
		percentage = 0.9;
	}else if (percentage < 0.0) {
		percentage = 0.1;
	}

	moon = &geog_array[data->moon_index].entity;
	planet = &geog_array[data->center_index].entity;

	vecx = moon->x_pos - planet->x_pos;
	vecy = moon->y_pos - planet->y_pos;
	vecz = moon->z_pos - planet->z_pos;

	dist = sqrt(vecx*vecx+vecy*vecy+vecz*vecz);

	x = vecx/dist;
	y = vecy/dist;
	z = vecz/dist;

	vecx = x*dist*percentage + planet->x_pos;
	vecy = y*dist*percentage + planet->y_pos;
	vecz = z*dist*percentage + planet->z_pos;

	data->x_pos = vecx;
	data->y_pos = vecy;
	data->z_pos = vecz;

	if ( (z > -0.9)&&(z <-1.1 )   )	// To prevent divide by zero errors if a moon is straight north
	{
		data->orient1 = (float)0.0;	// North
		data->orient2 = (float)0.25;
		data->orient3 = (float)0.25;
	}
	else
	{
		angle = acos(z)/2;

		data->orient1 = (float)cos(angle);
		data->orient2 = (float)(-y*cos(angle)/(z+1));
		data->orient3 = (float)(x*cos(angle)/(z+1));
	};
	
/*
		data->orient1 = (float)1.0;	// North
		data->orient2 = (float)0.0;
		data->orient3 = (float)0.0;
		*/
}



void ParseName(char * name)
{
	char temp[MAX_STRING];
	char * ptoken;
	int length, i;

	// finds name, but has white space lead and trail.
	ptoken = strtok(NULL, ",\n");

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

// Takes an input line and converts it into an arg array.
void TokenLine(char * line)
{
	int length;
	char * plead;
	char * ptail;

	length = strlen(line);
	plead = line;
	ptail = strpbrk(plead,",\n");
	token_count=0;

	// While we still find trailing token markers
	// keep copying tokens.

	while (ptail != NULL) {
		// change the trailing token marker to a null.
		*ptail = 0;

		// copy the token in the middle into the argument array.
		strncpy(&token_array[token_count][0],plead,2000);
		token_count++;
		// move the lead to just past the tail, and check if we have
		// overrun the end of the line.
		plead = ptail+1;
		if (plead >= (line + length))
		{
			ptail = NULL;
		}
		else {
			ptail = strpbrk(plead,",\n");
		}
	}
}

void WriteJumpRoutes(FILE * foutput)
{
	char * cp;
	int i;
	short len;
	char temp, junk[50];
	
	//printf("Jumps %d \n",jump_entries);

	// write the strange header block
	memset(junk,0,50);
	junk[3]=0x11;
	junk[7]=0x11;
	fwrite(junk,1,8,foutput);

	// write the number of entries
	cp = (char *)&jump_entries;
	fwrite(cp+3,1,1,foutput);
	fwrite(cp+2,1,1,foutput);
	fwrite(cp+1,1,1,foutput);
	fwrite(cp+0,1,1,foutput);

	for (i=0;i<jump_entries;++i){

		// Reverse the index and write to 
		// the buffer
		cp = (char *)&(jumps[i].lpoint);
		fwrite(cp+3,1,1,foutput);
		fwrite(cp+2,1,1,foutput);
		fwrite(cp+1,1,1,foutput);
		fwrite(cp+0,1,1,foutput);	
		
		// write two fixed bytes
		temp = (char)0x80;
		fwrite(&temp,1,1,foutput);
		temp = 0x00;
		fwrite(&temp,1,1,foutput);

		// write two string length bytes, reversed
		len = strlen(jumps[i].route);
		len++;
		cp = (char *)&(len);
		fwrite(cp+1,1,1,foutput);
		fwrite(cp+0,1,1,foutput);

		// write the string, including null.
		fwrite(jumps[i].route,1,len,foutput);

		//printf("Route :%s:\n",jumps[i].route);
	}
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

// This function reads the map file into an internal data structure.
void InputMapFile(FILE * finput)
{
	unsigned char value[4];
	int total;
	unsigned char * cp;


	// find the total records
	fread(value,4,1,finput);
	cp = (unsigned char *)&(total);
	*(cp+3) = value[0];
	*(cp+2) = value[1];	
	*(cp+1) = value[2];
	*(cp+0) = value[3];

	printf("Total Records %d\n",total);

	if (total > 1000) {

		printf("Too many entities to process, limit 1000, bailing\n");
		return;
	}

	// Do a binary copy of the map file into the internal data structure.
	fseek(finput, 4, SEEK_SET);

	fread(geog_array, sizeof(Entity_U), total, finput);
	geog_entries = total;

}

void InputLpointRoutes(FILE * finput, FILE * foutput, int total_records)
{
	unsigned char value[4];
	int lpoints, i, index;
	long base_pos;
	unsigned char * cp;
	short route_length;

	// Find the start of the lpoint route entries.
	base_pos = 360*total_records+4;
	fseek(finput,base_pos,SEEK_SET);

	// Read 8 bytes of unknown
	fseek(finput,base_pos+8,SEEK_SET);

	// Read 4 bytes telling number of entries
	fread(value,1,4,finput);
	cp = (unsigned char *)&(lpoints);
	*(cp+3) = value[0];
	*(cp+2) = value[1];	
	*(cp+1) = value[2];
	*(cp+0) = value[3];
	
	if (lpoints > MAX_JUMPS) {
		lpoints = MAX_JUMPS;
	}

	// jump over entry total to first entry.
	fseek(finput,base_pos+4+8,SEEK_SET);
	
	jump_entries = lpoints;

	for (i=0;i<lpoints;++i){
		// Get the current lpoint index,
		// and invert it into Intel byte order.
		fread(value,1,4,finput);
		cp = (unsigned char *)&(index);
		*(cp+3) = value[0];
		*(cp+2) = value[1];	
		*(cp+1) = value[2];
		*(cp+0) = value[3];

		//printf("Route, %s,",geog_array[index].entity.name);

		// skip over two constant bytes.
		fread(value,1,2,finput);

		// Read in the route string length.
		// Then invert it to intel byte order.
		fread(value,1,2,finput);	
		cp = (unsigned char *)&(route_length);
		*(cp+1) = value[0];
		*(cp) = value[1];	

		if (route_length > MAX_STRING){
			printf("Lpoint %s Route is too long\n", geog_array[index].entity.name);
			return;
		}

		jumps[i].lpoint = index;
		
		// Read in the whole route string. Includes the end null.
		fread(jumps[i].route,1,route_length,finput);

		//printf("%s,end\n\n",route);
	}
}

// This function writes the internal data structure out as a CSV file

void OutputCSVFile(FILE * output)
{
	int i;
	unsigned char entity_type;

	for (i=0;i<geog_entries;++i)
	{
		entity_type = geog_array[i].entity.entity_type;

		switch (entity_type)
		{
		case ET_Body:
			if (geog_array[i].body.body_type == BT_SystemCentre)
				OutputCenter(geog_array[i].body, output);
			else 
				OutputBody(geog_array[i].body,output);
			break;
		case ET_Star:
			OutputStar(geog_array[i].star,output);
			break;
		case ET_Nebula:
			OutputNebula(geog_array[i].nebula, output);
			break;
		case ET_Belt:
			OutputBelt(geog_array[i].belt, output);
			break;
		case ET_Station:
			OutputStation(geog_array[i].station, output);
			break;
		case ET_Lpoint:
			OutputLpoint(geog_array[i].lpoint, i, output);
			break;
		default:
			printf("Invalid entity type\n");
		}
	}
}

// center
void OutputCenter(Body_T  body, FILE * output)
{
	fprintf(output,";Center, Name,\n");

	fprintf(output,"Center,%s,end,\n\n", body.name);
}

// star
void OutputStar(Star_T  star, FILE * output)
{
	fprintf(output,";Star, Name, Parent, Distance, Rotation, Elevation, Color,\n"); 

	fprintf(output,"Star,%s,%s,", star.name, 
			geog_array[star.parent_index].entity.name);
	
	OutputOffsets(output, (Entity_T *)&star, geog_array[star.parent_index].entity);

	fprintf(output, "%d,end,\n\n", star.star_type);
}

//  planet, moon
void OutputBody(Body_T  body, FILE * output)
{
	fprintf(output,";Body, Name, Parent, Distance, Rotation, Elevation, Orientation X, Y, Z, Y Scale, Body Radius, Body Type,");
	fprintf(output,"Texture Type, Texture Map 1, Texture Map 2, Red Low, Blue Low, Green Low, Red High, Green High, Blue High, Red Unk, Green Unk, Blue Unk,");
	fprintf(output,"Cloud Texture Map, Number Rings, Cloud Opacity,\n");

	fprintf(output,"Body,%s,%s,", body.name, 
			geog_array[body.parent_index].entity.name);
	
	OutputOffsets(output, (Entity_T *)&body, geog_array[body.parent_index].entity);

	fprintf(output, "%f,%f,%f,", body.orient1, body.orient2, body.orient3);

	fprintf(output,"%f,%f,%d,", body.y_scale, body.body_radius, body.body_type);

	fprintf(output, "%d,", body.texture_type);
	fprintf(output,"%d,%d,", body.planet_texture1, body.planet_texture2);
	fprintf(output,"%3.1f,%3.1f,%3.1f,",body.texture1_red, body.texture1_green, body.texture1_blue);
	fprintf(output,"%3.1f,%3.1f,%3.1f,",body.texture2_red, body.texture2_green, body.texture2_blue);
	fprintf(output,"%3.1f,%3.1f,%3.1f,",body.texture3_red, body.texture3_green, body.texture3_blue);

	fprintf(output,"%d,%d,%d,end,\n\n",body.cloud_texture, body.ring_number, body.cloud_opacity);
}

void OutputStation(Station_T  station, FILE * output)
{
	fprintf(output,";Station, Name, Parent, Distance, Rotation, Elevation, Orientation X, Y, Z,");
	fprintf(output,"Station Model, Habitat Type, Faction Allegiance, Population,\n");

	fprintf(output,"Station,%s,%s,", station.name, 
			geog_array[station.parent_index].entity.name);
	
	OutputOffsets(output, (Entity_T *)&station, geog_array[station.parent_index].entity);

	fprintf(output, "%f,%f,%f,", station.orient1, station.orient2, station.orient3);

	fprintf(output,"%d,%d,%d,%d,end,\n\n",station.station_model, station.habitat_type, station.faction_byte, station.population);
}

// Asteroid Belt
void OutputBelt(Belt_T  belt, FILE * output)
{
	fprintf(output,";Belt, Name, Parent, Distance, Rotation, Elevation, Field Size,\n");
	fprintf(output,"Belt,%s,%s,", belt.name, 
			geog_array[belt.parent_index].entity.name);
	
	OutputOffsets(output, (Entity_T *)&belt, geog_array[belt.parent_index].entity);

	
	fprintf(output,"%f,",belt.field_size);

	//fprintf(output,"%f,",belt.field_size);
	//fprintf(output,"%d,%d,%d,%d,",belt.unused_b[0],belt.unused_b[1],belt.unused_b[2],belt.unused_b[3]);
	fprintf(output,"end,\n\n");
}

//  Nebula
void OutputNebula(Nebula_T  nebula, FILE * output)
{
	fprintf(output,";Nebula, Name, Parent, Distance, Rotation, Elevation, Nebula Radius,\n");

	fprintf(output,"Nebula,%s,%s,", nebula.name, 
			geog_array[nebula.parent_index].entity.name);
	
	OutputOffsets(output, (Entity_T *)&nebula, geog_array[nebula.parent_index].entity);

	fprintf(output, "%f,end,\n\n",nebula.nebula_radius);										
}


void OutputLpoint(Lpoint_T  lpoint, int index, FILE * output)
{
	double x1,x2,y1,y2,z1,z2,dist1,dist2;
	int route_index, route_length, i, entries;
	char route[MAX_STRING];

	fprintf(output,";Lpoint, Name, Planet, Moon, Distance,\n");

	fprintf(output,"Lpoint,%s,%s,%s,", lpoint.name, 
										geog_array[lpoint.center_index].entity.name, 
										geog_array[lpoint.moon_index].entity.name);

	// We need to calculate the distance percentage between the two objects.
	
	// Find vector between lpoint and parent planet
	x1 = lpoint.x_pos - geog_array[lpoint.center_index].entity.x_pos;
	y1 = lpoint.y_pos - geog_array[lpoint.center_index].entity.y_pos;
	z1 = lpoint.z_pos - geog_array[lpoint.center_index].entity.z_pos;
	dist1 = sqrt(pow(x1,2.0)+pow(y1,2.0)+pow(z1,2.0));

	// Find vector between moon and parent vector. 
	x2 = geog_array[lpoint.moon_index].entity.x_pos - geog_array[lpoint.center_index].entity.x_pos;
	y2 = geog_array[lpoint.moon_index].entity.y_pos - geog_array[lpoint.center_index].entity.y_pos;
	z2 = geog_array[lpoint.moon_index].entity.z_pos - geog_array[lpoint.center_index].entity.z_pos;
	dist2 = sqrt(pow(x2,2.0)+pow(y2,2.0)+pow(z2,2.0));

	// Find percentage of length.
	fprintf(output, "%1.2f,",dist1/dist2);

	route_index = find_lpoint(index);

	strcpy(route,jumps[route_index].route);
	route_length = strlen(route);

	entries = 0;
	// Change all the semicolons to comma.
	for (i=0;i<route_length; ++i)
	{
		if (route[i]==';'){
			route[i]=',';
			entries++;
		}
	}

	fprintf(output, "%d,%s", entries, route);

	fprintf(output,"end,\n\n");
}

int find_lpoint(int index)
{
	int i;

	for (i=0;i<jump_entries;++i)
	{
		if (jumps[i].lpoint == index){
			return i;
		}
	}

	printf("Error: Lpoint %d has no route entry\n",index);

	return 0;
}

// Return the length of the vector
double calc_distance(double x, double y, double z)
{

	return sqrt(pow(x,2.0)+pow(y,2.0)+pow(z,2.0));
}


//

// This function needs to take the absolute x, y, z coordinates for an object,
// and turn them into offsets from the parent, in distance, elevation and rotation.
// Input is the x, y, z map vector values and the parents x, y, z values.

// We now define Rotation as a 0-360 degree rotation around the parent.
// Elevation is defined as a 0-90 degree elevation above the parent, or
// a - 0-90 degree rotation below the parent.

void OutputOffsets(FILE * output, Entity_T * child, Entity_T parent)
{
	double distance, xdist, ydist, rotation, elevation;
	double xch, ych, zch;
	
	xch = child->x_pos;
	zch = child->z_pos;
	ych = child->y_pos;

	// Subtract out the parent vector component.
	xch = xch - parent.x_pos;
	zch = zch - parent.z_pos;
	ych = ych - parent.y_pos;
	
	// Find the length of the vector
	distance = sqrt(pow(xch,2.0)+pow(ych,2.0)+pow(zch,2.0));
	xdist = sqrt(pow(xch,2.0)+pow(zch,2.0));

	rotation = acos(xch/xdist);
	rotation = 180.0*rotation/3.14159;
	
	// acos only handles the top 180 deg, we invert if the Z value was
	// negative, and the angle has wrapped around the circle.
	if (zch < 0.0) {
		rotation = 360.0 - rotation;
	}

	if ((ych < 100.0)  && (ych > -100.0)) {
		elevation = 0.0;
	} else {
		ydist = sqrt(pow(xdist,2.0)+pow(ych,2.0));
		elevation = acos(xdist/ydist);
		elevation = 90.0*elevation/ 3.14159;

		// if y was negative, use a negative rotation.
		if (ych < 0.0) {
			elevation = elevation * -1.0;
		}
	}

	// We have a special case where stars or other objects are placed directly on top of 
	// parents, and it makes a mess of these calculations. In this case, we just clamp
	// everything to zero. Sizes like 100 meters are nearly zero on a planetary scale.

	if (distance < 100.0) {
		rotation = 0;
		elevation = 0;
		distance = 0;
	}
	
	fprintf(output, "%f,%3.0f,%3.0f,",distance, rotation, elevation);
}



/*
		if (0 == strcmp("SystemCentre",token)){
			
		}else if (0 == strcmp("Star",token)){

		}else if (0 == strcmp("Planet",token)){
			
		}else if (0 == strcmp("Moon", token)){

		}else if (0 == strcmp("GasGiant", token)){

		}else if (0 == strcmp("Asteroid", token)){

		}else if (0 == strcmp("DeadGasGiantCore", token)){

		}else if (0 == strcmp("AsteroidBelt", token)){

		}else if (0 == strcmp("Nebula",token)){

		}else if (0 == strcmp("Lpoint",token

*/

/*

Each entity gets a line in the spreadsheet. All values must be on the same line.

Text description of the input spreadsheet for each entity

string			entity type
string			name

float			dist from parent
float			rot around parent
float			rot above parent
float			roll 
float			pitch 
float			yaw
float			y_scale
float			body radius

string			parent
string			body type 

int             station model number (ignored for non station)
int				habitat type 
int				faction number
int				total population 
int				texture type

int				first planet texture index
int				second planet texture index
int				unknown texture index

int				first texture red
int				first texture green
int				first texture blue
int				second texture red
int				second texture green
int				second texture blue
int				unknown red
int				unknown blue
int				unknown green

int				cloud texture index
int				number of rings (max 8)
int				unknown
int				unknown


Jump routes are special entities.

int				jump route entity type (new value)
int				hidden? 0 = no, 1 = yes
int				known? 0 = no, 1 = yes
string			name of destination1
string			name of destinationN until no more

destination names end at end of line.

*/
/*

Geography .map notes:
byte 0-3 = number of entities in .map package (includes system entity and main star) big endian long

for each entity:
byte 0 = entity type ( see list 1 )
byte 1-263 = ASCII string, entity name (terminates in first 00, rest is meaningless filler ending in D7)
byte 264-271 = xvalue double-float
byte 272-279 = yvalue double-float
byte 280-287 = zvalue double-float
byte 288-291 = orientation1 float
byte 292-295 = orientation2 float
byte 296-299 = orientation3 float
byte 300-303 = yscale float
byte 304-307 = parent long
byte 308 = body type byte (see list 2) OR habitat model
byte 309 = habitat type (see list 3) byte
byte 310 = habitat faction byte
byte 311 = population
byte 312-315 = body radius float
byte 316 = texture type (see list 6)
byte 317 = planet texture1 byte
byte 318 = planet texture2 byte
byte 319 = unknown
byte 320-323 = first texture red float
byte 324-327 = first texture green float
byte 328-331 = first texture blue float
byte 332-335 = second texture red float
byte 336-339 = second texture green float
byte 340-343 = second texture blue float
byte 344-347 = unknown color red float
byte 348-351 = unknown color green float
byte 352-355 = unknown color blue float
byte 356 = cloud texture byte (ff = no clouds)
byte 357 = ring number
byte 358 = cloud opacity?
byte 359 = unknown


beginning of lpoint section at bottom of file:
byte 0-7 = unknown, usually 0000 0011 0000 0011 (probably marker for beginning of lpoints)
byte 8-11 = # of lpoint entries motorola long

each lpoint entry:
byte 0-3 = lpoint reference motorola long
byte 4-5 = unknown, always "80 00"
byte 6-7 = X# of destination bytes including null at end, short
following X bytes = destination references (for interstellar, destination is string name followed by ; ex:"hoffers_wake;" end destinations with a 00)
	(for non interstellar lpoints, destination length is "02" and destination is "20 00" )

LIST 1 entity types (byte 0):
00 = Body - Also system center, but not star
01 = Station
02 = Lpoint
03 = Unused
04 = Belt
05 = Star
06 = Gunstar
07 = Nebula

LIST 2 body types (byte 308):
enum IeBodyType 
{ 
BT_SystemCentre = 0, 
BT_Star = 1, 
BT_Planet = 2, 
BT_Moon = 3, 
BT_GasGiant = 4, 
BT_Asteroid = 5, 
BT_DeadGasGiantCore = 6, 
BT_AsteroidBelt = 7, 
BT_Nebula = 8, 
BT_Invalid = 9 
};

SystemCentre = 0, 
Star = 1, 
Planet = 2, 
Moon = 3, 
GasGiant = 4, 
Asteroid = 5, 
DeadGasGiantCore = 6, 
AsteroidBelt = 7, 
Nebula = 8,


Body type becomes star color type, when entity is a star.
1 - Blue 
2 - Bluish white 
5 - Yellow 
8 - Red with a touch of orange 
9 - Red 
11 - Deep, almost blood red 

Batatas M0_V 
Coyote G8_V 
Dagda M0_V 
Dante I F3_V 



Coyote G8_V 
Eureka G1_V 
Firefrost I G0_I 
Mwari II G0_V 
Santa Romera G5_V 

Drake K4_V 
Firefrost II K1_V 
Dante II K7_V 
Kompira K0_V 
Osprey K4_V 

Firefrost III M0_V 
Hoffer's Wake Alpha M0_V 
New Bavaria M7_V 
Ishme M7_V 
Owen's Star M9_V 

Formhault A3_V 

Hoffer's Wake Beta F5_V 
Mwari I F5_V 



V is main sequence, I is giant.

OBAFGKM

1	O blue
2	B blue-white
3	A white
4	F yellow-white
5	G yellow
6	K orange
7	M red
8	
9	
10
11	

for each Star:
byte 0 = entity type ( see list 1 )
byte 1-263 = ASCII string, entity name (terminates in first 00, rest is meaningless filler ending in D7)
byte 264-271 = xvalue double-float
byte 272-279 = yvalue double-float
byte 280-287 = zvalue double-float
byte 288-291 = orientation1 float
byte 292-295 = orientation2 float
byte 296-299 = orientation3 float
byte 300-303 = yscale float
byte 304-307 = parent long - always system center
byte 308 = star color type 
byte 309 = 0
byte 310 = 0
byte 311 = 0
byte 312-315 = body radius float
byte 316 - 359 = 0


for each jump route:
byte 0 = entity type ( see list 1 )
byte 1-263 = ASCII string, entity name (terminates in first 00, rest is meaningless filler ending in D7)
byte 264-271 = xvalue double-float
byte 272-279 = yvalue double-float
byte 280-287 = zvalue double-float
byte 288-291 = orientation1 float
byte 292-295 = orientation2 float
byte 296-299 = orientation3 float
byte 300-303 = yscale float
byte 304-307 = parent long
byte 308-311 = parent 2 long
byte 312-359 = 0


/// Nebula have a special structure all their own. Grrr.
Byte 0 = entity type (07)
Byte 1-263 = ASCII string, entity name (terminates in first 00, rest is meaningless filler ending in D7)
Byte 264-271 = xvalue double-float
Byte 272-279 = yvalue double-float
Byte 280-287 = zvalue double-float
Byte 288-291 = orientation1 float
Byte 292-295 = orientation2 float
Byte 296-299 = orientation3 float
Byte 300-303 = nothing
Byte 304-307 = parent long
Byte 308-311 = body radius
Byte 312-359 = nothing



LIST 6 texture type
1 to use rocky planet textures
2 to use gas giant planet textures


LIST 3 station types (byte 309):
enum IeHabitatType
{
	HT_Invalid = 0,
	HT_Disused = 1,
	HT_WaterMine = 2,
	HT_OrganicsMine = 3,
	HT_InorganicsMine = 4,
	HT_BiomassMine = 5,
	HT_CommonMetalsMine = 6,
	HT_RareMetalsMine = 7,
	HT_ExoticMetalsMine = 8,
	HT_RadioactivesMine = 9,
	HT_FusionableGasesMine = 10,
	HT_WaterProcessingPlant = 11,
	HT_OrganicsProcessingPlant = 12,
	HT_InorganicsProcessingPlant = 13,
	HT_BiomassProcessingPlant = 14,
	HT_CommonMetalsProcessingPlant = 15,
	HT_RareMetalsProcessingPlant = 16,
	HT_ExoticMetalsProcessingPlant = 17,
	HT_RadioactivesProcessingPlant = 18,
	HT_FusionableGasesProcessingPlant = 19,
	HT_NeutroniumProcessingPlant = 20,
	HT_Shipyard = 21,
	HT_HeavyManufacturingPlant = 22,
	HT_BiologicalManufacturingPlant = 23,
	HT_WetwareManufacturingPlant = 24,
	HT_HiTechManufacturingPlant = 25,
	HT_ElectronicsManufacturingPlant = 26,
	HT_WeaponsManufacturingPlant = 27,
	HT_PharmaceuticalsManufacturingPlant = 28,
	HT_PlasticsManufacturingPlant = 29,
	HT_FusionReactorsManufacturingPlant = 30,
	HT_EnergyCellsManufacturingPlant = 31,
	HT_StationFabricationManufacturingPlant = 32,
	HT_LuxuriesManufacturingPlant = 33,
	HT_TerraformingStation = 34,
	HT_BioBomber = 35,
	HT_Waystation = 36,
	HT_RepairStation = 37,
	HT_OreTransferStation = 38,
	HT_ResearchAndDevelopmentLab = 39,
	HT_ResearchStation = 40,
	HT_MedicalResearchCentre = 41,
	HT_BlackBudgetResearchStation = 42,
	HT_SensitiveResearchStation = 43,
	HT_FinancialCentre = 44,
	HT_RegionalHQ = 45,
	HT_Villa = 46,
	HT_CentralHQ = 47,
	HT_AgriculturalSettlement = 48,
	HT_Resort = 49,
	HT_LuxuryResort = 50,
	HT_MedicalFacility = 51,
	HT_LeisureComplex = 52,
	HT_NeutroniumMine = 53,
	HT_SecurityStation = 54,
	HT_Fortress = 55,
	HT_HighSecurityPrison = 56,
	HT_LowSecurityPrison = 57,
	HT_HardLabourPrison = 58,
	HT_Homestead = 59,
	HT_MercenaryBase = 60,
	HT_TradingPost = 61,
	HT_Warehousing = 62,
	HT_BlackMarket = 63,
	HT_DryDock = 64,
	HT_DockingStation = 65,
	HT_EntertainmentStation = 66,
	HT_Settlement = 67,
	HT_PoliceBase = 68,
	HT_PoliceOutpost = 69,
	HT_SystemDefenceStation = 70,
	HT_SystemDefenceDock = 71,
	HT_NavalAcademy = 72,
	HT_NavalTrainingBase = 73,
	HT_Outpost = 74,
	HT_Base = 75,
	HT_RepairDock = 76,
	HT_MarineBarracks = 78,
	HT_PerimeterDefences = 79,
	HT_NavalTestingSite = 80,
	HT_NavalResearchFacility = 81,
	HT_JumpFortress = 82,
	HT_SupplyDepot = 84,
	HT_DefenceStation = 85,
	HT_STCPost = 86,
	HT_STCHQ = 87,
	HT_FTLArray = 88,
	HT_FTLInterchange = 89,
	HT_STLTranceiver = 90,
	HT_STLInterchange = 91,
	HT_PlanetaryAdministration = 92,
	HT_SystemAdministration = 93,
	HT_ClusterAdministration = 94,
	HT_RegionalDepartment = 95,
	HT_University = 96,
	HT_Ark = 97,
	HT_Garden = 98,
	HT_Asylum = 99,
	HT_Hospice = 100,
	HT_PirateBase = 101,
	HT_PirateCove = 102,
	HT_PirateOutpost = 103,
	HT_GangsterHideout = 104,
	HT_ViceDen = 105,
	HT_Casino = 106,
	HT_CollectiveSettlement = 107,
	HT_Hermitage = 108,
	HT_ReligiousCentre = 109,
	HT_MadScientistLab = 110,
	HT_Hideout = 111,
	HT_Habitat = 112,
	HT_Junkyard = 113,
	HT_BoxTown = 114,
	HT_AsteroidSculptures = 115,
	HT_PlayerBase = 116,
	HT_GunstarArray = 117,
	HT_JumpAccelerator = 118,
	HT_HoffersGap = 119,
	HT_HoffersHeel = 120,
	HT_Beanstalk = 121,
	HT_TransferStation = 122

};

LIST 4 factions (byte 310);
enum IeAllegiance
{
	A_Neutral = 00,
	A_Independent = 01,
	A_Exile = 02,
	A_Military = 03,
	A_Underworld = 04,
	A_Government = 05,
	A_Transient = 06,
	A_Society = 07,
    A_Invalid = 08,
	A_Stepson = 09,
	A_Kong = 0a,
	A_MAASCorporation = 0b,
	A_CarvaCartel = 0c,
	A_Junkers = 0d,
	A_Police = 0e,
	A_NOMEXCorporation = 0f,
	A_NSOLaplace = 10,
	A_Marauders = 11,
	A_Angels = 12,
	A_TheOman = 13,
	A_MCA = 14,
	A_Player = 15,
	A_League = 16,
	A_TrimannShipping = 17,
	A_RhondusGasMining = 18,
	A_AshantiInvestment = 19,
	A_CrosspointMinerals = 1a,
	A_HeliosMining = 1b,
	A_JardinTerraforming = 1c,
	A_ChonBodifule = 1d,
	A_OrionProducts = 1e,
	A_VonShellingIndustries = 1f,
	A_MegalithCorp = 20,
	A_HibatshPMC = 21,
	A_DesterCorporation = 22,
	A_WhindWeaponsSystems = 23,
	A_AdvancedSecurityCorp = 24,
	A_Network54 = 25,
	A_Infonet = 26,
	A_StellarNet = 27,
	A_WordsworthTechnology = 28,
	A_NetcomSA = 29,
	A_CoventryEngineeringResearch = 2a,
	A_NINEXWetware = 2b,
	A_UniversalConsumerProducts = 2c,
	A_HighlifeProducts = 2d,
	A_LowOrbitRecovery = 2e,
	A_KIMOShipping = 2f,
	A_DatagonTechnologies = 30,
	A_MicoriaCommunications = 31,
	A_LOMAXEngines = 32,
	A_LOMAXTechnologies = 33,
	A_NumikoProducts = 34,
	A_TheThirdWay = 35,
	A_Aliens = 36,
	eIeAllegianceCount
};

LIST 5 rings (byte 316);
01 = no rings
02 = rings


  */