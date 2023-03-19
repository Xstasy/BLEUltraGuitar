

# BLEUltraGuitar - ESP32
ESP32 Bluetooth 4.2 Low Energy Guitar Hero Controller
- [x] ⏩1000hz polling (loop time is about 15µs)
- [x] 🧵Multithreaded
- [x] 🪫Battery support
- [x] 👋Whammybar support
- [x] 🫠Mercury tilt switch
- [x] 🔬12 bit ADC which uses vref from efuse
- [x] 😴Deep sleep @ ~10µA - wakeup from RTC1 pins
- [ ] 🚥LED Support from frets & strumbar (coming soon™️)

## Installation
- Open project from [Platform.IO](https://platformio.org/platformio-ide) home screen
- Define proper pins in config.h (or use the ones defined in there)
- Click the PIO Icon on the left menu and select upload / upload & monitor under BLEUltraGuitar

## Default Pins
    - Green: 32 - Red: 33 - Yellow: 25 - Blue: 26 - Orange: 27 
    - Strum up: 14 - Strum down: 12 - Start: 22 - Select: 19
    - Tilt: 15 - Whammy: 36 - Battery: 39

[$2.31 ESP32 with battery charging circuit + connector](https://www.aliexpress.com/item/33009178296.html) @ Aliexpress

I've personally ordered a few of these and I've not yet had a failing item.

![](https://i.imgur.com/ay6bxRN.png)


There's also ESP32-S3 which will support USB host connection if you don't want to rely on 850hz BT 4.2 (even though it is more than enough)


## [ License](https://github.com/Xstasy/BLEUltraGuitar/blob/master/LICENSE.md)

![](https://upload.wikimedia.org/wikipedia/commons/thumb/1/12/Cc-by-nc-sa_icon.svg/320px-Cc-by-nc-sa_icon.svg.png)

### You are free to:
 - Share — copy and redistribute the material in any medium or format
 - Adapt remix, transform, and build upon the material
 - The licensor cannot revoke these freedoms as long as you follow the license terms.
### Under the following terms:
 - Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
 - NonCommercial — You may not use the material for commercial purposes.
- ShareAlike — If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.

No additional restrictions — You may not apply legal terms or technological measures that legally restrict others from doing anything the license permits.
### Notices:
You do not have to comply with the license for elements of the material in the public domain or where your use is permitted by an applicable exception or limitation.
No warranties are given. The license may not give you all of the permissions necessary for your intended use. For example, other rights such as publicity, privacy, or moral rights may limit how you use the material.
