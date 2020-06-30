# Arduino-Proton-Pack


This is an example code to make a Ghostbusters Proton Pack Circuit.


Before using this code :

Ensure you have libraries listed below :

-__DFPlayer_Mini_Mp3__

-__softwareSerial__

____________________________________________________________________________________________________

__BY USING THIS PROJECT, YOU ACCEPT THAT PROTONGAMER IS NOT RESPONSIBLE OF ANY DAMAGE AND YOU
USING IT AT YOUR OWN RISK ! THIS OPEN SOURCE PROJECT IS A FREE USE AND YOU ACCEPT THAT YOU WILL NOT 
MAKE ANY PROFITS !__

____________________________________________________________________________________________________


## Compatible Arduino boards

-__Arduino Mega 2560__

-__Other Board Based on ATMega2560__


____________________________________________________________________________________________________

## Parameters

You have parameters in the header file __parameters.h__ that you can change to configure __PROTON_PACK_SIMPLE.ino__

____________________________________________________________________________________________________

### DEBUG PARAMETERS
|   Parameter   |    Range Values    |    Description    |
| ------------- | ------------------ | ----------------- |
| DEBUG         | Comment / Uncomment | Use debug through Serial USB for miscellaneous instructions |
| MP3_DEBUG         | Comment / Uncomment | Use debug through Serial USB to print mp3 played files |

____________________________________________________________________________________________________

### GENERAL TIMING PARAMETERS

|   Parameter   |    Range Values    |    Description    |
| ------------- | ------------------ | ----------------- |
| POWERCELL_DEFAULT_SPEED | 0-255 | Set Powercell speed in counts (Low value = High Refresh Speed) |
| BARGRAPH_DEFAULT_SPEED | 0-255 | Set Bargraph speed in counts (Low value = High Refresh Speed) |
| SEER_DEFAULT_SPEED | 0-65535 | Set seers speed in counts (Low value = High Refresh Speed) |
| FLASH_DEFAULT_SPEED | 0-65535 | Set flash speed in counts (Low value = High Refresh Speed) |

____________________________________________________________________________________________________


### CYCLOTRON PARAMETERS

|   Parameter   |    Range Values    |    Description    |
| ------------- | ------------------ | ----------------- |
| MAX_BRIGHT | 0-255 | Set max bright for cyclotron |
| BARGRAPH_DEFAULT_SPEED | 0-255 | Set Bargraph speed in counts (Low value = High Refresh Speed) |
| SEER_DEFAULT_SPEED | 0-65535 | Set seers speed in counts (Low value = High Refresh Speed) |
| FLASH_DEFAULT_SPEED | 0-65535 | Set flash speed in counts (Low value = High Refresh Speed) |
| TVG_CYCLOTRON_COUNTER_BRIGHT | 0-65535 | Set update speed of cyclotron's bright in counts (Low value = High Refresh Speed) (TVG MODE ONLY) |
| TVG_CYCLOTRON_COUNTER_OVERFLOW | 0-65535 | Set speed of main cyclotron's animation in counts (Low value = High Refresh Speed) (TVG MODE ONLY) |
| DECREMENT_FACTOR | 0-10(advice but can overflow these value) | Set Decrement factor for cyclotron's bright depend on TVG_CYCLOTRON_COUNTER_OVERFLOW (TVG MODE ONLY) |
| RED_BRIGHT | 0-255 | Set cyclotron's red color mixing (depending on MAX_BRIGHT value) |
| GREEN_BRIGHT | 0-255 | Set cyclotron's green color mixing (depending on MAX_BRIGHT value) |
| BLUE_BRIGHT | 0-255 | Set cyclotron's blue color mixing (depending on MAX_BRIGHT value) |
| CLASSIC_CYCLOTRON_COUNTER_OVERFLOW | 0-65535 | Set speed of main cyclotron's animation in counts (Low value = High Refresh Speed) (CLASSIC MODE ONLY) |
| DEFAULT_CYCLOTRON_COLOR | RED, GREEN, BLUE, YELLOW, NOCOLOR | Set cyclotron's color (CLASSIC MODE ONLY) |

____________________________________________________________________________________________________

### VARIOUS PARAMETERS

