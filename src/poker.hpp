#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include <ctime>

namespace poker {
    class Deck {
    private:
        vector<string> deck;
        int numberOfcardsInDeck;
        const vector<string> suits = {"C", "D", "H", "S"};
        const vector<string> ranks = {"J", "Q", "K", "A"};

        // std::random_device rd;
        // std::mt19937 gen;

    public:
        // Deck() : gen(rd()) {
        Deck() {
            deck = generate_deck();
            numberOfcardsInDeck = 52;
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
            const int min = 1;
            const int max = numberOfcardsInDeck;
            int randomNumber = min + rand() % (max - min + 1);

            string randomCard = deck[randomNumber];
            deck.erase(deck.begin() + randomNumber);

            printf(randomCard.c_str());
            printf("\n");
            return randomCard;
        }

        void reset_deck() {
            deck = generate_deck();
            numberOfcardsInDeck = 52;
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
            return "heart";
        }
        else if (suit == 'S') {
            return "spade";
        }
        printf("broken character: %c\n", suit);
        return 0;
    }

    string getRank(string card) {
        string rank = card.substr(1);
        return rank;
    }
}