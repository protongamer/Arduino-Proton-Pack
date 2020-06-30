#include "routines.h"
//if rookie have problem during internship
//#define DEBUG
#define MP3_DEBUG


//general timing
#define POWERCELL_DEFAULT_SPEED             100 //Powercell speed
#define BARGRAPH_DEFAULT_SPEED              100 //Bargraph speed
#define SEERS_DEFAULT_SPEED                 100 //Bargraph speed
#define FLASH_DEFAULT_SPEED                 150 //Bargraph speed

///////////////////////////////////////////////////////////////////
//Cyclotron parameters

#define MAX_BRIGHT        255

//TVG cyclotron
#define TVG_CYCLOTRON_COUNTER_BRIGHT          50   //for bright animation update
#define TVG_CYCLOTRON_COUNTER_OVERFLOW        2500
#define DECREMENT_FACTOR                      5     //cyclotron bright decrement factor
//color parameters
#define RED_BRIGHT                            200
#define GREEN_BRIGHT                          200
#define BLUE_BRIGHT                           200


//For classic only
#define CLASSIC_CYCLOTRON_COUNTER_OVERFLOW        2500    
#define DEFAULT_CYCLOTRON_COLOR                   RED

////////////////////////////////////////////////////////////////



//Various parameters

//use the video game program(otherwise comment it with // )
//#define ENABLE_TVG_BANK

//Use Classic and TVG Banks with dynamic change feature
#define ENABLE_BOTH_BANKS


//if the video game program, accurate overheat animation bargraph ?
#define BARGRAPH_OVERHEAT     CLASSIC_ANIMATION

//What fire animation do we use ? (discard it if classic animation and the video game program enabled)
#define ANIMATION_X ANIMATION_1

//external clock counter, 0 = full speed, x = ~(speed/x)
#define EXT_CLOCK_COUNTER                   1







#define FLASH_EFFECT    NORMAL
//For sound read
#define MIN_VALUE     124
#define MAX_VALUE     136


//Define default color blast when rookie give a try to blast that ghost

//
#define TVG_BLAST_TYPE                RGB_BLAST
//for classic proton pack or TVG_BLAST_TYPE COLOR_X_BLAST
#define DEFAULT_BLAST_COLOR_1         WHITE
#define DEFAULT_BLAST_COLOR_2         CLASSIC_COLOR

//for TVG proton pack (TVG_BLAST_TYPE = RGB_BLAST)
#define DEFAULT_RGB_BLAST_COLOR_1         RED
#define DEFAULT_RGB_BLAST_COLOR_2         BLUE
#define DEFAULT_RGB_BLAST_COLOR_3         GREEN
#define DEFAULT_RGB_BLAST_COLOR_4         YELLOW

////////////////////////////////////////////////////////////
//BLAST COLOR PART

//For blast flash bright
#define FLASH_BRIGHT                  255

//RGBW Blast Values Primitives(depend on flash bright)

//RED BLAST
#define RED_BLAST_LEVEL         255

//GREEN BLAST
#define GREEN_BLAST_LEVEL         255

//BLUE BLAST
#define BLUE_BLAST_LEVEL       255

//YELLOW BLAST
#define YELLOW_RED_BLAST_LEVEL       255
#define YELLOW_GREEN_BLAST_LEVEL       128

//WHITE BLAST
#define WHITE_BLAST_LEVEL       255

//CLASSIC BLAST
#define CLASSIC_RED_BLAST_LEVEL       255
#define CLASSIC_BLUE_BLAST_LEVEL       255

//USER 1 BLAST
#define USER1_RED_BLAST_LEVEL       255
#define USER1_GREEN_BLAST_LEVEL       255
#define USER1_BLUE_BLAST_LEVEL       255
#define USER1_WHITE_BLAST_LEVEL       255

//USER 2 BLAST
#define USER2_RED_BLAST_LEVEL       255
#define USER2_GREEN_BLAST_LEVEL       255
#define USER2_BLUE_BLAST_LEVEL       255
#define USER2_WHITE_BLAST_LEVEL       255

//USER 3 BLAST
#define USER3_RED_BLAST_LEVEL       255
#define USER3_GREEN_BLAST_LEVEL       255
#define USER3_BLUE_BLAST_LEVEL       255
#define USER3_WHITE_BLAST_LEVEL       255

//USER 4 BLAST
#define USER4_RED_BLAST_LEVEL       255
#define USER4_GREEN_BLAST_LEVEL       255
#define USER4_BLUE_BLAST_LEVEL       255
#define USER4_WHITE_BLAST_LEVEL       255

//USER 5 BLAST
#define USER5_RED_BLAST_LEVEL       255
#define USER5_GREEN_BLAST_LEVEL       255
#define USER5_BLUE_BLAST_LEVEL       255
#define USER5_WHITE_BLAST_LEVEL       255


//////////////////////////////////////////////////////////////


#define VOLUME                        30

#define OVERHEAT_THRESHOLD_1          60          //Warning sequence prefer these values[40~60]
#define OVERHEAT_THRESHOLD_2          90         //Overheat sequence prefer these values[70~90]
#define DART_OV_INCREMENT             20        //increment overheat level for every dart shot


#define START_SMOKE_DELAY             1500   //Define time to start smoke sequence

#define CLOCK_SEERS_1                 100 //Main Seers speed
#define CLOCK_SEERS_2                 5 //Overheat Seer speed
#define CLOCK_SEERS_3                 20 //Overheat Seer speed
