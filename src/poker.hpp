#include <array>

#include <algorithm>

#include <map>

#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include <ctime>

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
        // printf("broken character: %c\n", suit);
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

    // really poor code to demonstrate proof of concept
    // immediate rewrite requried

    bool isRoyalFlush(vector<string> cards) {
        vector<string> suits;

        int club_count = 0;
        int diamond_count = 0;
        int heart_count = 0;
        int spade_count = 0;

        for (int i = 0; i < 7; i++) {
            char suit = cards[i][0];

            if (suit == 'C') {
                club_count++;
            }
            else if (suit == 'D') {
                diamond_count++;
            }
            else if (suit == 'H') {
                heart_count++;
            }
            else if (suit == 'S') {
                spade_count++;
            }
        }

        char suit_5;
        if (club_count == 5) {
            suit_5 = 'C';
        }
        else if (diamond_count == 5) {
            suit_5 = 'D';
        }
        else if (heart_count == 5) {
            suit_5 = 'H';
        }
        else if (spade_count == 5) {
            suit_5 = 'S';
        }
        else {
            return false;
        }


        vector<string> ranks;
        for (int i = 0; i < 7; i++) {
            if (suit_5 == cards[i][0]) {
                ranks.push_back(cards[i].substr(1));
            }
        }

        if (inVector(ranks, "J") && inVector(ranks, "Q") && inVector(ranks, "K") && inVector(ranks, "A")) {
            return true;
        }
        else {
            return false;
        }
    }

    bool isStraightFlush(vector<string> cards) {
        vector<string> suits;

        int club_count = 0;
        int diamond_count = 0;
        int heart_count = 0;
        int spade_count = 0;

        for (int i = 0; i < 7; i++) {
            char suit = cards[i][0];

            if (suit == 'C') {
                club_count++;
            }
            else if (suit == 'D') {
                diamond_count++;
            }
            else if (suit == 'H') {
                heart_count++;
            }
            else if (suit == 'S') {
                spade_count++;
            }
        }

        char suit_5;
        if (club_count >= 5) {
            suit_5 = 'C';
        }
        else if (diamond_count >= 5) {
            suit_5 = 'D';
        }
        else if (heart_count >= 5) {
            suit_5 = 'H';
        }
        else if (spade_count >= 5) {
            suit_5 = 'S';
        }
        else {
            return false;
        }

        vector<int> ranks;
        for (int i = 0; i < 7; i++) {
            if (suit_5 == cards[i][0]) {
                string rank = cards[i].substr(1);

                if (rank == "J") {
                    ranks.push_back(11);
                }
                else if (rank == "Q") {
                    ranks.push_back(12);
                }
                else if (rank == "K") {
                    ranks.push_back(13);
                }
                else if (rank == "A") {
                    ranks.push_back(14);
                }
                else {
                    ranks.push_back(std::stoi(rank));
                }
            }
        }

        std::sort(ranks.begin(), ranks.end());

        if (hasFiveConsecutive(ranks)) {
            return true;
        }
        return false;
    }

    bool isFourOfAKind(vector<string> cards) {
        std::map<int, int> rankCounts;

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
                rank_value = std::stoi(cards[i].substr(1));
            }

            rankCounts[rank_value]++;
        }

        bool fourOfAKind = false;

        for (auto i = rankCounts.begin(); i != rankCounts.end(); i++) {
            if (i->second == 4) {
                fourOfAKind = true;
            }
        }

        return fourOfAKind;
    }

    bool isFullHouse(vector<string> cards) {
        std::map<int, int> rankCounts;

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
                rank_value = std::stoi(cards[i].substr(1));
            }

            rankCounts[rank_value]++;
        }

        bool threeOfAKind = false;
        bool twoOfAKind = false;

        for (auto i = rankCounts.begin(); i != rankCounts.end(); i++) {
            if (i->second == 3) {
                threeOfAKind = true;
            }
            if (i->second == 2) {
                twoOfAKind = true;
            }
        }

        return threeOfAKind && twoOfAKind;
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
        for (int i = 0; i < 7; i++) {
            string rank = getRank(cards[i]);

            // printf("string rank: %s\n", rank.c_str());

            if (rank == "J") {
                ranks.push_back(11);
            }
            else if (rank == "Q") {
                ranks.push_back(12);
            }
            else if (rank == "K") {
                ranks.push_back(13);
            }
            else if (rank == "A") {
                ranks.push_back(14);
            }
            else {
                // printf("v: %s\n", rank.c_str());
                ranks.push_back(std::stoi(rank));
            }
        }

        std::sort(ranks.begin(), ranks.end());

        if (hasFiveConsecutive(ranks)) {
            return true;
        }
        return false;
    }

    bool isThreeOfAKind(vector<string> cards) {
        std::map<int, int> rankCounts;

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
                rank_value = std::stoi(cards[i].substr(1));
            }

            rankCounts[rank_value]++;
        }

        for (auto i = rankCounts.begin(); i != rankCounts.end(); i++) {
            if (i->second == 3) {
                return true;
            }
        }
        return false;
    }

    bool isTwoPair(vector<string> cards) {
        std::map<int, int> rankCounts;

        for (int i = 0; i < cards.size(); i++) {
            string rank = getRank(cards[i]);
            int rank_value = 0;

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

            rankCounts[rank_value]++;
        }

        int pairCount = 0;
        for (auto i = rankCounts.begin(); i != rankCounts.end(); i++) {
            if (i->second == 2) {
                pairCount++;
            }
        }

        if (pairCount >= 2) {
            return true;
        }
        return false;
    }

    bool isPair(vector<string> cards) {
        std::map<int, int> rankCounts;

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
                rank_value = std::stoi(cards[i].substr(1));
            }

            rankCounts[rank_value]++;
        }

        for (auto i = rankCounts.begin(); i != rankCounts.end(); i++) {
            if (i->second == 2) {
                return true;
            }
        }
        return false;
    }

    int getHighestRank(vector<string> cards) {
        int highestRank = 0;
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
            // printf("rank_value: %d\n", highestRank);
            if (highestRank < rank_value) {
                highestRank = rank_value;
            }
            // printf("highestRank: %d\n", highestRank);
            // printf("\n");
        }
        // printf("highestRank final: %d\n", highestRank);
        return highestRank;
    }

    int getPoints(vector<string> cards) {
        int score = getHighestRank(cards);

        if (isRoyalFlush(cards)) {
            score += 100; 
        }
        else if (isStraightFlush(cards)) {
            score += 90;
        }
        else if (isFourOfAKind(cards)) {
            score += 80;
        }
        else if (isFullHouse(cards)) {
            score += 70;
        }
        else if (isFlush(cards)) {
            score += 60;
        }
        else if (isStraight(cards)) {
            score += 50;
        }
        else if (isThreeOfAKind(cards)) {
            score += 40;
        }
        else if (isTwoPair(cards)) {
            score += 30;
        }
        else if (isPair(cards)) {
            score += 20;
        }

        return score;
    }

}

