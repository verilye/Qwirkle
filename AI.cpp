#include "AI.h"
#include <string>
#include <vector>

    // NOTE
    // launch qwirkle with the --ai command to enable AI
    // ./qwirkle --ai


AI::AI(std::string name): Player(name){
    this->alive = false;
    // This is needed to call the Player constructor to initialise the AI as a player
}

std::string AI::takeTurn(Board* board){

    std::cout<<"I WILL DESTROY YOU";

    // The judge options state should exit based on heuristics and where each heuristic is 
    // ranked on a scale of importance. 
    // It will generate a series of viable options. 
    // For run speed, care should be taken to reduce these options down as fast as possible too
    // For humans too, 1 or 2 really good decisions normally present themselves as well. 
    
    // Heuristics reduce possible outcomes so we will use a similar elimination of possibilities

    _state = STATE_JUDGE_OPTIONS;

    // 100% of the time, the AI should place tiles next to another one, so we should identify these

    int counter = 0;
    std::vector<std::string> goodOptions;
    std::vector<std::string> greatOptions;

    std::vector<std::string> garbage;
    std::vector<std::string> fourRow;
    std::vector<std::string> fiveRow;

    std::cout << "\nTiles coordinates I can see:";
    for (int i = 0;i<ROWS;i++) {
        for (int j = 0; j<COLUMNS-1;j++) {
            if (board->boardState[i][j]->getColour() != ' ') {
                char a = row[i];
                char b = (char)(j+'0');
                std::string option = std::string()+a+b;
                goodOptions.push_back(option);
                counter++;
                std::cout<<a<<b<<", ";
            }
        } 
    }
    std::cout<<"\n";

    // Viable options are immediately limited to next to existing tiles of same colour or shape
    for(int i=0;i<6;i++){
        for(int j=0;j<counter;j++){
            int y = goodOptions[j][0];
            int r = 0;
            for (int l = 0; l < ROWS; l++)
            {
                if (y == this->row[l])
                {
                    r = l;
                }
            }
            if(this->getCurrentHands()->accessElement(i)->getTile()->getColour() 
                == board->boardState[r][(int)goodOptions[j][1]-'0']->getColour()){
                greatOptions.push_back(goodOptions[j]);
            }
            else if(this->getCurrentHands()->accessElement(i)->getTile()->getShape() 
                == board->boardState[r][(int)goodOptions[j][1]-'0']->getShape()){
                greatOptions.push_back(goodOptions[j]);
            }
        }
    }

    // Seek out lines of length 5
    // Avoid lines of length 4
    // Track garbage placements in 1 array

    for (long unsigned int i = 0; i < greatOptions.size(); i++) {
        int rowLength = checkRows(greatOptions[i][0],greatOptions[i][1],board);

        if(rowLength == 5){fiveRow.push_back(greatOptions[i]);};
        if(rowLength == 4){fourRow.push_back(greatOptions[i]);};
        if(rowLength < 4){garbage.push_back(greatOptions[i]);};
    }

    _state = STATE_MAKE_DECISION;

    std::string input_string;

    if(fiveRow.size() == 0){
        if(garbage.size() > 0){
            input_string = generatePlaceString(garbage, fourRow,board);
            return input_string;
        }else{
            input_string = generatePlaceString(goodOptions, fourRow,board);
            return input_string;
        }
    }else{
        input_string = generatePlaceString(fiveRow, fourRow,board);
        return input_string;
    }

    // This gathers all necessary information, now tile placement needs to be chosen
    //If no other options replace tile
    

    return generateReplaceString();

}

int AI::checkRows(char y, int x,  Board* board){

    int rowCounter = 0;

    int r = 0;
    for (int l = 0; l < ROWS; l++)
    {
        if (y == this->row[l])
        {
            r = l;
        }
    }

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
            if(qwirkleColourCheck>rowCounter){ 
                rowCounter = qwirkleColourCheck;
                if(qwirkleShapeCheck>rowCounter){
                    rowCounter = qwirkleColourCheck;
                }
            }
         }
      }

    return rowCounter;
}

std::string AI::generatePlaceString(std::vector<std::string> selection, std::vector<std::string> fourRow, Board* board){

    _state = STATE_REPLACE_TILE;
    Tile* tile = NULL;
    std::string input;
    char a =' ';
    char b = 0;


    // Check first element in array is not next to fourRow tile

    for(long unsigned int i =0;i<selection.size();i++){
        for(int j=0;j<6;i++){

            tile = this->currentHands->accessElement(j)->getTile();

            int r = 0;
            for (int l = 0; l < ROWS; l++)
            {
                if (selection[i][0] == this->row[l])
                {
                    r = l;
                }
            }

            int x = (int)selection[i][1]-'0';

            if(x+1 <26 &&board->boardState[r][x+1]->getColour() == ' '
            ){
                a = row[r];
                b = x+1;
                goto handcheck;};
            if(x-1>=0  && board->boardState[r][x-1]->getColour() == ' '){
                a = r;
                b = x-1;
                goto handcheck;};
            if(r+1 <26  &&board->boardState[r+1][x]->getColour() == ' '
            ){
                a = row[r+1];
                b = x;
                goto handcheck;};
            if(r-1 >=0 && board->boardState[r-1][x]->getColour() == ' '
              ){
                a = row[r-1];
                b = x;
                goto handcheck;};
        };
    };

    if(tile==NULL){tile = this->currentHands->accessElement(0)->getTile();
};

    handcheck:
    
    

    input ="place ";
    input = input + tile->getColour();
    input = input + (char)(tile->getShape()+'0');
    input = input + " at ";
    
    // parse selection into 2 parts and modify both parts to be adjacent coordinates
    input = input + a;
    input = input + (char)(b+'0');
    input = input + "\n";


    // avoid fourRow tiles at all cost
    // if placing a tile will make you put the tile next to a four row, its a bad play

    return input;

}

std::string AI::generateReplaceString(){
    _state = STATE_PLACE_TILE;

    std::string input;
    Tile* tile = this->currentHands->accessElement(0)->getTile();

    input ="replace ";
    input = input + tile->getColour();
    input = input + (char)(tile->getShape()+'0');
    input = input + "\n";

    return input;

}