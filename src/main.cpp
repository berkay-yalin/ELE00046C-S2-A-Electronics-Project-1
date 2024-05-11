#include "mbed.h"
#include "STM32.hpp"
#include "LiquidCrystal.h"

int main()
{
    while (true) {
 // bootup screen
const int reg = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(reg, en, d4, d5, d6, d7);

void setup() {

lcd.begin(16, 2);

lcd.clear();

lcd.setCursor(0, 1);

for (int i = 8; i >= 0; i--) {
    lcd.print(" ");  
lcd.setCursor(i, 1);
    lcd.print("neutronics");
    delay(200);
  }
}
void loop() {
 
}

    }
}
