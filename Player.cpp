#include "Player.h"
#include "LinkedList.h"
#include <iostream>
#include <vector>

// Player objects are what can be dealt tiles, place tiles
// save the game -> basically the proxy for the human players
// of the game and all actions that they can take
// If a human has to do something to set up or play qwirkle
// this class does it

Player::Player(std::string name)
{
    this->name = name;
    this->score = 0;
    this->qwirkleCounter = 0;

    this->currentHands = new LinkedList();
    this->placedHands = new LinkedList();

    this->score = 0;
}

Player::~Player()
{
    delete this->currentHands;
    delete this->placedHands;
}

Player::Player(Player &other)
{
    this->name = *new std::string(other.getName());
    this->score = *new int(other.getScore());
}

int Player::getScore()
{
    return this->score;
}

void Player::setScore(int x)
{
    this->score += x;
}

std::string Player::getName()
{
    return this->name;
}
void Player::setName(std::string name)
{
    this->name = name;
}

LinkedList *Player::getCurrentHands()
{
    return this->currentHands;
}

void Player::setCurrentHand(std::string hand, Player *player)
{
    for (int i = 0; i < 17; i = i + 3)
    {

        Tile *tile = new Tile();
        const char c = hand[i];
        tile->setColour(c);
        tile->setShape(std::atoi(&hand[i + 1]));
        player->getCurrentHands()->addEnd(tile);
    }
    return;
}

LinkedList *Player::getPlacedHands()
{
    return this->placedHands;
}

void Player::setQWIRKLECounter(int count)
{
    this->qwirkleCounter += count;
}

int Player::getQWIRKLECounter()
{
    return this->qwirkleCounter;
}

void Player::dealTiles(LinkedList *tileBag)
{
    // add 5 tiles to hand and
    // remove 5 tiles from tile bag

    for (int i = 0; i < HAND_SIZE; i++)
    {

        Node *tile = tileBag->accessElement(0);
        this->currentHands->addFront(tile->getTile());

        tileBag->removeFront();
    }
}

void Player::placeTile(int y, int x, Tile *tile, LinkedList *tileBag, Board *board)
{
    // Removing Tile From Current Hands to Placed Hands
    this->placedHands->addEnd(tile);
    this->currentHands->removeElementByTile(tile);

    Tile *draw = tileBag->accessElement(0)->getTile();
    // Grabbing a New Tile from Tile Bag
    this->currentHands->addEnd(draw);
    tileBag->removeElementByTile(draw);
}

void Player::replaceTile(Tile *oldTile, LinkedList *tileBag)
{
    // Add oldtile to tilebag
    tileBag->addEnd(oldTile);
    this->getCurrentHands()->removeElementByTile(oldTile);
    // Draw new tile
    Tile *newTile = tileBag->accessElement(0)->getTile();
    this->getCurrentHands()->addEnd(newTile);
    tileBag->removeElementByTile(newTile);
}
//Player actions

void Player::calculateScore(Player* player, Player* other, Board* board) {
   
    //copy data for simplicity
    LinkedList* tilesPlaced = player->getPlacedHands();    
    int numOfTiles = tilesPlaced->getLength();
    std::vector<std::vector<Tile*>> boardState = board->getBoardState();

    int runningScore = 0;
   
    if(numOfTiles > 0) {
        
        // Horizontal Board Check
        for(int i = 0; i < ROWS; i++) {

            for(int j = 0; j < COLUMNS - 1; j++) {
                // Check to See Tile Isn't Null
                if(boardState[i][j]->getShape() != 0 && boardState[i][j + 1]->getShape() != 0) {                    
             
                    if(boardState[i][j]->getColour() == boardState[i][j + 1]->getColour()) {                 
                        runningScore++;
                    }
                    // Shape Check
                    if(boardState[i][j]->getShape() == boardState[i][j + 1]->getShape()) {                 
                        runningScore++;
                    }
                }
            }
        }

        // Vertical Board Check
        for(int i = 0; i < ROWS; i++) {

            for(int j = 0; j < COLUMNS - 1; j++) {
                // Check to See Tile Isn't Null
                if(boardState[j][i]->getShape() != 0 && boardState[j + 1][i]->getShape() != 0) {          
                  
                    if(boardState[j][i]->getColour() == boardState[j + 1][i]->getColour()) {                     
                        runningScore++;
                    }
                    // Shape Check
                    if(boardState[j][i]->getShape() == boardState[j + 1][i]->getShape()) { 
                        runningScore++;
                    }                   
                }
            }
        }      
    }
    int totalRunningScore = 0;
    totalRunningScore = runningScore + (player->getQWIRKLECounter() * 6) + (other->getQWIRKLECounter() * 6);

    int QWIRKLEScore = 0;
    QWIRKLEScore = player->checkQWIRKLE(player, other, board);

    totalRunningScore = totalRunningScore + QWIRKLEScore;
    int incrementalScore = 0; 
    incrementalScore = totalRunningScore - board->getBoardScore();

    player->setScore(incrementalScore);
    board->setBoardScore(incrementalScore);   
}

//Player actions
int Player::checkQWIRKLE(Player* player, Player* other, Board* board) {
    std::vector<std::vector<Tile*>> boardState = board->getBoardState();

    int horizontalColorCheck = 0;
    int horizontalShapeCheck = 0;
    int verticalColorCheck = 0;
    int verticalShapeCheck = 0;
    int localCounter = 0;

    // Horizontal Board Check
    for(int i = 0; i < ROWS; i++) {

        for(int j = 0; j < COLUMNS - 1; j++) {
            // Check to See Tile Isn't Null
            if(boardState[i][j]->getShape() != 0 && boardState[i][j + 1]->getShape() != 0) {
                    // Color Check
                    if(boardState[i][j]->getColour() == boardState[i][j + 1]->getColour()) {
                        horizontalColorCheck++;
                    }
                    // Shape Check
                    if(boardState[i][j]->getShape() == boardState[i][j + 1]->getShape()) {
                        horizontalShapeCheck++;
                    }
                    // QWIRKLE Check
                    if(horizontalColorCheck == 5) {
                        localCounter++;                        
                    }
                    if(horizontalShapeCheck == 5) {
                        localCounter++;                        
                    }                            
            }            
        }
        horizontalColorCheck = 0;
        horizontalShapeCheck = 0;
    }

    // Vertical Board Check
    for(int i = 0; i < ROWS; i++) {

        for(int j = 0; j < COLUMNS - 1; j++) {
            // Check to See Tile Isn't Null
            if(boardState[j][i]->getShape() != 0 && boardState[j + 1][i]->getShape() != 0) {
                    // Color Check
                    if(boardState[j][i]->getColour() == boardState[j + 1][i]->getColour()) {
                        verticalColorCheck++;
                    }
                    // Shape Check
                    if(boardState[j][i]->getShape() == boardState[j + 1][i]->getShape()) {
                        verticalShapeCheck++;
                    }
                    // QWIRKLE Check
                    if(verticalColorCheck == 5) {
                        localCounter++;                        
                    }
                    if(verticalShapeCheck == 5) {
                        localCounter++;                        
                    }                                 
            }           
        }
        verticalColorCheck = 0;
        verticalShapeCheck = 0;
    }             
    // Updating Player Score
    // Incremental QWIRKLE * 6 

    int increment = localCounter - player->getQWIRKLECounter() - other->getQWIRKLECounter();
    
    if(localCounter - player->getQWIRKLECounter() - other->getQWIRKLECounter() >= 1) {
        player->setQWIRKLECounter(increment);      

        return increment * 6;      
    }
    else {
        return 0;
    }
 
}