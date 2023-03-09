// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <array>
#include <string>
#include "Pack.h"

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() {
    // suit D > C > H > S
    for (size_t s = 0; s < NUM_SUITS; ++s) {
        for (size_t r = 7; r < NUM_RANKS; ++r) {
            Card c = Card(RANK_NAMES_BY_WEIGHT[r], SUIT_NAMES_BY_WEIGHT[s]);
            cards.at(r-7 + 6*s) = c;
        }
    }
    next = 0;
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
    // can't assert the REQUIRES clause
    for (size_t i = 0; i < cards.size(); ++i) {
        std::string r;
        std::string s;
        std::string of; // dummy to handle "of"
        pack_input >> r >> of >> s;
        Card c = Card(r, s);
        cards.at(i) = c;
    }
    next = 0;
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    assert(cards.size() > 0);

    Card toReturn = cards.at(next);
    ++next;

    return toReturn;
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
    for (size_t i = 0; i < 7; ++i) {
        // cut the deck in half
        std::array<Card, 12> top;
        std::array<Card, 12> bot;
        for (size_t j = 0; j < cards.size(); ++j) {
            if (j < 12) {
                top.at(j) = cards.at(j);
            } else {
                bot.at(j-12) = cards.at(j);
            }
        }

        // interleave the two halves
        // eg) AoH 2oH 3oH 4oS 5oS 6oS >> 4oS AoH 5oS 2oH 6oS 3oH
        std::array<Card, 24> temp;
        for (size_t j = 0; j < cards.size(); ++j) {
            if (j%2 == 0) {
                temp.at(j+1) = top.at(j/2);
            } else {
                temp.at(j-1) = bot.at(j/2);
            }
        }

        cards = temp;
    }
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
    if (next >= cards.size()) {
        return true;
    } else {
        return false;
    }
}