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

    // Will replacing a tile now get me more points in the future? How often should I do this

    // Which of the available positions should I place my tile in? Am I opening myself up for 
    // better moves in the futures?

    // Where is the place I should place my tile for optimal points? Are there multiple places?
    
    // When should an AI ever not place a tile in a place that is points optimal? 
    // - when holding off could let the Ai score a qwirkle
    // - stopping the player's qwirkle
    // 

    public:
    AI();
    ~AI();

    private:
};