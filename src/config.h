/**************************************
 * BLEUltraGuitar for ESP32           *
 * by Xstasy - https://strum.bar      * 
 **************************************/
// Bluetooth Device Name
const char* DEVICE_NAME=    "XGuitar";

//  Generally anything from GPIO 4 and
//     upwards can be used for buttons
#define FRET_GREEN                  32
#define FRET_RED                    33
#define FRET_YELLOW                 25
#define FRET_BLUE                   26
#define FRET_ORANGE                 27
#define FRET_BOUNCE_MS               5

#define STRUM_UP                    14
#define STRUM_DOWN                  12
#define STRUM_UP_BOUNCE_MS           5
#define STRUM_DOWN_BOUNCE_MS         5

#define START                       19
#define SELECT                      22

//  Use two mercury switches in series
//        and connect positive to GPIO
#define TILT                        15

// Pins 34,35,36,39 can be used for
// Battery voltage sensing or whammy
// Uncomment/comment to enable/disable
#define BATTERY_PIN                 35 
#define BATTERY_SAMPLES             30
#define BATTERY_HZ                  60

// Pins 34,35,36,39 can be used for
// Battery voltage sensing or whammy
// Uncomment/comment to enable/disable
#define WHAMMY_PIN                  36 
#define WHAMMY_SAMPLES              20
#define WHAMMY_HZ                    5

//#define DEBUG_MODE
//#define DEBUG_BUTTONS
//#define DEBUG_BATTERY

// This will not report in DEBUG_MODE
// because of the rate it's pushing
//#define DEBUG_LOOP_TIME 