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

void display_river(LCD1602::LCD1602& lcd, vector<string> river, int numberOfCards){
    lcd.locate(0, 0);
    for (int i = 0; i < numberOfCards; i++) {
        lcd.display_char(poker::getSuit(river[i]));
        lcd.display_string(poker::getRank(river[i]));
        lcd.display_string(" ");
    }
}

void display_player_cards(LCD1602::LCD1602& lcd, vector<string> player1, vector<string> player2, vector<string> user) {
    vector<vector<string>> players = {player1, player2, user};
    for (int i = 0; i < players.size(); i++) {
        vector<string> player = players[i];

        for (int j = 0; j < player.size(); j++) {
            lcd.display_char(   poker::getSuit(player[j]) );
            lcd.display_string( poker::getRank(player[j]) );
        }

        lcd.display_string(" ");
    }
}

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

enum difficulty { BEGINNER, INTERMEDIATE, PRO };

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

void start_screen() {
    blackbox.clear();
    blackbox.locate(0, 0);
    blackbox.display_string("Neutronics Poker");
    blackbox.locate(0, 1);
    blackbox.display_string(utilities::center_string("Press Start"));
}

void menu_screen() {
    blackbox.clear();
    blackbox.locate(0, 0);
    blackbox.display_string("Game Select:");
    blackbox.locate(0, 1);
    blackbox.display_string("A) Poker B) BKJK");
}

void select_difficulty(difficulty* diff) {
    const char* difficulty_levels[3] = {
        "Beginner",
        "Intermediate",
        "Pro"
    };

    int selection = 0;

    blackbox.clear();
    blackbox.locate(0, 0);
    blackbox.display_string("Difficulty:");
    blackbox.locate(0, 1);
    blackbox.display_string(difficulty_levels[selection]);

    while (true) {
        // Update LCD display based on selection

        // Check for Select button press
        if (button_select == false) {
            selection++;
            blackbox.clear_row(1);
            blackbox.display_string(difficulty_levels[selection]);

            // Updates displayed selection when select button is pressed
            if (selection >= 3) {
                selection = 0;
                blackbox.clear_row(1);
                blackbox.display_string(difficulty_levels[selection]);
            }

            thread_sleep_for(200);
        }

        // returns selected difficulty when A button is pressed
        if (button_a == false) {
            *diff = (difficulty)(selection);
            break;
        }

        // returns to the menu screen if B button is pressed
        if (button_b == false) {
            menu_screen();
            break;
        }
    }
}

int main() {
    setup();
    difficulty selectedDiff;

    while (true) {
        // STAGE 1: START SCREEN
        if (state == "start screen") {
            start_screen();
            // blackbox.display_string("Neutronics Poker");
            // blackbox.display_string(utilities::center_string("Press Start"));

            while (true) {
                // STAGE 2: MENU SCREEN
                if (button_start == false) {
                    menu_screen();
                    // state = "river3";
                    // thread_sleep_for(200);
                    // break;

                    while (true) {
                        // STAGE 3: DIFFICULTY SELECTION
                        if (button_a == false) {
                            select_difficulty(&selectedDiff);
                            state = "river3"; // selects poker game
                            thread_sleep_for(200);
                            break;
                        } else if (button_b == false) {
                            select_difficulty(&selectedDiff);
                            state = "river3"; // change to select blackjack game later
                            thread_sleep_for(200);
                            break;
                        }
                    }
                    break;
                }
            }
            
        }

        // STAGE 4
        if (state == "river3") {
            deck.reset_deck();
            blackbox.clear();
            blackbox.locate(0, 0);

            river   = {deck.draw_card(), deck.draw_card(), deck.draw_card(), deck.draw_card(), deck.draw_card()};
            user    = {deck.draw_card(), deck.draw_card()};
            player1 = {deck.draw_card(), deck.draw_card()};
            player2 = {deck.draw_card(), deck.draw_card()};

            display_river(blackbox, river, 3);

            blackbox.locate(2, 1);

            for (int i = 0; i < 2; i++) {
                blackbox.display_char("fill");
                blackbox.display_char("fill");
                blackbox.display_char("fill");
                blackbox.display_char("fill");
                blackbox.display_string(" ");
            }

            for (int i = 0; i < user.size(); i++) {
                blackbox.display_char(   poker::getSuit(user[i]) );
                blackbox.display_string( poker::getRank(user[i]) );
            }

            while (true) {
                if (button_a == false) {
                    state = "river4";
                    thread_sleep_for(200);
                    break;
                }
            }
        }

        // STAGE 5
        if (state == "river4") {
            display_river(blackbox, river, 4);

            while (true) {
                if (button_a == false) {
                    state = "river5";
                    thread_sleep_for(200);
                    break;
                }
            }
        }

        // STAGE 6
        if (state == "river5") {
            display_river(blackbox, river, 5);

            while (true) {
                if (button_a == false) {
                    state = "end screen";
                    thread_sleep_for(500);
                    break;
                }
            }
        }

        // STAGE 7
        if (state == "end screen") {
            blackbox.clear();
            blackbox.locate(0, 0);
            display_river(blackbox, river, 5);

            // blackbox.locate(2, 1);
            // display_player_cards(blackbox, player1, player2, user);

            // vector<string> user_cards    = { river[0], river[1], river[2], river[3], river[4], user[0],    user[1]    };
            // vector<string> player1_cards = { river[0], river[1], river[2], river[3], river[4], player1[0], player1[1] };
            // vector<string> player2_cards = { river[0], river[1], river[2], river[3], river[4], player2[0], player2[1] };

            // int userPoints    = poker::getPoints(user_cards);
            // int player1Points = poker::getPoints(player1_cards);
            // int player2Points = poker::getPoints(player2_cards);

            // // DEBUG: print player scores
            // printf("%d\n", userPoints);
            // printf("%d\n", player1Points);
            // printf("%d\n", player2Points);

            // thread_sleep_for(1000);

            // int winnerScore = 0;
            // int winnerPosition = 0;

            // if (winnerScore > userPoints) {
            //     winnerScore = userPoints;
            //     winnerPosition = 0;
            // }
            // if (winnerScore > player1Points) {
            //     winnerScore = player1Points;
            //     winnerPosition = 1;
            // }
            // if (winnerScore > player2Points) {
            //     winnerScore = player2Points;
            //     winnerPosition = 2;
            // }

            // winnerPosition = 0;

            // if (winnerPosition == 1) {
            //     blackbox.locate(7, 1);
            //     blackbox.display_string("    ");
            //     blackbox.locate(12, 1);
            //     blackbox.display_string("    ");
            // }

            // if (winnerPosition == 2) {
            //     blackbox.locate(2, 1);
            //     blackbox.display_string("    ");
            //     blackbox.locate(12, 1);
            //     blackbox.display_string("    ");
            // }

            // if (winnerPosition == 0) {
            //     blackbox.locate(7, 1);
            //     blackbox.display_string("    ");
            //     blackbox.locate(12, 1);
            //     blackbox.display_string("    ");
            // }

            while (true) {
                if (button_start == false) {
                    state = "river3";
                    thread_sleep_for(200);
                    break;
                }
            }
        }

        

    }
}
