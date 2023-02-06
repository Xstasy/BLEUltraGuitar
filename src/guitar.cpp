#include <guitar.h>

#if defined(BATTERY_PIN) && BATTERY_PIN > 0
    void bTask(void * parameter) {
        const TickType_t xDelay = BATTERY_HZ / portTICK_PERIOD_MS;
        for( ;; ) {
            bTot = bTot - bSamples[bIndex];
            bSamples[bIndex]  = adc1_get_raw(bc);
            bTot = bTot + bSamples[bIndex];
            bIndex = bIndex + 1;
            if (bIndex >= BATTERY_SAMPLES)  bIndex = 0;
            bAvg = bTot / BATTERY_SAMPLES;

            if(bIndex == 0) {
                if(bAvg < bMin) bAvg = bMin;
                int lvl = map(bAvg, bMin, 4095, 0, 100);
                pad.setBatteryLevel(lvl);
                pad.setSlider1(map(bAvg, bMin, 4095, 0, 32767));
                #if defined(DEBUG_MODE) || defined(DEBUG_BATTERY)
                    Serial.printf("Battery: %d - Raw: %d\n", lvl, bSamples[bIndex]);
                #endif
            }
            vTaskDelay(xDelay);
        }
    }
#endif

#if defined(WHAMMY_PIN) && WHAMMY_PIN > 0
    void wTask(void * parameter) {
        const TickType_t xDelay = WHAMMY_HZ / portTICK_PERIOD_MS;
        bool ft = true;
        for( ;; ) { 
            wTot = wTot - wSamples[wIndex];
            wSamples[wIndex] = adc1_get_raw(wc);
            
            if(wSamples[wIndex] > wMax) wMax =  wSamples[wIndex];
            if(wSamples[wIndex] < wMin) wMin =  wSamples[wIndex];
            
            wTot = wTot + wSamples[wIndex];
            wIndex = wIndex + 1;

            if (wIndex >= WHAMMY_SAMPLES) wIndex = 0;
            
            wAvg = wTot / WHAMMY_SAMPLES;
            wAvg = ft ? 0 : map(wAvg, wMin, wMax, 0, 32767);
            
            if(wAvg <= 1000) wAvg = 0;
            
            if(abs(wAvg - wLast) > 1000) {
                wLast = wAvg;
                if(wLast > 30000) {
                    wLast = 32767;
                    pad.setSlider2(wLast);
                } else pad.setSlider2(wAvg);
            }

            if(ft) ft=0;
            vTaskDelay(xDelay);
        }
    };
#endif

bool Button(int b, bool s = true) {
    bool db = false;
    #if defined(DEBUG_MODE) || defined(DEBUG_BUTTONS)
        db = true;
    #endif
    if(b < 8) {
        if(s) pad.press(b+1);
        else pad.release(b+1);
        if(db) Serial.printf("%s: %s\n", bN[b], s ? (b < 8 ? "Pressed" : "Tilted") : (b < 8 ? "Released" : "Normal"));
    } else {
        if(s) {
            pad.setHat1(b == 8 ? HAT_UP : HAT_DOWN);
            if(db) Serial.printf("Strumbar: %s\n", b == 8 ? "Up" : "Down");
        } else {
            pad.setHat1(HAT_CENTERED);
            if(db) Serial.println("Strumbar: Centred");
        } 
    }
    return true;
}

void setup() {
    if(ser) {
        Serial.begin(115200);
        while(!Serial) { delay(50); };
        delay(1000);
        Serial.printf("\r\n\r\nBLEUltraGuitar");
    }

    if(wp > 0 || bp > 0) {
        adc1_config_width(ADC_WIDTH_12Bit);
        #if defined(WHAMMY_PIN) && WHAMMY_PIN > 0
            adc1_config_channel_atten(wc, ADC_ATTEN_11db);
        #endif
        #if defined(BATTERY_PIN) && BATTERY_PIN > 0
            adc1_config_channel_atten(bc, ADC_ATTEN_11db);
        #endif
    }

    for(int i = 0; i < 10; i++) {
        btns[i].attach ( (int)bpins[i], INPUT_PULLUP);
        if(i < 8)       btns[i].interval(FRET_BOUNCE_MS);
        else if(i == 8) btns[i].interval(STRUM_UP_BOUNCE_MS);
        else if(i == 9) btns[i].interval(STRUM_DOWN_BOUNCE_MS);
        #if defined(DEBUG_MODE) || defined(DEBUG_BUTTONS)
            Serial.printf("%s: configured using pin %d\n", bN[i], bpins[i]);
        #endif
    };

    cfg.setAutoReport(0);
    cfg.setWhichAxes(0, 0, 0, 0, 0, 0, wp != 0 ? 1 : 0, bp != 0 ? 1 : 0);
    cfg.setButtonCount(8);
    cfg.setHatSwitchCount(1);
    cfg.setVid(0x0420);
    cfg.setPid(0x6969);
    pad.begin(&cfg);

    #if defined(WHAMMY_PIN) && WHAMMY_PIN > 0
        xTaskCreate(&wTask, "wTask", 10000, NULL, 5,  NULL);
    #endif
    
    
    #if defined(BATTERY_PIN) && BATTERY_PIN > 0
        xTaskCreate(&bTask, "bTask", 10000, NULL, 10, NULL);
        esp_err_t error;
        for(int i = 0; i < 5; i++) {
            esp_err_t error = esp_sleep_enable_ext0_wakeup(static_cast<gpio_num_t>(bpins[i]), 0);
            switch(error) {
                case ESP_OK:
                    #if defined(DEBUG_MODE) || defined(DEBUG_SLEEP)
                        Serial.printf("Sleep wakeup enabled on %s (pin: %d)\n", bN[i], bpins[i]);
                    #endif
                    break;
                case ESP_ERR_INVALID_ARG:
                    if(ser) Serial.printf("Sleep wakeup failed on pin: %d - GPIO is not an RTC GPIO\n", bpins[i]);
                    break;
                case ESP_ERR_INVALID_STATE:
                    if(ser) Serial.printf("Sleep wakeup failed on pin: %d - Wakeup triggers conflict\n", bpins[i]);
                    break;
                default:
                    break;
            }
        }
    #endif
}

void loop() {
    ticks++;
    long s = micros();

    for(int i = 0; i < 10; i++) {
        btns[i].update();
        if(btns[i].fell())      update = Button(i);
        else if(btns[i].rose()) update = Button(i, 0);
    }
    
    if(ticks >= 20000) {
        ticks = 0;
        if((millis() - lastHit && bp > 0) > 120000)
            esp_deep_sleep_start();
    }
    
    if(update) {
        lastHit = millis();   
        pad.sendReport();
    }
    
    delayMicroseconds(180);

    #ifdef DEBUG_LOOP_TIME
        Serial.printf("%d, ", (micros() - s));
    #endif
}