#include <array>

#include <algorithm>

#include <map>

#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include <ctime>
#include <set>

#include <unordered_set>


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

            // printf(randomCard.c_str());
            // printf("\n");
            return randomCard;
        }

        void reset_deck() {
            deck = generate_deck();
            numberOfcardsInDeck = 52;
        }

        void debug_print_deck() {
            for (int i = 0; i < deck.size(); i++) {
                // printf("%s\n", (const char*)deck[i].c_str());
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
        return 0;
    }

    string getRank(string card) {
        string rank = card.substr(1);
        return rank;
    }



    bool inVector(std::vector<std::string> vec, std::string str) {
        for (const auto& element : vec) {
            if (element == str) {
                return true;
            }
        }
        return false;
    }

    bool hasFiveConsecutive(const std::vector<int>& nums) {
        int consecutiveCount = 1;
        for (size_t i = 0; i < nums.size() - 1; ++i) {
            if (std::abs(nums[i] - nums[i + 1]) == 1) {
                consecutiveCount++;
                if (consecutiveCount == 5) {
                    return true;
                }
            } else {
                consecutiveCount = 1;
            }
        }
        return false;
    }



    bool isRoyalFlush(vector<string> cards) {
        std::map<string, int> suitCounts;
        for (int i = 0; i < cards.size(); i++) {
            suitCounts[getSuit(cards[i])]++;
        }

        char mostCommonSuit;
        for (auto i = suitCounts.begin(); i != suitCounts.end(); i++) {
            if (i->second == 5) {
                mostCommonSuit = i->first[0];
            }
        }

        mostCommonSuit = toupper(mostCommonSuit);

        vector<string> ranks;
        for (int i = 0; i < cards.size(); i++) {
            if (mostCommonSuit == cards[i][0]) {
                ranks.push_back(getRank(cards[i]));
            }
        }

        if (
            std::find(ranks.begin(), ranks.end(), "10") != ranks.end()
            && std::find(ranks.begin(), ranks.end(), "J") != ranks.end()
            && std::find(ranks.begin(), ranks.end(), "Q") != ranks.end()
            && std::find(ranks.begin(), ranks.end(), "K") != ranks.end()
            && std::find(ranks.begin(), ranks.end(), "A") != ranks.end()
        ) {
            return true;
        }
        return false;
    }

    bool isStraightFlush(vector<string> cards) {
        std::map<string, int> suitCounts;
        for (int i = 0; i < cards.size(); i++) {
            suitCounts[getSuit(cards[i])]++;
        }

        char mostCommonSuit;
        for (auto i = suitCounts.begin(); i != suitCounts.end(); i++) {
            if (i->second == 5) {
                mostCommonSuit = i->first[0];
            }
        }

        mostCommonSuit = toupper(mostCommonSuit);

        vector<int> ranks;
        for (int i = 0; i < cards.size(); i++) {
            if (mostCommonSuit == cards[i][0]) {
                string rank = getRank(cards[i]);
                int rank_value;

                if (rank == "J") {
                    rank_value = 11;
                }
                else if (rank == "Q") {
                    rank_value = 12;
                }
                else if (rank == "K") {
                    rank_value = 13;
                }
                else if (rank == "A") {
                    rank_value = 14;
                }
                else {
                    rank_value = std::stoi(rank);
                }

                ranks.push_back(rank_value);
            }
        }

        std::sort(ranks.begin(), ranks.end());

        if (hasFiveConsecutive(ranks)) {
            return true;
        }
        return false;
    }

    bool isFourOfAKind(vector<string> cards) {
        std::map<string, int> rankCounts;
        for (int i = 0; i < cards.size(); i++) {
            rankCounts[getRank(cards[i])]++;
        }

        for (auto i = rankCounts.begin(); i != rankCounts.end(); i++) {
            if (i->second == 4) {
                return true;
            }
        }
        return false;
    }

    bool isFullHouse(vector<string> cards) {
        std::map<string, int> rankCounts;
        for (int i = 0; i < cards.size(); i++) {
            rankCounts[getRank(cards[i])]++;
        }

        bool isThreeOfAKind = false;
        bool isTwoOfAKind = false;
        for (auto i = rankCounts.begin(); i != rankCounts.end(); i++) {
            if (i->second == 3) {
                isThreeOfAKind = true;
            }
            if (i->second == 2) {
                isTwoOfAKind = true;
            }
        }
        return isThreeOfAKind && isTwoOfAKind;
    }

    bool isFlush(vector<string> cards) {
        std::map<string, int> suitCounts;

        for (int i = 0; i < cards.size(); i++) {
            suitCounts[getSuit(cards[i])]++;
        }

        for (auto i = suitCounts.begin(); i != suitCounts.end(); i++) {
            if (i->second == 5) {
                return true;
            }
        }
        return false;
    }

    bool isStraight(vector<string> cards) {
        vector<int> ranks;
        for (int i = 0; i < cards.size(); i++) {
            string rank = getRank(cards[i]);
            int rank_value;

            if (rank == "J") {
                rank_value = 11;
            }
            else if (rank == "Q") {
                rank_value = 12;
            }
            else if (rank == "K") {
                rank_value = 13;
            }
            else if (rank == "A") {
                rank_value = 14;
            }
            else {
                rank_value = std::stoi(rank);
            }

            ranks.push_back(rank_value);
        }

        std::sort(ranks.begin(), ranks.end());

        if (hasFiveConsecutive(ranks)) {
            return true;
        }
        return false;
    }

    bool isThreeOfAKind(vector<string> cards) {
        std::map<string, int> rankCounts;
        for (int i = 0; i < cards.size(); i++) {
            rankCounts[getRank(cards[i])]++;
        }

        for (auto i = rankCounts.begin(); i != rankCounts.end(); i++) {
            if (i->second == 3) {
                return true;
            }
        }
        return false;
    }

    bool isTwoPair(vector<string> cards) {
        std::map<string, int> rankCounts;
        for (int i = 0; i < cards.size(); i++) {
            rankCounts[getRank(cards[i])]++;
        }

        int numberOfPairs = 0;
        for (auto i = rankCounts.begin(); i != rankCounts.end(); i++) {
            if (i->second == 2) {
                numberOfPairs++;
            }
        }
        
        if (numberOfPairs >= 2) {
            return true;
        }
        return false;
    }

    bool isPair(vector<string> cards) {
        std::map<string, int> rankCounts;
        for (int i = 0; i < cards.size(); i++) {
            rankCounts[getRank(cards[i])]++;
        }

        for (auto i = rankCounts.begin(); i != rankCounts.end(); i++) {
            if (i->second == 2) {
                return true;
            }
        }
        return false;
    }

    int getHighCard(vector<string> cards) {
        vector<int> ranks;
        for (int i = 0; i < cards.size(); i++) {
            string rank = getRank(cards[i]);
            int rank_value;

            if (rank == "J") {
                rank_value = 11;
            }
            else if (rank == "Q") {
                rank_value = 12;
            }
            else if (rank == "K") {
                rank_value = 13;
            }
            else if (rank == "A") {
                rank_value = 14;
            }
            else {
                rank_value = std::stoi(rank);
            }

            ranks.push_back(rank_value);
        }

        std::sort(ranks.begin(), ranks.end());

        int highestCard = 0;
        for (int i = 0; i < ranks.size(); i++) {
            if (highestCard < ranks[i]) {
                highestCard = ranks[i];
            }
        }

        return highestCard;
    }

}
