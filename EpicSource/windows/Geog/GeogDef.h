

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
	unsigned char body_model;
	unsigned char habitat_type;
	unsigned char faction_byte;
	unsigned char population;
	float body_radius;
	unsigned char texture_type;
	unsigned char planet_texture1;
	unsigned char planet_texture2;
	unsigned char unknown_a;
	float texture1_red;
	float texture1_green;
	float texture1_blue;
	float texture2_red;
	float texture2_green;
	float texture2_blue;
	float texture3_red;
	float texture3_green;
	float texture3_blue;
	unsigned char cloud_texture;
	unsigned char ring_number;
	unsigned char cloud_opacity;
	unsigned char unknown_c;
} Entity_T;

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
	unsigned char star_type;

	unsigned char habitat_type;
	unsigned char faction_byte;
	unsigned char population;

	float body_radius;
	unsigned char texture_type;
	unsigned char planet_texture1;
	unsigned char planet_texture2;
	unsigned char unknown_a;
	float texture1_red;
	float texture1_green;
	float texture1_blue;
	float texture2_red;
	float texture2_green;
	float texture2_blue;
	float texture3_red;
	float texture3_green;
	float texture3_blue;
	unsigned char cloud_texture;
	unsigned char ring_number;
	unsigned char cloud_opacity;
	unsigned char unknown_c;
} Star_T;

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
	unsigned char body_type;
	// next three unused.
	unsigned char habitat_type;
	unsigned char faction_byte;
	unsigned char population;
	//
	float body_radius;
	unsigned char texture_type;
	unsigned char planet_texture1;
	unsigned char planet_texture2;
	unsigned char unknown_a;
	float texture1_red;
	float texture1_green;
	float texture1_blue;
	float texture2_red;
	float texture2_green;
	float texture2_blue;
	float texture3_red;
	float texture3_green;
	float texture3_blue;
	unsigned char cloud_texture;
	unsigned char ring_number;
	unsigned char cloud_opacity;
	unsigned char unknown_c;
} Body_T;

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
	float nebula_radius;
	
	/*
	unsigned char body_model;
	unsigned char habitat_type;
	unsigned char faction_byte;
	unsigned char population;
	*/
	unsigned char unused_a[8];
	
	/*
	float body_radius;
	unsigned char texture_type;
	unsigned char planet_texture1;
	unsigned char planet_texture2;
	unsigned char unknown_a;
	*/
	float texture1_red;
	float texture1_green;
	float texture1_blue;
	float texture2_red;
	float texture2_green;
	float texture2_blue;
	float texture3_red;
	float texture3_green;
	float texture3_blue;
	
	/*
	unsigned char cloud_texture;
	unsigned char ring_number;
	unsigned char cloud_opacity;
	unsigned char unknown_c;
	*/
	unsigned char unused_b[4];
} Nebula_T;

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
	unsigned char station_model;
	unsigned char habitat_type;
	unsigned char faction_byte;
	unsigned char population;
	unsigned char unused[48];
	
	/*
	float body_radius;
	unsigned char texture_type;
	unsigned char planet_texture1;
	unsigned char planet_texture2;
	unsigned char unknown_a;
	float texture1_red;
	float texture1_green;
	float texture1_blue;
	float texture2_red;
	float texture2_green;
	float texture2_blue;
	float texture3_red;
	float texture3_green;
	float texture3_blue;
	unsigned char cloud_texture;
	unsigned char ring_number;
	unsigned char cloud_opacity;
	unsigned char unknown_c;
	*/
} Station_T;

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
	float belt_radius;
	/*
	unsigned char body_model;
	unsigned char habitat_type;
	unsigned char faction_byte;
	unsigned char population;
	*/
	float field_size;
	unsigned char unused_b[44];
/*
	unsigned char texture_type;
	unsigned char planet_texture1;
	unsigned char planet_texture2;
	unsigned char unknown_a;
	float texture1_red;
	float texture1_green;
	float texture1_blue;
	float texture2_red;
	float texture2_green;
	float texture2_blue;
	float texture3_red;
	float texture3_green;
	float texture3_blue;
	unsigned char cloud_texture;
	unsigned char ring_number;
	unsigned char cloud_opacity;
	unsigned char unknown_c;
	*/
} Belt_T;

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
	int center_index;
	int moon_index;
	unsigned char unused[48];
	
	/*
	unsigned char body_model;
	unsigned char habitat_type;
	unsigned char faction_byte;
	unsigned char population;
	float body_radius;
	unsigned char texture_type;
	unsigned char planet_texture1;
	unsigned char planet_texture2;
	unsigned char unknown_a;
	float texture1_red;
	float texture1_green;
	float texture1_blue;
	float texture2_red;
	float texture2_green;
	float texture2_blue;
	float texture3_red;
	float texture3_green;
	float texture3_blue;
	unsigned char cloud_texture;
	unsigned char ring_number;
	unsigned char cloud_opacity;
	unsigned char unknown_c;
	*/
} Lpoint_T;

typedef union {
	Star_T star;
	Body_T body;
	Nebula_T nebula;
	Belt_T belt;
	Lpoint_T lpoint;
	Station_T station;
	Entity_T entity;
} Entity_U;

enum eEntityType {
ET_Body = 0,
ET_Station = 1,
ET_Lpoint = 2,
ET_Unused = 3,
ET_Belt = 4,
ET_Star = 5,
ET_Gunstar = 6,
ET_Nebula = 7
};

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
/*
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