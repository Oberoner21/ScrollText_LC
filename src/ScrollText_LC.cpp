#include "ScrollText_LC.h"

ScrollText::ScrollText(LiquidCrystal_I2C *lcd, uint8_t lcd_cols, byte lcdScrollRow) {

    _lcd = lcd;
    _lcd_cols = lcd_cols;
    _lcdScrollRow = lcdScrollRow;
    _scrollText = NULL;
    _scrollTextLenght = 0;
    _outBuff = new char[lcd_cols];  // create the out buffer with size of display colums
}

void ScrollText::setScrollText(const char *scrolltext) {

    _scrollText = scrolltext;
    _scrollTextLenght = strlen(scrolltext);
    _arrayPos = 0;
    _clearOutBuffer();
}

void ScrollText::setScrollDelay(uint32_t scrollDelayMS) {

    _scrollDelayMS = scrollDelayMS;
}

void ScrollText::_clearOutBuffer() {

    memset(_outBuff, char(' '), _lcd_cols);   // fill the out buffer with space chars
    _outBuff[_lcd_cols] = 0x00;               // let the out buffer ends with 0
}

void ScrollText::_shiftAndPrint() {

    if(_scrollText == NULL || _scrollTextLenght == 0) return;     // if pointer to scrollText not set or lengh of scrolltext = 0, then do nothing

    // shift char of arraypos from left into outBuff and all other chars in the outBuff one position to left
    // the char in position 0 get lost
    for(uint8_t i = 1; i < _lcd_cols; i++) {
        _outBuff[i-1] = _outBuff[i];
    }
    _outBuff[_lcd_cols - 1] = _scrollText[_arrayPos];

    _lcd->setCursor(0, _lcdScrollRow);    // print the shifted out buffer on defined display row
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