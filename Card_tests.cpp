// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here
TEST(test_card_ctor_default) {
    Card c;
    ASSERT_EQUAL(c.get_rank(), Card::RANK_TWO);
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_SPADES);
}

TEST(test_card_get_rank) {
    Card c;
    ASSERT_EQUAL(c.get_rank(), Card::RANK_TWO);
}

TEST(test_card_get_suit) {
    Card c;
    ASSERT_EQUAL(c.get_suit(), Card::SUIT_SPADES);
}

TEST(test_card_get_suit_bower) {
    struct test {
        Card c;
        std::string trump;
        std::string expected;
    };
    vector<test> tests = {
        {Card(Card::RANK_ACE, Card::SUIT_CLUBS), Card::SUIT_CLUBS, Card::SUIT_CLUBS},
        {Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS), Card::SUIT_CLUBS, Card::SUIT_DIAMONDS},
        {Card(Card::RANK_NINE, Card::SUIT_HEARTS), Card::SUIT_CLUBS, Card::SUIT_HEARTS},
        {Card(Card::RANK_KING, Card::SUIT_SPADES), Card::SUIT_CLUBS, Card::SUIT_SPADES},
        {Card(Card::RANK_TWO, Card::SUIT_CLUBS), Card::SUIT_CLUBS, Card::SUIT_CLUBS},
        {Card(Card::RANK_JACK, Card::SUIT_CLUBS), Card::SUIT_CLUBS, Card::SUIT_CLUBS},
        {Card(Card::RANK_JACK, Card::SUIT_CLUBS), Card::SUIT_SPADES, Card::SUIT_SPADES},
        {Card(Card::RANK_JACK, Card::SUIT_SPADES), Card::SUIT_SPADES, Card::SUIT_SPADES},
        {Card(Card::RANK_JACK, Card::SUIT_SPADES), Card::SUIT_CLUBS, Card::SUIT_CLUBS},
        {Card(Card::RANK_JACK, Card::SUIT_HEARTS), Card::SUIT_HEARTS, Card::SUIT_HEARTS},
        {Card(Card::RANK_JACK, Card::SUIT_HEARTS), Card::SUIT_DIAMONDS, Card::SUIT_DIAMONDS},
        {Card(Card::RANK_JACK, Card::SUIT_DIAMONDS), Card::SUIT_DIAMONDS, Card::SUIT_DIAMONDS},
        {Card(Card::RANK_JACK, Card::SUIT_DIAMONDS), Card::SUIT_HEARTS, Card::SUIT_HEARTS},
    };

    for (auto t : tests) {
        ASSERT_EQUAL(t.c.get_suit(t.trump), t.expected);
    }
}

TEST(test_card_is_face_or_ace) {
    struct test {
        Card c;
        bool expected;
    };
    vector<test> tests = {
        {Card(Card::RANK_ACE, Card::SUIT_CLUBS), true},
        {Card(Card::RANK_KING, Card::SUIT_SPADES), true},
        {Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS), true},
        {Card(Card::RANK_JACK, Card::SUIT_CLUBS), true},
        {Card(Card::RANK_NINE, Card::SUIT_HEARTS), false},
        {Card(Card::RANK_EIGHT, Card::SUIT_CLUBS), false},
        {Card(Card::RANK_SEVEN, Card::SUIT_CLUBS), false},
        {Card(Card::RANK_SIX, Card::SUIT_CLUBS), false},
        {Card(Card::RANK_FIVE, Card::SUIT_CLUBS), false},
        {Card(Card::RANK_FOUR, Card::SUIT_CLUBS), false},
        {Card(Card::RANK_THREE, Card::SUIT_CLUBS), false},
        {Card(Card::RANK_TWO, Card::SUIT_CLUBS), false},
    };

    for (auto t : tests) {
        ASSERT_EQUAL(t.c.is_face_or_ace(), t.expected);
    }
}

TEST(test_card_is_right_bower) {
    struct test {
        Card c;
        std::string trump;
        bool expected;
    };
    vector<test> tests = {
        {Card(Card::RANK_ACE, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_KING, Card::SUIT_SPADES), Card::SUIT_SPADES, false},
        {Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS), Card::SUIT_DIAMONDS, false},
        {Card(Card::RANK_NINE, Card::SUIT_HEARTS), Card::SUIT_HEARTS, false},
        {Card(Card::RANK_EIGHT, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_SEVEN, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_SIX, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_FIVE, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_FOUR, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_THREE, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_TWO, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_JACK, Card::SUIT_CLUBS), Card::SUIT_CLUBS, true},
        {Card(Card::RANK_JACK, Card::SUIT_CLUBS), Card::SUIT_SPADES, false},
        {Card(Card::RANK_JACK, Card::SUIT_SPADES), Card::SUIT_SPADES, true},
        {Card(Card::RANK_JACK, Card::SUIT_SPADES), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_JACK, Card::SUIT_HEARTS), Card::SUIT_HEARTS, true},
        {Card(Card::RANK_JACK, Card::SUIT_HEARTS), Card::SUIT_DIAMONDS, false},
        {Card(Card::RANK_JACK, Card::SUIT_DIAMONDS), Card::SUIT_DIAMONDS, true},
        {Card(Card::RANK_JACK, Card::SUIT_DIAMONDS), Card::SUIT_HEARTS, false},
    };

    for (auto t : tests) {
        ASSERT_EQUAL(t.c.is_right_bower(t.trump), t.expected);
    }
}

