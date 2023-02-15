#include "TileBag.h"
#include "TileCodes.h"
#include <stdlib.h>
#include <time.h>

// Randomised repository of all tiles that are in the game
// 6 should be dealt out to players at the start of the game

TileBag::TileBag()
{
}

TileBag::TileBag(LinkedList *newBag)
{
    this->newBag = newBag;

    newTileBag();     // Creating New Bag of Tiles
    shuffleTileBag(); // Shuffling the New Bag
}

TileBag::~TileBag()
{
    delete this->newBag;
}

void TileBag::newTileBag()
{

    // Populate the list of tiles by adding tiles at the beggining and end of list
    // Tiles need to be added twice as there has to be 2 of each for a total
    // of 72 tiles
    for (int i = 1; i <= 6; i++)
    {
        for (char c : colours)
        {
            Tile *tile1 = new Tile(c, i);
            Tile *tile2 = new Tile(c, i);
            this->newBag->addFront(tile1);
            this->newBag->addEnd(tile2);
        }
    }
}

void TileBag::shuffleTileBag()
{
    int length = newBag->getLength();
    LinkedList *shuffledBag = new LinkedList();
    // Based on Fisher–Yates shuffle algorithm
    srand(time(NULL));
    for (int i = length - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Node *newJ = newBag->accessElement(j);
        shuffledBag->addEnd(newJ->getTile());
        // delete newJ;
    }
    this->newBag = shuffledBag;

    // delete shuffledBag;
}

// // Returns a Tile from the tile bag
Tile *TileBag::getTile()
{
    Tile *playTile = (newBag->accessElement(0))->getTile();
    return playTile;
}

void TileBag::addTileEnd(Tile *tile)
{
    newBag->addEnd(tile);
}

LinkedList *TileBag::getBagList()
{
    return newBag;
}

TileBag TileBag::getTileBag()
{
    return this->newBag;
}

void TileBag::printTileBag()
{
    this->newBag->printAll();
}