|   Parameter   |    Range Values    |    Description    |
| ------------- | ------------------ | ----------------- |
| ENABLE_TVG_BANK | Comment / Uncomment | Active Classic Mode (Comment) or TVG Mode (Uncomment) |
| ENABLE_BOTH_BANKS | Comment / Uncomment | Active Classic Mode and TVG Mode that user can swap without programming |
| BARGRAPH_OVERHEAT | CLASSIC_ANIMATION, SPEED_ANIMATION | Define overheat bargraph animation when proton pack goes to heat (TVG MODE ONLY) if CLASSIC_ANIMATION ==> It will use ANIMATION_OH otherwise it will use ANIMATION_X with speed depending on overheat level |
| ANIMATION_X | ANIMATION_1, ANIMATION_2, ANIMATION_3, ..., ANIMATION_20 | Define bargraph fire animation |
| EXT_CLOCK_COUNTER | 0-255 | Set External Clock Speed (Low value = High Speed) |
| FLASH_EFFECT | NORMAL, SOUND_REACT | Define blast effect(normal random flash or flash depending on sound file recorded through ADC) |
| MIN_VALUE | 0-1023 | Set range of min value(for SOUND_REACT) |
| MAX_VALUE | 0-1023 | Set range of max value(for SOUND_REACT) |
| TVG_BLAST_TYPE | RGB_BLAST, COLOR_1_BLAST, COLOR_2_BLAST | Define in TVG Mode a RGB Blast color depend on range selected or a same blast color(whatever of range selected) |
| DEFAULT_BLAST_COLOR_1 | CLASSIC_COLOR, RED, GREEN, BLUE, YELLOW, WHITE | Define Blast color 1 |
| DEFAULT_BLAST_COLOR_2 | CLASSIC_COLOR, RED, GREEN, BLUE, YELLOW, WHITE | Define Blast color 2 |
| DEFAULT_RGB_BLAST_COLOR_1 | CLASSIC_COLOR, RED, GREEN, BLUE, YELLOW, WHITE, USER1_COLOR, ..., USER5_COLOR | Define RGB Blast color 1 |
| DEFAULT_RGB_BLAST_COLOR_2 | CLASSIC_COLOR, RED, GREEN, BLUE, YELLOW, WHITE, USER1_COLOR, ..., USER5_COLOR | Define RGB Blast color 2 |
| DEFAULT_RGB_BLAST_COLOR_3 | CLASSIC_COLOR, RED, GREEN, BLUE, YELLOW, WHITE, USER1_COLOR, ..., USER5_COLOR | Define RGB Blast color 3 |
| DEFAULT_RGB_BLAST_COLOR_4 | CLASSIC_COLOR, RED, GREEN, BLUE, YELLOW, WHITE, USER1_COLOR, ..., USER5_COLOR | Define RGB Blast color 4 |
| FLASH_BRIGHT | 0-255 | Set Max bright value for flasher(blast leds) |
| RED_BLAST_LEVEL | 0-255 | Set Max Bright value of RED_BLAST red color |
| GREEN_BLAST_LEVEL | 0-255 | Set Max Bright value of GREEN_BLAST green color |
| BLUE_BLAST_LEVEL | 0-255 | Set Max Bright value of BLUE_BLAST blue color |
| YELLOW_RED_BLAST_LEVEL | 0-255 | Set Max Bright value of YELLOW_BLAST red color |
| YELLOW_GREEN_BLAST_LEVEL | 0-255 | Set Max Bright value of YELLOW_BLAST green color |
| WHITE_BLAST_LEVEL | 0-255 | Set Max Bright value of WHITE_BLAST white color |
| CLASSIC_RED_BLAST_LEVEL | 0-255 | Set Max Bright value of CLASSIC_BLAST red color |
| CLASSIC_BLUE_BLAST_LEVEL | 0-255 | Set Max Bright value of CLASSIC_BLAST blue color |
| USER1_RED_BLAST_LEVEL | 0-255 | Set Max Bright value of USER1_BLAST red color |
| USER1_GREEN_BLAST_LEVEL | 0-255 | Set Max Bright value of USER1_BLAST green color |
| USER1_BLUE_BLAST_LEVEL | 0-255 | Set Max Bright value of USER1_BLAST blue color |
| USER1_WHITE_BLAST_LEVEL | 0-255 | Set Max Bright value of USER1_BLAST white color |
| USER2_RED_BLAST_LEVEL | 0-255 | Set Max Bright value of USER2_BLAST red color |
| USER2_GREEN_BLAST_LEVEL | 0-255 | Set Max Bright value of USER2_BLAST green color |
| USER2_BLUE_BLAST_LEVEL | 0-255 | Set Max Bright value of USER2_BLAST blue color |
| USER2_WHITE_BLAST_LEVEL | 0-255 | Set Max Bright value of USER2_BLAST white color |
| USER3_RED_BLAST_LEVEL | 0-255 | Set Max Bright value of USER3_BLAST red color |
| USER3_GREEN_BLAST_LEVEL | 0-255 | Set Max Bright value of USER3_BLAST green color |
| USER3_BLUE_BLAST_LEVEL | 0-255 | Set Max Bright value of USER3_BLAST blue color |
| USER3_WHITE_BLAST_LEVEL | 0-255 | Set Max Bright value of USER3_BLAST white color |
| USER4_RED_BLAST_LEVEL | 0-255 | Set Max Bright value of USER4_BLAST red color |
| USER4_GREEN_BLAST_LEVEL | 0-255 | Set Max Bright value of USER4_BLAST green color |
| USER4_BLUE_BLAST_LEVEL | 0-255 | Set Max Bright value of USER4_BLAST blue color |
| USER4_WHITE_BLAST_LEVEL | 0-255 | Set Max Bright value of USER4_BLAST white color |
| USER5_RED_BLAST_LEVEL | 0-255 | Set Max Bright value of USER5_BLAST red color |
| USER5_GREEN_BLAST_LEVEL | 0-255 | Set Max Bright value of USER5_BLAST green color |
| USER5_BLUE_BLAST_LEVEL | 0-255 | Set Max Bright value of USER5_BLAST blue color |
| USER5_WHITE_BLAST_LEVEL | 0-255 | Set Max Bright value of USER5_BLAST white color |
| VOLUME | 0-30 | Set Mp3 Dfrobot module Volume |
| OVERHEAT_THRESHOLD_1 | 40-60(advice) | Set a threshold value that advert user by sending warning sequence (TVG MODE ONLY) |
| OVERHEAT_THRESHOLD_2 | 70-90(advice) | Set a threshold value that launch overheat sequence (TVG MODE ONLY) |
| DART_OV_INCREMENT | 5-25(advice) | Set an overheat increment factor when user launch a dart blast (TVG MODE ONLY) |
| START_SMOKE_DELAY | 1000-2500(advice) | Set freeze timing before launch Smoke sequence (TVG MODE ONLY) |
| CLOCK_SEERS_1 | 0-65535 | Set blinking seers' speed in count (Low value = High Refresh Speed) |
| CLOCK_SEERS_2 | 0-65535 | Set overheat seers' speed in count (Low value = High Refresh Speed) |
| CLOCK_SEERS_3 | 0-65535 | Set Main seers' speed in count (Low value = High Refresh Speed) |

