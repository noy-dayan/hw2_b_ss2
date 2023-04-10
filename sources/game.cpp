#include "game.hpp"
#include <iostream>
#include <algorithm>
#include <random>

namespace ariel {
    // Game object
    Game::Game(Player& p1__, Player& p2__): 
        p1_(p1__), p2_(p2__), draws(0), p1_wins(0), p2_wins(0), totalTurns(0), war_flag(true){
            if(p1_.getIsPlaying() == true || p2_.getIsPlaying() == true)
                throw std::invalid_argument("Player(s) already in game and playing");

            p1_.setIsPlaying(true);
            p2_.setIsPlaying(true);

            std::vector<Card> deck;

            for (int i = 1; i <= 13; i++)
                deck.push_back(Card(Suit::CLUBS,i));

            for (int i = 1; i <= 13; i++)
                deck.push_back(Card(Suit::DIAMONDS,i));    

            for (int i = 1; i <= 13; i++)
                deck.push_back(Card(Suit::HEARTS,i));

            for (int i = 1; i <= 13; i++)
                deck.push_back(Card(Suit::SPADES,i));
                
            shuffleDeck(deck);
            dealDeck(deck);
        }
    
    // shuffle deck cards
    void Game::shuffleDeck(std::vector<Card>& deck) const{
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(deck.begin(), deck.end(), g);
    }

    // deal each player his set of cards
    void Game::dealDeck(std::vector<Card>& deck) {
        int dealTo = 0;
        for (auto card : deck) {
            if (dealTo % 2 == 0)
                p1_.addCard(card);
            else
                p2_.addCard(card);
            dealTo++;

        }

    }

    // award pot to winner and clear pot
    void Game::awardCardsTo(Player& winner) {
        winner.takeCards(pot.size());
        pot.clear();
    }

    // award amount of cards to winner
    void Game::awardCardsTo(Player& winner, int numberOfCards) {
        winner.takeCards(numberOfCards);
    }

    // check if game is over
    bool Game::isGameOver() const {
        if (p1_.stacksize() == 0 || p2_.stacksize() == 0){
            this->p1_.setIsPlaying(false);
            this->p2_.setIsPlaying(false);
            return true;
        }
        else
            return false;
    }

    // play 1 turn
    void Game::playTurn() {
        if (p1_.getName() == p2_.getName())
            throw std::invalid_argument("Duplicate player detected");
        

        if (isGameOver()){
            throw std::out_of_range("Duplicate player detected");
            return;

        }
        

        Card c1_ = p1_.drawCard();
        Card c2_ = p2_.drawCard();
        pot.push_back(c1_);
        pot.push_back(c2_);


        // check if draw
        if (c1_.getValue() == c2_.getValue()) {
            logDraw(c1_, c2_);
            war_flag = true;
            totalTurns++;
            playWar();
        }

        // check turn winner
        else if (c1_.getValue() > c2_.getValue()) {
            // check if p2 card is Ace
            if (c2_.getValue() == 1){
                if(c1_.getValue() == 2){
                    logTurn(c1_, c2_, p1_);
                    awardCardsTo(p1_);
                    p1_wins++;
                }
                else{
                    logTurn(c1_, c2_, p2_);
                    awardCardsTo(p2_);
                    p2_wins++;
                }
            }
            else{
                logTurn(c1_, c2_, p1_);
                awardCardsTo(p1_);
                p1_wins++;
            }
            totalTurns++;


        } 

        else {
            // check if p1 card is Ace
            if (c1_.getValue() == 1){
                if(c2_.getValue() == 2){
                    logTurn(c1_, c2_, p2_);
                    awardCardsTo(p2_);
                    p2_wins++;
                }
                else{
                    logTurn(c1_, c2_, p1_);
                    awardCardsTo(p1_);
                    p1_wins++;
                }
            }
            else{
                logTurn(c1_, c2_, p2_);
                awardCardsTo(p2_);
                p2_wins++;
            }
            totalTurns++;

        }
    }

