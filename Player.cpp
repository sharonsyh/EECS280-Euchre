// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>
#include "Player.h"

class SimplePlayer : public Player {
public:
    SimplePlayer(std::string in_name) {
        name = in_name;
    }

    //EFFECTS returns player's name
    const std::string & get_name() const {
        return name;
    }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &c) {
        assert(hand.size() < MAX_HAND_SIZE);
        hand.push_back(c);
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
    int round, std::string &order_up_suit) const {
        assert(round == 1 || round == 2);
        assert(hand.size() == MAX_HAND_SIZE);

        if (round == 1) {

            int total = 0;

            for(int i = 0; i < hand.size(); i++) {
                // if(upcard.get_suit() == hand[i].get_suit(upcard.get_suit())) {
                //     if (hand[i].get_rank() != Card::RANK_NINE 
                //     && hand[i].get_rank() != Card::RANK_TEN) {
                //         ++total;
                //     }
                // }
                if(upcard.get_suit() == hand[i].get_suit(upcard.get_suit())
                && hand[i].get_rank() != Card::RANK_NINE
                && hand[i].get_rank() != Card::RANK_TEN) {
                    ++total;
                }
                if(total >= 2) {
                    order_up_suit = upcard.get_suit();
                    return true;
                }
            }
            return false;
        } else if (round == 2) {
            std::string nextSuit = Suit_next(upcard.get_suit());
            for (int i = 0; i < hand.size(); i++) {
                // if (hand[i].get_suit(nextSuit) == nextSuit) {
                //     if (hand[i].get_rank() != Card::RANK_NINE 
                //     && hand[i].get_rank() != Card::RANK_TEN) {
                //         order_up_suit = nextSuit;
                //         return true;
                //     }
                // }
                if (hand[i].get_suit(nextSuit) == nextSuit
                && hand[i].get_rank() != Card::RANK_NINE
                && hand[i].get_rank() != Card::RANK_TEN) {
                    order_up_suit = nextSuit;
                    return true;
                }
            }

            // screw the dealer
            if (is_dealer) {
                order_up_suit = nextSuit;
                return true;
            }
            return false;
        } else {
            assert(false);
            return false;
        }
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) {

        assert(hand.size() >= 1 && hand.size() <= MAX_HAND_SIZE);
        
        hand.push_back(upcard);
        Card lowest = hand.at(0);
        int toErase = 0;
        for (size_t i = 0; i < hand.size(); ++i) {
            if (Card_less(hand.at(i), lowest, upcard.get_suit(upcard.get_suit()))) {
                lowest = hand.at(i);
                toErase = i;
            }
        }

        // we should replace the card in pack
        hand.erase(hand.begin()+toErase);
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(const std::string &trump) {

        assert(hand.size() >= 1 && hand.size() <= MAX_HAND_SIZE);

        assert(trump == Card::SUIT_SPADES || trump == Card::SUIT_CLUBS 
        || trump == Card::SUIT_HEARTS || trump == Card::SUIT_DIAMONDS);

        std::sort(hand.begin(), hand.end());

        std::vector<std::pair<int, Card>> nonTrumps;

        for (size_t i = 0; i < hand.size(); ++i) {
            if (hand.at(i).get_suit(trump) != trump) {
                nonTrumps.push_back({i, hand.at(i)});
            }
        }

        if (nonTrumps.size() != 0) {
            Card highest = nonTrumps.at(0).second;
            int toErase = nonTrumps.at(0).first;
            for (auto i : nonTrumps) {
                if (Card_less(highest, i.second, trump)) {
                    highest = i.second;
                    toErase = i.first;
                }
            }
            hand.erase(hand.begin() + toErase);
            return highest;
        } else {
            Card highest = hand.at(0);
            int toErase = 0;
            for (size_t i = 0; i < hand.size(); ++i) {
                if (Card_less(highest, hand.at(i), trump)) {
                    highest = hand.at(i);
                    toErase = i;
                }
            }
            hand.erase(hand.begin() + toErase);
            return highest;
        }
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump) {

        assert(hand.size() >= 1 && hand.size() <= MAX_HAND_SIZE);
        assert(trump == Card::SUIT_SPADES || trump == Card::SUIT_CLUBS 
        || trump == Card::SUIT_HEARTS || trump == Card::SUIT_DIAMONDS);

        std::sort(hand.begin(), hand.end());

        // split cards into ones that follow and ones that don't
        bool canFollowSuit = false;
        std::vector<std::pair<int, Card>> cardsThatFollow;
        for (size_t i = 0; i < hand.size(); ++i) {
            if (hand.at(i).get_suit(trump) == led_card.get_suit(trump)) {
                cardsThatFollow.push_back({i, hand.at(i)});
                canFollowSuit = true;
            }
        }

        // if the player can follow suit:
        if (canFollowSuit) {
            Card highest = cardsThatFollow.at(0).second;
            int toErase = cardsThatFollow.at(0).first;
            for (auto i : cardsThatFollow) {
                if (Card_less(highest, i.second, led_card, trump)) {
                    highest = i.second;
                    toErase = i.first;
                }
            }
            hand.erase(hand.begin() + toErase);
            return highest;
        } else {
            // if the player can't follow suit
            Card lowest = hand.at(0);
            int toErase = 0;
            for (size_t i = 0; i < hand.size(); ++i) {
                if (Card_less(hand.at(i), lowest, led_card, trump)) {
                    lowest = hand.at(i);
                    toErase = i;
                }
            }
            hand.erase(hand.begin() + toErase);
            return lowest;
        }
    }

    ~SimplePlayer() {}

private:
    std::string name;
    const std::string strategy = "Simple";
    std::vector<Card> hand;
};

