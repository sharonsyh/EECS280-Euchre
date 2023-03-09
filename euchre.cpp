// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <iostream>
#include <fstream>
#include <vector>
#include "Card.h"
#include "Pack.h"
#include "Player.h"

class Game {
    public:
        Game(std::string file, std::string shuffle, int points, 
        std::vector<std::pair<std::string, std::string>> playerStratPairs);
        void play();
    
    private:
        // set by the constructor
        std::vector<Player*> gamePlayers;
        Pack gamePack;
        int gamePointsToWin;
        bool gameShuffle;

        // set by methods
        int game02Score = 0;
        int game13Score = 0;
        int gameDealerIndex = 0;

        // per-hand variables
        int gameOrderedUpIndex = 0;
        std::string gameTrumpSuit = "";
        int gameTricks02 = 0;
        int gameTricks13 = 0;

        void setupTable();
        void makeTrump();
        void trickTaking();
        void scoring();
};

Game::Game(std::string file, std::string shuffle, int points, 
std::vector<std::pair<std::string, std::string>> playerStratPairs) {
    // read pack.in
    std::ifstream input_file;
    input_file.open(file);
    if(!input_file) {
        std::cout << "Error opening " << file << std::endl;
    }

    // make pack, save it to gamePack, close stream
    Pack pack = Pack(input_file);
    pack = gamePack;
    input_file.close();

    // set the remaining member variables
    if (shuffle == "shuffle") {
        gameShuffle = true;
    } else {
        gameShuffle = false;
    }

    gamePointsToWin = points;

    for (auto playerStratPair : playerStratPairs) {
        Player* player = Player_factory(playerStratPair.first, playerStratPair.second);
        gamePlayers.push_back(player);
    }
}

void Game::play() {
    int handNumber = 0;
    while (game02Score < gamePointsToWin && game13Score < gamePointsToWin) {
        // prehand routine
        std::cout << "Hand " << handNumber << std::endl;
        std::cout << gamePlayers.at(gameDealerIndex)->get_name() << " deals" << std::endl;
        // upcard is announced in Game::makeTrump();

        // each hand consists of these four steps
        setupTable();
        makeTrump();
        trickTaking();
        scoring();

        // posthand routine
        std::cout << gamePlayers.at(0)->get_name() << " and "
        << gamePlayers.at(2)->get_name() << " have "
        << game02Score << " points" << std::endl;

        std::cout << gamePlayers.at(1)->get_name() << " and "
        << gamePlayers.at(3)->get_name() << " have "
        << game13Score << " points" << std::endl;

        // reset per-hand variables
        gameOrderedUpIndex = 0;
        gameTrumpSuit = "";
        gameTricks02 = 0;
        gameTricks13 = 0;
        
        // rotate dealer after each hand
        gameDealerIndex = (gameDealerIndex+1) % 4;

        ++handNumber;
        std::cout << std::endl;
    }

    // postgame routine
    if (game02Score > game13Score) {
        std::cout << gamePlayers.at(0)->get_name() << " and " 
        << gamePlayers.at(2)->get_name() << " win!" << std::endl;
    } else {
        std::cout << gamePlayers.at(1)->get_name() << " and " 
        << gamePlayers.at(3)->get_name() << " win!" << std::endl;
    }

    for (size_t i = 0; i < gamePlayers.size(); ++i) {
        delete gamePlayers.at(i);
    }
}

