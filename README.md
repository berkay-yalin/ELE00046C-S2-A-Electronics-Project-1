# ELE00046C-S2-A-Electronics-Project-1

Electronics Project 1 - ELE00046C

## Resources

- [STM32 Nucleo Boards](https://www.st.com/en/evaluation-tools/stm32-nucleo-boards.html)

- [NUCLEO-G071RB](https://os.mbed.com/platforms/ST-Nucleo-G071RB/)

- [LCD1602 Module](http://wiki.sunfounder.cc/index.php?title=LCD1602_Module)

- [mbedLCD Library](https://os.mbed.com/users/sstaub/code/mbedLCD/)

- [Poker Handa](https://www.cardplayer.com/rules-of-poker/hand-rankings)

## LCD1602 Custom class

The [LCD1602](https://github.com/berkay-yalin/ELE00046C-S2-A-Electronics-Project-1/blob/main/src/LCD1602.hpp) library
possesses the following methods:

- `display_string`
- `create_char`
- `display_char`
- `locate`
- `clear`

Each method is described below with examples.

### display_string
Print a string onto the LCD display (basically a printf wrapper).

```cpp
#include "mbed.h"
#include "LCD1602.hpp"

LCD1602::LCD1602 lcd(D0, D1, D4, D5, D6, D7);

int main() {
    lcd.display_string("Hello World!");
}

```

### create_char & display_char

Displaying custom characters using the [mbedLCD](https://os.mbed.com/users/sstaub/code/mbedLCD/) library can become quite monotonous as:

- you have to constantly update the position of the cursor so characters don't write over each other
- characters are referenced in functions through their memory location which damages code readability

as can be seen in the example below:

```cpp
#include <string>
#include <vector>

#include "mbed.h"
#include "LCD.h"

uint8_t heart[8] = {0b00000, 0b01010, 0b11111, 0b11111, 0b11111, 0b01110, 0b00100, 0b00000};
uint8_t diamond[8] = {0b00000, 0b00100, 0b01110, 0b11111, 0b11111, 0b01110, 0b00100, 0b00000};
uint8_t spade[8] = {0b00000, 0b00100, 0b01110, 0b11111, 0b11111, 0b00100, 0b01110, 0b00000};
uint8_t club[8] = {0b00000, 0b01110, 0b01110, 0b11111, 0b11111, 0b00100, 0b01110, 0b00000};

LCD lcd(D0, D1, D4, D5, D6, D7, LCD16x2);

int main() {
    lcd.create(1, club);
    lcd.create(2, diamond);
    lcd.create(3, heart);
    lcd.create(4, spade);

    int column = 0;
    int row = 0;

    lcd.character(column, row, 1);
    column += 1;
    lcd.locate(column, row);

    lcd.character(column, row, 2);
    column += 1;
    lcd.locate(column, row);

    lcd.character(column, row, 3);
    column += 1;
    lcd.locate(column, row);

    lcd.character(column, row, 4);
    column += 1;
    lcd.locate(column, row);
}
```

The `LCD1602` class automatically keeps track of the cursor's location and allows you to reference the characters through an easily identifiable string:

```cpp
#include <string>
#include <vector>

#include "mbed.h"
#include "LCD1602.hpp"

uint8_t heart[8] = {0b00000, 0b01010, 0b11111, 0b11111, 0b11111, 0b01110, 0b00100, 0b00000};
uint8_t diamond[8] = {0b00000, 0b00100, 0b01110, 0b11111, 0b11111, 0b01110, 0b00100, 0b00000};
uint8_t spade[8] = {0b00000, 0b00100, 0b01110, 0b11111, 0b11111, 0b00100, 0b01110, 0b00000};
uint8_t club[8] = {0b00000, 0b01110, 0b01110, 0b11111, 0b11111, 0b00100, 0b01110, 0b00000};

LCD1602::LCD1602 lcd(D0, D1, D4, D5, D6, D7);

int main() {
    lcd.create_char("club", club);
    lcd.create_char("diamond", diamond);
    lcd.create_char("heart", heart);
    lcd.create_char("spade", spade);

    lcd.display_char("club");
    lcd.display_char("diamond");
    lcd.display_char("heart");
    lcd.display_char("spade");
}
```

## locate
Locate cursor to a position on the screen.

Keep in mind the `16x2` screen dimensions as attempting to going over the bounds will cause problems.

```cpp
#include "mbed.h"
#include "LCD1602.hpp"

LCD1602::LCD1602 lcd(D0, D1, D4, D5, D6, D7);

int main() {
    lcd.locate(1, 4);
}
```

## clear
Clear the screen and locate the cursor to `(0, 0)`.

```cpp
#include "mbed.h"
#include "LCD1602.hpp"

LCD1602::LCD1602 lcd(D0, D1, D4, D5, D6, D7);

int main() {
    lcd.clear();
}
```
