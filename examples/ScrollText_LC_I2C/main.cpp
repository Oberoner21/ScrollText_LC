#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "SmartDebug.h"
#include "ScrollText_LC.h"

const uint8_t LCD_ROWS = 2;     // displays row count
const uint8_t LCD_COLS = 16;    // displays column count

// Create the lcd object with I2C intreface
LiquidCrystal_I2C lcd(0x27, LCD_COLS, LCD_ROWS);
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

    lcd.init();                      // initialize the lcd 
    lcd.backlight();
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
