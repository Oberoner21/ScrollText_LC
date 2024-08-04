#include <Arduino.h>
#include <LiquidCrystal.h>
#include "SmartDebug.h"

#define USE_STANDARD_LCD
#include "ScrollText_LC.h"

const uint8_t LCD_ROWS = 2;     // displays row count
const uint8_t LCD_COLS = 16;    // displays column count

// LCD pins
const uint8_t RS_PIN = 2; 
const uint8_t EN_PIN = 3;
const uint8_t D4_PIN = 4;
const uint8_t D5_PIN = 5;
const uint8_t D6_PIN = 6;
const uint8_t D7_PIN = 7;

// Create the lcd object
LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);
// create the scroll text object
ScrollText sc(&lcd, 15, 1, 1);  // text scrolls from column 16 to column 1 in row 1                  

const char scrollText1[] = {"This is a long text that scrolls across the entire line of the display - "};
const char scrollText2[] = {"Short text - "};
const char *scrollTextes[2];

const unsigned long textChangeDelayTime = 40000;
unsigned long lastTextChangeTime = 0;
byte cureScrollText = 0;

void setup() 
{ 
    DEBUG_BEGIN(9600);

    scrollTextes[0] = scrollText1;
    scrollTextes[1] = scrollText2;

    lcd.begin(LCD_COLS, LCD_ROWS);  // initialize the lcd 
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("Demo");

    sc.setScrollText(scrollTextes[0]);

    DEBUG_PRINTLN("Setup done...");
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
