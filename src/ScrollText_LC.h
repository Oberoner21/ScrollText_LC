/***
 * ScrollText_LC
 *  
 * Scroll text class for LCD-Displays use the LiquidCrystal library LiquidCrystal_I2C
 * 
 *   Based on left shift char buffer 
 *          --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 *   out <- | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | <- Next char
 *          --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 *           0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
 * 
 * Version 1.0 by Oberoner21 
 */

#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class ScrollText {
    public:
        ScrollText(LiquidCrystal_I2C *lcd, uint8_t lcd_cols, byte lcdScrollRow);
        void setScrollText(const char *scrollText);
        void setScrollDelay(uint32_t scrollDelayMS);
        void loop();
    private:
        LiquidCrystal_I2C *_lcd;
        uint8_t _lcd_cols;
        byte _lcdScrollRow;
        char *_outBuff;
        const char *_scrollText;
        uint16_t _scrollTextLenght;
        uint8_t _arrayPos;
        uint32_t _scrollDelayMS = 500;
        unsigned long _lastScrollTimeStamp = 0;

        void _clearOutBuffer();
        void _shiftAndPrint();  
};