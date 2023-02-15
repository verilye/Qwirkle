
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <string>

class LinkedList
{
private:
   Node *head;
   Node *tail;
   int length;

public:
   LinkedList();
   ~LinkedList();

   int getLength();
   // Linked List Functions
   void printHand();
   void printAll();
   void addFront(Tile *tile);
   void removeFront();
   void addEnd(Tile *tile);
   void removeEnd();

   // Advanced Functions
   bool searchElement(char color, int shape);
   Node *accessElement(int index);
   void removeElementByTile(Tile *tile);
   void removeElementByNode(Node *node);
   std::string printElementChar();
};

#endif // ASSIGN2_LINKEDLIST_H
