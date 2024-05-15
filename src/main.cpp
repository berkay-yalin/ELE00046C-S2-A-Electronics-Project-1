#include "mbed.h"
#include "LCD.h"

#include <string>
#include <vector>

#include "card_suit_characters.hpp"

string center_string(string text, int width = 16) {
    /**
        centre a string in a fixed-width with padded spaces
        e.g., center_string("four", 16) would return "      four      "
    **/
    int padding_number = ceil( (width - text.length()) / 2 );
    string padding = "";
    while (padding_number > 0) {
        padding += " ";
        padding_number--;
    }
    string padded_text = padding + text + padding;
    return padded_text;
}

vector<string> generate_cards() {
    const vector<string> suits = {"C", "D", "H", "S"};
    const vector<string> ranks = {"J", "Q", "K", "A"};
    vector<string> cards;

    for (int i = 0; i < 4; i++) {
        for (int j = 2; j <= 10; j++) {
            cards.push_back(suits[i] + to_string(j));
        }

        for (int j = 0; j < 4; j++) {
            cards.push_back(suits[i] + ranks[j]);
        }
    }

    return cards;
}

// initalise buttons
DigitalOut button_start(D8, PullUp);
DigitalOut button_select(D9, PullUp);
DigitalOut button_a(D10, PullUp);
DigitalOut button_b(D11, PullUp);

// global variable to determine which state the game is at
string state = "start screen";

//  lcd(rs, en, d4, d5, d6, d7, LCD type)
LCD lcd(D0, D1, D4, D5, D6, D7, LCD16x2);


vector<string> cards = generate_cards();

int main() {
    printf("\n");

    lcd.create(0, card_suit_characters::club);
    lcd.create(1, card_suit_characters::diamond);
    lcd.create(2, card_suit_characters::heart);
    lcd.create(3, card_suit_characters::spade);

    while (true) {
        if (state == "start screen") {
            lcd.printf("Neutronics Poker");

            lcd.printf("%s", (const char*)center_string("Press Start").c_str());

            while (true) {
                if (button_start == false) {
                    break;
                }
            }
            lcd.cls();
            state = "stage2";
        }

        // very poor code just to prove working concept
        // requires immediate rewrite
        if (state == "stage2") {
            int column_position = 0;
            int row_position = 1;

            lcd.cls();

            // display first number
            string card = "C9";
            char suit = card[0];
            string value = card.substr(1);
            lcd.locate(column_position, row_position);

            if (suit == 'C') {
                lcd.character(column_position, row_position, 0);
            }
            else if (suit == 'D') {
                lcd.character(column_position, row_position, 1);
            }
            else if (suit == 'H') {
                lcd.character(column_position, row_position, 2);
            }
            else if (suit == 'S') {
                lcd.character(column_position, row_position, 3);
            }

            column_position += 1;
            lcd.locate(column_position, row_position);

            lcd.printf(value.c_str());
            column_position += value.length() + 1;
            lcd.locate(column_position, row_position);

            // display second number
            card = "S10";
            suit = card[0];
            value = card.substr(1);
            lcd.locate(column_position, row_position);

            if (suit == 'C') {
                lcd.character(column_position, row_position, 0);
            }
            else if (suit == 'D') {
                lcd.character(column_position, row_position, 1);
            }
            else if (suit == 'H') {
                lcd.character(column_position, row_position, 2);
            }
            else if (suit == 'S') {
                lcd.character(column_position, row_position, 3);
            }

            column_position += 1;
            lcd.locate(column_position, row_position);

            lcd.printf(value.c_str());
            column_position += value.length() + 1;
            lcd.locate(column_position, row_position);

            // display third number
            card = "H3";
            suit = card[0];
            value = card.substr(1);
            lcd.locate(column_position, row_position);

            if (suit == 'C') {
                lcd.character(column_position, row_position, 0);
            }
            else if (suit == 'D') {
                lcd.character(column_position, row_position, 1);
            }
            else if (suit == 'H') {
                lcd.character(column_position, row_position, 2);
            }
            else if (suit == 'S') {
                lcd.character(column_position, row_position, 3);
            }

            column_position += 1;
            lcd.locate(column_position, row_position);

            lcd.printf(value.c_str());
            column_position += value.length() + 1;
            lcd.locate(column_position, row_position);


            break;
        }
    }
}
