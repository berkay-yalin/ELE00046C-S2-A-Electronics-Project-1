#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include <random>
#include <ctime>

namespace poker {
    struct CardSuitCharacters {
        uint8_t heart[8] = {0b00000, 0b01010, 0b11111, 0b11111, 0b11111, 0b01110, 0b00100, 0b00000};
        uint8_t diamond[8] = {0b00000, 0b00100, 0b01110, 0b11111, 0b11111, 0b01110, 0b00100, 0b00000};
        uint8_t spade[8] = {0b00000, 0b00100, 0b01110, 0b11111, 0b11111, 0b00100, 0b01110, 0b00000};
        uint8_t club[8] = {0b00000, 0b01110, 0b01110, 0b11111, 0b11111, 0b00100, 0b01110, 0b00000};
    };

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
            deck = generate_deck();
            numberOfcardsInDeck = deck.size();
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
    
    string getSuit(string card) {
        char suit = card[0];
        
        if (suit == 'C') {
            return "club";
        }
        else if (suit == 'D') {
            return "diamond";
        }
        else if (suit == 'H') {
            return "hearts";
        }
        else if (suit == 'S') {
            return "spades";
        }
        return 0;
    }

    string getRank(string card) {
        string rank = card.substr(1);
        return rank;
    }
}