TEST(test_card_is_left_bower) {
    struct test {
        Card c;
        std::string trump;
        bool expected;
    };
    vector<test> tests = {
        {Card(Card::RANK_ACE, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_KING, Card::SUIT_SPADES), Card::SUIT_SPADES, false},
        {Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS), Card::SUIT_DIAMONDS, false},
        {Card(Card::RANK_NINE, Card::SUIT_HEARTS), Card::SUIT_HEARTS, false},
        {Card(Card::RANK_EIGHT, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_SEVEN, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_SIX, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_FIVE, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_FOUR, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_THREE, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_TWO, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_JACK, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_JACK, Card::SUIT_CLUBS), Card::SUIT_SPADES, true},
        {Card(Card::RANK_JACK, Card::SUIT_SPADES), Card::SUIT_SPADES, false},
        {Card(Card::RANK_JACK, Card::SUIT_SPADES), Card::SUIT_CLUBS, true},
        {Card(Card::RANK_JACK, Card::SUIT_HEARTS), Card::SUIT_HEARTS, false},
        {Card(Card::RANK_JACK, Card::SUIT_HEARTS), Card::SUIT_DIAMONDS, true},
        {Card(Card::RANK_JACK, Card::SUIT_DIAMONDS), Card::SUIT_DIAMONDS, false},
        {Card(Card::RANK_JACK, Card::SUIT_DIAMONDS), Card::SUIT_HEARTS, true},
    };

    for (auto t : tests) {
        ASSERT_EQUAL(t.c.is_left_bower(t.trump), t.expected);
    }
}

TEST(test_card_is_trump) {
    struct test {
        Card c;
        std::string trump;
        bool expected;
    };
    vector<test> tests = {
        {Card(Card::RANK_ACE, Card::SUIT_CLUBS), Card::SUIT_CLUBS, true},
        {Card(Card::RANK_KING, Card::SUIT_SPADES), Card::SUIT_SPADES, true},
        {Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS), Card::SUIT_DIAMONDS, true},
        {Card(Card::RANK_NINE, Card::SUIT_HEARTS), Card::SUIT_HEARTS, true},
        {Card(Card::RANK_EIGHT, Card::SUIT_CLUBS), Card::SUIT_HEARTS, false},
        {Card(Card::RANK_SEVEN, Card::SUIT_CLUBS), Card::SUIT_HEARTS, false},
        {Card(Card::RANK_SIX, Card::SUIT_DIAMONDS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_FIVE, Card::SUIT_CLUBS), Card::SUIT_DIAMONDS, false},
        {Card(Card::RANK_FOUR, Card::SUIT_DIAMONDS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_THREE, Card::SUIT_CLUBS), Card::SUIT_CLUBS, true},
        {Card(Card::RANK_TWO, Card::SUIT_SPADES), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_JACK, Card::SUIT_CLUBS), Card::SUIT_CLUBS, true},
        {Card(Card::RANK_JACK, Card::SUIT_CLUBS), Card::SUIT_SPADES, true},
        {Card(Card::RANK_JACK, Card::SUIT_SPADES), Card::SUIT_SPADES, true},
        {Card(Card::RANK_JACK, Card::SUIT_SPADES), Card::SUIT_CLUBS, true},
        {Card(Card::RANK_JACK, Card::SUIT_HEARTS), Card::SUIT_HEARTS, true},
        {Card(Card::RANK_JACK, Card::SUIT_HEARTS), Card::SUIT_DIAMONDS, true},
        {Card(Card::RANK_JACK, Card::SUIT_DIAMONDS), Card::SUIT_DIAMONDS, true},
        {Card(Card::RANK_JACK, Card::SUIT_DIAMONDS), Card::SUIT_HEARTS, true},
    };

    for (auto t : tests) {
        ASSERT_EQUAL(t.c.is_trump(t.trump), t.expected);
    }
}

