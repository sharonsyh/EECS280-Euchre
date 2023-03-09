// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "Card.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here

TEST(test_simple_player_ctor) {
    struct test {
        std::string in_name;
    };

    vector<test> tests {
        {"Alice"}, {"Bob"}, {"Charlie"}, {"Diana"}, {"Eric"}, {"12345"},
    };

    for (auto t : tests) {
        Player* someone = Player_factory(t.in_name, "Simple");
        ASSERT_EQUAL(t.in_name, someone->get_name());

        delete someone;
    }
}

TEST(test_simple_player_get_name) {
    // same test as ctor
    struct test {
        std::string in_name;
    };

    vector<test> tests {
        {"Alice"}, {"Bob"}, {"Charlie"}, {"Diana"}, {"Eric"}, {"12345"},
    };

    for (auto t : tests) {
        Player* someone = Player_factory(t.in_name, "Simple");
        ASSERT_EQUAL(t.in_name, someone->get_name());
        
        delete someone;
    }
}
//void add_card(const Card &c) {
    
// TEST(test_simple_player_add_card) {
//     // unless we create a getter to get simple player's hand,
//     // we can't really test this...
//     struct test {
        
//     };

//     vector<test> tests {

//     };

//     for (auto t : tests) {
        
//     }
// }

//void add_and_discard(const Card &upcard) 
    
TEST(test_simple_player_add_and_discard) {

    struct test {
        vector<Card> add_to_hand;
        std::string trump;
        Card added_card;
        Card expected;
    };

    vector<test> tests {
        {
            {
                Card(Card::RANK_KING, Card::SUIT_HEARTS),
                Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_HEARTS,
            Card(Card::RANK_JACK, Card::SUIT_HEARTS),
            Card(Card::RANK_JACK, Card::SUIT_HEARTS)
        },
        {
            {
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
                Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_JACK, Card::SUIT_CLUBS),
            Card(Card::RANK_KING, Card::SUIT_DIAMONDS)

        },
        {
            {
                Card(Card::RANK_KING, Card::SUIT_CLUBS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_CLUBS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_ACE, Card::SUIT_CLUBS),
            Card(Card::RANK_ACE, Card::SUIT_CLUBS)
        },
        {
            {
                Card(Card::RANK_NINE, Card::SUIT_SPADES),
                Card(Card::RANK_NINE, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_HEARTS)
            },
            Card::SUIT_SPADES,
            Card(Card::RANK_NINE, Card::SUIT_DIAMONDS),
            Card(Card::RANK_NINE, Card::SUIT_DIAMONDS)

        },
        {
            {
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
                Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_DIAMONDS,
            Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
            Card(Card::RANK_QUEEN, Card::SUIT_HEARTS)

        },
        {
            {
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS)
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
            Card(Card::RANK_JACK, Card::SUIT_DIAMONDS)
        }
        

    };


    for(auto t : tests) {

        Player* someone = Player_factory("someone", "Simple");

        for(auto card : t.add_to_hand) {
            someone->add_card(card);
        }

        someone->add_and_discard(t.added_card);
        Card output = someone->lead_card(t.trump);
        ASSERT_EQUAL(t.expected, output);
        delete someone;
    }

}

TEST(test_simple_player_make_trump) {

    struct test {
        vector<Card> add_to_hand;
        Card upcard;
        bool is_dealer;
        int round;
        std::string order_up_suit;
        std::string expected_suit;
        bool expected;
    };

    vector<test> tests {
        // round 1
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card(Card::RANK_KING, Card::SUIT_SPADES),
            false, 1, "", "Spades", true,
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_SPADES),
            },
            Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
            false, 1, "", "", false,
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
            false, 1, "", "", false,
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card(Card::RANK_KING, Card::SUIT_SPADES),
            true, 1, "", "Spades", true,
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_SPADES),
            },
            Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
            true, 1, "", "", false,
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
            true, 1, "", "", false,
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
            true, 1, "", "", false,
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_DIAMONDS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
            true, 1, "", "", false,
        },
        // round 2
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card(Card::RANK_KING, Card::SUIT_SPADES),
            false, 2, "", "Clubs", true,
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_HEARTS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card(Card::RANK_KING, Card::SUIT_SPADES),
            false, 2, "", "Clubs", true,
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card(Card::RANK_KING, Card::SUIT_CLUBS),
            false, 2, "", "", false,
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_SPADES),
            },
            Card(Card::RANK_KING, Card::SUIT_CLUBS),
            false, 2, "", "", false,
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card(Card::RANK_KING, Card::SUIT_CLUBS),
            true, 2, "", "Spades", true,
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
            true, 2, "", "Hearts", true,
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
            false, 2, "", "Hearts", true,
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card(Card::RANK_KING, Card::SUIT_HEARTS),
            true, 2, "", "Diamonds", true,
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card(Card::RANK_KING, Card::SUIT_HEARTS),
            false, 2, "", "Diamonds", true,
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_CLUBS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_SPADES),
            },
            Card(Card::RANK_KING, Card::SUIT_HEARTS),
            true, 2, "", "Diamonds", true,
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_TEN, Card::SUIT_HEARTS),
                Card(Card::RANK_NINE, Card::SUIT_DIAMONDS),
            },
            Card(Card::RANK_KING, Card::SUIT_HEARTS),
            false, 2, "", "", false,
        },

    };

    for (auto t : tests) {

        Player* someone = Player_factory("someone", "Simple");

        for (auto card : t.add_to_hand) {
            someone->add_card(card);
        }

        bool didOrderUp = someone->make_trump(t.upcard, t.is_dealer, t.round, t.order_up_suit);

        ASSERT_EQUAL(t.expected, didOrderUp);
        ASSERT_EQUAL(t.expected_suit, t.order_up_suit);

        delete someone;
    }
}

