//Protongamer 2020


/* TODO LIST :

   -Maybe add more tracks


*/



#include <DFPlayer_Mini_Mp3.h>
#include "pins.h"
#include "parameters.h"
#include "routines.h"
#include "bargraph_animations.h"
#include "mp3_files_names.h"


#ifndef ENABLE_BOTH_BANKS
#ifdef ENABLE_TVG_BANK
#define ENABLE_TVG
#endif
#else
#define ENABLE_BB
bool BANK = CLASSIC_BANK;
#endif


//Pin layout order
uint8_t powercell[] = { P_PIN_1, P_PIN_2, P_PIN_3, P_PIN_4, P_PIN_5, P_PIN_6, P_PIN_7, P_PIN_8, P_PIN_9, P_PIN_10, P_PIN_11, P_PIN_12, P_PIN_13, P_PIN_14, P_PIN_15, };
uint8_t bargraph[] = { B_PIN_1, B_PIN_2, B_PIN_3, B_PIN_4, B_PIN_5, B_PIN_6, B_PIN_7, B_PIN_8, B_PIN_9, B_PIN_10, B_PIN_11, B_PIN_12, B_PIN_13, B_PIN_14, B_PIN_15, };
uint8_t cyclotron[] = { C_PIN_1, C_PIN_2, C_PIN_3, C_PIN_4,};
uint8_t colorFilter[] = { C_RED, C_GREEN, C_BLUE, };
uint8_t seers[] = { S_PIN_1, S_PIN_2, S_PIN_3, S_PIN_4, S_PIN_5, S_PIN_6, };
uint8_t specialPins[] = { S_RELAY_PIN, S_LED_PIN, EXT_CLOCK, BLAST_RELAY, CMD_EXT_CIRCUIT};
uint8_t buttons[] = { BUT1, BUT2, SW1, SW2, };


/////////////////////////////////////////////////////
//var process

//miscellaneous
volatile uint8_t extCounter = 0;
volatile uint8_t seersByte;
volatile uint16_t counterTimeSeers = 0;
volatile uint16_t clock1 = 0;
volatile uint16_t clock2 = 0;
volatile uint16_t clock3 = 0;
int16_t overheatLevel = 0;
volatile uint8_t range = RED;
uint8_t TRK_OF = 0;

uint32_t timerPackOff, timerOverheat;

//flags
volatile bool blast = false;
bool protonActivated = false;
bool protonArmed = false;
bool protonFired = false;
bool protonVent = false;
bool TrackPlay = false;

////////////////////////////////////////////////////



//for seers
volatile bool sLed1 = false;
volatile bool sLed2 = false;
volatile bool sLed3 = false;
volatile bool sLedA = false;
volatile bool sLedW = false;

bool startOvSound = false;

//for cyclotron
volatile uint16_t counterTimeCyclotron = 0;
volatile uint16_t counterTimeBright = 0;
volatile uint8_t cycC = 0;
uint8_t C_BRIGHT[sizeof(cyclotron)];



//for powercell
uint16_t powC = 1;
uint8_t counterTimePowercell = 0;
uint8_t PowercellSpeed = POWERCELL_DEFAULT_SPEED;



//for bargraph
uint8_t barC = 0;
uint8_t counterTimeBargraph = 0;
uint8_t BargraphSpeed = BARGRAPH_DEFAULT_SPEED;


//for flasher
uint16_t counterTimeFlasher = 0;
uint8_t blastColor = WHITE;







//prototypes
void setPowercell(uint16_t leds);
void setBargraph(const uint16_t *leds PROGMEM, uint8_t p);
void setCyclotron(uint8_t leds, uint8_t color);
void setSeers(uint8_t leds);
void setBlastLeds(uint8_t color);
void classicProtonPack(void);
void HybrideProtonPack(void);
void TVGProtonPack(void);
void playFile(uint8_t FILE_N);
void playFile(uint8_t FILE_N, uint8_t offset);
bool mp3IsPlaying(void);
void callOverheatPin(void);



void setup() {

  //For debug
  Serial.begin(115200);
  Serial.println("Proton Pack Program by protongamer");
  //For mp3
  Serial1.begin(9600);
  mp3_set_serial(Serial1); //attribute Serial1 for mp3
  mp3_set_volume(VOLUME);
  delay(50);
  mp3_play(CHANGE_BANK);
  delay(50);
#ifdef DEBUG
  Serial.println("Routines Values :");
  Serial.print("fire animation default value : ");
  Serial.println(USE_THIS);
  Serial.print("Number of frames(fire) : ");
  Serial.println(sizeof(fire) / sizeof(fire[0]));
#endif

  //Init Pins
  for (uint8_t i = 0; i < sizeof(powercell); i++) {
    pinMode(powercell[i], OUTPUT);
  }
  for (uint8_t i = 0; i < sizeof(bargraph); i++) {
    pinMode(bargraph[i], OUTPUT);
  }
  for (uint8_t i = 0; i < sizeof(cyclotron); i++) {
    //pinMode(cyclotron[i], OUTPUT); don't need it arduino core do this job for analogWrite
    C_BRIGHT[i] = 0; //for TVG
  }
  for (uint8_t i = 0; i < sizeof(colorFilter); i++) {
    pinMode(colorFilter[i], OUTPUT);
  }
  for (uint8_t i = 0; i < sizeof(seers); i++) {
    pinMode(seers[i], OUTPUT);
  }
  for (uint8_t i = 0; i < sizeof(specialPins); i++) {
    pinMode(specialPins[i], OUTPUT);
  }
  for (uint8_t i = 0; i < sizeof(buttons); i++) {
    pinMode(buttons[i], INPUT);
  }

  pinMode(MP3_BUSY_PIN, INPUT);

  digitalWrite(BLAST_RELAY, HIGH);

  digitalWrite(CMD_EXT_CIRCUIT, LOW); //never forget that pin must have LOW level(for a pull up circuit set)

  //delay(3000);
  cli();
  //TCCR5A = 0;
  TCCR5B = _BV(CS51); //set DIV8 prescaler
  TIMSK5 &= ~_BV(TOIE5);
  sei();
}



