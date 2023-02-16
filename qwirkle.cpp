#include "Player.h"
#include "Board.h"
#include "TileBag.h"
#include "SaveFilesManip.h"
#include "Menu.h"

#include <iostream>
#include <limits>
#include <array>
#include <string>
#include <fstream>

#define EXIT_SUCCESS 0

// QWIRKLE!
//
// This game file is structured like so:
//
//    The main menu is accessed and players can create a new game or load a game
//    New objects are created if new game is selected
//    Objects are populated with preexisting details if load game is selected
//
//    Which ever one the player choses, these objects are both passed into the
//    'game loop' which drives the game and continues until one of the players has won
// 
//    The game loop works by passing each player to the player turn function consecutively
//    where each player can take one of the player actions place, replace, save or quit

int gameloop(Player *player1, Player *player2, Board *board, TileBag *bag);
void playerTurn(Player *player, Board *board, TileBag *bag, Player *other);
bool place(std::string tile, std::string location, Player *player, Board *board, TileBag *bag, Player *other);
bool replace(std::string tile, Player *player, LinkedList *list);
bool save(std::string saveName, Board *currentState, Player *player1, Player *player2, TileBag *tilebag, std::string activePlayer);
void error();

int main(void)
{

   Player *player1 = new Player("");
   Player *player2 = new Player("");
   TileBag *bag = new TileBag(new LinkedList());
   std::cout << "\n";

   Board *board = new Board();

   Menu menu;
   int choice;

   std::cout << "Welcome to Qwirkle!\n-------------------" << std::endl;
   do
   {
      menu.mainMenu();
      std::cin >> choice;
      std::cout << "\n>";
      if (choice == 1)
      {
         menu.newGameMenu(player1, player2, bag, board);
         std::cin.clear();
         gameloop(player1, player2, board, bag);
      }
      if (choice == 2)
      {

         if (menu.loadGameMenu(player1, player2, bag, board) == true)
         {
            std::cin.clear();
            gameloop(player1, player2, board, bag);
         }
         else
         {
            std::cout << "\nNO SUCH SAVE EXISTS!\n";
         }
      }
      if (choice == 3)
      {
         menu.creditDisplay();
      }
      else if (choice == 4 || std::cin.eof())
      {
         std::cout << "Goodbye\n";
         exit(EXIT_SUCCESS);
      }
      else if (choice < 1 || choice > 4 || std::cin.fail())
      {
         std::cout << "Invalid input, please try again\n";
         std::cin.clear();
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }

   } while (std::cin.good() || !std::cin.eof());
}

// Pass the Gameboard in so that we can construct a new board
// or pass in a loaded gameboard from a save file

int gameloop(Player *player1, Player *player2, Board *board, TileBag *bag)
{
   std::cin.clear();
   // board->printCurrentBoard();

   while (1)
   {

      if (bag->getBagList()->getLength() == 0)
      {
         if (player1->getCurrentHands()->getLength() == 0)
         {

            std::cout << "\n"
                      << player1->getName() << " YOU WON WOOHOO!\n";

            exit(EXIT_SUCCESS);
         }
      }
      playerTurn(player1, board, bag, player2);

      if (bag->getBagList()->getLength() == 0)
      {
         if (player2->getCurrentHands()->getLength() == 0)
         {

            std::cout << "\n"
                      << player1->getName() << " YOU WON WOOHOO!\n";

            exit(EXIT_SUCCESS);
         }
      }
      playerTurn(player2, board, bag, player1);
   }
   return 1;
}

//
void playerTurn(Player *player, Board *board, TileBag *bag, Player *other)
{

   // system("clear");
   board->printCurrentBoard();
   std::cout << player->getName() << " your turn \n";

   bool playerTurn = true;

   while (playerTurn == true)
   {
      std::cin.clear();
      std::cout << player->getName() << ": " << player->getScore() << std::endl;
      std::cout << other->getName() << ": " << other->getScore() << std::endl;
      std::string input = "";
      std::string command = "";
      std::string tile = "";
      std::string at = "";
      std::string coordinates = "";

      std::cout << "\nYour hand is: \n";
      player->getCurrentHands()->printHand();

      // Display user prompt then interpret what player wants to do

      std::cout << "\n> ";
      std::getline(std::cin, input);
      input = input + " ";

      char separator = ' ';
      int k = 0;

      while (input[k] != ' ')
      {
         if (input[k] != separator)
         {
            // Append the char to the temp string.
            command += input[k];
         }
         k++;
      }

      k++;

      while (input[k] != ' ')
      {
         if (input[k] != separator)
         {
            tile += input[k];
         }
         k++;
      }
      k++;
      while (input[k] != ' ')
      {
         if (input[k] != separator)
         {
            at += input[k];
         }
         k++;
      }
      k++;
      while (input[k] != '\0')
      {
         if (input[k] != separator)
         {
            coordinates += input[k];
         }
         k++;
      }

      if (command == "place")
      {

         if (place(tile, coordinates, player, board, bag, other) == true)
         {
            playerTurn = false;
         }
         else
         {
            error();
         }
      }
      else if (command == "replace")
      {
         if (replace(tile, player, bag->getBagList()) == true)
         {
            playerTurn = false;
         }
         else
         {
            error();
         }
      }
      else if (command == "save")
      {
         if (save(tile, board, player, other, bag, player->getName()) == false)
         {
            error();
         }
         else
         {
            std::cout << "\nFile saved Successfully!\n";
         };
      }
      else if (command == "quit" || command == "^D" || std::cin.fail() || std::cin.eof())
      {

         std::cout << "\nGoodbye!\n";
         exit(EXIT_SUCCESS);
      }
      else
      {
         error();
      }
   }

   std::cin.clear();

   return;
}

