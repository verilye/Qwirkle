
#include <iostream>
#include <vector>
#include "Tests.h"
#include "TileBag.h"
#include "LinkedList.h"
#include "Node.h"

void testPrintShuffledBag(LinkedList *newTestBag)
{
    std::cout << "Printing ordered tile bag" << std::endl;
    TileBag *bag = new TileBag(newTestBag);
    // bag->newBag(newTestBag);
    bag->printTileBag(); // <- This prints out the shuffled linked list
    // newTestBag->printAll();

    // std::cout << "Printing shuffled TileList" << std::endl;
    // LinkedList* newTestShuffleBag = new LinkedList();
    // newTestShuffleBag = bag->getTileBag();
    // newTestShuffleBag = bag->shuffleTileBag();
    // newTestShuffleBag->printAll();

    delete bag;
    // delete newTestShuffleBag;
}

void testPrintTileFromNode(LinkedList *newTestBag, int i)
{
    TileBag *testBag = new TileBag(newTestBag);
    testBag->shuffleTileBag();
    Tile *testTile = testBag->getTile();
    if (testTile != nullptr)
    {
        char colour = testTile->getColour();
        int shape = testTile->getShape();
        std::cout << "Tile " << i << ": " << colour << shape << std::endl;
    }

    delete testTile;
    delete testBag;
}

void print2DVector(std::vector<std::vector<Tile *>> vector, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            Tile *tile = vector[i][j];
            if (tile == nullptr)
            {
                std::cout << "|   ";
            }
            else if (tile != nullptr)
            {
                char colour = tile->getColour();
                int shape = tile->getShape();
                std::cout << "|" << colour << shape;
                delete tile;
            }
            else
            {
                std::cout << "Error! ";
            }
            delete tile;
        }
    }
    std::cout << std::endl;
}

//   LinkedList* test = new LinkedList;
//
//   std::cout << "Start testing" << std::endl;
//   testPrintShuffledBag(test);
//   std::array<int, 5> tileTests ({3, 5, 19, 20, 29});
//   for (int i = 0; i < tileTests.size(); i++) {
//      int j = tileTests[i];
//      testPrintTileFromNode(test, j);
//   }
//
//   Tile* a1 = nullptr;
//   Tile* a2 = new Tile(R,1);
//   Tile* a3 = nullptr;
//   Tile* b4 = new Tile(G,3);
//   Tile* b5 = new Tile(P,6);
//   Tile* b6 = nullptr;
//   Tile* c7 = nullptr;
//   Tile* c8 = new Tile(B,6);
//   Tile* c9 = nullptr;
//
//   std::vector<std::vector<Tile*>> vector
//   {
//        {a1, a2, a3},
//        {b4, b5, b6},
//        {c7, c8, c9}
//   };
//
//   print2DVector(vector, 3);
//   std::cout << "Finish testing" << std::endl;
//
//   delete a1, a2, a3, b4, b5, b6, c7, c8, c9;
//   delete test;