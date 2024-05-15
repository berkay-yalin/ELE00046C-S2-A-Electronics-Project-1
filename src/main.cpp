/*Program to display simple messages and values on an LCD screen
Adapted from publically available GITHUB program for an arduino
01/11/23
Version 3
*/

/* Ensure RW LCD pin is connected to GND and connect a 10 K potentiometer with wiper connected to V0 and other ends to A and K LCD pins.
 Connect a 100 ohm resistor (ideally 500 Ohm) between A LCD pin and VDD.
 */

#include "mbed.h"
#include "TextLCD.h"

TextLCD lcd(D0, D1, D4, D5, D6, D7, TextLCD::LCD16x2); // Connect these nucleo pins to RS, E, D4, D5, D6 and D7 pins of the LCD
// Define byte array for a filled square

// initalise buttons
DigitalOut button_start(D8, PullUp);
DigitalOut button_select(D9, PullUp);
DigitalOut button_a(D10, PullUp);
DigitalOut button_b(D11, PullUp);

using byte = unsigned char;

char heart[] = {
    0x0,
    0x0,
    0xa,
    0x15,
    0x11,
    0xa,
    0x4,
    0x0
};

char diamond[] = {
    0x0,
    0x0,
    0x4,
    0xa,
    0x11,
    0xa,
    0x4,
    0x0
};

char spade[] = {
    0x0,
    0x4,
    0xe,
    0x1f,
    0x1f,
    0xe,
    0x4,
    0xe
};

char clubs[] = {
    0x4,
    0xe,
    0x4,
    0xa,
    0x1f,
    0xa,
    0x4,
    0xe
};

enum difficulty { BEGINNER, INTERMEDIATE, PRO };
// Function prototypes for program flow
void startScreen();
void menuScreen();
void selectDifficulty(difficulty* diff);

void startScreen() {
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("Neutronics Games");
    lcd.locate(0, 1);
    lcd.printf("Press Start...");
}

void menuScreen() {
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("Game Select:");
    lcd.locate(0, 1);
    lcd.printf("A) Poker B) Bkjk");
}

void selectDifficulty(difficulty* diff) {
    const char* difficulty_levels[3] = {
        "Beginner",
        "Intermediate",
        "Pro"
    };

    int selection = 0;
    
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("Difficulty: ");
    lcd.locate(0, 1);
    lcd.printf("%s", difficulty_levels[selection]);

    while (true) {
        // Update LCD display based on selection (highlight current option)

        // Check for Select button press
        if (!button_select) {
            selection++;

            lcd.locate(0, 1);
            for (int i = 0; i < 16; i++) {
                lcd.printf(" ");  // Print spaces to clear previous selection
            }

            lcd.locate(0, 1);
            lcd.printf("%s", difficulty_levels[selection]);

            if (selection >= 3) {
                selection = 0;
                lcd.locate(0, 1);
                for (int i = 0; i < 16; i++) {
                    lcd.printf(" ");  // Print spaces to clear previous selection
                }
                lcd.locate(0, 1);
                lcd.printf("%s", difficulty_levels[selection]);

            }
            thread_sleep_for(500);
        }
        
        // Check for A button press (confirm)
        if (!button_a) {
            *diff = (difficulty)(selection); // Update difficulty based on selection
            break;
        }
    }

}

int main() 
{
    lcd.cls();

    //The 7 animation characters
    char spin[]={   0x4,0x4,0x4,0x4,0x4,0x4,0x4,0x0,
                    0x2,0x2,0x2,0x4,0x8,0x8,0x8,0x0,
                    0x1,0x2,0x2,0x4,0x8,0x8,0x10,0x0,
                    0x0,0x0,0x3,0x4,0x18,0x0,0x0,0x0,
                    0x0,0x0,0x0,0x1f,0x0,0x0,0x0,0x0,
                    0x0,0x0,0x18,0x4,0x3,0x0,0x0,0x0,
                    0x10,0x8,0x8,0x4,0x2,0x2,0x01,0x0
    };
    
    // // Output text.
    lcd.cls();
    lcd.printf("\1Testing Suits:\1");
    lcd.locate(0, 1); //set cursor on row number 1 (bottom row)
    lcd.printf("\2 \3 \4 \5"); 
    lcd.defineChar(2, heart);
    lcd.defineChar(3, spade);
    lcd.defineChar(4,diamond);
    lcd.defineChar(5, clubs);


    //Animation loop
    int frame=0;
    while (1) {
        lcd.defineChar(1, spin + frame * 8);
        frame=(frame + 1) % (sizeof(spin) / 8);
        wait_us(140000);
    }
    thread_sleep_for(3000);

    startScreen();
    while (true) {
        thread_sleep_for(500);
        while (!button_start);
        thread_sleep_for(500);

        menuScreen();

        while (!button_a && !button_b);
        thread_sleep_for(500);

        difficulty selectedDiff;
        if (!button_a) {
            thread_sleep_for(500);
            selectDifficulty(&selectedDiff);
            // poker(selectedDiff);
        } else if (!button_b) {
            thread_sleep_for(500);
            selectDifficulty(&selectedDiff);
            // blackjack(selectedDiff);
        }
        // Break out of the inner loop after a game
        break;
        thread_sleep_for(500);
    }

}