// The Human Player reads input from the human user. 
// You may assume all user input is correctly formatted and has correct values. 
// You may also assume the user will follow the rules of the game and not try to cheat.
// See Example With Human Players for exact output for a game with a human player.

class HumanPlayer : public Player {
public:
    HumanPlayer(std::string in_name) {
        name = in_name;
    }

    //EFFECTS returns player's name
    const std::string & get_name() const {
        return name;
    }


    void add_card(const Card &c) {
        assert(hand.size() < MAX_HAND_SIZE);

        hand.push_back(c);
        std::sort(hand.begin(), hand.end());
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                            int round, std::string &order_up_suit) const {
        assert(round == 1 || round == 2);
        assert(hand.size() == MAX_HAND_SIZE);
        std::string user_input;

        print_hand();
        std::cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
        std::cin >> user_input;

        if (user_input == "pass") {
            // return false;
            // std::string nextSuit = Suit_next(upcard.get_suit());
            if (round == 2 && is_dealer) {
                std::string user_input_for_dealer;
                // std::cout << "screw the dealer" << std::endl;
                std::cin >> user_input_for_dealer;
                
                order_up_suit = user_input_for_dealer;
                return true;
            } else {
                return false;
            }
        } else if (user_input == "Spades" || user_input == "Hearts" 
        || user_input == "Clubs" || user_input == "Diamonds") {
            order_up_suit = user_input;
            return true;
        } else {
            return false;
        }
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard) {

        assert(hand.size() >= 1 && hand.size() <= MAX_HAND_SIZE);

        print_hand();
        std::cout << "Discard upcard: [-1]" << std::endl;

        hand.push_back(upcard);
        
        int discard;

        std::cout << "Human player " << name 
        << ", please select a card to discard:" << std::endl;
        std::cin >> discard ;

        if(discard == -1){
            hand.pop_back();
        }
        else{
            hand.erase(hand.begin()+ discard);
        }

    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(const std::string &trump) {

        assert(hand.size() >= 1 && hand.size() <= MAX_HAND_SIZE);
        assert(trump == Card::SUIT_SPADES || trump == Card::SUIT_CLUBS 
        || trump == Card::SUIT_HEARTS || trump == Card::SUIT_DIAMONDS);

        std::sort(hand.begin(), hand.end());
        print_hand();
        int selected_card;
        std::cout << "Human player " << name << ", please select a card:\n";
        std::cin >> selected_card;

        for(size_t i = 0 ; i < hand.size() ; i++){
            if (i == selected_card) {
                Card selected = hand.at(i);
                hand.erase(hand.begin()+i);
                return selected;
            }
        }
        
        Card c = Card();

        assert(false);
        return c;
    }

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump) {
        return lead_card(trump);
        // assert(hand.size() >= 1);
        // assert(trump == Card::SUIT_SPADES || trump == Card::SUIT_CLUBS 
        // || trump == Card::SUIT_HEARTS || trump == Card::SUIT_DIAMONDS);

        // std::sort(hand.begin(), hand.end());
        // print_hand();
        // int selected_card;
        // std::cout << "Human player " << name 
        // << ", please select a card:\n";
        // std::cin >> selected_card ;

        // for(size_t i = 0 ; i < hand.size() ; i++){
        //     if (i == selected_card) {
        //         Card selected = hand.at(i);
        //         hand.erase(hand.begin()+i);
        //         return selected;
        //     }
        // }
        
        // Card c = Card();

        // assert(false);
        // return c;
    }

    ~HumanPlayer() {}

private:
    std::string name;
    const std::string strategy = "Human";
    std::vector<Card> hand;

    void print_hand() const {
        for (size_t i=0; i < hand.size(); ++i)
            std::cout << "Human player " << name << "'s hand: "
            << "[" << i << "] " << hand[i] << "\n";
    }
};


//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) {
    // We need to check the value of strategy and return 
    // the corresponding player type.

  if (strategy == "Simple") {

    // The "new" keyword dynamically allocates an object.
    return new SimplePlayer(name);

  } else if (strategy == "Human") {

    return new HumanPlayer(name);

  }
    // Repeat for each other type of Player
    //   ...
    // Invalid strategy if we get here

  assert(false);
  return nullptr;

}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p){
    os << p.get_name();
    return os;
}