#include "player.hpp"
#include <iostream>
#include <string>

namespace ariel {
    // Player object 
    Player::Player(std::string name){
        this->name = name;
        this->isPlaying = false;
        this->cardsTaken = 0;
    }

    // add card to the stack
    void Player::addCard(Card card) {
        cards.push_back(card);
    }

    // draw a card from the stack
    Card Player::drawCard() {
        Card card = cards.front();
        cards.erase(cards.begin());
        return card;
    }

    // get the current amount of cards in the stack
    int Player::stacksize() const {
        return cards.size();
    }
    
    // get amount of total amount of cards taken
    int Player::cardesTaken() const {
        return cardsTaken;
    }

    // take acertain amount of cards
    void Player::takeCards(int card_amount){
        this->cardsTaken += card_amount;
    }

    // set the playing state (true/false)
    void Player::setIsPlaying(bool isPlaying){
        this->isPlaying = isPlaying;
    }

    // get the playing state (true/false)
    bool Player::getIsPlaying(){
        return this->isPlaying;
    }

    // get the player's name
    std::string Player::getName() const{
        return this->name;
    }

    // print current cards
    void Player::printCards() const {
        std::cout << name << "'s cards:" << std::endl;
        for (Card card : cards) {
            std::cout << "  " << card.toString() << std::endl;
        }
    }
}
