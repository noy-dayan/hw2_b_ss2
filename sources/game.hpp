#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"

namespace ariel {
    class Game {
        // Game object header
        private:
            Player &p1_, &p2_;
            std::vector<Card> pot;
            std::vector<std::string> log;
            int draws, p1_wins, p2_wins, totalTurns;
            bool war_flag;

            // game status
            bool isGameOver() const;    // check if game is over

            // card management
            void shuffleDeck(std::vector<Card>& deck) const;    // shuffle deck cards
            void dealDeck(std::vector<Card>& deck);    // deal each player his set of cards
            void awardCardsTo(Player& winner);    // award pot to winner and clear pot
            void awardCardsTo(Player& winner, int numberOfCards);    // award amount of cards to winner

            // logs
            void logTurn(const Card& c1_, const Card& c2_, const Player& winner);    // log turn
            void logDraw(const Card& c1_, const Card& c2_);    // log draw

            // plays
            void playWar();    // play a war (if there is a draw)
            
        public:
            Game(Player& p1_, Player& p2_);

            // plays
            void playTurn();    // play 1 turn
            void playAll();    // play all turns until game is over

            // prints
            void printLastTurn() const;    // print the last turn's log
            void printWiner() const;    // print the winner up to this point
            void printLog() const;    // print the game's log up to this point
            void printStats() const;    // print game stats up to this point
    };
}

#endif