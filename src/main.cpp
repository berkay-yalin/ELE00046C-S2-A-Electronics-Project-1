#include "mbed.h"
#include "TextLCD.h"

TextLCD lcd(D2, D3, D4, D5, D6, D7);

int main() {
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("Hello, World!");
}