ISR(TIMER5_OVF_vect) {
  //put light stuff here


  //blast part
  counterTimeFlasher++;

  digitalWrite(BLAST_RELAY, !blast);

  if (blast) {


#ifndef ENABLE_BB

#ifndef ENABLE_TVG
    blastColor = (protonArmed ? DEFAULT_BLAST_COLOR_1 : DEFAULT_BLAST_COLOR_2);
#else

#if TVG_BLAST_TYPE == RGB_BLAST
    blastColor = range;
#elif TVG_BLAST_TYPE == COLOR_1_BLAST
    blastColor = DEFAULT_BLAST_COLOR_1;
#elif TVG_BLAST_TYPE == COLOR_2_BLAST
    blastColor = DEFAULT_BLAST_COLOR_2;
#endif

#endif

#else //ENABLE_BB

   // if (BANK == CLASSIC_BANK) {

      blastColor = (protonArmed ? DEFAULT_BLAST_COLOR_1 : DEFAULT_BLAST_COLOR_2);

  /*  } else { //TVG_BANK

#if TVG_BLAST_TYPE == RGB_BLAST
      blastColor = range;
#elif TVG_BLAST_TYPE == COLOR_1_BLAST
      blastColor = DEFAULT_BLAST_COLOR_1;
#elif TVG_BLAST_TYPE == COLOR_2_BLAST
      blastColor = DEFAULT_BLAST_COLOR_2;
#endif

    }*/

#endif



  } else {
    blastColor = NOCOLOR;//turn off flasher
  }

  if (counterTimeFlasher > FLASH_DEFAULT_SPEED) {
    setBlastLeds(blastColor);
    counterTimeFlasher = 0;
  }



  ////////////////////////////////////////////////////////
  //Powercell part

  if (counterTimePowercell > POWERCELL_DEFAULT_SPEED - map(overheatLevel, 0, 100, 0, POWERCELL_DEFAULT_SPEED)) { //if counterTime overflow value
    //update powercell

    powC <<= 1; //bitwise on left by 1
    powC |= 1; //add new 1 value bit

    setPowercell(powC); //send value

#ifdef DEBUG
    Serial.print("powercell(bin) : ");
    Serial.println(powC, BIN);
#endif

    if (powC >= 65535) { //if 0b1111111111111111(powercell full)
      powC = 0; //back to 0
    }
    counterTimePowercell = 0; //reset counter
  }
  counterTimePowercell++; //increment counter

  ///////////////////////////////////////////////////////
  //Bargraph part

#if BARGRAPH_OVERHEAT == SPEED_ANIMATION
  //Serial.println("Bargraph Count status : ");
  //Serial.println(BARGRAPH_DEFAULT_SPEED - map(overheatLevel, 0, 100, 0, BARGRAPH_DEFAULT_SPEED));
  if (counterTimeBargraph > BARGRAPH_DEFAULT_SPEED - map(overheatLevel, 0, 100, 0, BARGRAPH_DEFAULT_SPEED)) { //if counterTime overflow value
#else
  if (counterTimeBargraph > BARGRAPH_DEFAULT_SPEED) { //if counterTime overflow value
#endif

    //update bargraph

    if (blast) { //if rookie fire

#ifndef ENABLE_BB //not defined

#ifndef ENABLE_TVG //CLASSIC
      setBargraph(fire, barC);
      barC++;
      if (barC >= sizeof(fire) / sizeof(fire[0])) {
        barC = 0;
      }

#else //TVG


#if BARGRAPH_OVERHEAT == SPEED_ANIMATION

      setBargraph(fire, barC);
      barC++;
      if (barC >= sizeof(fire) / sizeof(fire[0])) {
        barC = 0;
      }
#else //CLASSIC_ANIMATION


#if DEBUG
      Serial.print("OV_LVL STATUS : ");
      Serial.println(map(overheatLevel, 0, OVERHEAT_THRESHOLD_2, 0, (sizeof(fire) / sizeof(fire[0]))));
#endif
      setBargraph(fire, map(overheatLevel, 0, OVERHEAT_THRESHOLD_2, 0, (sizeof(fireOH) / sizeof(fireOH[0])) - 1));

#endif //BARGRAPH_OVERHEAT == SPEED_ANIMATION


#endif //ENABLE_TVG

#else //ENABLE_BB

      if (BANK == CLASSIC_BANK) {
        setBargraph(fire, barC);
        barC++;
        if (barC >= sizeof(fire) / sizeof(fire[0])) {
          barC = 0;
        }

      } else {


#if BARGRAPH_OVERHEAT == SPEED_ANIMATION

        setBargraph(fire, barC);
        barC++;
        if (barC >= sizeof(fire) / sizeof(fire[0])) {
          barC = 0;
        }
#else //TVG


#if DEBUG
        Serial.print("OV_LVL STATUS : ");
        Serial.println(map(overheatLevel, 0, OVERHEAT_THRESHOLD_2, 0, (sizeof(fireOH) / sizeof(fireOH[0])) - 1));
#endif
        setBargraph(fireOH, map(overheatLevel, 0, OVERHEAT_THRESHOLD_2, 0, (sizeof(fireOH) / sizeof(fireOH[0])) - 1));

#endif //BARGRAPH_OVERHEAT == SPEED_ANIMATION

      }


#endif //ENABLE_BB



#ifdef DEBUG
      Serial.print("bargraph(bin) fire : ");
      Serial.println(pgm_read_word(&fire[barC]), BIN);
#endif

    } else { //if rookie is rookie


#ifndef ENABLE_BB //not defined

#ifndef ENABLE_TVG//ENABLE_TVG CLASSIC
      setBargraph(idle, barC);
      barC++;
      if (barC >= sizeof(idle) / sizeof(idle[0])) {
        barC = 0;
      }

#else //ENABLE_TVG TVG

#if BARGRAPH_OVERHEAT == CLASSIC_ANIMATION

      //accurate animation
      if (overheatLevel <= 0) {
        setBargraph(idle, barC);
        barC++;
        if (barC >= sizeof(idle) / sizeof(idle[0])) {
          barC = 0;
        }
      } else {

#if DEBUG
        Serial.print("OV_LVL STATUS : ");
        Serial.println(map(overheatLevel, 0, 100, 0, (sizeof(fireOH) / sizeof(fireOH[0])) - 1));
#endif
        setBargraph(fireOH, map(overheatLevel, 0, 100, 0, (sizeof(fireOH) / sizeof(fireOH[0])) - 1));
      }

#else //BARGRAPH_OVERHEAT
      //speed animation
      setBargraph(idle, barC);
      barC++;
      if (barC >= sizeof(idle) / sizeof(idle[0])) {
        barC = 0;
      }

#endif//BARGRAPH_OVERHEAT

#endif//ENABLE_TVG TVG



#else //ENABLE_BB defined

      if (BANK == CLASSIC_BANK) {
        setBargraph(idle, barC);
        barC++;
        if (barC >= sizeof(idle) / sizeof(idle[0])) {
          barC = 0;
        }

      } else {

#if BARGRAPH_OVERHEAT == CLASSIC_ANIMATION

        //accurate animation
        if (overheatLevel <= 0) {
          setBargraph(idle, barC);
          barC++;
          if (barC >= sizeof(idle) / sizeof(idle[0])) {
            barC = 0;
          }
        } else {

#if DEBUG
          Serial.print("OV_LVL STATUS : ");
          Serial.println(map(overheatLevel, 0, 100, 0, (sizeof(fireOH) / sizeof(fireOH[0])) - 1));
#endif
          setBargraph(fireOH, map(overheatLevel, 0, 100, 0, (sizeof(fireOH) / sizeof(fireOH[0])) - 1));
        }

#else //BARGRAPH_OVERHEAT
        //speed animation
        setBargraph(idle, barC);
        barC++;
        if (barC >= sizeof(idle) / sizeof(idle[0])) {
          barC = 0;
        }

#endif//BARGRAPH_OVERHEAT

      }

#endif //ENABLE_BB


#ifdef DEBUG
      Serial.print("bargraph(bin) idle : ");
      Serial.println(pgm_read_word(&idle[barC]), BIN);
#endif

    }

    counterTimeBargraph = 0; //reset counter
  }
  counterTimeBargraph++; //increment counter


  ///////////////////////////////////////////////////////
  //Cyclotron part


#ifndef ENABLE_BB

#ifndef ENABLE_TVG //if classic cyclotron
  counterTimeCyclotron++;
  if (counterTimeCyclotron > CLASSIC_CYCLOTRON_COUNTER_OVERFLOW) {
    setCyclotron(cycC, CLASSIC_COLOR);
    cycC++;
    if (cycC >= sizeof(cyclotron)) { //ensure to not overflow cyclotron array
      cycC = 0;//reset counter
    }
    counterTimeCyclotron = 0;
  }
#else //if not -> TVG cyclotron
  counterTimeCyclotron++;
  if (counterTimeCyclotron > TVG_CYCLOTRON_COUNTER_OVERFLOW  - map(overheatLevel, 0, 100, 0, TVG_CYCLOTRON_COUNTER_OVERFLOW)) {
    cycC++;
    if (cycC >= 4) {
      cycC = 0;
    }
    counterTimeCyclotron = 0;
  }

  if (counterTimeBright > TVG_CYCLOTRON_COUNTER_BRIGHT) {
    setCyclotron(cycC, range);
    counterTimeBright = 0;
  }
  counterTimeBright++;
#endif //cyclotron

#else //ENABLE_BB

  if (BANK == CLASSIC_BANK) {
    counterTimeCyclotron++;
    if (counterTimeCyclotron > CLASSIC_CYCLOTRON_COUNTER_OVERFLOW) {
      setCyclotron(cycC, CLASSIC_COLOR);
      cycC++;
      if (cycC >= sizeof(cyclotron)) { //ensure to not overflow cyclotron array
        cycC = 0;//reset counter
      }
      counterTimeCyclotron = 0;
    }
  } else {
    counterTimeCyclotron++;
    if (counterTimeCyclotron > TVG_CYCLOTRON_COUNTER_OVERFLOW  - map(overheatLevel, 0, 100, 0, TVG_CYCLOTRON_COUNTER_OVERFLOW)) {
      cycC++;
      if (cycC >= 4) {
        cycC = 0;
      }
      counterTimeCyclotron = 0;
    }

    if (counterTimeBright > TVG_CYCLOTRON_COUNTER_BRIGHT) {
      setCyclotron(cycC, range);
      counterTimeBright = 0;
    }
    counterTimeBright++;
  }

#endif //ENABLE_BB



  ///////////////////////////////////////////////////////////
  //Seers stuff

  if (counterTimeSeers > SEERS_DEFAULT_SPEED) {

    //this stuff is not finished
#ifdef DEBUG
    Serial.print("clock1 : ");
    Serial.println(clock1);
    Serial.print("clock2 : ");
    Serial.println(clock2);
#endif
    clock1++;
    if (clock1 > CLOCK_SEERS_1) {
      sLed1 = !sLed1;
      sLed2 = !sLed1;
      clock1 = 0;
    }

    clock2++;
    if (clock2 > CLOCK_SEERS_2) {

#ifndef ENABLE_BB

#ifndef ENABLE_TVG //classic

      sLedW = !sLedW;

#else //TVG proton pack

      if (overheatLevel > OVERHEAT_THRESHOLD_1) {
        sLedW = !sLedW;
      }
#endif //ENABLE_TVG

#else //ENABLE_BB

      if (BANK == CLASSIC_BANK) {

        sLedW = !sLedW;

      } else {

        if (overheatLevel > OVERHEAT_THRESHOLD_1) {
          sLedW = !sLedW;
        }
      }

#endif //ENABLE_BB

      clock2 = 0;
    }

    //add seers if proton pack is armed (sLedA)

    clock3++;
    if (clock3 > CLOCK_SEERS_3) {
      //sLed3 = (!sLed3 & protonArmed); //see bitwise operation for blink effect
      sLed3 = protonArmed; 
      clock3 = 0;
    }

    sLedA = protonActivated;
    //sLed3 = protonArmed;

    //add seers if proton pack is activated (sLed3)
    //add seers if proton pack is overheated (sLedW)

    //Very bad coding (russian accent)
    seersByte = sLed1;
    seersByte <<= 1;
    seersByte |= sLed2;
    seersByte <<= 1;
    seersByte |= sLed3;
    seersByte <<= 1;
    seersByte |= sLedA;
    seersByte <<= 1;
    seersByte |= sLedW;
    seersByte <<= 1;
    seersByte |= 1;
#ifdef DEBUG
    Serial.print("seersByte : ");
    Serial.println(seersByte, BIN);
#endif
    setSeers(seersByte);

    counterTimeSeers = 0;

  }
  counterTimeSeers++;



  //////////////////////////////////////////////////////////
  //ext clock stuff

  extCounter++;
  /*if (extCounter >= EXT_CLOCK_COUNTER) {
    digitalWrite(EXT_CLOCK, !digitalRead(EXT_CLOCK));
  }*/

if (extCounter >= map(overheatLevel, 0, 100, EXT_CLOCK_COUNTER, 5)) {
    digitalWrite(EXT_CLOCK, !digitalRead(EXT_CLOCK));
  }
	  


}//end of ISR TIMER 5




void loop() {

  //Main process
  if (digitalRead(SW1) && !protonActivated) { //turn on proton pack
    digitalWrite(S_PIN_2, LOW); //turn off this light
    //enable interrupts
    cli();
    //TCCR5A = 0;
    TIMSK5 |= _BV(TOIE5);
    sei();
    //add pack on sound(here)
#ifndef ENABLE_BB
#ifndef ENABLE_TVG //classic proton pack program
    playFile(CLASSIC_BOOT_ON);
#else
    playFile(TVG_BOOT_ON);
#endif
#else //ENABLE_BB
    if (BANK == CLASSIC_BANK) {
      playFile(CLASSIC_BOOT_ON);
    } else {
      playFile(TVG_BOOT_ON);
    }
#endif//ENABLE_BB
    protonActivated = true;
  }
  if (!digitalRead(SW1) && protonActivated) { //turn off proton pack
    //disable interrupts
    cli();
    //TCCR5A = 0;
    TIMSK5 &= ~_BV(TOIE5);
    sei();
    //power off pins
    for (uint8_t i = 0; i < sizeof(powercell); i++) {
      digitalWrite(powercell[i], LOW);
    }
    for (uint8_t i = 0; i < sizeof(bargraph); i++) {
      digitalWrite(bargraph[i], LOW);
    }
    for (uint8_t i = 0; i < sizeof(cyclotron); i++) {
      //digitalWrite(cyclotron[i], OUTPUT); don't need it arduino core do this job for analogWrite
      C_BRIGHT[i] = 0; //for TVG
    }
    for (uint8_t i = 0; i < sizeof(colorFilter); i++) {
      digitalWrite(colorFilter[i], LOW);
    }
    for (uint8_t i = 0; i < sizeof(seers); i++) {
      digitalWrite(seers[i], LOW);
    }
    for (uint8_t i = 0; i < sizeof(specialPins); i++) {
      digitalWrite(specialPins[i], LOW);
    }

    digitalWrite(BLAST_RELAY, HIGH);
    
    //reset vars
    powC = 1;
    barC = 0;
#ifndef ENABLE_BB
#ifndef ENABLE_TVG //classic proton pack program
    playFile(CLASSIC_BOOT_OFF);
#else
    playFile(TVG_BOOT_OFF);
#endif
#else //ENABLE_BB
    if (BANK == CLASSIC_BANK) {
      playFile(CLASSIC_BOOT_OFF);
    } else {
      playFile(TVG_BOOT_OFF);
    }
#endif //ENABLE_BB
    //add pack off sound(here)
    protonActivated = false;
  }



  if (protonActivated) { //pack on
    TrackPlay = false;
#ifndef ENABLE_BB
#ifndef ENABLE_TVG //classic proton pack program
    classicProtonPack();
#else //the video game proton pack program
#ifndef ENABLE_HYBRIDE
    TVGProtonPack();
#else
    HybrideProtonPack();
#endif
#endif
#else //ENABLE_BB
    if (BANK == CLASSIC_BANK) {
      classicProtonPack();
    } else {
#ifndef ENABLE_HYBRIDE
      TVGProtonPack();
#else
      HybrideProtonPack();
#endif
    }
#endif //ENABLE_BB


  } else { //pack off
    if (millis() - timerPackOff >= 1000) {
      digitalWrite(S_PIN_2, !digitalRead(S_PIN_2));
      timerPackOff = millis();
    }

    //add music track here

    if (digitalRead(BUT1)) {
      delay(50);
      while (digitalRead(BUT1));
      playFile(TRACK_1, TRK_OF);
	  TRK_OF++;
	  if(TRK_OF >= NUMBER_OF_TRACKS){
		  TRK_OF = 0;
	  }
      TrackPlay = true;
    }

    if (!mp3IsPlaying() && TrackPlay) {

      uint16_t vuMeter = 20 * log(analogRead(SOUND_PIN));
      Serial.println(vuMeter);
      vuMeter = constrain(vuMeter, MIN_VALUE, MAX_VALUE);
      vuMeter = map(vuMeter, MIN_VALUE, MAX_VALUE, 0, (sizeof(fireOH) / sizeof(fireOH[0])) - 1);
      setBargraph(fireOH, vuMeter);
      setPowercell(pgm_read_word(&fireOH[vuMeter]));
      for (uint8_t i = 0; i < sizeof(cyclotron); i++) {
        //digitalWrite(cyclotron[i], LOW);

#if DEFAULT_CYCLOTRON_COLOR == RED
        analogWrite(C_RED, MAX_BRIGHT);
#elif DEFAULT_CYCLOTRON_COLOR == GREEN
        analogWrite(C_GREEN, MAX_BRIGHT);
#elif DEFAULT_CYCLOTRON_COLOR == BLUE
        analogWrite(C_BLUE, MAX_BRIGHT);
#elif DEFAULT_CYCLOTRON_COLOR == YELLOW
        analogWrite(C_RED, MAX_BRIGHT);
        analogWrite(C_GREEN, MAX_BRIGHT);
#elif DEFAULT_CYCLOTRON_COLOR == PURPLE
        analogWrite(C_RED, MAX_BRIGHT);
        analogWrite(C_BLUE, MAX_BRIGHT);
#elif DEFAULT_CYCLOTRON_COLOR == CYAN
        analogWrite(C_GREEN, MAX_BRIGHT);
        analogWrite(C_BLUE, MAX_BRIGHT);
#elif DEFAULT_CYCLOTRON_COLOR == WHITE
        analogWrite(C_RED, MAX_BRIGHT);
        analogWrite(C_GREEN, MAX_BRIGHT);
        analogWrite(C_BLUE, MAX_BRIGHT);
#endif

        analogWrite(cyclotron[i] , map(vuMeter, 0, (sizeof(fireOH) / sizeof(fireOH[0])) - 1, 0, MAX_BRIGHT));
      }
    } else {
      setBargraph(fireOH, 0);
      setPowercell(0);
      analogWrite(C_RED, 0);
      analogWrite(C_GREEN, 0);
      analogWrite(C_BLUE, 0);
    }

    //add change bank function
#ifdef ENABLE_BB
    if (digitalRead(BUT2)) {
      playFile(CHANGE_BANK);
      delay(100);
      while (!mp3IsPlaying()); //while mp3 play
      BANK = !BANK;
    }
#endif
  }

}



//That programs

///////////////////////////////////////////////////////////
//Classic program
void classicProtonPack(void) {

  if (!blast) {
    if (digitalRead(SW2) && !protonArmed) {
      //add sound(here)
      playFile(CLASSIC_PWR_UP);
      protonArmed = true;
    }

    if (!digitalRead(SW2) && protonArmed) {
      //add sound(here)
      playFile(CLASSIC_PWR_DOWN);
      protonArmed = false;
    }
  }




  if ((digitalRead(BUT1) || digitalRead(BUT2)) && !blast) {
    //add fire sound(here)
    playFile(protonArmed ? CLASSIC_BLAST_1 : CLASSIC_BLAST_2);
    blast = true;
  }

  if (!digitalRead(BUT1) && !digitalRead(BUT2) && blast) {
    //add stop sound(here)
    playFile(protonArmed ? CLASSIC_STOP_1 : CLASSIC_STOP_2);
    blast = false;
  }



}




///////////////////////////////////////////////////////////
//TVG program



void HybrideProtonPack(void) {


  if (overheatLevel < OVERHEAT_THRESHOLD_1) {
    sLedW = 0;
  }

  if (!blast) {
    if (digitalRead(SW2) && !protonArmed) {

      //add arm sound(here)
      playFile(TVG_BOOT_ON);
      delay(100);
      protonArmed = true;
    }

    if (!digitalRead(SW2) && protonArmed) {

     if (overheatLevel > 0) {
        playFile(TVG_PCK_VENT);
        digitalWrite(S_LED_PIN, HIGH);
        while (overheatLevel > 0) {
          overheatLevel--;
          delay(10);
        }
        digitalWrite(S_LED_PIN, LOW);
        overheatLevel = 0;
      } else {
        playFile(TVG_DRY_VENT);
      }
      
      protonArmed = false;
    }

  }


  //add loop sound if proton armed and no shoot
  if (protonArmed && !blast) {
    if (mp3IsPlaying()) { //if player don't play
      //play loop hum according range
      playFile(TVG_LOOP_1);
      delay(100);
    }
  }



  //UNUSED
  /* if (digitalRead(BUT2)) {//dart blast

     if (protonArmed) {
       //blast dart
       overheatLevel += DART_OV_INCREMENT;
       if (overheatLevel >= OVERHEAT_THRESHOLD_2) {
         //Overheat Sequence
         overheatLevel = OVERHEAT_THRESHOLD_2;

         playFile(range == RED ? TVG_BLAST_1B_OV : range == BLUE ? TVG_BLAST_2B_OV : range == GREEN ? TVG_BLAST_3B_OV : TVG_BLAST_4B_OV);
         delay(100);
         while (!mp3IsPlaying()); //wait for play finished

         playFile(TVG_OVERHEAT);
         digitalWrite(S_LED_PIN, HIGH);
         delay(START_SMOKE_DELAY + 100);

         while (!mp3IsPlaying()) { //wait for play finished
           if (overheatLevel > 1) {
             digitalWrite(S_RELAY_PIN, HIGH);
             overheatLevel--;
             delay(10);
           } else {
             digitalWrite(S_RELAY_PIN, LOW);
           }
         }

         //Once sequence finished
         digitalWrite(S_LED_PIN, LOW);
         overheatLevel = 0;

       } else {
         playFile(range == RED ? TVG_BLAST_1B : range == BLUE ? TVG_BLAST_2B : range == GREEN ? TVG_BLAST_3B : TVG_BLAST_4B);
       }
       blast = true;
       delay(250);
       blast = false;
       delay(1000);
     }

    }*/

if(!digitalRead(BUT2)){

  if (digitalRead(BUT1) && !blast) { //multi fonction button

    if (protonArmed) {//normal blast
      //add fire sound(here)
      playFile(CLASSIC_BLAST_2);
      blast = true;
      delay(1000);
    }

  }

  if (!digitalRead(BUT1) && blast) {
    //add stop sound(here)
    playFile(CLASSIC_STOP_2);
    delay(100);
    blast = false;
  }

}

if(!digitalRead(BUT1)){

  if (digitalRead(BUT2) && !blast) { //multi fonction button

    if (protonArmed) {//normal blast
      //add fire sound(here)
      playFile(CLASSIC_BLAST_1);
      blast = true;
      delay(1000);
    } /*else { //refresh sequence

      //add safe on sound(here)
      if (overheatLevel > 0) {
        playFile(TVG_PCK_VENT);
        digitalWrite(S_LED_PIN, HIGH);
        while (overheatLevel > 0) {
          overheatLevel--;
          delay(10);
        }
        digitalWrite(S_LED_PIN, LOW);
        overheatLevel = 0;
      } else {
        playFile(TVG_DRY_VENT);
      }


    }*/

  }
  

 if (!digitalRead(BUT2) && blast) {
    //add stop sound(here)
    playFile(CLASSIC_STOP_1);
    delay(100);
    blast = false;
  }


}

  //UNUSED
  /*else { //if not of course change range


    uint8_t tempRange = range;
    tempRange++;
    if (tempRange > 4) {
      tempRange = 1;
    }
    playFile(tempRange == RED ? TVG_RANGE_1 : tempRange == BLUE ? TVG_RANGE_2 : tempRange == GREEN ? TVG_RANGE_3 : TVG_RANGE_4);
    delay(100);
    range = NOCOLOR;
    while(!mp3IsPlaying()); //wait for sound finished
    range  = tempRange;
    delay(100);
    }//end of range select
  */




  if (blast) { //if blast(BLAST_XA)

    if (millis() - timerOverheat > 250) {
      overheatLevel++;
      timerOverheat = millis();
    }

    if (overheatLevel > OVERHEAT_THRESHOLD_1 && !startOvSound) {
      playFile(digitalRead(BUT1) ? HYBRIDE_BLAST_2_OV : HYBRIDE_BLAST_1_OV);
      delay(100);
      startOvSound = true;
    }

    if (overheatLevel > OVERHEAT_THRESHOLD_2) { //start overheat sequence(here)
      //overheatLevel = OVERHEAT_THRESHOLD_2;
      //Overheat Sequence

      playFile(digitalRead(BUT1) ? HYBRIDE_STOP_2_OV : HYBRIDE_STOP_1_OV);
      blast = false;
      delay(100);
      while (!mp3IsPlaying());
      playFile(TVG_OVERHEAT);
      callOverheatPin(); //tell to another circuit to change state !
      digitalWrite(S_LED_PIN, HIGH);
      delay(START_SMOKE_DELAY + 100);

      while (!mp3IsPlaying()) { //wait for play finished
        if (overheatLevel > 1) {
          digitalWrite(S_RELAY_PIN, HIGH);
          overheatLevel--;
          delay(10);
        } else {
          digitalWrite(S_RELAY_PIN, LOW);
        }
      }

      //Once sequence finished
      digitalWrite(S_LED_PIN, LOW);
      callOverheatPin(); //tell to another circuit to change state !
      overheatLevel = 0;
    }

  } else {

    startOvSound = false;

    if (millis() - timerOverheat > 1000) {
      overheatLevel--;
      timerOverheat = millis();
    }



    if (overheatLevel < 0) {
      overheatLevel = 0;
    }

  }



}






void TVGProtonPack(void) {


  if (overheatLevel < OVERHEAT_THRESHOLD_1) {
    sLedW = 0;
  }

  if (!blast) {
    if (digitalRead(SW2) && !protonArmed) {

      //add arm sound(here)
      playFile(TVG_BOOT_ON);
      delay(100);
      protonArmed = true;
    }

    if (!digitalRead(SW2) && protonArmed) {

      //add safe on sound(here)
      if (overheatLevel > 0) {
        playFile(TVG_PCK_VENT);
        digitalWrite(S_LED_PIN, HIGH);
        while (overheatLevel > 0) {
          overheatLevel--;
          delay(10);
        }
        digitalWrite(S_LED_PIN, LOW);
        overheatLevel = 0;
      } else {
        playFile(TVG_DRY_VENT);
      }

      protonArmed = false;
    }

  }


  //add loop sound if proton armed and no shoot
  if (protonArmed && !blast) {
    if (mp3IsPlaying()) { //if player don't play
      //play loop hum according range
      playFile(range == RED ? TVG_LOOP_1 : range == BLUE ? TVG_LOOP_2 : range == GREEN ? TVG_LOOP_3 : TVG_LOOP_4);
      delay(100);
    }
  }


  if (digitalRead(BUT2)) {//dart blast

    if (protonArmed) {
      //blast dart
      overheatLevel += DART_OV_INCREMENT;
      if (overheatLevel >= OVERHEAT_THRESHOLD_2) {
        //Overheat Sequence
        overheatLevel = OVERHEAT_THRESHOLD_2;

        playFile(range == RED ? TVG_BLAST_1B_OV : range == BLUE ? TVG_BLAST_2B_OV : range == GREEN ? TVG_BLAST_3B_OV : TVG_BLAST_4B_OV);
        delay(100);
        while (!mp3IsPlaying()); //wait for play finished

        playFile(TVG_OVERHEAT);
        callOverheatPin(); //tell to another circuit to change state !
        digitalWrite(S_LED_PIN, HIGH);
        delay(START_SMOKE_DELAY + 100);

        while (!mp3IsPlaying()) { //wait for play finished
          if (overheatLevel > 1) {
            digitalWrite(S_RELAY_PIN, HIGH);
            overheatLevel--;
            delay(10);
          } else {
            digitalWrite(S_RELAY_PIN, LOW);
          }
        }

        //Once sequence finished
        digitalWrite(S_LED_PIN, LOW);
        callOverheatPin(); //tell to another circuit to change state !
        overheatLevel = 0;

      } else {
        playFile(range == RED ? TVG_BLAST_1B : range == BLUE ? TVG_BLAST_2B : range == GREEN ? TVG_BLAST_3B : TVG_BLAST_4B);
      }
      blast = true;
      delay(250);
      blast = false;
      delay(1000);
    }

  }

  if (digitalRead(BUT1) && !blast) { //multi fonction button

    if (protonArmed) {//normal blast
      //add fire sound(here)
      playFile(range == RED ? TVG_BLAST_1A : range == BLUE ? TVG_BLAST_2A : range == GREEN ? TVG_BLAST_3A : TVG_BLAST_4A);
      blast = true;
      delay(1000);
    }
    else { //if not of course change range


      uint8_t tempRange = range;
      tempRange++;
      if (tempRange > 4) {
        tempRange = 1;
      }
      playFile(tempRange == RED ? TVG_RANGE_1 : tempRange == BLUE ? TVG_RANGE_2 : tempRange == GREEN ? TVG_RANGE_3 : TVG_RANGE_4);
      delay(100);
      range = NOCOLOR;
      while (!mp3IsPlaying()); //wait for sound finished
      range  = tempRange;
      delay(100);
    }//end of range select

  }

  if (!digitalRead(BUT1) && blast) {
    //add stop sound(here)
    playFile(range == RED ? TVG_STOP_1 : range == BLUE ? TVG_STOP_2 : range == GREEN ? TVG_STOP_3 : TVG_STOP_4);
    delay(100);
    blast = false;
  }

  if (blast) { //if blast(BLAST_XA)

    if (millis() - timerOverheat > 250) {
      overheatLevel++;
      timerOverheat = millis();
    }

    if (overheatLevel > OVERHEAT_THRESHOLD_1 && !startOvSound) {
      playFile(range == RED ? TVG_BLAST_1A_OV : range == BLUE ? TVG_BLAST_2A_OV : range == GREEN ? TVG_BLAST_3A_OV : TVG_BLAST_4A_OV);
      delay(100);
      startOvSound = true;
    }

    if (overheatLevel > OVERHEAT_THRESHOLD_2) { //start overheat sequence(here)
      //overheatLevel = OVERHEAT_THRESHOLD_2;
      //Overheat Sequence
      playFile(range == RED ? TVG_STOP_1_OV : range == BLUE ? TVG_STOP_2_OV : range == GREEN ? TVG_STOP_3_OV : TVG_STOP_4_OV);
      blast = false;
      delay(100);
      while (!mp3IsPlaying());
      playFile(TVG_OVERHEAT);
      callOverheatPin(); //tell to another circuit to change state !
      digitalWrite(S_LED_PIN, HIGH);
      delay(START_SMOKE_DELAY + 100);

      while (!mp3IsPlaying()) { //wait for play finished
        if (overheatLevel > 1) {
          digitalWrite(S_RELAY_PIN, HIGH);
          overheatLevel--;
          delay(10);
        } else {
          digitalWrite(S_RELAY_PIN, LOW);
        }
      }

      //Once sequence finished
      digitalWrite(S_LED_PIN, LOW);
      callOverheatPin(); //tell to another circuit to change state !
      overheatLevel = 0;
    }

  } else {

    startOvSound = false;

    if (millis() - timerOverheat > 1000) {
      overheatLevel--;
      timerOverheat = millis();
    }



    if (overheatLevel < 0) {
      overheatLevel = 0;
    }

  }



}




void playFile(uint8_t FILE_N) {
#ifdef MP3_DEBUG
  Serial.print("TRYING TO PLAY : [");
  Serial.print(FILE_N);
  Serial.print("]\t");
  Serial.println(mp3Names[FILE_N - 1]);
#endif
  mp3_play(FILE_N);
  delay(30);
}





void playFile(uint8_t FILE_N, uint8_t offset) {
#ifdef MP3_DEBUG
  Serial.print("TRYING TO PLAY : [");
  Serial.print(FILE_N);
  Serial.print("]\t");
  Serial.println(mp3Names[FILE_N - 1]);
#endif
  mp3_play(FILE_N + offset);
  delay(30);
}




bool mp3IsPlaying(void) {
  return digitalRead(MP3_BUSY_PIN);
}




void setBlastLeds(uint8_t color) {

#if FLASH_EFFECT == NORMAL
  uint8_t tempFade = random(0, FLASH_BRIGHT);
#elif FLASH_EFFECT == SOUND_REACT
  uint16_t tempFade = map(20 * log(analogRead(SOUND_PIN)), MIN_VALUE, MAX_VALUE, 0, 255);
#endif

  switch (color) {

    case NOCOLOR:
      analogWrite(F_RED, 0);
      analogWrite(F_GREEN, 0);
      analogWrite(F_BLUE, 0);
      analogWrite(F_WHITE, 0);
      break;

    case CLASSIC_COLOR:

      analogWrite(F_RED, tempFade);
      analogWrite(F_BLUE, 255 - tempFade);
      break;

    case RED:
      analogWrite(F_RED, tempFade);
      break;

    case GREEN:
      analogWrite(F_GREEN, tempFade);
      break;

    case BLUE:
      analogWrite(F_BLUE, tempFade);
      break;

    case YELLOW:
      analogWrite(F_RED, tempFade);
      analogWrite(F_GREEN, tempFade);
      break;

    case WHITE:
      analogWrite(F_WHITE, tempFade);
      break;

  }

}



void setSeers(uint8_t leds) {

  uint8_t mask = 1;

  for (uint8_t i = 0; i < sizeof(seers); i++) {
    if ((mask & leds) >> i) { //if condition
      digitalWrite(seers[i], HIGH);
    } else {
      digitalWrite(seers[i], LOW);
    }
    mask <<= 1; //bitwise
  }


}



void setPowercell(uint16_t leds) {

  uint16_t mask = 1;

  for (uint8_t i = 0; i < sizeof(powercell); i++) {
    if ((mask & leds) >> i) { //if condition
      digitalWrite(powercell[i], HIGH);
    } else {
      digitalWrite(powercell[i], LOW);
    }
    mask <<= 1; //bitwise
  }


}

void setBargraph(const uint16_t *leds PROGMEM, uint8_t p) {

  uint16_t mask = 1;

  for (uint8_t i = 0; i < sizeof(bargraph); i++) {
    if ((mask & pgm_read_word(&leds[p])) >> i) { //if condition
      digitalWrite(bargraph[i], HIGH);
    } else {
      digitalWrite(bargraph[i], LOW);
    }
    mask <<= 1; //bitwise
  }


}


void setCyclotron(uint8_t leds, uint8_t color) {



  if (color == CLASSIC_COLOR) { //classic
    for (uint8_t i = 0; i < sizeof(cyclotron); i++) {
      //digitalWrite(cyclotron[i], LOW);
      analogWrite(cyclotron[i] , 255);
    }
    //digitalWrite(cyclotron[leds], HIGH);
#if DEFAULT_CYCLOTRON_COLOR == RED
    analogWrite(C_RED, MAX_BRIGHT);
#elif DEFAULT_CYCLOTRON_COLOR == GREEN
    analogWrite(C_GREEN, MAX_BRIGHT);
#elif DEFAULT_CYCLOTRON_COLOR == BLUE
    analogWrite(C_BLUE, MAX_BRIGHT);
#elif DEFAULT_CYCLOTRON_COLOR == YELLOW
    analogWrite(C_RED, MAX_BRIGHT);
    analogWrite(C_GREEN, MAX_BRIGHT);
#elif DEFAULT_CYCLOTRON_COLOR == PURPLE
    analogWrite(C_RED, MAX_BRIGHT);
    analogWrite(C_BLUE, MAX_BRIGHT);
#elif DEFAULT_CYCLOTRON_COLOR == CYAN
    analogWrite(C_GREEN, MAX_BRIGHT);
    analogWrite(C_BLUE, MAX_BRIGHT);
#elif DEFAULT_CYCLOTRON_COLOR == WHITE
    analogWrite(C_RED, MAX_BRIGHT);
    analogWrite(C_GREEN, MAX_BRIGHT);
    analogWrite(C_BLUE, MAX_BRIGHT);
#endif
    analogWrite(cyclotron[leds] , 0);
  }

  if (color != CLASSIC_COLOR) {

    //bad coding but anyway let's do this(lazy to use for loops) ;D
    analogWrite(C_RED, 0);
    analogWrite(C_GREEN, 0);
    analogWrite(C_BLUE, 0);

    switch (color) {

      case RED:
        analogWrite(C_RED, RED_BRIGHT);
        break;

      case GREEN:
        analogWrite(C_GREEN, GREEN_BRIGHT);
        break;

      case BLUE:
        analogWrite(C_BLUE, BLUE_BRIGHT);
        break;

      case YELLOW:
        analogWrite(C_RED, RED_BRIGHT);
        analogWrite(C_GREEN, GREEN_BRIGHT);
        break;

    }

    for (uint8_t i = 0; i < sizeof(cyclotron); i++) {

      if (C_BRIGHT[i] < DECREMENT_FACTOR) { // we now anyway that value goes to 0
        C_BRIGHT[i] = 0;
      } else if (C_BRIGHT[i] >= DECREMENT_FACTOR) { //otherwise decrement
        C_BRIGHT[i] -= DECREMENT_FACTOR;
      }

    }

    C_BRIGHT[cycC] = MAX_BRIGHT; //keep one led at max bright during state

    //update cyclotron
    for (uint8_t i = 0; i < sizeof(cyclotron); i++) {
      analogWrite(cyclotron[i], MAX_BRIGHT - C_BRIGHT[i]);
#ifdef DEBUG
      Serial.print(MAX_BRIGHT - C_BRIGHT[i]);
      Serial.print("\t");
#endif
    }
#ifdef DEBUG
    Serial.println();
#endif
  }





}


void callOverheatPin(void) {

  digitalWrite(CMD_EXT_CIRCUIT, HIGH);
  delay(150);
  digitalWrite(CMD_EXT_CIRCUIT, LOW);
  delay(150);

}
