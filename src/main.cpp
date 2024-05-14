// #include "mbed.h"
// #include "TextLCD.h"

// TextLCD lcd(D0, D1, D4, D5, D6, D7); // rs, e, d4, d5, d6, d7

// char custom_char[8][8] = {
//     {0x07,0x08,0x1F,0x08,0x1F,0x08,0x07,0x00}, // Euro sign.
//     {0x00,0x0E,0x11,0x11,0x11,0x0A,0x1B,0x00}, // Ohm sign.
//     {0x00,0x00,0x00,0x12,0x12,0x12,0x1C,0x10}, // Micro sign.
//     {0x00,0x00,0x1F,0x0A,0x0A,0x0A,0x0A,0x00}, // Pi sign.
//     {0x0C,0x12,0x12,0x0C,0x00,0x00,0x00,0x00}, // Degree sign.
//     {0x0E,0x04,0x0E,0x15,0x015,0x0E,0x04,0x0E},// Phi sign.
//     {0x04,0x0E,0x15,0x04,0x04,0x04,0x04,0x04}, // Arrow up.
//     {0x04,0x04,0x04,0x04,0x04,0x15,0x0E,0x04}  // Arrow down.
// };

// BusOut Lcd_pins(D4, D5, D6, D7);

// DigitalOut rs_pin(D0);

// DigitalOut e_pin(D1);

// void writePort(int value) {
//     Lcd_pins = value >> 4;  // Shifts 4 bit right.
//     thread_sleep_for(0.000040f); // Wait 40us.
//     e_pin = 0;
//     thread_sleep_for(0.000040f);
//     e_pin = 1;
//     Lcd_pins = value;
//     thread_sleep_for(0.000040f);
//     e_pin = 0;
//     thread_sleep_for(0.000040f);
//     e_pin = 1;
// }


// int main() {
//     lcd.cls();
//     lcd.printf("Loading...");
//     thread_sleep_for(2);
//     for (int j=0; j<8; j++) {
//         rs_pin = 0; // We send a command.

//     /* 0X40 is the initial CGRAM address. Because each character needs a total amount of 8 memory 
//     locations, we increment addres in 8 units after each character.
//     */
//         writePort(0x40+8*j);

//         // Writes data.
//         rs_pin = 1; // We send data.
//         for (int i=0; i<8; i++) {
//             writePort(custom_char[j][i]);
//         }
//     }

//     lcd.cls();
//     thread_sleep_for(0.010);
//     lcd.printf("Custom character");
//     lcd.locate(0,1);
//     // Prints loaded custom characters. ASCII codes 0 to 7.
//     for (int j=0; j<8; j++) {
//         lcd.putc(j);
//     }
// }














// #include <cmath>
// #include <string>

// #include "LCD1602.hpp"

// string center_string(string text, int width = 16) {
//     /**
//         centre a string in a fixed-width with padded spaces
//         e.g., center_string("four", 16) would return "      four      "
//     **/
//     int padding_number = ceil( (width - text.length()) / 2 );
//     string padding = "";
//     while (padding_number > 0) {
//         padding += " ";
//         padding_number--;
//     }
//     string padded_text = padding + text + padding;
//     return padded_text;
// }

// // LCD is controlled through the blackbox object
// LCD1602::LCD1602 blackbox(D0, D1, D4, D5, D6, D7);

// // initalise buttons
// DigitalOut button_start(D8, PullUp);
// DigitalOut button_select(D9, PullUp);
// DigitalOut button_a(D10, PullUp);
// DigitalOut button_b(D11, PullUp);

// // global variable to determine which state the game is at
// string state = "start screen";

// int main() {
//     while (true) {
//         if (state == "start screen") {
//             /**
//                 STAGE 1: "start screen"
//                 displays the opening title until user input
//             **/
//             blackbox.clear();
//             blackbox.locate(0, 0);
//             blackbox.display("Neutronics Poker");
//             blackbox.display(center_string("Press Start"));
//             blackbox.setCursorMode("off");

//             while (true) {
//                 if (button_start == false) {
//                     break;
//                 }
//             }

//             blackbox.clear();
//             // TODO: develop next stage of the game
//             state = "stage2";
//         }

//         if (state == "stage2") {
//             /**
//                 STAGE 2: ""
//                 // TODO: develop next stage of the game
//             **/
//             blackbox.clear();
//             blackbox.locate(0, 0);
//             blackbox.display2();
//         }
//     }
// }



// example for mbed6 LCD library

#include "mbed.h"
#include "LCD.h"

// special chars
uint8_t upArrow[8] = {  
    0b00100,
    0b01010,
    0b10001,
    0b00100,
    0b00100,
    0b00100,
    0b00000,
    };

uint8_t downArrow[8] = {
    0b00000,
    0b00100,
    0b00100,
    0b00100,
    0b10001,
    0b01010,
    0b00100,
    };

uint8_t rightArrow[8] = {
    0b00000,
    0b00100,
    0b00010,
    0b11001,
    0b00010,
    0b00100,
    0b00000,
    };

uint8_t leftArrow[8] = {
    0b00000,
    0b00100,
    0b01000,
    0b10011,
    0b01000,
    0b00100,
    0b00000,
    };

LCD lcd(D0, D1, D4, D5, D6, D7, LCD16x2); // rs, en, d4-d7, LCD type

int main() {

    lcd.create(0, downArrow);
    lcd.create(1, upArrow);
    lcd.create(2, rightArrow);
    lcd.create(3, leftArrow);

    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("Hello World!\n");
    lcd.character(0, 1, 0);
    lcd.character(3, 1, 1);
    lcd.character(5, 1, 2);
    lcd.character(7, 1, 3);

    ThisThread::sleep_for(2s);
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("Hello World!\n");

    ThisThread::sleep_for(2s);
    lcd.display(DISPLAY_OFF);
    ThisThread::sleep_for(2s);
    lcd.display(DISPLAY_ON);
    ThisThread::sleep_for(2s);
    lcd.display(CURSOR_ON);
    ThisThread::sleep_for(2s);
    lcd.display(BLINK_ON);
    ThisThread::sleep_for(2s);
    lcd.display(BLINK_OFF);
    ThisThread::sleep_for(2s);
    lcd.display(CURSOR_OFF);

    while(1) {
        for (uint8_t pos = 0; pos < 13; pos++) {
        // scroll one position to left
        lcd.display(SCROLL_LEFT);
        // step time
        ThisThread::sleep_for(500ms);
        }

    // scroll 29 positions (string length + display length) to the right
    // to move it offscreen right
    for (uint8_t pos = 0; pos < 29; pos++) {
      // scroll one position to right
      lcd.display(SCROLL_RIGHT);
      // step time
      ThisThread::sleep_for(500ms);
        }

    // scroll 16 positions (display length + string length) to the left
    // to move it back to center
    for (uint8_t pos = 0; pos < 16; pos++) {
      // scroll one position to left
      lcd.display(SCROLL_LEFT);
      // step time
      ThisThread::sleep_for(500ms);
        }

        ThisThread::sleep_for(1s);
        }
    }







