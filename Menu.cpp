#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include "Menu.h"

#define EXIT_SUCCESS 0

// The Menu Class is all functionality that can be accessed when first
// opening qwirkle. Originally was a series of methods in a file
// but we found it to be more readable to create a class out of it. 

Menu::Menu() {}
Menu::~Menu() {}

void Menu::mainMenu()
{
    /* Displays main menu content */
    menuContent = "Menu\n"
                  "-----\n"
                  "1. New Game\n"
                  "2. Load Game\n"
                  "3. Credits\n"
                  "4. Quit\n";
    std::cout << menuContent;
    std::cout << "\n>";
}

void Menu::creditDisplay()
{
    // system("clear");
    std::cout << std::endl
              << "- - - - - - - -" << std::endl;
    std::cout << "Created by: " << std::endl;
    std::cout << "Name: Connor Logan" << std::endl;
    std::cout << "Student ID: s3768929" << std::endl;
    std::cout << "Email: connor.j.logan@outlook.com" << std::endl
              << std::endl;

    std::cout << "Name: Constanza Von Marees" << std::endl;
    std::cout << "Student ID: s3777909" << std::endl;
    std::cout << "Email: s3777909@student.rmit.edu.au" << std::endl
              << std::endl;

    std::cout << "Name: Peter Choi" << std::endl;
    std::cout << "Student ID: s3756382" << std::endl;
    std::cout << "Email: s3756382@student.rmit.edu.au" << std::endl
              << std::endl;

    std::cout << "Name: Stacey Voyka" << std::endl;
    std::cout << "Student ID: s3637177" << std::endl;
    std::cout << "Email: s3637177@student.rmit.edu.au" << std::endl;
    std::cout << "- - - - - - - -" << std::endl
              << std::endl;
}

// Creates new users out of user input. Tiles are dealt out the player classes here
// and the tilebag and board are initialised

void Menu::newGameMenu(Player *player1, Player *player2, TileBag *bag, Board *board)
{
    
    // Enter Player 1's name
    bool playerNameLoop = true;

    std::cout << "Starting a New Game\n\n";

    // Loops until name requirements are met
    while (playerNameLoop == true)
    {
        std::cout << "Enter a name for player 1 (uppercase characters only)\n>  ";
        if (!std::cin.eof())
        {

            std::string name1;
            std::cin >> name1;

            if (nameCheck(name1) == true)
            {

                player1->setName(name1);
                player1->dealTiles(bag->getBagList());
                playerNameLoop = false;
                std::cout << "Player 1 Created\n";

                std::cin.clear();
                std::cin.ignore();
            }
            else
            {
                std::cout << "\n(Names must not have "
                          << "numbers and symbols. "
                          << "Name must also be in upper case characters.)\n";
            }
        }
        else
        {
            std::cout << "Goodbye\n";
            playerNameLoop = false;
            exit(EXIT_SUCCESS);
        }
    }

    playerNameLoop = true;

    // Enter Player 2's name
    // Loops until name requirements are met
    while (playerNameLoop == true)
    {
        std::cout << "Enter a name for player 2 (uppercase characters only)\n>  ";
        if (!std::cin.eof())
        {

            std::string name2;
            std::cin >> name2;

            if (nameCheck(name2) == true)
            {

                player2->setName(name2);
                player2->dealTiles(bag->getBagList());
                playerNameLoop = false;
                std::cout << "Player 2 Created\n";

                std::cin.clear();
                std::cin.ignore();
            }
            else
            {
                std::cout << "\n(Names must not have "
                          << "numbers and symbols. "
                          << "Name must also be in upper case characters.)\n";
            }
        }
        else
        {
            std::cout << "Goodbye\n";
            playerNameLoop = false;
            exit(EXIT_SUCCESS);
        }
    }
}

// Open up the filestream, access the save file from user input only if its correct
// load all information into objects ready to be passed into the gameloop.

bool Menu::loadGameMenu(Player *player1, Player *player2, TileBag *bag, Board *board)
{
    // system("clear");
    // Take user input for filename

    std::string input = "";

    std::cout << "What is the name of your save file: (Enter without file extension)";
    std::cout << "\n>";
    std::getline(std::cin >> std::ws, input);
    // std::cin >> input;

    std::ifstream ifile;
    std::string savedFile = "./save/";
    savedFile += input;
    savedFile += ".txt";

    ifile.open(savedFile);

    if (!ifile)
    {
        return false;
    }
    std::string line;

    int i = 0;
    while (getline(ifile, line))
    {
        if (i == 0)
        {
            player1->setName(line);
        }
        else if (i == 1)
        {
            std::string score = line;
            player1->setScore(stoi(score));
        }
        else if (i == 2)
        {
            player1->setCurrentHand(line, player1);
        }
        else if (i == 3)
        {
            player2->setName(line);
        }
        else if (i == 4)
        {
            std::string score = line;
            player2->setScore(stoi(score));
        }
        else if (i == 5)
        {
            player1->setCurrentHand(line, player2);
        }
        else if (i == 6)
        {
            // Empty board is already initialised
        }
        else if (i == 7)
        {
            readBoard(line, board);
        }
        else if (i == 8)
        {
            setTileBag(line, bag);
        }
        else if (i == 9)
        {
            if (line == player1->getName())
            {
            }
            else
            {

                // swap player pointers if player 2's turn
                // so they go first
                Player *temp;
                temp = player1;
                player1 = player2;
                player2 = temp;
            }
        }
        i++;
    }

    ifile.close();

    return true;
}

// Checks if name is valid
bool Menu::nameCheck(std::string name)
{
    bool uppConfirm;
    if (std::all_of(name.begin(), name.end(), [](char e)
                    { return std::isupper(e); }))
    {
        return uppConfirm = true;
    }
    else
    {
        return uppConfirm = false;
    }
}
