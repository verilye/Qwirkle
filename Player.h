#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H
#include "TileCodes.h"
#include "LinkedList.h"
#include "TileBag.h"
#include "TileCodes.h"

#include "Board.h"
#include <iostream>
#include <string>

// Player objects are what can be dealt tiles, place tiles
// save the game -> basically the proxy for the human players
// of the game and all actions that they can take
// If a human has to do something to set up or play qwirkle
// this class does it

class Player
{
public:
    Player(std::string name);
    Player(Player &other);
    ~Player();

    std::string getName();
    void setName(std::string name);
    int getScore();
    void setScore(int score);
    LinkedList *getCurrentHands();
    LinkedList *getPlacedHands();
    void setCurrentHand(std::string hand, Player *player);

    // Functions
    void dealTiles(LinkedList *tileBag);
    void placeTile(int y, int x, Tile *tile, LinkedList *TileBag, Board *board);
    void replaceTile(Tile *oldTile, LinkedList *tileBag);
    void calculateScore(Player *player,Player* other, Board *board, int y,int x);
    int checkQWIRKLE(Player *player, Player *other, Board *board);
    void setQWIRKLECounter(int count);
    int getQWIRKLECounter();

    int score;
    // char colours[6] = { RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    // int shapes[6] = { CIRCLE , STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER };

private:
    char colours[6] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    int shapes[6] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
    std::string name;

    int qwirkleCounter;
    LinkedList *placedHands;
    LinkedList *currentHands;
};
#endif