TEST(test_card_overload_lt) {
    struct test {
        Card lhs;
        Card rhs;
        bool expected;
    };
    vector<test> tests = {
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_CLUBS), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_DIAMONDS), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS), false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_JACK, Card::SUIT_SPADES), false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_SPADES), false},
    };

    for (auto t : tests) {
        ASSERT_EQUAL(t.lhs < t.rhs, t.expected);
    }
}

TEST(test_card_overload_lteq) {
    struct test {
        Card lhs;
        Card rhs;
        bool expected;
    };
    vector<test> tests = {
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_CLUBS), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_DIAMONDS), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS), false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_JACK, Card::SUIT_SPADES), false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_SPADES), false},
    };

    for (auto t : tests) {
        ASSERT_EQUAL(t.lhs <= t.rhs, t.expected);
    }
}

TEST(test_card_overload_gt) {
    struct test {
        Card lhs;
        Card rhs;
        bool expected;
    };
    vector<test> tests = {
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_CLUBS), false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_DIAMONDS), false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_JACK, Card::SUIT_SPADES), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_SPADES), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_CLUBS), false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_HEARTS), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_DIAMONDS), false},
    };

    for (auto t : tests) {
        ASSERT_EQUAL(t.lhs > t.rhs, t.expected);
    }
}

TEST(test_card_overload_gteq) {
    struct test {
        Card lhs;
        Card rhs;
        bool expected;
    };
    vector<test> tests = {
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_CLUBS), false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_DIAMONDS), false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_JACK, Card::SUIT_SPADES), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_SPADES), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_CLUBS), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_HEARTS), true},
    };

    for (auto t : tests) {
        ASSERT_EQUAL(t.lhs >= t.rhs, t.expected);
    }
}

TEST(test_card_overload_eq) {
    struct test {
        Card lhs;
        Card rhs;
        bool expected;
    };
    vector<test> tests = {
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_CLUBS), false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_DIAMONDS), false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS), false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_JACK, Card::SUIT_SPADES), false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_SPADES), false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_CLUBS), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_HEARTS), false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_DIAMONDS), false},
    };

    for (auto t : tests) {
        ASSERT_EQUAL(t.lhs == t.rhs, t.expected);
    }
}

TEST(test_card_overload_noteq) {
    struct test {
        Card lhs;
        Card rhs;
        bool expected;
    };
    vector<test> tests = {
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_CLUBS), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_DIAMONDS), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_JACK, Card::SUIT_SPADES), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_SPADES), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_CLUBS), false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_HEARTS), true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_DIAMONDS), true},
    };

    for (auto t : tests) {
        ASSERT_EQUAL(t.lhs != t.rhs, t.expected);
    }
}

TEST(test_card_suit_next) {
    struct test {
        std::string input;
        std::string expected;
    };
    vector<test> tests = {
        {Card::SUIT_CLUBS, Card::SUIT_SPADES},
        {Card::SUIT_SPADES, Card::SUIT_CLUBS},
        {Card::SUIT_HEARTS, Card::SUIT_DIAMONDS},
        {Card::SUIT_DIAMONDS, Card::SUIT_HEARTS},
    };

    for (auto t : tests) {
        ASSERT_EQUAL(Suit_next(t.input), t.expected);
    }
}

TEST(test_card_overload_stream) {
    struct test {
        Card c;
        std::string expected;
    };
    vector<test> tests = {
        {Card(Card::RANK_ACE, Card::SUIT_CLUBS), "Ace of Clubs"},
        {Card(Card::RANK_KING, Card::SUIT_DIAMONDS), "King of Diamonds"},
        {Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS), "Queen of Diamonds"},
        {Card(Card::RANK_JACK, Card::SUIT_SPADES), "Jack of Spades"},
        {Card(Card::RANK_KING, Card::SUIT_SPADES), "King of Spades"},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), "King of Clubs"},
        {Card(Card::RANK_KING, Card::SUIT_HEARTS), "King of Hearts"},
        {Card(Card::RANK_KING, Card::SUIT_DIAMONDS), "King of Diamonds"},
    };

    for (auto t : tests) {
        std::ostringstream oss;
        oss << t.c;
        ASSERT_EQUAL(oss.str(), t.expected);
    }
}

TEST(test_card_card_less) {
    struct test {
        Card a;
        Card b;
        std::string trump;
        bool expected;
    };
    vector<test> tests = {
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_CLUBS), Card::SUIT_CLUBS, true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_JACK, Card::SUIT_CLUBS), Card::SUIT_CLUBS, true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_JACK, Card::SUIT_SPADES), Card::SUIT_CLUBS, true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false},

        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_HEARTS), Card::SUIT_HEARTS, true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_HEARTS), Card::SUIT_HEARTS, true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_HEARTS), Card::SUIT_HEARTS, true},

        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_HEARTS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_HEARTS), Card::SUIT_CLUBS, false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_HEARTS), Card::SUIT_CLUBS, false},

        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_DIAMONDS), Card::SUIT_HEARTS, true},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS), Card::SUIT_HEARTS, false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_JACK, Card::SUIT_SPADES), Card::SUIT_HEARTS, false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_SPADES), Card::SUIT_HEARTS, false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_CLUBS), Card::SUIT_HEARTS, false},
        {Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_DIAMONDS), Card::SUIT_HEARTS, true},
    };

    for (auto t : tests) {
        ASSERT_EQUAL(Card_less(t.a, t.b, t.trump), t.expected);
    }
}