bool place(std::string tile, std::string location, Player *player, Board *board, TileBag *bag, Player *other)
{

   if (isalpha(location[0]) == 0)
   {
      return false;
   }
   if (isdigit(location[1] == 0))
   {
      return false;
   }

   char y = location[0];
   int x = atoi(&location[1]);

   if (x >=ROWS || x<0)
   {
      return false;
   }

   int r = 0;
   for (int l = 0; l < ROWS; l++)
   {
      if (y == row[l])
      {
         r = l;
      }
   }

   if (board->boardState[r][x]->getShape() == 0)
   {

      char colour = tile[0];
      int shape = atoi(&tile[1]);


      //Check to see if there are any qwirkles around the tile
      for(int i = 1;i<=4;i++){
         int qwirkleColourCheck = 0;
         int qwirkleShapeCheck = 0;
         for(int j = 1; j<=6;j++){
            int index1 = j;
            int index2 = 0; 
            if(i%2 == 0){
               index1 = index1 - (index1 *2);
            }
            if(i>2){
               index2 = index1;
               index1 = 0;
            }

            if(x+index2 >25 ||x+index2<0 || r+index1>25 || r+index1<0){
               break;
            }

            char alpha = board->boardState[r+index1][x+index2]->getColour();
            int beta = board->boardState[r+index1][x+index2]->getShape();

            if(beta == 0 || alpha == ' '){
               break;
            }

            if(board->boardState[r+index1][x+index2]->getColour() == alpha){
               qwirkleColourCheck++;
            }
            if(board->boardState[r+index1][x+index2]->getShape() == beta){
               qwirkleShapeCheck++;
            }
            if(qwirkleColourCheck==6||qwirkleShapeCheck==6){ 
               std::cout<<"\nCant place at the end of a Qwirkle!\n";
               return false;}
         }
      }
      
      // Take the tile out of your hand and place it on the board
      for (int i = 0; i < player->getCurrentHands()->getLength(); i++)
      {
         if (colour == player->getCurrentHands()->accessElement(i)->getTile()->getColour() && shape == player->getCurrentHands()->accessElement(i)->getTile()->getShape())
         {
            board->updateBoard(y, x, player->getCurrentHands()->accessElement(i)->getTile());
            player->placeTile(y, x,
                              player->getCurrentHands()->accessElement(i)->getTile(), bag->getBagList(), board);
            player->calculateScore(player,other, board,r, x);
            return true;
         }
      }
   }

   std::cout << "\nInvalid coordinates\n";
   return false;
}

bool replace(std::string tile, Player *player, LinkedList *tilebag)
{

   char colour = tile[0];
   int shape = atoi(&tile[1]);

   for (int i = 0; i < player->getCurrentHands()->getLength(); i++)
   {
      if (colour == player->getCurrentHands()->accessElement(i)->getTile()->getColour() && shape == player->getCurrentHands()->accessElement(i)->getTile()->getShape())
      {

         player->replaceTile(player->getCurrentHands()->accessElement(i)->getTile(), tilebag);

         return true;
      }
   }

   return false;
}

bool save(std::string saveName, Board *currentState, Player *player1, Player *player2, TileBag *tilebag, std::string activePlayer)
{

   std::string str = saveName;

   for (long unsigned int i = 0; i < str.length(); i++)
   {
      if (isalpha(str[i]) == 0)
      {
         return false;
      }
   }

   saveGame(saveName, currentState, player1, player2, tilebag, activePlayer);

   return true;
}

void error()
{
   std::cout << "\nValid commands are: ";
   std::cout << "\n place <tilename> at <letter,number>";
   std::cout << "\n replace <tilename>";
   std::cout << "\n save <savename>";
   std::cout << "\n quit\n\n";
}