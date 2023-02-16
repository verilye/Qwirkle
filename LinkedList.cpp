#include "LinkedList.h"
#include "Node.cpp"
#include "Tile.cpp"
#include <iostream>
#include <stdexcept>

LinkedList::LinkedList()
{
   this->head = NULL;
   this->tail = NULL;
   this->length = 0;
}

LinkedList::~LinkedList()
{
   delete this->head;
   delete this->tail;
}

int LinkedList::getLength()
{
   return this->length;
}

// Formatted specifically for player hands
// This is also used for testing and checking
// that tilebag and placed tiles work properly
// so it belongs in the linked list class

void LinkedList::printHand()
{

   Node *temp = this->head;
   if (temp == NULL)
   {
      std::cout << "Empty :(" << std::endl;
   }

   while (temp != NULL)
   {
      std::cout << escapeCodes.getEscapeCode(temp->tile->getColour())<< temp->tile->getColour() <<""<< temp->tile->getShape() << ", ";
      temp = temp->next;
   }
   std::cout << "\u001b[37m";
}

// General linked list testing function

void LinkedList::printAll()
{
   Node *temp = this->head;

   if (temp == NULL)
   {
      std::cout << "This Linked List is Empty..." << std::endl;
   }
   else
   {
      int counter = 1;

      std::cout << "Printing out Linked List..." << std::endl;
      std::cout << "----------------------------------" << std::endl;

      while (temp != NULL)
      {
         std::cout << "Tile # " << counter << std::endl;
         std::cout << "Color: " << temp->tile->getColour() << std::endl;
         std::cout << "Shape: " << temp->tile->getShape() << std::endl;
         std::cout << "---------------------------------------" << std::endl;

         temp = temp->next;
         counter++;
      }
   }

}

std::string LinkedList::printElementChar()
{
   Node *temp = this->head;

   std::string str = "";

   if (temp == NULL)
   {
      return str;
   }
   else
   {
      while (temp != NULL)
      {
         str += temp->tile->getColour();
         std::string c = std::to_string(temp->tile->getShape());
         str += c;
         str += ',';

         temp = temp->next;
      }
      return str;
   }
}

void LinkedList::addFront(Tile *tile)
{
   Node *newNode = new Node();
   newNode->tile = tile;
   newNode->next = NULL;
   newNode->previous = NULL;

   if (this->head == NULL)
   {
      this->head = newNode;
      this->tail = newNode;
   }
   else
   {
      newNode->next = this->head;
      this->head->previous = newNode;
      this->head = newNode;
   }
   this->length++;
}

void LinkedList::removeFront()
{

   if (this->head == NULL)
   {
      throw std::exception();
   }
   else if (this->head == this->tail)
   {
      this->head = NULL;
      this->tail = NULL;
   }
   else
   {
      this->head = this->head->next;
      this->head->previous = NULL;
   }
   this->length--;
}

void LinkedList::addEnd(Tile *tile)
{
   Node *newNode = new Node();
   newNode->tile = tile;
   newNode->next = NULL;
   newNode->previous = NULL;

   if (this->head == NULL)
   {
      this->head = newNode;
      this->tail = newNode;
   }
   else
   {
      this->tail->next = newNode;
      newNode->previous = this->tail;
      this->tail = newNode;
   }
   this->length++;
}

void LinkedList::removeEnd()
{
   if (this->head == NULL)
   {
      throw std::exception();
   }

   Node *temp = this->head;

   while (temp->next != this->tail)
   {
      temp = temp->next;
   }
   temp->next = NULL;
   this->tail = temp;

   this->length--;
}

// Search for the first tile elemenr in the linked list that
// matches the passed in description

bool LinkedList::searchElement(char color, int shape)
{
   int check = 0;
   Node *temp = this->head;

   for (int i = 0; i < this->getLength(); i++)
   {

      if (temp->tile->getColour() == color && temp->tile->getShape() == shape)
      {
         check = 1;
      }
      temp = temp->next;
   }

   if (check == 1)
   {
      return true;
   }
   else
   {
      return false;
   }
   delete temp;
}

//Access the element in the list that matches the passed in index

Node *LinkedList::accessElement(int index)
{

   // Check to See if Linked List is Empty
   if (this->head == NULL)
   {
      throw std::out_of_range("Cannot Access Anything as Linked List is Empty...");
   }
   // Index Out of Bounds Check
   else if (index >= this->getLength() || index < 0)
   {
      throw std::out_of_range("Selected Index is Out of Bounds Error...");
   }
   // Return Element
   else
   {
      Node *temp = this->head;

      for (int i = 0; i < index; i++)
      {
         temp = temp->next;
      }

      return temp;

      delete temp;
   }
}

// Find the exact tile that is passed in by reference
// and deletes it

void LinkedList::removeElementByTile(Tile *tile)
{

   // Check to See if Linked List is Empty
   if (this->head == NULL)
   {
      throw std::out_of_range("Nothing to Remove as Linked List is Empty...");
   }
   else
   {
      Node *temp = this->head;
      int length = this->getLength();

      for (int i = 0; i < length; i++)
      {

         if (temp->tile->getColour() == tile->getColour() && temp->tile->getShape() == tile->getShape())
         {
            // if First - Remove Element
            if (temp->previous == NULL)
            {
               this->head = this->accessElement(i + 1);
               this->head->previous = NULL;
            }
            // If Last - Remove Element
            else if (temp->next == NULL)
            {
               this->tail = this->accessElement(i - 1);
               this->tail->next = NULL;
            }
            // Remove Element
            else
            {
               temp->previous->next = temp->next;
               temp->next->previous = temp->previous;
            }
            this->length--;
            return;
         }
         temp = temp->next;
      }
      delete temp;
   }
}

// Removes node that stores a tile by finding it
// by passed reference

void LinkedList::removeElementByNode(Node *node)
{

   if (this->head == NULL)
   {
      throw new std::out_of_range("Nothing to Remove as Linked List is Empty...");
   }
   else
   {
      Node *temp = this->head;
      int length = this->getLength();

      for (int i = 0; i < length; i++)
      {
         if (temp->tile->getColour() == node->tile->getColour() && temp->tile->getShape() == node->tile->getShape())
         {
            // If First Element - Remove
            if (temp->previous == NULL)
            {
               this->head = this->accessElement(i + 1);
               this->head->previous = NULL;

               this->accessElement(i + 1)->previous = NULL;
               this->head = this->accessElement(i + 1);
            }
            // If Last Element - Remove
            else if (temp->next == NULL)
            {
               this->tail = this->accessElement(i - 1);
               this->tail->next = NULL;
            }
            // Remove Element
            else
            {
               temp->previous->next = temp->next;
               temp->next->previous = temp->previous;
            }
            this->length--;
         }
         temp = temp->next;
      }
      delete temp;
   }
}
