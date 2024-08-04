#include "ScrollText_LC.h"

#ifndef USE_STANDARD_LCD
ScrollText::ScrollText(LiquidCrystal_I2C *lcd, uint8_t startCol, uint8_t endCol, uint8_t row) 
{
    _lcd = lcd;
    _startCol = startCol;
    _endCol = endCol;
    _row = row;
    _scrollText = NULL;
    _scrollTextLenght = 0;
    _displayBufSize = startCol - endCol + 1;
    _outBuff = new char[_displayBufSize];  // create the out buffer with size of display colums
}
#endif

#ifdef  USE_STANDARD_LCD
ScrollText::ScrollText(LiquidCrystal *lcd, uint8_t startCol, uint8_t endCol, uint8_t row);
{
    _lcd = lcd;
    _startCol = startCol;
    _endCol = endCol;
    _row = row;
    _scrollText = NULL;
    _scrollTextLenght = 0;
    _displayBufSize = startCol - endCol + 1;
    _outBuff = new char[_displayBufSize];  // create the out buffer with size of display colums
}
#endif

void ScrollText::setScrollText(const char *scrolltext) 
{
    _scrollText = scrolltext;
    _scrollTextLenght = strlen(scrolltext);
    _arrayPos = 0;
    _clearOutBuffer();
}

void ScrollText::setScrollDelay(uint32_t scrollDelayMS) 
{
    _scrollDelayMS = scrollDelayMS;
}

void ScrollText::_clearOutBuffer() 
{
    memset(_outBuff, char(' '), _displayBufSize);   // fill the out buffer with space chars
    _outBuff[_displayBufSize] = 0x00;               // let the out buffer ends with 0
}

void ScrollText::_shiftAndPrint()
{

    if(_scrollText == NULL || _scrollTextLenght == 0) return;     // if pointer to scrollText not set or lengh of scrolltext = 0, then do nothing

    // shift char of arraypos from right into outBuff and all other chars in the outBuff one position to left
    // the char in position 0 get lost
    for(uint8_t i = 1; i < _displayBufSize; i++) {
        _outBuff[i-1] = _outBuff[i];
    }
    _outBuff[_displayBufSize - 1] = _scrollText[_arrayPos];

    _lcd->setCursor(_endCol, _row);    // print the shifted out buffer on defined display row
    _lcd->print(_outBuff);

    _arrayPos++;
    if(_arrayPos == _scrollTextLenght) {
        _arrayPos = 0;
    }
}

void ScrollText::loop() {

    if(millis() - _lastScrollTimeStamp >= _scrollDelayMS) {

        _shiftAndPrint();
        _lastScrollTimeStamp = millis();
    }
}