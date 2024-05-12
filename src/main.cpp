#include "mbed.h"
#include "TextLCD.h"

#include <cmath>
#include <string>

#include "LCD1602.hpp"

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

// LCD is controlled through the blackbox object
LCD1602::LCD1602 blackbox(D0, D1, D4, D5, D6, D7);

// initalise buttons
DigitalOut button_start(D8, PullUp);
DigitalOut button_select(D9, PullUp);
DigitalOut button_a(D10, PullUp);
DigitalOut button_b(D11, PullUp);

// global variable to determine which state the game is at
string state = "start screen";

int main() {
    while (true) {
        if (state == "start screen") {
            /**
                STAGE 1: "start screen"
                displays the opening title until user input
            **/
            blackbox.clear();
            blackbox.locate(0, 0);
            blackbox.display("Neutronics Poker");
            blackbox.display(center_string("Press Start"));
            blackbox.setCursorMode("off");

            while (true) {
                if (button_start == false) {
                    break;
                }
            }

            blackbox.clear();
            // TODO: develop next stage of the game
            state = "";
        }

        if (state == "") {
            /**
                STAGE 2: ""
                // TODO: develop next stage of the game
            **/
        }
    }
}

