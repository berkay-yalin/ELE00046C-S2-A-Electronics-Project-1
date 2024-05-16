#include <cmath>
#include <string>

namespace utilities {
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
}