// TEST(test_simple_player_add_and_discard) {
//     // unless we create a getter to get simple player's hand,
//     // we can't really test this...
//     struct test {

//     };

//     vector<test> tests {

//     };

//     for (auto t : tests) {
        
//     }
// }

TEST(test_simple_player_lead_card) {
    struct test {
        vector<Card> add_to_hand;
        std::string trump;
        Card expected;
    };

    vector<test> tests {
        // cards in hand = 4, 3, 2, 1
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_CLUBS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_KING, Card::SUIT_SPADES),
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_SPADES),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_KING, Card::SUIT_SPADES),
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_CLUBS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_CLUBS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_JACK, Card::SUIT_CLUBS),
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_CLUBS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_SPADES),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_JACK, Card::SUIT_SPADES),
        },
        {
            {
                Card(Card::RANK_JACK, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_DIAMONDS,
            Card(Card::RANK_JACK, Card::SUIT_CLUBS),
        },
        {
            {
                Card(Card::RANK_NINE, Card::SUIT_SPADES),
                Card(Card::RANK_NINE, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_HEARTS),
                Card(Card::RANK_NINE, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_SPADES,
            Card(Card::RANK_NINE, Card::SUIT_DIAMONDS),
        },
        {
            {
                Card(Card::RANK_KING, Card::SUIT_HEARTS),
                Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_HEARTS,
            Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
        },
        {
            {
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
                Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
            },
            Card::SUIT_DIAMONDS,
            Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
        },
        {
            {
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
                Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
        },
        {
            {
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
            },
            Card::SUIT_HEARTS,
            Card(Card::RANK_JACK, Card::SUIT_HEARTS),
        },
        {
            {
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
        },
        {
            {
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
            },
            Card::SUIT_HEARTS,
            Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
        },
        {
            {
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_HEARTS,
            Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
        },
        {
            {
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_HEARTS,
            Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
        },
        // previous tests
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_KING, Card::SUIT_SPADES),
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_CLUBS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_CLUBS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_ACE, Card::SUIT_CLUBS),
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_CLUBS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_CLUBS),
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_JACK, Card::SUIT_CLUBS),
        },
        {
            {
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_DIAMONDS,
            Card(Card::RANK_JACK, Card::SUIT_SPADES),
        },
        {
            {
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_HEARTS,
            Card(Card::RANK_JACK, Card::SUIT_SPADES),
        },
        {
            {
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_HEARTS,
            Card(Card::RANK_JACK, Card::SUIT_SPADES),
        },


        // trump = SUIT_CLUBS

        //num of trump card = 0

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_HEARTS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS),
                Card(Card::RANK_NINE, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_ACE, Card::SUIT_HEARTS),
        },


        //num of trump card = 1

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_HEARTS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_TEN, Card::SUIT_SPADES),
                Card(Card::RANK_NINE, Card::SUIT_CLUBS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_ACE, Card::SUIT_HEARTS),
        },
        //num of trump card = 2

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_HEARTS),
                Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_CLUBS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_ACE, Card::SUIT_HEARTS),
        },
        //num of trump card = 3

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_HEARTS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_CLUBS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_ACE, Card::SUIT_HEARTS),
        },
        //num of trump card = 4

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_HEARTS),
                Card(Card::RANK_KING, Card::SUIT_CLUBS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_CLUBS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_ACE, Card::SUIT_HEARTS),
        },
        //num of trump card = 5

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_CLUBS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_CLUBS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_ACE, Card::SUIT_CLUBS),
        },

        // trump = SUIT_HEARTS

         //num of trump card = 0

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS),
                Card(Card::RANK_NINE, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_HEARTS,
            Card(Card::RANK_ACE, Card::SUIT_CLUBS),
        },


        //num of trump card = 1

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_HEARTS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_TEN, Card::SUIT_SPADES),
                Card(Card::RANK_NINE, Card::SUIT_CLUBS),
            },
            Card::SUIT_HEARTS,
            Card(Card::RANK_KING, Card::SUIT_SPADES),
        },
        //num of trump card = 2

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_HEARTS),
                Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_TEN, Card::SUIT_HEARTS),
                Card(Card::RANK_NINE, Card::SUIT_CLUBS),
            },
            Card::SUIT_HEARTS,
            Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
        },
        //num of trump card = 3

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_HEARTS),
                Card(Card::RANK_NINE, Card::SUIT_HEARTS),
            },
            Card::SUIT_HEARTS,
            Card(Card::RANK_ACE, Card::SUIT_CLUBS),
        },
        //num of trump card = 4

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_HEARTS),
                Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_HEARTS),
                Card(Card::RANK_NINE, Card::SUIT_HEARTS),
            },
            Card::SUIT_HEARTS,
            Card(Card::RANK_ACE, Card::SUIT_CLUBS),
        },
        //num of trump card = 5

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_HEARTS),
                Card(Card::RANK_KING, Card::SUIT_HEARTS),
                Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_HEARTS),
                Card(Card::RANK_NINE, Card::SUIT_HEARTS),
            },
            Card::SUIT_HEARTS,
           Card(Card::RANK_ACE, Card::SUIT_HEARTS),
        },

        // trump = SUIT_SPADES
        //num of trump card = 0

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_HEARTS),
                Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS),
                Card(Card::RANK_NINE, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_SPADES,
            Card(Card::RANK_ACE, Card::SUIT_HEARTS),
        },


        //num of trump card = 1

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_DIAMONDS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
                Card(Card::RANK_NINE, Card::SUIT_CLUBS),
            },
            Card::SUIT_SPADES,
            Card(Card::RANK_ACE, Card::SUIT_DIAMONDS),
        },
        //num of trump card = 2

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_HEARTS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_CLUBS),
            },
            Card::SUIT_SPADES,
            Card(Card::RANK_ACE, Card::SUIT_HEARTS),
        },
        //num of trump card = 3

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_HEARTS),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_TEN, Card::SUIT_SPADES),
                Card(Card::RANK_NINE, Card::SUIT_SPADES),
            },
            Card::SUIT_SPADES,
            Card(Card::RANK_ACE, Card::SUIT_CLUBS),
        },
        //num of trump card = 4

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_HEARTS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_TEN, Card::SUIT_SPADES),
                Card(Card::RANK_NINE, Card::SUIT_SPADES),
            },
            Card::SUIT_SPADES,
            Card(Card::RANK_ACE, Card::SUIT_HEARTS),
        },
        //num of trump card = 5

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_SPADES),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_TEN, Card::SUIT_SPADES),
                Card(Card::RANK_NINE, Card::SUIT_SPADES),
            },
            Card::SUIT_SPADES,
            Card(Card::RANK_ACE, Card::SUIT_SPADES),
        },


        // trump = SUIT_DIAMONDS
        //num of trump card = 0

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_CLUBS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
                Card(Card::RANK_NINE, Card::SUIT_SPADES),
            },
            Card::SUIT_DIAMONDS,
            Card(Card::RANK_ACE, Card::SUIT_CLUBS),
        },


        //num of trump card = 1

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_DIAMONDS),
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_TEN, Card::SUIT_HEARTS),
                Card(Card::RANK_NINE, Card::SUIT_CLUBS),
            },
            Card::SUIT_DIAMONDS,
            Card(Card::RANK_KING, Card::SUIT_SPADES),
        },
        //num of trump card = 2

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_HEARTS),
                Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS),
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_CLUBS),
            },
            Card::SUIT_DIAMONDS,
            Card(Card::RANK_ACE, Card::SUIT_HEARTS),
        },
        //num of trump card = 3

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_HEARTS),
                Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
                Card(Card::RANK_NINE, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_DIAMONDS,
            Card(Card::RANK_ACE, Card::SUIT_CLUBS),
        },
        //num of trump card = 4

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_SPADES),
                Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
                Card(Card::RANK_NINE, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_DIAMONDS,
            Card(Card::RANK_ACE, Card::SUIT_SPADES),
        },
        //num of trump card = 5

        {
            {
                Card(Card::RANK_ACE, Card::SUIT_DIAMONDS),
                Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
                Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
                Card(Card::RANK_NINE, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_DIAMONDS,
            Card(Card::RANK_ACE, Card::SUIT_DIAMONDS),
        },


    };

    for (auto t : tests) {
        Player* someone = Player_factory("someone", "Simple");
        for (auto card : t.add_to_hand) {
            someone->add_card(card);
        }

        Card output = someone->lead_card(t.trump);
        ASSERT_EQUAL(t.expected, output);
        
        delete someone;
    }
}

