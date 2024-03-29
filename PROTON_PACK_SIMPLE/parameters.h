#include "routines.h"
//if rookie have problem during internship
//#define DEBUG
#define MP3_DEBUG


//general timing
#define POWERCELL_DEFAULT_SPEED             140 //Powercell speed
#define BARGRAPH_DEFAULT_SPEED              150 //Bargraph speed
#define SEERS_DEFAULT_SPEED                 40 //Seers speed
#define FLASH_DEFAULT_SPEED                 150 //Flash speed

///////////////////////////////////////////////////////////////////
//Cyclotron parameters

#define MAX_BRIGHT        255

//TVG cyclotron
#define TVG_CYCLOTRON_COUNTER_BRIGHT          50   //for bright animation update
#define TVG_CYCLOTRON_COUNTER_OVERFLOW        4000
#define DECREMENT_FACTOR                      5     //cyclotron bright decrement factor
//color parameters
#define RED_BRIGHT                            200
#define GREEN_BRIGHT                          200
#define BLUE_BRIGHT                           200


//For classic only
#define CLASSIC_CYCLOTRON_COUNTER_OVERFLOW        4000    
#define DEFAULT_CYCLOTRON_COLOR                   RED

////////////////////////////////////////////////////////////////



//Various parameters

//use the video game program(otherwise comment it with // )
#define ENABLE_TVG_BANK

//Use Classic and TVG Banks with dynamic change feature
//#define ENABLE_BOTH_BANKS

//Use Hybride program than the video game program (NEED AT LEAST "ENABLE_TVG_BANK" PARAMETER ENABLED !!!!)
#define ENABLE_HYBRIDE


//if the video game program, accurate overheat animation bargraph ?
#define BARGRAPH_OVERHEAT     SPEED_ANIMATION

//What fire animation do we use ? (discard it if classic animation and the video game program enabled)
#define ANIMATION_X ANIMATION_3

//external clock counter
#define EXT_CLOCK_COUNTER                   4000
#define MIN_EXT_CLOCK_COUNTER               3000

#define FLASH_BRIGHT                  255




#define FLASH_EFFECT    NORMAL
//For sound read
#define MIN_VALUE     124
#define MAX_VALUE     136


//Define default color blast when rookie give a try to blast that ghost

//
#define TVG_BLAST_TYPE                COLOR_1_BLAST
//for classic proton pack or TVG_BLAST_TYPE COLOR_X_BLAST
#define DEFAULT_BLAST_COLOR_1         WHITE
#define DEFAULT_BLAST_COLOR_2         WHITE

#define VOLUME                        30

#define OVERHEAT_THRESHOLD_1          50          //Warning sequence prefer these values[40~60]
#define OVERHEAT_THRESHOLD_2          70         //Overheat sequence prefer these values[70~90]
#define DART_OV_INCREMENT             20        //increment overheat level for every dart shot


#define START_SMOKE_DELAY             1500   //Define time to start smoke sequence

#define CLOCK_SEERS_1                 100 //Main Seers speed
#define CLOCK_SEERS_2                 5 //Overheat Seer speed
#define CLOCK_SEERS_3                 20 //Overheat Seer speed

#define NUMBER_OF_TRACKS			  12
