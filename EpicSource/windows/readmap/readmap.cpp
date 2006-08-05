// readmap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[])
{
	FILE * finput;
	FILE * foutput;
	int total;
	char name[512];
	char value[4];
	char * cp;
	int i;
	long base_pos;
	unsigned char entity, body_type, hab_type, tex_type, tex1,tex2,tex3;
	unsigned char ring, cloud, unk1, unk2;
	unsigned char faction, population;
	int parent, parent2;
	float red, green, blue;
	float radius;
	double x_pos,y_pos,z_pos;
	float x_ori,y_ori,z_ori;
	float y_scale;

	// used for lpoint references.
	int lpoints, index;
	char lead1, lead2;
	short length;

	finput = fopen(argv[1],"rb");
	foutput = fopen(argv[2],"w");

	// find the total records
	fread(value,4,1,finput);
	cp = (char *)&(total);
	*(cp+3) = value[0];
	*(cp+2) = value[1];	
	*(cp+1) = value[2];
	*(cp+0) = value[3];

	printf("Total Records %d\n",total);
	// read each record and write to outfile

	for (i=0;i<total;++i){
		base_pos = 360*i+4;

		// Read entity type
		fseek(finput,base_pos,SEEK_SET);
		fread(&entity,1,1,finput);

		// Read name
		fseek(finput,base_pos+1,SEEK_SET);
		fread(name,1,261,finput);


		// Read, pos
		fseek(finput,base_pos+264,SEEK_SET);
		fread(&x_pos,8,1,finput);
		fread(&y_pos,8,1,finput);
		fread(&z_pos,8,1,finput);

		fread(&x_ori,4,1,finput);
		fread(&y_ori,4,1,finput);
		fread(&z_ori,4,1,finput);

		fread(&y_scale,4,1,finput);

		// Read parent
		fseek(finput,base_pos+304,SEEK_SET);
		fread(&parent,4,1,finput);

		fread(&parent2,4,1,finput);

		// Read body type
		fseek(finput,base_pos+308,SEEK_SET);
		fread(&body_type,1,1,finput);

		// Read station type 
		fseek(finput,base_pos+309,SEEK_SET);
		fread(&hab_type,1,1,finput);

		//Read faction
		fseek(finput,base_pos+310,SEEK_SET);
		fread(&faction,1,1,finput);

		// Read population
		fseek(finput,base_pos+311,SEEK_SET);
		fread(&population,1,1,finput);

		//Read radius
		fseek(finput,base_pos+312,SEEK_SET);
		fread(&radius,sizeof(radius),1,finput);

		// Read texture type
		fseek(finput,base_pos+316,SEEK_SET);
		fread(&tex_type,1,1,finput);

		fseek(finput,base_pos+317,SEEK_SET);
		fread(&tex1,1,1,finput);

		fseek(finput,base_pos+318,SEEK_SET);
		fread(&tex2,1,1,finput);

		fseek(finput,base_pos+319,SEEK_SET);
		fread(&tex3,1,1,finput);


		fprintf(foutput,"Entity %d, type %d, body type %d hab_type %d yscale %f radius %10.0f name %s\n",
			i,entity,body_type,hab_type,y_scale,radius,name);

		fprintf(foutput,"Parent %d 2 %d, Faction %d, Population %d\n",parent,parent2, faction, population);

		fprintf(foutput,"Texture type %d, t1 %d, t2 %d, t3 %d \n",
			tex_type,tex1,tex2,tex3);


		fprintf(foutput,"Pos %e %e %e, Ori %f %f %f\n",x_pos,y_pos,z_pos,x_ori,y_ori,z_ori);



		// first color triple
		fseek(finput,base_pos+320,SEEK_SET);
		fread(&red,4,1,finput);
	
		fseek(finput,base_pos+324,SEEK_SET);
		fread(&green,4,1,finput);

		fseek(finput,base_pos+328,SEEK_SET);
		fread(&blue,4,1,finput);

		fprintf(foutput,"Color r %3.0f g %3.0f b %3.0f\n",red,green,blue);

		// second color triple
		fseek(finput,base_pos+332,SEEK_SET);
		fread(&red,4,1,finput);
	
		fseek(finput,base_pos+336,SEEK_SET);
		fread(&green,4,1,finput);

		fseek(finput,base_pos+340,SEEK_SET);
		fread(&blue,4,1,finput);

		fprintf(foutput,"Color r %3.0f g %3.0f b %3.0f\n",red,green,blue);

		// second color triple
		fseek(finput,base_pos+344,SEEK_SET);
		fread(&red,4,1,finput);
	
		fseek(finput,base_pos+348,SEEK_SET);
		fread(&green,4,1,finput);

		fseek(finput,base_pos+352,SEEK_SET);
		fread(&blue,4,1,finput);

		fprintf(foutput,"Color r %3.0f g %3.0f b %3.0f\n",red,green,blue);



		fseek(finput,base_pos+356,SEEK_SET);
		fread(&cloud,1,1,finput);


		fseek(finput,base_pos+357,SEEK_SET);
		fread(&ring,1,1,finput);


		fseek(finput,base_pos+358,SEEK_SET);
		fread(&unk1,1,1,finput);

		fseek(finput,base_pos+359,SEEK_SET);
		fread(&unk2,1,1,finput);

		fprintf(foutput, "Cloud %d Ring %d Unk %d Unk2 %d \n",cloud,ring, unk1, unk2);


		// record spacer.
		fprintf(foutput,"\n");
	}


	// Parse out the jump links

	base_pos = 360*total+4;
	fseek(finput,base_pos,SEEK_SET);

	// Read 8 bytes of unknown

	// Read 4 bytes telling number of entries

	fseek(finput,base_pos+8,SEEK_SET);

	fread(value,1,4,finput);
	cp = (char *)&(lpoints);
	*(cp+3) = value[0];
	*(cp+2) = value[1];	
	*(cp+1) = value[2];
	*(cp+0) = value[3];

	printf("Lpoint Entries %d file pos %d \n",lpoints, ftell(finput));
	
	if (lpoints > 10) {
		lpoints = 10;
	}

	// jump over entry total to first entry.
	fseek(finput,base_pos+4+8,SEEK_SET);

	for (i=0;i<lpoints;++i){
	//	fread(&index,4,1,finput);

		fread(value,1,4,finput);
		cp = (char *)&(index);
		*(cp+3) = value[0];
		*(cp+2) = value[1];	
		*(cp+1) = value[2];
		*(cp+0) = value[3];

		// move to lead bytes
	//	fseek(finput,4,SEEK_CUR);
		fread(&lead1,1,1,finput);

	//	fseek(finput,1,SEEK_CUR);
		fread(&lead2,1,1,finput);

		// move to destination string length
	//	fseek(finput,1,SEEK_CUR);
	//	fread(&length,2,1,finput);
		fread(value,1,2,finput);	
		cp = (char *)&(length);
		*(cp+1) = value[0];
		*(cp) = value[1];	


		// move to destination string, and read.
	//	fseek(finput,2,SEEK_CUR);
		fread(name,1,length,finput);

		// move to next entry, ready for loop.
	//	fseek(finput,length,SEEK_CUR);

		printf("Lpoint %d l1 %0x l2 %0x len %d str :%s: \n",
			index,lead1,lead2,length,name);
	}

	// Splash out the remainder of the file, just to see what is there.

	while (0 !=fread(&unk1,1,1,finput)) {
		fprintf(foutput,"%x",unk1);
	}

	fprintf(foutput,"\n");

	fclose(finput);
	fclose(foutput);

	return 0;
}

/*

beginning of lpoint section at bottom of file:
byte 0-7 = unknown, usually 0000 0011 0000 0011 (probably marker for beginning of lpoints)
byte 8-11 = # of lpoint entries motorola long

each lpoint entry:
byte 0-3 = lpoint reference motorola long
byte 4-5 = unknown, always "80 00"
byte 6-7 = X# of destination bytes including null at end, short
following X bytes = destination references (for interstellar, destination is string name followed by ; ex:"hoffers_wake;" end destinations with a 00)
	(for non interstellar lpoints, destination length is "02" and destination is "20 00" )







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





  */