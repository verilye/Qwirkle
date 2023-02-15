#ifndef TESTS
#define TESTS

#include "LinkedList.h"
#include "Node.h"
#include <vector>

//Check bag shuffling is working properly
void testPrintShuffledBag(LinkedList* newBag);
// Print tile from node to check that it is retrieveing properly (debugging)
void testPrintTileFromNode(LinkedList* newTestBag, int i);
// Print 2D vector to verify it is reading and writting the files correctly
void print2DVector(std::vector<std::vector<Tile*>> vector, int i);

#endif //TESTS