TEST(test_card_card_less_led) {
    struct test {
        Card a;
        Card b;
        Card led;
        std::string trump;
        bool expected;
    };
    vector<test> tests = {
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_CLUBS),
            Card(Card::RANK_ACE, Card::SUIT_CLUBS), Card::SUIT_CLUBS, true,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_JACK, Card::SUIT_CLUBS),
            Card(Card::RANK_ACE, Card::SUIT_CLUBS), Card::SUIT_CLUBS, true,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_JACK, Card::SUIT_SPADES),
            Card(Card::RANK_ACE, Card::SUIT_CLUBS), Card::SUIT_CLUBS, true,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
            Card(Card::RANK_ACE, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false,
        },

        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_HEARTS), 
            Card(Card::RANK_ACE, Card::SUIT_CLUBS), Card::SUIT_HEARTS, true,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_HEARTS), 
            Card(Card::RANK_ACE, Card::SUIT_CLUBS), Card::SUIT_HEARTS, true,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
            Card(Card::RANK_ACE, Card::SUIT_CLUBS), Card::SUIT_HEARTS, true,
        },

        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_HEARTS),
            Card(Card::RANK_ACE, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_HEARTS),
            Card(Card::RANK_ACE, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
            Card(Card::RANK_ACE, Card::SUIT_CLUBS), Card::SUIT_CLUBS, false,
        },

        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_CLUBS),
            Card(Card::RANK_TWO, Card::SUIT_CLUBS), Card::SUIT_HEARTS, true,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_CLUBS),
            Card(Card::RANK_TWO, Card::SUIT_CLUBS), Card::SUIT_HEARTS, false,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
            Card(Card::RANK_TWO, Card::SUIT_CLUBS), Card::SUIT_HEARTS, false,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_JACK, Card::SUIT_CLUBS),
            Card(Card::RANK_TWO, Card::SUIT_CLUBS), Card::SUIT_HEARTS, false,
        },

        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_SPADES),
            Card(Card::RANK_TWO, Card::SUIT_SPADES), Card::SUIT_HEARTS, true,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_SPADES), 
            Card(Card::RANK_TWO, Card::SUIT_SPADES), Card::SUIT_HEARTS, true,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
            Card(Card::RANK_TWO, Card::SUIT_SPADES), Card::SUIT_HEARTS, true,
        },
        
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_SPADES),
            Card(Card::RANK_TWO, Card::SUIT_CLUBS), Card::SUIT_HEARTS, false,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_SPADES), 
            Card(Card::RANK_TWO, Card::SUIT_CLUBS), Card::SUIT_HEARTS, false,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
            Card(Card::RANK_TWO, Card::SUIT_CLUBS), Card::SUIT_HEARTS, false,
        },
        
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_ACE, Card::SUIT_DIAMONDS),
            Card(Card::RANK_TWO, Card::SUIT_SPADES), Card::SUIT_HEARTS, true,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
            Card(Card::RANK_TWO, Card::SUIT_SPADES), Card::SUIT_HEARTS, true,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS),
            Card(Card::RANK_TWO, Card::SUIT_SPADES), Card::SUIT_HEARTS, false,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_JACK, Card::SUIT_SPADES),
            Card(Card::RANK_TWO, Card::SUIT_DIAMONDS), Card::SUIT_HEARTS, false,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_CLUBS), Card(Card::RANK_KING, Card::SUIT_SPADES),
            Card(Card::RANK_TWO, Card::SUIT_DIAMONDS), Card::SUIT_HEARTS, false,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_DIAMONDS), Card(Card::RANK_KING, Card::SUIT_SPADES),
            Card(Card::RANK_TWO, Card::SUIT_CLUBS), Card::SUIT_HEARTS, false,
        },
        {
            Card(Card::RANK_KING, Card::SUIT_DIAMONDS), Card(Card::RANK_KING, Card::SUIT_HEARTS),
            Card(Card::RANK_TWO, Card::SUIT_CLUBS), Card::SUIT_SPADES, false,
        },
    };

    for (auto t : tests) {
        ASSERT_EQUAL(Card_less(t.a, t.b, t.led, t.trump), t.expected);
    }
}

TEST_MAIN()
