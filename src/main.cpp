#include <array>

#include <string>
#include <vector>
#include <utility>
#include <ctime>

#include "mbed.h"
#include "LCD.h"
#include "LCD1602.hpp"
#include "poker.hpp"
#include "custom_characters.hpp"
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

vector<string> river;
vector<string> user;
vector<string> player1;
vector<string> player2;

void setup() {
    // print newline otherwise printf doesn't work for some reason
    printf("START\n");

    blackbox.create_char("fill", custom_characters::fill);

    // Fill first 4 CGRAM locations with custom card suit characters
    blackbox.create_char("club", custom_characters::club);
    blackbox.create_char("diamond", custom_characters::diamond);
    blackbox.create_char("heart", custom_characters::heart);
    blackbox.create_char("spade", custom_characters::spade);
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
                    blackbox.clear();
                    state = "river3";
                    thread_sleep_for(200);
                    break;
                }
            }
        }

        // STAGE 2
        if (state == "river3") {
            // deck.reset_deck();
            blackbox.clear();
            blackbox.locate(0, 0);

            river = {deck.draw_card(), deck.draw_card(), deck.draw_card(), deck.draw_card(), deck.draw_card()};
            user = {deck.draw_card(), deck.draw_card()};
            player1 = {deck.draw_card(), deck.draw_card()};
            player2 = {deck.draw_card(), deck.draw_card()};
            

            // display river
            for (int i = 0; i < 3; i++) {
                string suit = poker::getSuit(river[i]);
                string rank = poker::getRank(river[i]);

                blackbox.display_char(suit);
                blackbox.display_string(rank);
                blackbox.display_string(" ");
            }

            // display player cards;
            blackbox.locate(2, 1);

            vector<vector<string>> players = {player1, player2};

            for (int i = 0; i < players.size(); i++) {
                    blackbox.display_char("fill");
                    blackbox.display_char("fill");
                    blackbox.display_char("fill");
                    blackbox.display_char("fill");
                    blackbox.display_string(" ");
            }

            // display user cards
            for (int i = 0; i < user.size(); i++) {
                string suit = poker::getSuit(user[i]);
                string rank = poker::getRank(user[i]);

                blackbox.display_char(suit);
                blackbox.display_string(rank);
            }

            while (true) {
                if (button_a == false) {
                    state = "river4";
                    thread_sleep_for(200);
                    break;
                }
            }
        }

        // STAGE 3
        if (state == "river4") {
            // display fourth card in river
            blackbox.locate(9, 0);
            string suit = poker::getSuit(river[3]);
            string rank = poker::getRank(river[3]);
            blackbox.display_char(suit);
            blackbox.display_string(rank);

            while (true) {
                if (button_a == false) {
                    state = "river5";
                    thread_sleep_for(200);
                    break;
                }
            }
        }

        // STAGE 4
        if (state == "river5") {
            // display fifth card in river
            blackbox.locate(12, 0);
            string suit = poker::getSuit(river[4]);
            string rank = poker::getRank(river[4]);
            blackbox.display_char(suit);
            blackbox.display_string(rank);

            while (true) {
                if (button_a == false) {
                    state = "end screen";
                    thread_sleep_for(200);
                    break;
                }
            }
        }

        // STAGE 4
        if (state == "end screen") {
            blackbox.clear();
            blackbox.locate(0, 0);

            // display river
            for (int i = 0; i < river.size(); i++) {
                string suit = poker::getSuit(river[i]);
                string rank = poker::getRank(river[i]);

                blackbox.display_char(suit);
                blackbox.display_string(rank);
                blackbox.display_string(" ");
            }
            
            // display players
            blackbox.locate(2, 1);

            vector<vector<string>> players = {player1, player2, user};
            for (int i = 0; i < players.size(); i++) {
                    vector<string> _player = players[i];
                    
                for (int j = 0; j < _player.size(); j++) {
                    string card = _player[j];
                    string suit = poker::getSuit(card);
                    string rank = poker::getRank(card);

                    blackbox.display_char(suit);
                    blackbox.display_string(rank);
                }
                
                blackbox.display_string(" ");
            }

            vector<string> user_cards    = { river[0], river[1], river[2], river[3], river[4], user[0],    user[1]    };
            vector<string> player1_cards = { river[0], river[1], river[2], river[3], river[4], player1[0], player1[1] };
            vector<string> player2_cards = { river[0], river[1], river[2], river[3], river[4], player2[0], player2[1] };

            int userPoints    = poker::getPoints(user_cards);
            int player1Points = poker::getPoints(player1_cards);
            int player2Points = poker::getPoints(player2_cards);

            // DEBUG: print player scores
            printf("%d\n", userPoints);
            printf("%d\n", player1Points);
            printf("%d\n", player2Points);

            thread_sleep_for(1000);

            int winnerScore = 0;
            int winnerPosition = 0;

            if (winnerScore > userPoints) {
                winnerScore = userPoints;
                winnerPosition = 0;
            }
            if (winnerScore > player1Points) {
                winnerScore = player1Points;
                winnerPosition = 1;
            }
            if (winnerScore > player2Points) {
                winnerScore = player2Points;
                winnerPosition = 2;
            }

            winnerPosition = 0;

            if (winnerPosition == 1) {
                blackbox.locate(7, 1);
                blackbox.display_string("    ");
                blackbox.locate(12, 1);
                blackbox.display_string("    ");
            }

            if (winnerPosition == 2) {
                blackbox.locate(2, 1);
                blackbox.display_string("    ");
                blackbox.locate(12, 1);
                blackbox.display_string("    ");
            }

            if (winnerPosition == 0) {
                blackbox.locate(7, 1);
                blackbox.display_string("    ");
                blackbox.locate(12, 1);
                blackbox.display_string("    ");
            }

            return 0;
        }

    }
}