        // play a war (if there is a draw)
    void Game::playWar() {

        if (war_flag == false)
            return;

        if (isGameOver() || p1_.stacksize() < 2 || p2_.stacksize() < 2){
            awardCardsTo(p1_, pot.size()/2);
            awardCardsTo(p2_, pot.size()/2);
            pot.clear();

            war_flag = false;
            return;
        }

        std::vector<Card> warCards;

        warCards.push_back(p1_.drawCard());
        warCards.push_back(p2_.drawCard());

        pot.insert(pot.end(), warCards.begin(), warCards.end());
        Card c1_ = p1_.drawCard();
        Card c2_ = p2_.drawCard();

        pot.push_back(c1_);
        pot.push_back(c2_);

        if (c1_.getValue() == c2_.getValue()) {
            logDraw(c1_, c2_);
            playWar();
        }
        
        else if (c1_.getValue() > c2_.getValue()) {
            // check if p2 card is Ace
            if (c2_.getValue() == 1){
                if(c1_.getValue() == 2){
                    logTurn(c1_, c2_, p1_);
                    awardCardsTo(p1_);
                    p1_wins++;
                }
                else{
                    logTurn(c1_, c2_, p2_);
                    awardCardsTo(p2_);
                    p2_wins++;
                }
            }
            else{
                logTurn(c1_, c2_, p1_);
                awardCardsTo(p1_);
                p1_wins++;
            }
            pot.clear();

        } 

        else {
            // check if p1 card is Ace
            if (c1_.getValue() == 1){
                if(c2_.getValue() == 2){
                    logTurn(c1_, c2_, p2_);
                    awardCardsTo(p2_);
                    p2_wins++;
                }
                else{
                    logTurn(c1_, c2_, p1_);
                    awardCardsTo(p1_);
                    p1_wins++;
                }
            }
            else{
                logTurn(c1_, c2_, p2_);
                awardCardsTo(p2_);
                p2_wins++;
            }
            pot.clear();

        }

    }

    // play all turns until game is over
    void Game::playAll() {
        while (!isGameOver()) {
            playTurn();
        }
    }

    // log turn
    void Game::logTurn(const Card& c1_, const Card& c2_, const Player& winner) {
        std::string curr_log = p1_.getName()+ " played " + c1_.toString()+ " " +p2_.getName() + " played " + c2_.toString() + ". " +  winner.getName() + " wins.";
        if (log.size() > 0)
            if (log.back().length()>=6){
                if (log.back().substr(log.back().length()-6, 6).compare("Draw. ") == 0)
                    log.back() += curr_log; 
                else
                    log.push_back(curr_log);
            }
            else
                log.push_back(curr_log);

        else            
            log.push_back(curr_log);

        
    }

    // log draw
    void Game::logDraw(const Card& c1_, const Card& c2_) {
        std::string curr_log = p1_.getName()+ " played " + c1_.toString()+ " " +p2_.getName() + " played " + c2_.toString() + ". Draw. ";
        draws++;
        if (log.size() > 0)
            if (log.back().length()>=6){
                if (log.back().substr(log.back().length()-6, 6).compare("Draw. ") == 0)
                    log.back() += curr_log; 
                else
                    log.push_back(curr_log);
            }
            else
                log.push_back(curr_log);

        else            
            log.push_back(curr_log);
    }

    // print the last turn's log
    void Game::printLastTurn() const {
        std::cout << log.back() << std::endl;
    }

    // print the winner up to this point
    void Game::printWiner() const {
        if (p1_.cardesTaken() > p2_.cardesTaken())
            std::cout << "The winner is " << p1_.getName() << std::endl;

        else if (p2_.cardesTaken() > p1_.cardesTaken())
            std::cout << "The winner is " << p2_.getName() << std::endl;

        else
            std::cout << "It's a tie!" << std::endl;  
    }

    // print the game's log up to this point
    void Game::printLog() const {
        std::cout << "============================ Game Logs =============================" << std::endl;
        for (auto curr_log : log)
            std::cout << curr_log << std::endl;
        std::cout << "====================================================================" << std::endl;

    }

    // print game stats up to this point
    void Game::printStats() const {
        
        double p1_WinRate = (double) p1_wins / (double)totalTurns;
        double p2_WinRate = (double) p2_wins / (double)totalTurns;
        int p1_CardsWon = p1_.cardesTaken();
        int p2_CardsWon = p2_.cardesTaken();
        double drawRate = (double) draws / (double) totalTurns;

        std::cout << "============================ Game Stats ============================" << std::endl;
        std::cout << "Player " << p1_.getName() << " won " << p1_CardsWon << " cards, with a win rate of " << p1_WinRate * 100 << "%" << std::endl;
        std::cout << "Player " << p2_.getName() << " won " << p2_CardsWon << " cards, with a win rate of " << p2_WinRate * 100 << "%" << std::endl;
        std::cout << "\nThere were total of " << totalTurns << " turns" << std::endl;
        std::cout << "There were " << draws << " draws (" << drawRate * 100.0 << "% of all turns)" << std::endl;
        std::cout << "====================================================================" << std::endl;

        
    }
}
