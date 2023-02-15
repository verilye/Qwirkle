
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

// Building block of the Linked List class
// stores tiles

class Node { 

   public:
      Tile* tile;
      Node* next;
      Node* previous;

      Node(Tile* tile, Node* next, Node* previous);
      Node(Node* node);
      Node();
      Node(Node& other);
      ~Node();
      Tile* getTile();   
};

#endif // ASSIGN2_NODE_H

