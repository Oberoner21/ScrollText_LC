/***
 * @file ScrollText_LC.h
 * 
 * @brief Scroll text class for LCD-Displays.
 *    
 * The class use the LiquidCrystal library LiquidCrystal_I2C (default)
 * or LiquidCrystal and is based on a left shift char buffer. 
 * 
 *                              Display out char buffer          
 *          --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 *   out <- | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | <- Next char
 *          --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
 *           |   1   2   3   4   5   6   7   8   9   x   x   x   x   x   |
 *           |                                                           |
 *        startCol                                                     endCol
 * 
 * Version 1.0 by Oberoner21 
 */

#pragma once
#include <Arduino.h>

#ifndef USE_STANDARD_LCD
#include <LiquidCrystal_I2C.h>
#else
#include <LiquidCrystal.h>
#endif

class ScrollText 
{
    public:
        #ifndef USE_STANDARD_LCD
        ScrollText(LiquidCrystal_I2C *lcd, uint8_t startCol, uint8_t endCol, uint8_t row);
        #else
        ScrollText(LiquidCrystal *lcd, uint8_t startCol, uint8_t endCol, uint8_t row);
        #endif
        void setScrollText(const char *scrollText);
        void setScrollDelay(uint32_t scrollDelayMS);
        void loop();
    private:
        #ifndef USE_STANDARD_LCD
        LiquidCrystal_I2C *_lcd;
        #else
        LiquidCrystal *_lcd;
        #endif   
        uint8_t _startCol;
        uint8_t _endCol;
        uint8_t _row;
        uint8_t _outBuffSize;
        char *_outBuff;
        const char *_scrollText = NULL;
        uint16_t _scrollTextLenght = 0;
        uint8_t _arrayPos;
        uint32_t _scrollDelayMS = 500;
        unsigned long _lastScrollTimeStamp = 0;

        void _clearOutBuffer();
        void _shiftAndPrint();  
};