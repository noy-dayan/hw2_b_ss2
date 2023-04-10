#include "card.hpp"
#include <string>

namespace ariel {
    // Card object
    Card::Card(Suit suit, int value):
        suit(suit), value(value) {}

    // get card suit
    Suit Card::getSuit() const {
        return suit;
    }

    // get card value
    int Card::getValue() const {
        return value;
    }

    // card (suit and value) to string
    std::string Card::toString() const {
        std::string suitString;
        switch (suit) {
            case Suit::CLUBS:
                suitString = "Clubs";
                break;
            case Suit::DIAMONDS:
                suitString = "Diamonds";
                break;
            case Suit::HEARTS:
                suitString = "Hearts";
                break;
            case Suit::SPADES:
                suitString = "Spades";
                break;
        }
        std::string valueString;
        switch (value) {
            case 1:
                valueString = "Ace";
                break;
            case 11:
                valueString = "Jack";
                break;
            case 12:
                valueString = "Queen";
                break;
            case 13:
                valueString = "King";
                break;
            default:
                valueString = std::to_string(value);
                break;
        }
        return valueString + " of " + suitString;
    }
}
