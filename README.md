# Arduino-Proton-Pack


This is an example code to make a Ghostbusters Proton Pack Circuit.


Before using this code :

Ensure you have libraries listed below :

-DFPlayer_Mini_Mp3


BY USING THIS PROJECT, YOU ACCEPT THAT PROTONGAMER IS NOT RESPONSIBLE OF ANY DAMAGE AND YOU
USING IT AT YOUR OWN RISK ! THIS OPEN SOURCE PROJECT IS A FREE USE AND YOU ACCEPT THAT YOU WILL NOT 
MAKE ANY PROFITS !


## Compatible Arduino boards

-Arduino Mega 2560
-Other Board Based on ATMega2560


## Parameters

You have parameters in the header file parameters.h that you can change to configure the program

### DEBUG PARAMETERS
|   Parameter   |    Range Values    |    Description    |
| ------------- | ------------------ | ----------------- |
| DEBUG         | Comment / Uncomment | Use debug through Serial USB for miscellaneous instructions |
| MP3_DEBUG         | Comment / Uncomment | Use debug through Serial USB to print mp3 played files |

### GENERAL TIMING PARAMETERS

|   Parameter   |    Range Values    |    Description    |
| ------------- | ------------------ | ----------------- |
| POWERCELL_DEFAULT_SPEED | 0-255 | Set Powercell speed in counts (Low value = High Refresh Speed) |
| BARGRAPH_DEFAULT_SPEED | 0-255 | Set Bargraph speed in counts (Low value = High Refresh Speed) |
| SEER_DEFAULT_SPEED | 0-65535 | Set seers speed in counts (Low value = High Refresh Speed) |
| FLASH_DEFAULT_SPEED | 0-65535 | Set flash speed in counts (Low value = High Refresh Speed) |


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

### VARIOUS PARAMETERS

|   Parameter   |    Range Values    |    Description    |
| ------------- | ------------------ | ----------------- |
| ENABLE_TVG_BANK | Comment / Uncomment | Active Classic Mode (Comment) or TVG Mode (Uncomment) |
| ENABLE_BOTH_BANKS | Comment / Uncomment | Active Classic Mode and TVG Mode that user can swap without programming |
| BARGRAPH_OVERHEAT | CLASSIC_ANIMATION, SPEED_ANIMATION | Define overheat bargraph animation when proton pack goes to heat (TVG MODE ONLY) if CLASSIC_ANIMATION ==> It will use ANIMATION_OH otherwise it will use ANIMATION_X with speed depending on overheat level |
| ANIMATION_X | ANIMATION_1, ANIMATION_2, ANIMATION_3, ..., ANIMATION_20 | Define bargraph fire animation |
| EXT_CLOCK_COUNTER | 0-255 | Set External Clock Speed (Low value = High Speed) |
| FLASH_BRIGHT | 0-255 | Set Max bright value for flasher(blast leds) |
| FLASH_EFFECT | NORMAL, SOUND_REACT | Define blast effect(normal random flash or flash depending on sound file recorded through ADC) |
| MIN_VALUE | 0-1023 | Set range of min value(for SOUND_REACT) |
| MAX_VALUE | 0-1023 | Set range of max value(for SOUND_REACT) |
| TVG_BLAST_TYPE | RGB_BLAST, COLOR_1_BLAST, COLOR_2_BLAST | Define in TVG Mode a RGB Blast color depend on range selected or a same blast color(whatever of range selected) |
| DEFAULT_BLAST_COLOR_1 | CLASSIC_COLOR, RED, GREEN, BLUE, YELLOW, WHITE | Define Blast color 1 |
| DEFAULT_BLAST_COLOR_2 | CLASSIC_COLOR, RED, GREEN, BLUE, YELLOW, WHITE | Define Blast color 2 |
| VOLUME | 0-30 | Set Mp3 Dfrobot module Volume |
| OVERHEAT_THRESHOLD_1 | 40-60(advice) | Set a threshold value that advert user by sending warning sequence (TVG MODE ONLY) |
| OVERHEAT_THRESHOLD_2 | 70-90(advice) | Set a threshold value that launch overheat sequence (TVG MODE ONLY) |
| DART_OV_INCREMENT | 5-25(advice) | Set an overheat increment factor when user launch a dart blast (TVG MODE ONLY) |
| START_SMOKE_DELAY | 1000-2500(advice) | Set freeze timing before launch Smoke sequence (TVG MODE ONLY) |
| CLOCK_SEERS_1 | 0-65535 | Set blinking seers' speed in count (Low value = High Refresh Speed) |
| CLOCK_SEERS_2 | 0-65535 | Set overheat seers' speed in count (Low value = High Refresh Speed) |
| CLOCK_SEERS_3 | 0-65535 | Set Main seers' speed in count (Low value = High Refresh Speed) |


## Bargraph Animation

//add tutorial here

