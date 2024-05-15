#include "mbed.h"
#include "LCD.h"

#include <string>
#include <vector>
#include <utility>
#include <random>
#include <ctime>

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

int getSuit(string card) {
    /**
        returns the number representing the input card's suit
    **/
    char suit = card[0];
    
    if (suit == 'C') {
        return 1;
    }
    else if (suit == 'D') {
        return 2;
    }
    else if (suit == 'H') {
        return 3;
    }
    else if (suit == 'S') {
        return 4;
    }
    return 0;
}

string getRank(string card) {
    string rank = card.substr(1);
    return rank;
}

class Deck {
private:
    vector<string> deck;
    int numberOfcardsInDeck;
    const vector<string> suits = {"C", "D", "H", "S"};
    const vector<string> ranks = {"J", "Q", "K", "A"};

    std::random_device rd;
    std::mt19937 gen;

public:
    Deck() : gen(rd()) {
        // generate deck
        deck = generate_deck();
        numberOfcardsInDeck = deck.size();
        // gen.seed(static_cast<unsigned>(std::time(nullptr)));
    }

    vector<string> generate_deck() {
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

    string draw_card() {
        std::uniform_int_distribution<> dis(0, numberOfcardsInDeck - 1);
        int randomNumber = dis(gen);
        string randomCard = deck[randomNumber];
        deck.erase(deck.begin() + randomNumber);
        return randomCard;
    }

    void reset_deck() {
        deck = generate_deck();
    }

    void debug_print_deck() {
        for (int i = 0; i < deck.size(); i++) {
            printf("%s\n", (const char*)deck[i].c_str());
        }
    }
};

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

Deck deck;

void setup() {
    printf("\n");
    lcd.create(1, card_suit_characters::club);
    lcd.create(2, card_suit_characters::diamond);
    lcd.create(3, card_suit_characters::heart);
    lcd.create(4, card_suit_characters::spade);
}

int main() {
    setup();

    while (true) {
        // STAGE 1: START SCREEN
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

        // STAGE 2: 
        if (state == "stage2") {
            // define stuff
            int column = 0;
            int row = 0;
            vector<string> cards;

            lcd.cls();

            // river
            cards = {
                deck.draw_card(),
                deck.draw_card(),
                deck.draw_card(), 
            };

            for (int i = 0; i < cards.size(); i++) {
                int suit = getSuit(cards[i]);
                string rank = getRank(cards[i]);

                lcd.character(column, row, suit);
                column += 1;
                lcd.locate(column, row);

                lcd.printf("%s", (const char *)rank.c_str());
                column += rank.length() + 1;
                lcd.locate(column, row);
            }

            deck.debug_print_deck();

            column = 11;
            row = 1;

            // player cards
            cards = {
                deck.draw_card(),
                deck.draw_card()
            };

            for (int i = 0; i < cards.size(); i++) {
                int suit = getSuit(cards[i]);
                string rank = getRank(cards[i]);

                lcd.character(column, row, suit);
                column += 1;
                lcd.locate(column, row);

                lcd.printf("%s", (const char *)rank.c_str());
                column += rank.length() + 1;
                lcd.locate(column, row);
            }

            deck.debug_print_deck();

            break;
        }
    }
}

