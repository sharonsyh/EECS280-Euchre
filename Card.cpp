// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
int helperCardLess(const Card &a, const Card &b, const std::string &trump);
std::pair<int, int> helperOperatorLtGt(const Card &lhs, const Card &rhs);
//EFFECTS Initializes Card to the Two of Spades
Card::Card() {
    rank = RANK_TWO;
    suit = SUIT_SPADES;
}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const std::string &rank_in, const std::string &suit_in) {
    rank = rank_in;
    suit = suit_in;
}

//EFFECTS Returns the rank
std::string Card::get_rank() const {
    return rank;
}

//EFFECTS Returns the suit.  Does not consider trump.
std::string Card::get_suit() const {
    return suit;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const {
    assert(trump == SUIT_SPADES || trump == SUIT_CLUBS
    || trump == SUIT_HEARTS || trump == SUIT_DIAMONDS);

    if (trump == SUIT_SPADES) {
        if (rank == RANK_JACK && suit == SUIT_CLUBS) {
            return trump;
        }
    } else if (trump == SUIT_CLUBS) {
        if (rank == RANK_JACK && suit == SUIT_SPADES) {
            return trump;
        }
    } else if (trump == SUIT_HEARTS) {
        if (rank == RANK_JACK && suit == SUIT_DIAMONDS) {
            return trump;
        }
    } else if (trump == SUIT_DIAMONDS) {
        if (rank == RANK_JACK && suit == SUIT_HEARTS) {
            return trump;
        }
    } else {
        assert(false);
    }

    return suit;
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face_or_ace() const {
    if (rank == RANK_JACK || rank == RANK_QUEEN 
    || rank == RANK_KING || rank == RANK_ACE) {
        return true;
    } else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const {
    assert(trump == SUIT_SPADES || trump == SUIT_CLUBS 
    || trump == SUIT_HEARTS || trump == SUIT_DIAMONDS);

    if (suit == trump && rank == RANK_JACK) {
        return true;
    } else {
        return false;
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const {
    assert(trump == SUIT_SPADES || trump == SUIT_CLUBS 
    || trump == SUIT_HEARTS || trump == SUIT_DIAMONDS);

    if (trump == SUIT_SPADES) {
        if (rank == RANK_JACK && suit == SUIT_CLUBS) {
            return true;
        }
    } else if (trump == SUIT_CLUBS) {
        if (rank == RANK_JACK && suit == SUIT_SPADES) {
            return true;
        }
    } else if (trump == SUIT_HEARTS) {
        if (rank == RANK_JACK && suit == SUIT_DIAMONDS) {
            return true;
        }
    } else if (trump == SUIT_DIAMONDS) {
        if (rank == RANK_JACK && suit == SUIT_HEARTS) {
            return true;
        }
    } else {
        assert(false);
    }

    return false;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if the card is a trump card.  All cards of the trump
// suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const {
    assert(trump == SUIT_SPADES || trump == SUIT_CLUBS 
    || trump == SUIT_HEARTS || trump == SUIT_DIAMONDS);

    if (suit == trump) {
        return true;
    } else if (is_left_bower(trump)) {
        return true;
    } else {
        return false;
    }
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs) {
    std::pair<int, int> rankIndexes = helperOperatorLtGt(lhs, rhs);
    int lhsRankIndex = rankIndexes.first;
    int rhsRankIndex = rankIndexes.second;
    
    if (lhsRankIndex < rhsRankIndex) {
        return true;
    } else if (lhsRankIndex > rhsRankIndex) {
        return false;
    } else {
        // comare suits
        int lhsSuitIndex = -1;
        int rhsSuitIndex = -1;
        for (size_t i = 0; i < NUM_SUITS; ++i) {
            if (SUIT_NAMES_BY_WEIGHT[i] == lhs.get_suit()) {
                lhsSuitIndex = i;
            }
            if (SUIT_NAMES_BY_WEIGHT[i] == rhs.get_suit()) {
                rhsSuitIndex = i;
            }
            if (lhsSuitIndex != -1 && rhsSuitIndex != -1) {
                break;
            }
        }
        if (lhsSuitIndex < rhsSuitIndex) {
            return true;
        } else {
            return false;
        }
    }
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs) {

    // std::string lhsRank = lhs.get_rank();
    // std::string rhsRank = rhs.get_rank();

    // find the index of lhsRank and rhsRank
    // int lhsRankIndex = -1;
    // int rhsRankIndex = -1;

    // for (size_t i = 0; i < NUM_RANKS; ++i) {
    //     if (RANK_NAMES_BY_WEIGHT[i] == lhsRank) {
    //         lhsRankIndex = i;
    //     }
    //     if (RANK_NAMES_BY_WEIGHT[i] == rhsRank) {
    //         rhsRankIndex = i;
    //     }
    //     if (lhsRankIndex != -1 && rhsRankIndex != -1) {
    //         break;
    //     }
    // }
    
    // if (lhsRankIndex <= rhsRankIndex) {
    //     return true;
    // } else if (lhsRankIndex > rhsRankIndex) {
    //     return false;
    // } else {
    //     assert(false);
    // }

    if(lhs < rhs || lhs == rhs) {
        return true;
    } else {
        return false;
    }
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs) {
    std::pair<int, int> rankIndexes = helperOperatorLtGt(lhs, rhs);
    int lhsRankIndex = rankIndexes.first;
    int rhsRankIndex = rankIndexes.second;
    
    if (lhsRankIndex > rhsRankIndex) {
        return true;
    } else if (lhsRankIndex < rhsRankIndex) {
        return false;
    } else {
        // comare suits
        int lhsSuitIndex = -1;
        int rhsSuitIndex = -1;
        for (size_t i = 0; i < NUM_SUITS; ++i) {
            if (SUIT_NAMES_BY_WEIGHT[i] == lhs.get_suit()) {
                lhsSuitIndex = i;
            }
            if (SUIT_NAMES_BY_WEIGHT[i] == rhs.get_suit()) {
                rhsSuitIndex = i;
            }
            if (lhsSuitIndex != -1 && rhsSuitIndex != -1) {
                break;
            }
        }
        if (lhsSuitIndex > rhsSuitIndex) {
            return true;
        } else {
            return false;
        }
    }
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs) {
    // std::string lhsRank = lhs.get_rank();
    // std::string rhsRank = rhs.get_rank();

    // find the index of lhsRank and rhsRank
    // int lhsRankIndex = -1;
    // int rhsRankIndex = -1;
    // for (size_t i = 0; i < NUM_RANKS; ++i) {
    //     if (RANK_NAMES_BY_WEIGHT[i] == lhsRank) {
    //         lhsRankIndex = i;
    //     }
    //     if (RANK_NAMES_BY_WEIGHT[i] == rhsRank) {
    //         rhsRankIndex = i;
    //     }
    //     if (lhsRankIndex != -1 && rhsRankIndex != -1) {
    //         break;
    //     }
    // }
    
    // if (lhsRankIndex >= rhsRankIndex) {
    //     return true;
    // } else if (lhsRankIndex < rhsRankIndex) {
    //     return false;
    // } else {
    //     assert(false);
    // }
    if(lhs > rhs || lhs == rhs) {
        return true;
    } else {
        return false;
    }
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs) {
    std::string lhsRank = lhs.get_rank();
    std::string rhsRank = rhs.get_rank();
    std::string lhsSuit = lhs.get_suit();
    std::string rhsSuit = rhs.get_suit();

    if (lhsRank == rhsRank && lhsSuit == rhsSuit) {
        return true;
    } else {
        return false;
    }
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs) {
    std::string lhsRank = lhs.get_rank();
    std::string rhsRank = rhs.get_rank();
    std::string lhsSuit = lhs.get_suit();
    std::string rhsSuit = rhs.get_suit();

    if (lhsRank != rhsRank || lhsSuit != rhsSuit) {
        return true;
    } else {
        return false;
    }
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit) {
    assert(suit == Card::SUIT_SPADES || suit == Card::SUIT_CLUBS 
    || suit == Card::SUIT_HEARTS || suit == Card::SUIT_DIAMONDS);

    if (suit == Card::SUIT_SPADES) {
        return Card::SUIT_CLUBS;
    } else if (suit == Card::SUIT_CLUBS) {
        return Card::SUIT_SPADES;
    } else if (suit == Card::SUIT_HEARTS) {
        return Card::SUIT_DIAMONDS;
    } else if (suit == Card::SUIT_DIAMONDS) {
        return Card::SUIT_HEARTS;
    } else {
        assert(false);
    }
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card) {
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump) {
    assert(trump == Card::SUIT_SPADES || trump == Card::SUIT_CLUBS 
    || trump == Card::SUIT_HEARTS || trump == Card::SUIT_DIAMONDS);

    // if a and b are both trump cards, order them from 
    // 9 < 10 < Q < K < A < leftBower < rightBower
    // if (a.is_trump(trump) && b.is_trump(trump)) {
    //     if (a < b) {
    //         if (a.is_right_bower(trump)) {
    //             return false;
    //         } else if (a.is_left_bower(trump) && !b.is_right_bower(trump)) {
    //             return false;
    //         } else {
    //             return true;
    //         }
    //     } else {
    //         if (b.is_right_bower(trump)) {
    //             return true;
    //         } else if (b.is_left_bower(trump) && !a.is_right_bower(trump)) {
    //             return true;
    //         } else {
    //             return false;
    //         }
    //     }
    // }
    // // if b is trump card, always return 
    // else if (b.is_trump(trump)) {
    //     return true;
    // }

    // // if a is trump card, always return false
    // else if (a.is_trump(trump)) {
    //     return false;
    // }
    if (helperCardLess(a, b, trump) == 0) {
        return false;
    } else if (helperCardLess(a, b, trump) == 1) {
        return true;
    }

    // if a and b are both not trump cards
    else {
        if (a < b) {
            return true;
        } else {
            return false;
        }
    }
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump) {
    assert(trump == Card::SUIT_SPADES || trump == Card::SUIT_CLUBS 
    || trump == Card::SUIT_HEARTS || trump == Card::SUIT_DIAMONDS);

    // if a and b are both trump cards, order them from 
    // 9 < 10 < Q < K < A < leftBower < rightBower
    // if (a.is_trump(trump) && b.is_trump(trump)) {
    //     if (a < b) {
    //         if (a.is_right_bower(trump)) {
    //             return false;
    //         } else if (a.is_left_bower(trump) && !b.is_right_bower(trump)) {
    //             return false;
    //         } else {
    //             return true;
    //         }
    //     } else {
    //         if (b.is_right_bower(trump)) {
    //             return true;
    //         } else if (b.is_left_bower(trump) && !a.is_right_bower(trump)) {
    //             return true;
    //         } else {
    //             return false;
    //         }
    //     }
    // }
    // // if b is trump card, always return 
    // else if (b.is_trump(trump)) {
    //     return true;
    // }

    // // if a is trump card, always return false
    // else if (a.is_trump(trump)) {
    //     return false;
    // }
    if (helperCardLess(a, b, trump) == 0) {
        return false;
    } else if (helperCardLess(a, b, trump) == 1) {
        return true;
    } else {
        // if a and b are both not trump cards, check for led suit first
        // if a and b are both lead suit, use the overloaded < for comparison
        if (a.get_suit() == led_card.get_suit(trump) 
        && b.get_suit() == led_card.get_suit(trump)) {
            if (a < b) {
                return true;
            } else {
                return false;
            }
        }

        else if (b.get_suit() == led_card.get_suit(trump)) {
            return true;
        }

        else if (a.get_suit() == led_card.get_suit(trump)) {
            return false;
        }

        else {
            if (a < b) {
                return true;
            } else {
                return false;
            }
        }
    }
}

int helperCardLess(const Card &a, const Card &b, const std::string &trump) {
    assert(trump == Card::SUIT_SPADES || trump == Card::SUIT_CLUBS 
    || trump == Card::SUIT_HEARTS || trump == Card::SUIT_DIAMONDS);

    // if a and b are both trump cards, order them from 
    // 9 < 10 < Q < K < A < leftBower < rightBower
    if (a.is_trump(trump) && b.is_trump(trump)) {
        if (a < b) {
            if (a.is_right_bower(trump)) {
                return 0;
            } else if (a.is_left_bower(trump) && !b.is_right_bower(trump)) {
                return 0;
            } else {
                return 1;
            }
        } else {
            if (b.is_right_bower(trump)) {
                return 1;
            } else if (b.is_left_bower(trump) && !a.is_right_bower(trump)) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    // if b is trump card, always return 
    else if (b.is_trump(trump)) {
        return 1;
    }

    // if a is trump card, always return 0
    else if (a.is_trump(trump)) {
        return 0;
    }

    else {
        return 2;
    }
}

std::pair<int, int> helperOperatorLtGt(const Card &lhs, const Card &rhs) {
    std::string lhsRank = lhs.get_rank();
    std::string rhsRank = rhs.get_rank();

    // find the index of lhsRank and rhsRank
    int lhsRankIndex = -1;
    int rhsRankIndex = -1;
    for (size_t i = 0; i < NUM_RANKS; ++i) {
        if (RANK_NAMES_BY_WEIGHT[i] == lhsRank) {
            lhsRankIndex = i;
        }
        if (RANK_NAMES_BY_WEIGHT[i] == rhsRank) {
            rhsRankIndex = i;
        }
        if (lhsRankIndex != -1 && rhsRankIndex != -1) {
            break;
        }
    }

    return {lhsRankIndex, rhsRankIndex};
}

// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