TEST(test_simple_player_play_card) {
    struct test {
        vector<Card> add_to_hand;
        std::string trump;
        Card led_card;
        Card expected;
    };

    vector<test> tests {
        //4
        {
            {
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_KING, Card::SUIT_CLUBS),
            Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
        }, 
        {
            {
                Card(Card::RANK_JACK, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_HEARTS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_KING, Card::SUIT_CLUBS),
            Card(Card::RANK_JACK, Card::SUIT_SPADES),
        }, 
        {
            {
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_CLUBS),
                Card(Card::RANK_TEN, Card::SUIT_HEARTS),
            },
            Card::SUIT_SPADES,
            Card(Card::RANK_KING, Card::SUIT_SPADES),
            Card(Card::RANK_JACK, Card::SUIT_CLUBS),
        },
        {
            {
                Card(Card::RANK_KING, Card::SUIT_SPADES),
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_HEARTS,
            Card(Card::RANK_KING, Card::SUIT_CLUBS),
            Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
        },
        {
            {
                Card(Card::RANK_KING, Card::SUIT_CLUBS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_DIAMONDS,
            Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
            Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
        },
        {
            {
                Card(Card::RANK_JACK, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_DIAMONDS,
            Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
            Card(Card::RANK_JACK, Card::SUIT_SPADES),
        },
        {
            {
                Card(Card::RANK_NINE, Card::SUIT_SPADES),
                Card(Card::RANK_NINE, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_HEARTS),
                Card(Card::RANK_NINE, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_DIAMONDS,
            Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
            Card(Card::RANK_NINE, Card::SUIT_SPADES),
        },
        //3
        {
            {
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_KING, Card::SUIT_CLUBS),
            Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
        },
        {
            {
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_KING, Card::SUIT_SPADES),
            Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
        },
        {
            {
                Card(Card::RANK_QUEEN, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
            },
            Card::SUIT_HEARTS,
            Card(Card::RANK_KING, Card::SUIT_DIAMONDS),
            Card(Card::RANK_JACK, Card::SUIT_CLUBS),
        },
        //2
        {
            {
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_KING, Card::SUIT_CLUBS),
            Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
        },
        {
            {
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_DIAMONDS,
            Card(Card::RANK_KING, Card::SUIT_CLUBS),
            Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
        },
        {
            {
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_KING, Card::SUIT_CLUBS),
            Card(Card::RANK_JACK, Card::SUIT_HEARTS),
        },
        //1
        {
            {
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_KING, Card::SUIT_CLUBS),
            Card(Card::RANK_JACK, Card::SUIT_HEARTS),
        },
        {
            {
                Card(Card::RANK_KING, Card::SUIT_CLUBS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_KING, Card::SUIT_HEARTS),
            Card(Card::RANK_KING, Card::SUIT_CLUBS),
        },
        // should we implement the case with 0 card?
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_CLUBS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_SPADES),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_NINE, Card::SUIT_CLUBS),
            Card(Card::RANK_ACE, Card::SUIT_CLUBS),
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_CLUBS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_SPADES),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_TEN, Card::SUIT_SPADES),
            Card(Card::RANK_NINE, Card::SUIT_SPADES),
        },
        {
            {
                Card(Card::RANK_ACE, Card::SUIT_CLUBS),
                Card(Card::RANK_KING, Card::SUIT_CLUBS),
                Card(Card::RANK_QUEEN, Card::SUIT_CLUBS),
                Card(Card::RANK_JACK, Card::SUIT_CLUBS),
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
            },
            Card::SUIT_CLUBS,
            Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
            Card(Card::RANK_TEN, Card::SUIT_CLUBS),
        },
        {
            {
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_DIAMONDS,
            Card(Card::RANK_TEN, Card::SUIT_SPADES),
            Card(Card::RANK_JACK, Card::SUIT_SPADES),
        },
        {
            {
                Card(Card::RANK_TEN, Card::SUIT_CLUBS),
                Card(Card::RANK_NINE, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_SPADES),
                Card(Card::RANK_JACK, Card::SUIT_HEARTS),
                Card(Card::RANK_TEN, Card::SUIT_DIAMONDS),
            },
            Card::SUIT_DIAMONDS,
            Card(Card::RANK_JACK, Card::SUIT_DIAMONDS),
            Card(Card::RANK_JACK, Card::SUIT_HEARTS),
        },
    };

    for (auto t : tests) {
        Player* someone = Player_factory("someone", "Simple");
        for (auto card : t.add_to_hand) {
            someone->add_card(card);
        }

        Card output = someone->play_card(t.led_card, t.trump);
        ASSERT_EQUAL(t.expected, output);
        
        delete someone;
    }
}

TEST(test_player_factory) {
    struct test {
        std::string name;
        std::string strategy;
    };

    vector<test> tests {
        {"Alice", "Simple"},
        {"Bob", "Human"},
        {"Charlie", "Simple"},
        {"Diana", "Simple"},
        {"Eric", "Human"},
        {"12345", "Human"},
        {"X AE A-12", "Human"}
    };

    for (auto t : tests) {
        Player* someone = Player_factory(t.name, t.strategy);
        ASSERT_EQUAL(t.name, someone->get_name());
        // can't test for strategy

        delete someone;
    }
}

TEST(test_player_overload_stream) {
    struct test {
        std::string name;
        std::string strategy;
    };

    vector<test> tests {
        {"Alice", "Simple"},
        {"Bob", "Human"},
        {"Charlie", "Simple"},
        {"Diana", "Simple"},
        {"Eric", "Human"},
        {"12345", "Human"},
        {"X AE A-12", "Human"}
    };

    for (auto t : tests) {
        Player* someone = Player_factory(t.name, t.strategy);
        std::ostringstream oss;
        oss << *someone;
        ASSERT_EQUAL(oss.str(), someone->get_name());

        delete someone;
    }
}

TEST_MAIN()
