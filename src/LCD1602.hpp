#include "mbed.h"
#include "LCD.h"

#include <cstdint>
#include <string>
#include <map>

namespace LCD1602 {
    class LCD1602 {
    private:
        LCD _lcd;
        int _column;
        int _row;
        
        int _charactersCount = 0;
        std::map<string, int> _characters;
    
        void _update_location(int length) {
            _column += length;
            while (_column >= 16) {
                _column -= 16;
                _row += 1;
            }
        }

    public:
        LCD1602(PinName RS, PinName E, PinName D4, PinName D5, PinName D6, PinName D7) : _lcd(RS, E, D4, D5, D6, D7) {
            _column = 0;
            _row = 0;
        }

        void display_string(string text) {
            _lcd.locate(_column, _row);
            _lcd.printf("%s", (const char*)text.c_str());
            _update_location(text.length());

            // printf("debug : column row: %d %d\n", _column, _row);
        }

        void create_char(string name, uint8_t charmap[]) {
            _characters.insert({name, _charactersCount});
            _lcd.create(_charactersCount, charmap);
            _charactersCount++;
        }

        void display_char(string name) {
            _lcd.character(_column, _row, _characters[name]);
            _update_location(1);

            // printf("debug : column row: %d %d\n", _column, _row);
        }

        void clear() {
            _lcd.cls();
            _column = 0;
            _row = 0;
        }

        void locate(int x, int y) {
            _column = x;
            _row = y;
            _lcd.locate(x, y);
        }
    };
}