#include <Arduino.h>
#include <Bounce2.h>
#include <BleGamepad.h>
#include "esp_adc_cal.h"
#include <config.h>

#if defined(DEBUG_MODE) || defined(DEBUG_BATTERY) || defined(DEBUG_BUTTONS) || defined(DEBUG_LOOP_TIME)
    bool ser = true;
#else
    bool ser = false;
#endif

const char* bN[10] = { 
    (char*)"Green",
    (char*)"Red",
    (char*)"Yellow",
    (char*)"Blue",
    (char*)"Orange",
    (char*)"Select",
    (char*)"Start",
    (char*)"Tilt",
    (char*)"Strum up",
    (char*)"Strum down",

};

Bounce btns[10] = { Bounce(), Bounce(), Bounce(), Bounce(), Bounce(), Bounce(), Bounce(), Bounce(), Bounce(), Bounce() };
int bpins[10] = { FRET_GREEN, FRET_RED, FRET_YELLOW, FRET_BLUE, FRET_ORANGE, SELECT, START, TILT, STRUM_UP, STRUM_DOWN };
BleGamepad pad = BleGamepad(DEVICE_NAME, "Strum.bar", 100);
BleGamepadConfiguration cfg;

bool update = false;
int ticks = 0;
int lastHit = millis();

#if defined(WHAMMY_PIN) && WHAMMY_PIN > 0
    int wp = WHAMMY_PIN;
    int wMin = 32767;
    int wSamples[WHAMMY_SAMPLES];
    int wIndex, wAvg, wTot, wMax, wLast = 0;
    adc1_channel_t wc = (wp == 34 ? ADC1_CHANNEL_6 : (wp == 35  ? ADC1_CHANNEL_7 : (wp == 36 ? ADC1_CHANNEL_0 : ADC1_CHANNEL_3)));
#else 
    int wp = 0;
#endif

#if defined(BATTERY_PIN) && BATTERY_PIN > 0
    int bp = BATTERY_PIN;   
    int bIndex, bAvg, bTot = 0;
    int bSamples[BATTERY_SAMPLES];
    int bMin = 2500;
    adc1_channel_t bc = (bp == 34 ? ADC1_CHANNEL_6 : (bp == 35  ? ADC1_CHANNEL_7 : (bp == 36 ? ADC1_CHANNEL_0 : ADC1_CHANNEL_3)));
#else
    int bp = 0;
#endif