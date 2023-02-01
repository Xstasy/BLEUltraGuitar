![](https://creativecommons.org/images/deed/cc_icon_white_x2.png) ![](https://creativecommons.org/images/deed/attribution_icon_white_x2.png) ![](https://creativecommons.org/images/deed/nc_white_x2.png) ![](https://creativecommons.org/images/deed/svg/sa_white.svg)

# BLEULtraGuitar - ESP32
ESP32 Bluetooth 4.2 Low Energy Guitar Hero Controller
- [x] ⏩1000hz polling
- [x] 🧵Multithreaded
- [x] 🪫Battery support
- [x] 👋Whammybar support
- [x] 🫠Mercury tilt switch
- [x] 🔬12 bit ADC which uses vref from efuse
- [x] 😴Deep sleep @ ~10µA - wakeup from RTC1 frets)
- [ ] 🚥LED Support from frets & strumbar (coming soon™️)

## [ License](https://github.com/Xstasy/BLEUltraGuitar/blob/master/LICENSE.md)

## Installation
- Open project from [Platform.IO](https://platformio.org/platformio-ide) home screen
- Define proper pins in config.h (or use the ones defined in there)
- Click the PIO Icon on the left menu and select upload / upload & monitor under BLEUltraGuitar >

# Default Pins
    - Green: 32,
    - Red: 33,
    - Yellow: 25,
    - Blue: 26,
    - Orange: 27 
    - Strum up: 14
    - Strum down: 12
    - Start: 22
    - Select: 19
    - Tilt: 15
    - Whammy: 36
    - Battery: 39