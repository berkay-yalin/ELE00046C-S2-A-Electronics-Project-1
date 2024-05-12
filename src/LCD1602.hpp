#include "mbed.h"
#include "TextLCD.h"

#include <string>

namespace LCD1602 {
    class LCD1602 {
    private:
        TextLCD _lcd;

    public:
        LCD1602(PinName RS, PinName E, PinName D4, PinName D5, PinName D6, PinName D7) : _lcd(RS, E, D4, D5, D6, D7) {
            return;
        }

        void display(string text) {
            _lcd.printf("%s", (const char*)text.c_str());
        }

        void clear() {
            _lcd.cls();
        }

        void locate(int x, int y) {
            _lcd.locate(x, y);
        }

        void setCursorMode(string cursorMode) {
            if (cursorMode == "on") {
                _lcd.setCursor(TextLCD::CurOn_BlkOff);
            }
            else if (cursorMode == "blinking") {
                _lcd.setCursor(TextLCD::CurOn_BlkOn);
            }
            else if (cursorMode == "off") {
                _lcd.setCursor(TextLCD::CurOff_BlkOff);
            }
        }
    };
}
