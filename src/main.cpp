#include <string>
#include <vector>
#include <utility>
#include <random>
#include <ctime>

#include "mbed.h"
#include "LCD.h"
#include "LCD1602.hpp"
#include "card_suit_characters.hpp"
#include "poker.hpp"
#include "utilities.hpp"

// initalise buttons
DigitalOut button_start(D8, PullUp);
DigitalOut button_select(D9, PullUp);
DigitalOut button_a(D10, PullUp);
DigitalOut button_b(D11, PullUp);

// global variable to determine which state the game is at
string state = "start screen";

LCD1602::LCD1602 blackbox(D0, D1, D4, D5, D6, D7);

poker::Deck deck;

void setup() {
    printf("\n");
    blackbox.create_char("club", card_suit_characters::club);
    blackbox.create_char("diamond", card_suit_characters::diamond);
    blackbox.create_char("heart", card_suit_characters::heart);
    blackbox.create_char("spade", card_suit_characters::spade);
}

int main() {
    setup();

    while (true) {
        // STAGE 1: START SCREEN
        if (state == "start screen") {
            blackbox.display_string("Neutronics Poker");
            blackbox.display_string(utilities::center_string("Press Start"));

            while (true) {
                if (button_start == false) {
                    break;
                }
            }

            blackbox.clear();
            state = "stage2";
        }

        // STAGE 2: 
        if (state == "stage2") {
            // river
            vector<string> cards = {
                deck.draw_card(),
                deck.draw_card(),
                deck.draw_card(), 
            };

            for (int i = 0; i < cards.size(); i++) {
                string suit = poker::getSuit(cards[i]);
                string rank = poker::getRank(cards[i]);

                blackbox.display_char(suit);
                blackbox.display_string(rank);
                blackbox.display_string(" ");
            }

            deck.debug_print_deck();

            // player cards
            blackbox.locate(10, 1);

            cards = {
                deck.draw_card(),
                deck.draw_card()
            };

            for (int i = 0; i < cards.size(); i++) {
                string suit = poker::getSuit(cards[i]);
                string rank = poker::getRank(cards[i]);

                blackbox.display_string(" ");
                blackbox.display_char(suit);
                blackbox.display_string(rank);
            }

            deck.debug_print_deck();

            break;
        }
    }
}