void Game::setupTable() {
    // reset everything
    gamePack.reset();

    // shuffle
    if (gameShuffle) {
        gamePack.shuffle();
    }

    // deal
    for (size_t i = 1; i < 5; ++i) {
        if (i%2 == 1) {
            for (size_t j = 0; j < 3; ++j) {
                Card dealtCard = gamePack.deal_one();
                gamePlayers.at((gameDealerIndex+i) % 4)->add_card(dealtCard);
            }
        } else {
            for (size_t j = 0; j < 2; ++j) {
                Card dealtCard = gamePack.deal_one();
                gamePlayers.at((gameDealerIndex+i) % 4)->add_card(dealtCard);
            }
        }
    }
    for (size_t i = 1; i < 5; ++i) {
        if (i%2 == 1) {
            for (size_t j = 0; j < 2; ++j) {
                Card dealtCard = gamePack.deal_one();
                gamePlayers.at((gameDealerIndex+i) % 4)->add_card(dealtCard);
            }
        } else {
            for (size_t j = 0; j < 3; ++j) {
                Card dealtCard = gamePack.deal_one();
                gamePlayers.at((gameDealerIndex+i) % 4)->add_card(dealtCard);
            }
        }
    }

    // at this point, each player has 5 cards in hand.
    // four cards remain in the pack.
    // the next card in the pack is the upcard.
}

void Game::makeTrump() {
    // round 1
    // announce upcard
    Card upcard = gamePack.deal_one();
    std::cout << upcard << " turned up" << std::endl;

    std::string orderedUpSuit;

    for (size_t i = 1; i < 5; ++i) {
        bool isDealer;
        if ((gameDealerIndex+i) % 4 == gameDealerIndex) {
            isDealer = true;
        } else {
            isDealer = false;
        }

        bool orderedUp = gamePlayers.at((gameDealerIndex+i) % 4)->make_trump(
            upcard, isDealer, 1, orderedUpSuit);
        if (orderedUp) {
            gameOrderedUpIndex = (gameDealerIndex+i) % 4;
            std::cout << gamePlayers.at((gameDealerIndex+i) % 4)->get_name() 
            << " orders up " << orderedUpSuit << std::endl;

            gamePlayers.at(gameDealerIndex)->add_and_discard(upcard);

            gameTrumpSuit = orderedUpSuit;
            std::cout << std::endl;
            return;
        } else {
            std::cout << gamePlayers.at((gameDealerIndex+i) % 4)->get_name() 
            << " passes" << std::endl;
        }
    }

    // round 2
    for (size_t i = 1; i < 5; ++i) {
        bool isDealer;
        if ((gameDealerIndex+i) % 4 == gameDealerIndex) {
            isDealer = true;
        } else {
            isDealer = false;
        }

        bool orderedUp = gamePlayers.at((gameDealerIndex+i) % 4)->make_trump(
            upcard, isDealer, 2, orderedUpSuit);
        if (orderedUp) {
            gameOrderedUpIndex = (gameDealerIndex+i) % 4;
            std::cout << gamePlayers.at((gameDealerIndex+i) % 4)->get_name() 
            << " orders up " << orderedUpSuit << std::endl;

            gameTrumpSuit = orderedUpSuit;
            std::cout << std::endl;
            return;
        } else {
            std::cout << gamePlayers.at((gameDealerIndex+i) % 4)->get_name() 
            << " passes" << std::endl;
        }
    }

    std::cout << std::endl;
    // at this point, a trump suit is selected.
    // we kept track of which player has ordered up.
}

