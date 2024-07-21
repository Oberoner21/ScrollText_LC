#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "ScrollText_LC.h"

#define DEBUG 0     // set to 1 to enable serial outputs of debugging
#if DEBUG == 1
    #define Debug_print(x) Serial.print(x)
    #define Debug_println(x) Serial.println(x)
#else
    #define Debug_print(x)
    #define Debug_println(x)
#endif

LiquidCrystal_I2C lcd(0x27, 16, 2);     // create the lcd object
ScrollText sc(&lcd, 16, 1);             // create the scroll text object with 16 colums and scroll text line 1

const char scrollText1[] = {"This is a long text that scrolls across the entire line of the display - "};
const char scrollText2[] = {"Short text - "};
const char *scrollTextes[2];

const unsigned long textChangeDelayTime = 40000;
unsigned long lastTextChangeTime = 0;
byte cureScrollText = 0;

void setup() { 

    #if DEBUG == 1
        Serial.begin(9600);
        while(!Serial);
    #endif

    Debug_println(F("Setup is starting"));

    scrollTextes[0] = scrollText1;
    scrollTextes[1] = scrollText2;


    lcd.init();                      // initialize the lcd 
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("Demo");

    sc.setScrollText(scrollTextes[0]);
}

void loop() {

    sc.loop();      // call the scroll text loop

    if(millis() - lastTextChangeTime >= textChangeDelayTime) {

        if(cureScrollText == 0) {
            cureScrollText = 1;
        } else {
            cureScrollText = 0;
        }

        sc.setScrollText(scrollTextes[cureScrollText]);     // change the scrolltext

        lastTextChangeTime = millis();
    }
}
