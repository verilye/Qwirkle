
#include "Node.h"

// Building block of the Linked List class
// stores tiles

Node::Node(Tile *tile, Node *next, Node *previous)
{
   this->tile = tile;
   this->next = next;
   this->previous = previous;
}

Node::Node(Node *node)
{
   this->tile = node->tile;
   this->next = node->next;
   this->previous = node->previous;
}

Node::Node()
{
   this->tile = new Tile();
   this->next = nullptr;
   this->previous = nullptr;
}

Node::Node(Node &other)
{
   this->tile = new Tile(*other.tile);
   this->next = new Node(nullptr, nullptr, nullptr);
}

Node::~Node()
{
   delete this->tile;
   delete this->next;
   delete this->previous;
}

Tile *Node::getTile()
{
   return tile;
}
