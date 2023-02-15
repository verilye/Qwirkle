#ifndef ASSIGN2_MENU_H
#define ASSIGN2_MENU_H
#include "Player.h"
#include "SaveFilesManip.h"
#include <iostream>

// The Menu Class is all functionality that can be accessed when first
// opening qwirkle. Originally was a series of methods in a file
// but we found it to be more readable to create a class out of it. 

class Menu
{
public:
    Menu();
    ~Menu();

    // Functions
    void mainMenu();
    void creditDisplay();
    void newGameMenu(Player *player1, Player *player2, TileBag *bag, Board *board);
    bool loadGameMenu(Player *player1, Player *player2, TileBag *bag, Board *board);
    bool nameCheck(std::string name);
    char colours[6] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    int shapes[6] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

protected:
    std::string menuContent;
};

#endif