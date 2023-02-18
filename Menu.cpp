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

void mainMenu()
{
    /* Displays main menu content */
    std::string menuContent = "Menu\n"
                  "-----\n"
                  "1. New Game\n"
                  "2. Load Game\n"
                  "3. Credits\n"
                  "4. Quit\n";
    std::cout << menuContent;
    std::cout << "\n>";
}

void creditDisplay()
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

void newGameMenu(Player *player1, Player *player2,Player* player3, Player* player4, TileBag *bag, Board *board)
{
    
    // Enter Player 1's name
    
    bool numberOPlayers = true;
    std::cout << "Starting a New Game\n\n";

    while (numberOPlayers == true)
    {
        std::cout << "How many players are playing today?\n>  ";
        if (!std::cin.eof())
        {
            int numberOfPlayers;
            std::cin >> numberOfPlayers;

            if(isdigit(numberOfPlayers)==true||numberCheck(numberOfPlayers) == true){
                addNewPlayer(1,player1,bag);
                addNewPlayer(2,player2,bag);
                if(numberOfPlayers>2){
                    addNewPlayer(3,player3,bag);
                }
                if(numberOfPlayers==4){
                    addNewPlayer(4,player4,bag);
                }
                numberOPlayers=false;
            }
            else{
                std::cin.clear();
                std::cin.ignore();
                std::cout<<"\n Please enter a number from 2-4\n";  
            }
        }
        else
        {
            std::cout << "Goodbye\n";
            numberOPlayers = false;
            exit(EXIT_SUCCESS);
        }
    }

}

void addNewPlayer(int number,Player* player, TileBag* bag){

    bool playerNameLoop = true;
     // Loops until name requirements are met
    while (playerNameLoop == true)
    {
        std::cout << "Enter a name for Player "<< number<<" (uppercase characters only)\n>  ";
        if (!std::cin.eof())
        {

            std::string name;
            std::cin >> name;

            if (nameCheck(name) == true)
            {

                player->setName(name);
                player->dealTiles(bag->getBagList());
                playerNameLoop = false;
                std::cout << "Player "<<number<<" created\n";

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

bool loadGameMenu(Player *player1, Player *player2,Player* player3, Player* player4, TileBag *bag, Board *board)
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
    std::string whoseTurn ="";
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

            whoseTurn = line;
            // store the variable, swap them around at end of file read

            // if (line == player1->getName()){

            // }
            // {
                // swap player pointers if player 2's turn
                // so they go first
            //     Player *temp;
            //     temp = player1;
            //     player1 = player2;
            //     player2 = temp;
            // }

        }
        else if(i==10){
            player3->setName(line);
        }
        else if(i==11){
            std::string score = line;
            player3->setScore(stoi(score));
        }
        else if(i==12){
            player3->setCurrentHand(line,player3);
        }
        else if(i==13){
            player4->setName(line);
        }
         else if(i==14){
            std::string score = line;
            player4->setScore(stoi(score));
        }
        else if(i==15){
            player4->setCurrentHand(line,player4);
        }
        i++;
    }

    // Swap player pointers around so that current turn is correct when resumed

    // std::string p1 = player1->getName();
    // std::string p2 = player2->getName();
    // std::string p3 = player3->getName();
    // std::string p4 = player4->getName();
    // std::string names[] = {p1,p2,p3,p4};
    // int bump = 0;

    // // string match

    // for(int i =0;i<4;i++){
    //     if(names[i]==whoseTurn){bump = i; break;}
    // }
    
    // // bump up player pointers number of appropriate times

    // if(bump ==1){

    //     Player *temp;
    //     temp = player2;
    //     player2 = player3;
    //     player3 = temp;

    //     temp = nullptr;
    //     temp = player3;
    //     player3 = player4;
    //     player4 = temp;
        
        
    // }else if(bump == 2){

    //     Player *temp;
    //     temp = player1;
    //     player1 = player3;
    //     player3 = temp;

    //     temp = nullptr;
    //     temp = player2;
    //     player2 = player4;
    //     player4 = temp;

    // }else if(bump == 3){

    //     Player *temp;
    //     temp = player4;
    //     player4 = player3;
    //     player3 = temp;

    //     temp = nullptr;
    //     temp = player3;
    //     player3 = player2;
    //     player2 = temp;

    //     temp = nullptr;
    //     temp = player2;
    //     player2 = player1;
    //     player1 = temp;
    // }

    ifile.close();

    return true;
}

// Checks if name is valid
bool nameCheck(std::string name)
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

bool numberCheck(int number){

    if(number==2||number==3||number==4){
        return true;
    }

    return false;    
}
