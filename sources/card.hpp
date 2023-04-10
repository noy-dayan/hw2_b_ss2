#ifndef CARD_HPP
#define CARD_HPP

#include <string>

namespace ariel {
    // suit enum
    enum class Suit {CLUBS, DIAMONDS, HEARTS, SPADES};

    // Card object header
    class Card {
    private:
        Suit suit;    // card suit
        int value;    // card value
    public:
        Card(Suit suit, int value);

        Suit getSuit() const;    // get card suit
        int getValue() const;    // get card value

        std::string toString() const;    // card (suit and value) to string
    };
}

#endif