void Game::trickTaking() {
    // keep track of who took the trick
    int tricks02 = 0;
    int tricks13 = 0;

    // the eldest hand leads first
    int leaderIndex = ((gameDealerIndex+1) % 4);
    
    // five tricks are played
    for (size_t i = 0; i < 5; ++i) {
        Card ledCard = gamePlayers.at(leaderIndex)->lead_card(gameTrumpSuit);
        std::cout << ledCard << " led by " 
        << gamePlayers.at(leaderIndex)->get_name() << std::endl;

        Card topCard = ledCard;
        Card mostValuableCard = ledCard;
        int mvp = leaderIndex;

        for (size_t j = 1; j < 4; ++j) {
            topCard = gamePlayers.at((leaderIndex+j) % 4)->play_card(
                ledCard, gameTrumpSuit);
            std::cout << topCard << " played by " 
            << gamePlayers.at((leaderIndex+j) % 4)->get_name() << std::endl;

            if (Card_less(mostValuableCard, topCard, ledCard, gameTrumpSuit)) {
                mostValuableCard = topCard;
                mvp = (leaderIndex+j) % 4;
            }
        }

        // posttrick routine
        if (mvp == 0) {
            std::cout << gamePlayers.at(0)->get_name() << " takes the trick" << std::endl;
            leaderIndex = 0;
            ++tricks02;
        } else if (mvp == 1) {
            std::cout << gamePlayers.at(1)->get_name() << " takes the trick" << std::endl;
            leaderIndex = 1;
            ++tricks13;
        } else if (mvp == 2) {
            std::cout << gamePlayers.at(2)->get_name() << " takes the trick" << std::endl;
            leaderIndex = 2;
            ++tricks02;
        } else {
            std::cout << gamePlayers.at(3)->get_name() << " takes the trick" << std::endl;
            leaderIndex = 3;
            ++tricks13;
        }

        std::cout << std::endl;
    }

    gameTricks02 = tricks02;
    gameTricks13 = tricks13;

    // at this point, five tricks have been played.
    // players' hands are empty.
    // we kept track of how many tricks each team took.
}

void Game::scoring() {
    // The team that takes the majority of tricks receives points for that hand.
    if (gameTricks02 > gameTricks13) {
        std::cout << gamePlayers.at(0)->get_name() << " and "
        << gamePlayers.at(2)->get_name() << " win the hand" << std::endl;

        int score02 = 0;
        // If the winning team had also ordered up, 
        // they get 1 point for taking 3 or 4 tricks, 
        // and 2 points for taking all 5.
        if (gameOrderedUpIndex == 0 || gameOrderedUpIndex == 2) {
            if (gameTricks02 == 3 || gameTricks02 == 4) {
                score02 += 1;
            } else {
                std::cout << "march!" << std::endl;
                score02 += 2;
            }
        } else {
            std::cout << "euchred!" << std::endl;
            score02 += 2;
        }

        game02Score += score02;
    } else {
        std::cout << gamePlayers.at(1)->get_name() << " and "
        << gamePlayers.at(3)->get_name() << " win the hand" << std::endl;

        int score13 = 0;
        // If the winning team had also ordered up, 
        // they get 1 point for taking 3 or 4 tricks, 
        // and 2 points for taking all 5.
        if (gameOrderedUpIndex == 1 || gameOrderedUpIndex == 3) {
            if (gameTricks13 == 3 || gameTricks13 == 4) {
                score13 += 1;
            } else {
                std::cout << "march!" << std::endl;
                score13 += 2;
            }
        } else {
            std::cout << "euchred!" << std::endl;
            score13 += 2;
        }

        game13Score += score13;
    }

    // at this point, game02Score and game13Score has been updated.
}

int main(int argc, char** argv) {
    // cmdline error handling
    if (argc != 12) {
        std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << std::endl;
        return 1;
    }

    int points = atoi(argv[3]);
    if (points < 1 || points > 100) {
        std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << std::endl;
        return 1;
    }

    std::string shuffle = argv[2];
    if (shuffle != "shuffle" && shuffle != "noshuffle") {
        std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << std::endl;
        return 1;
    }

    std::vector<int> strategyIndex = {5, 7, 9, 11};
    for (auto i : strategyIndex) {
        std::string strategy = argv[i];
        if (strategy != "Simple" && strategy != "Human") {
            std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << std::endl;
            return 1;
        }
    }

    std::vector<std::pair<std::string, std::string>> playerStratPairs = {
        {argv[4], argv[5]}, {argv[6], argv[7]}, {argv[8], argv[9]}, {argv[10], argv[11]},
    };

    for (size_t i = 0; i < 12; ++i) {
        std::cout << argv[i] << " ";
    }
    std::cout << std::endl;

    Game game = Game(argv[1], shuffle, points, playerStratPairs);
    game.play();
    
    return 0;
}