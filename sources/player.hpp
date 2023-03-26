#pragma once
#include <string>
namespace ariel{
}
class Player{

    public:
        Player(){};
        Player(const std::string &name){};
        int static stacksize(){return 0;};
        int static cardesTaken(){return 0;};
};
