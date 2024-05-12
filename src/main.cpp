#include "mbed.h"
#include "TextLCD.h"

TextLCD lcd(D4, D5, D9, D10, D11, D12);

int main() {
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("Hello, World!");
}
