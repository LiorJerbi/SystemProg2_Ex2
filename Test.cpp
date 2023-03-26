#include "doctest.h"
#include <stdexcept>
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"
using namespace ariel;

Player p1("Lior"), p2("Yael");
Game g1(p1,p2);
TEST_CASE("Testing new game start and players first moves:"){
    CHECK(p1.stacksize() == 26);    
    CHECK(p2.stacksize() == 26);    //Check if deck splits equally.
    CHECK(p1.cardesTaken() == 0);    
    CHECK(p2.cardesTaken() == 0);   //Check that both start with 0 cards taken.
    
    CHECK_NOTHROW(g1.playTurn());   //Chek no exceptions throws while playing turn.
    CHECK_NOTHROW(g1.printLastTurn());  //Check no exeptions throws while printing the last turn.
    
    CHECK((p1.stacksize() < 26 && p2.stacksize() < 26));    //Check if players stack changes after turn played.
    CHECK((p1.cardesTaken() >= 2 || p2.cardesTaken() >= 2));    //Check if player won an round(war or not) and got the cards.

    CHECK_NOTHROW(for(int i=0;i<5;i++){     //Check if throw exceprion while playing some rounds.
        g1.playTurn();
    });             
    CHECK_NOTHROW(g1.printLog());       //try to print all the rounds played.
    CHECK(p1.stacksize() == p2.stacksize());    //Check if players stack size is equal after some rounds.
    CHECK((p1.cardesTaken() >= 2 || p2.cardesTaken() >= 2));    //Check if player won and changed his cards won size.
}

TEST_CASE("Testing finishing an game and Extreme cases:"){
    if(p1.stacksize() > 0 && p2.stacksize() > 0){
        CHECK_NOTHROW(g1.playAll());    //Try to play the entire game left.
    }
    else{
        Game g1(p1,p2);
        CHECK_NOTHROW(g1.playAll());    //Try to play the entire game left.
    }
    CHECK((p1.stacksize() == 0 && p2.stacksize() == 0));  //Check if both players finished their cards.
    CHECK_NOTHROW(g1.printStats()); //Try to print the whole game stats.
    CHECK_NOTHROW(g1.printLog()); //Try to print the whole rounds of the game.
    CHECK_NOTHROW(g1.printWiner()); //Try to print the game winner.
    CHECK((p1.cardesTaken()>p2.cardesTaken() || p2.cardesTaken()>p1.cardesTaken()));    //One of the cards stack won has to be bigger the the other.
}

TEST_CASE("Test bad implements cases:"){
    Player p3("test");
    Game g2(p3,p3);
    CHECK_THROWS(g2.playTurn());    //Can't start game with only 1 player.
    Player p4("test");
    Game g3(p3,p4);
    CHECK_THROWS(g3.playTurn());    //Can't start game wiht player's with same name.
    Player p5("test1");
    Game g4(p3,p5);
    CHECK_THROWS(g3.printLastTurn());  //Game didn't started yet, nothing to print!
    CHECK_THROWS(g3.printWiner());      //No winner yet!
    CHECK_THROWS(g3.printStats());      //empty stats.
    CHECK_THROWS(g3.printLog());        //no tounds played.
    g3.playAll();
    CHECK_THROWS(g3.playTurn());        //game ended.
    CHECK_THROWS(g3.playAll());         //same, game ended.
}