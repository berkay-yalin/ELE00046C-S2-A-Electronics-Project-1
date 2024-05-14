#include "mbed.h"
#include "TextLCD.h"
#include <cstdint>
#include <string>
#include <chrono>

TextLCD lcd(D0, D1, D4, D5, D6, D7);
void timerCallback() {}
const uint8_t playButton[8] = {
    0b10000,
    0b11000,
    0b11100,
    0b11110,
    0b11110,
    0b11100,
    0b11000,
    0b10000
};
const uint8_t heart[8] = {
    0b00000,
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
};
const uint8_t skull[8] = {
    0b00000,
    0b01110,
    0b10101,
    0b11011,
    0b01110,
    0b01110,
    0b00000,
    0b00000
};

int main() {
std::string text = "Heart: \x00 Skull: \x01 playButton: \x10 ";
    lcd.putc(0x40); // Set CGRAM address to 0x40
    for (int i = 0; i < 8; i++) {
        lcd.putc(heart[i]); // Write heart custom character data to CGRAM
    }

    lcd.putc(0x48); // Set CGRAM address to 0x48
    for (int i = 0; i < 8; i++) {
        lcd.putc(skull[i]); // Write skull custom character data to CGRAM
    }
    lcd.putc(0x50); // Set CGRAM address to 0x50
        for (int i = 0; i < 8; i++) {
        lcd.putc(playButton[i]);
 }
}
    Ticker ticker;{
    ticker.attach(&timerCallback, 5ms); 

    std::string scrollText = "Neutronics";

    int textLength = scrollText.size();
    for (int i = 0; i <= textLength - 16; i++) {
        lcd.cls();
        lcd.locate(0, 0);
        lcd.printf("%s", scrollText.substr(i, 16).c_str());
        lcd.locate(0, 1);
        lcd.printf("%s", scrollText.substr(i + 16).c_str());
        ThisThread::sleep_for(50ms); // need to add a timer doesnt work rn
    }

    std::string text = "Start Game";
    textLength = text.size();
    int screenWidth = 16;
    int textStartPos = (screenWidth - textLength) / 2;
    lcd.cls();
    lcd.locate(textStartPos, 0);
    lcd.printf("%s", text.c_str());
    lcd.locate(2, 0);
    lcd.putc(0x01);
    lcd.locate(15, 0);
    lcd.putc(0x00);

    int buttonPos = (screenWidth - 1) / 2;
    lcd.locate(buttonPos, 1);

    while (1) {
        ThisThread::sleep_for(100ms);
    }
}
