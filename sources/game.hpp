#pragma once
#include "player.hpp"
namespace ariel{
}
class Game{

    public:
        Game(){};
        Game(const Player &pl1, const Player &pl2){};
        void playTurn(){};
        void printLastTurn(){};

        void playAll(){};
        void printWiner(){};
        void printLog(){};
        void printStats(){};

};
