#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

#include "card.hpp"

namespace ariel {
    // Player object header
    class Player {
        private:
            std::string name;    // Player name
            int cardsTaken;     // amount of cards taken
            bool isPlaying;     // current playing state
            std::vector<Card> cards;    // card stack        


        public:
            Player(std::string name);
            int stacksize() const;    // get the current amount of cards in the stack
            int cardesTaken() const;    // get amount of total amount of cards taken
            bool getIsPlaying();    // get the playing state (true/false)
            std::string getName() const;    // get the player's name

            void setIsPlaying(bool isPlaying);  // set the playing state (true/false)

            void takeCards(int card_amount);    // take acertain amount of cards
            void addCard(Card card);     // add card to the stack
            Card drawCard();    // draw a card from the stack

            void printCards() const;    // print current cards

    };  
}

#endif