____________________________________________________________________________________________________

## Bargraph Animation

You have 2 differents animations, 1 idle animation and 1 firing animation. Idle animation launch only when user don't fire with the Proton Pack. If user start fire, the bargraph will display a firing animation(depend on parameters used).

How to configure an animation ?

For Idle animation :

Idle animation has one 16 bits type array named "idle" that you can find in __bargraph_animation.h__ . Every bits of the 16 bits type are led state depending by the bargraph pins configured array(that you can find in __PROTON_PACK_SIMPLE.ino__ file).

``` 
uint8_t bargraph[] = { B_PIN_1, B_PIN_2, B_PIN_3, B_PIN_4, B_PIN_5, B_PIN_6, B_PIN_7, B_PIN_8, B_PIN_9, B_PIN_10, B_PIN_11, B_PIN_12, B_PIN_13, B_PIN_14, B_PIN_15, }; 
```

The default idle array should be like this :

```
const uint16_t idle[] PROGMEM = {
  0b0000000000000000,
  0b0000000000000001,
  0b0000000000000011,
  0b0000000000000111,
  0b0000000000001111,
  0b0000000000011111,
  0b0000000000111111,
  0b0000000001111111,
  0b0000000011111111,
  0b0000000111111111,
  0b0000001111111111,
  0b0000011111111111,
  0b0000111111111111,
  0b0001111111111111,
  0b0011111111111111,
  0b0111111111111111,
  0b0011111111111111,
  0b0001111111111111,
  0b0000111111111111,
  0b0000011111111111,
  0b0000001111111111,
  0b0000000111111111,
  0b0000000011111111,
  0b0000000001111111,
  0b0000000000111111,
  0b0000000000011111,
  0b0000000000001111,
  0b0000000000000111,
  0b0000000000000011,
  0b0000000000000001,
};
```

The order of bits depending on pins in default should be first bit(LSB) as first pin and last bit (MSB) as last pin(not necessarily the bit 16, it could be the bit 10 if you have 10 pins !)

In example if you change idle array like this

```
const uint16_t idle[] PROGMEM = {
  0b0000000010101111,
  };
```

You should have this(1st led on the right is LSB bit) :

![BARGRAPH_STATIC](https://i.imgur.com/XggEJsm.jpg)



And if you change idle array like below

```
const uint16_t idle[] PROGMEM = {
  0b0100000011111111,
  0b0100000111111101,
  0b0100001111111001,
  0b0100011111110001,
  0b0100111111100001,
  0b0101111111000001,
  0b0111111110000001,
  0b0101111111000001,
  0b0100111111100001,
  0b0100011111110001,
  0b0100001111111001,
  0b0100000111111101,
  };
```

![BARGRAPH_ANIMATED](https://i.imgur.com/KoFsyLX.gif)



Firing animation has an array named __fire[]__ like __idle[]__ and an another array named __fireOH[]__

__fire[]__ is the default firing animation, and __fireOH[]__ is the firing animation configured as overheat level.

What is the difference between by __fire[]__ and __fireOH[]__ ?

__fire[]__ array display as an animated frame when user fire. __fireOH[]__ will display the frame according to the overheat level.


__fireOH[]__ array can be configured like __idle[]__ array. __fire[]__ array can be configured like __idle[]__ array too, but it as a dictionnary that the user can create, and choose it by the parameter __ANIMATION_X__(see __VARIOUS PARAMETERS__ table  above).

To create a new animation, you must create your array named __fire[]__ and set frame to it (of course), and add define conditions, see example below :

```
#if USE_THIS == ANIMATION_4
const uint16_t fire[] PROGMEM {

0b1100000000000011,
0b0011000000001100,
0b0000110000110000,
0b0000001111000000,
0b0000000110000000,
0b0000000000000000,

};

#endif

```



