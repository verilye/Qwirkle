#ifndef ASSIGN2_TILEBAG
#define ASSIGN2_TILEBAG

#include "TileCodes.h"
#include "LinkedList.h"

// Randomised repository of all tiles that are in the game
// 6 should be dealt out to players at the start of the game

class TileBag
{
private:
    int length;
    LinkedList *newBag;
    char colours[6] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
public:
    TileBag();
    TileBag(LinkedList *newBag);
    ~TileBag();
    void newTileBag();
    void shuffleTileBag();
    Tile *getTile();
    void addTileEnd(Tile *tile);
    LinkedList *getBagList();
    TileBag getTileBag();
    void printTileBag();
};
#endif // TILEBAG