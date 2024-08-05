/***********************************************************
 * @file ScrollText_LC.cpp
 * 
 * @brief Scroll text from left to right on an LCD display.
 * 
 * Version 1.0 by Oberoner21.
 ***********************************************************/

#include "ScrollText_LC.h"

#ifndef USE_STANDARD_LCD
/**
 * @brief Construct the ScrollText object 
 * 
 * @param lcd The pointer to LiquidCrystal_I2C object
 * @param startCol The display column number where the scrolltext starts
 * @param endCol The display column number where the scrolltext ends
 * @param row The display row where the text scrolls
 */
ScrollText::ScrollText(LiquidCrystal_I2C *lcd, uint8_t startCol, uint8_t endCol, uint8_t row)
    : _lcd(lcd), _startCol(startCol), _endCol(endCol), _row(row)     
{
    _outBuffSize = startCol - endCol + 1; ///< size of out buffer
    _outBuff = new char[_outBuffSize]; ///< create the out buffer
}
#else
/**
 * @brief Construct the ScrollText object 
 * 
 * @param lcd The pointer to LiquidCrystal object
 * @param startCol The display column number where the scrolltext starts
 * @param endCol The display column number where the scrolltext ends
 * @param row The display row where the text scrolls
 */
ScrollText::ScrollText(LiquidCrystal *lcd, uint8_t startCol, uint8_t endCol, uint8_t row)
    : _lcd(lcd), _startCol(startCol), _endCol(endCol), _row(row)
{
    _displayBufSize = startCol - endCol + 1; ///< size of out buffer
    _outBuff = new char[_displayBufSize]; ///< create the out buffer
}
#endif

/**
 * @brief Set the scrolltext, reset the out buffer and the index
 * 
 * @param scrolltext Text to scroll.
 */
void ScrollText::setScrollText(const char *scrolltext)
{
    _scrollText = scrolltext;
    _scrollTextLenght = strlen(scrolltext);
    _arrayPos = 0;
    _clearOutBuffer();
}

/**
 * @brief Set the scroll delay time in mS.
 * 
 * @param scrollDelayMS The delay time
 */
void ScrollText::setScrollDelay(uint32_t scrollDelayMS) 
{
    _scrollDelayMS = scrollDelayMS;
}

/**
 * @brief Reset and clear the out buffer 
 */
void ScrollText::_clearOutBuffer() 
{
    memset(_outBuff, char(' '), _outBuffSize); ///< fill the out buffer with space chars
    _outBuff[_outBuffSize] = '\0'; ///< let the out buffer ends with 0
}

/**
 * @brief Shift the out buffer content one position to left.
 *        The first left char position get to lost. 
 *        From right fills the current scrolltext char the buffer.
 */
void ScrollText::_shiftAndPrint()
{
    /**
     * If scrolltext not set or the text length is 0, then do nothing.
     */
    if(_scrollText == NULL || _scrollTextLenght == 0) return;

    /**
     * Shift all chars in the out buffer one posizion to left.
     * The first position is overwritten.
     */
    for(uint8_t i = 1; i < _outBuffSize; i++)
    {
        _outBuff[i-1] = _outBuff[i];
    }
    /**
     * Replace the last out buffer position with the current
     * scroll text char, addressd by index _arrayPos. 
     */
    _outBuff[_outBuffSize - 1] = _scrollText[_arrayPos];

    /**
     * Place the cursor on the specified display position and
     * print the shifted out buffer. 
     */
    _lcd->setCursor(_endCol, _row);
    _lcd->print(_outBuff);

    /**
     * Set the scrolltext index to the next position. If the 
     * index is at the last text position, reset it to the beginning.
     */
    _arrayPos++;
    if(_arrayPos == _scrollTextLenght)
    {
        _arrayPos = 0;
    }
}

/**
 * @brief The class loop function.
 *        Call this from main loop() to scroll the text.
 */
void ScrollText::loop()
{
    /**
     * If the scroll delay time elapsed?
     */
    if(millis() - _lastScrollTimeStamp >= _scrollDelayMS)
    {
        /**
         * Scroll the text one position to left.
         */
        _shiftAndPrint();

        _lastScrollTimeStamp = millis();
    }
}

