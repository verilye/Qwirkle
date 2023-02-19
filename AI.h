#include "Player.h"

class AI : public Player
{

    // AI should be able to take the same actions as a player
    // so it makes sense to make it a subclass of Player.

    // A game AI is considered 'intelligent' when it makes good 
    // informed game decisions. These good decisions will be 
    // defined here by heuristic checks

    // The highest level might be a finite state machine - should the AI ever
    // use replace? There are a number of valid locations, which should the ai 
    // pick?
    // Finite State machine : https://gameprogrammingpatterns.com/state.html

    // Things the ai should be concerned with:

    // Where is the place I should place my tile for optimal points? Are there multiple places?
    
    // When should an AI ever not place a tile in a place that is points optimal? 
    // - when holding off could let the Ai score a qwirkle
    // - stopping the player's qwirkle

    // No valid moves? (potentially the Ai should only react to things the player does)

    // Play tiles that the AI has the most of, sooner qwirkle

    // Always add onto the longest line of tiles if possible that isnt 5 

    public:
    AI(std::string name);
    virtual std::string takeTurn(Board * board);
    int checkRows(char y,int x,  Board* board);
    std::string generatePlaceString(std::vector<std::string> selection, std::vector<std::string> fourRow, Board* board);
    std::string generateReplaceString();
    
    enum State{
        STATE_JUDGE_OPTIONS,
        STATE_SELECT_HAND_TILE,
        STATE_MAKE_DECISION,
        STATE_REPLACE_TILE,
        STATE_PLACE_TILE
    };

    const char row[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    State _state;

};