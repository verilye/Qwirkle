#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>

class Tile
{
private:
   char color;
   int shape;

public:
   Tile();
   Tile(char color, int shape, int row, int column);
   Tile(char color, int shape);

   char getColour();
   int getShape();
   void setColour(char color);
   void setShape(int shape);

   void setTile(Tile *tile);

   //    Colour char's matched with their escape codes
   //    
   //    std::string R = "\u001b[31m";
   //    std::string O = "\u001b[36m";
   //    std::string Y = "\u001b[33m";
   //    std::string G = "\u001b[32m";
   //    std::string B = "\u001b[34m";
   //    std::string P = "\u001b[35m";

   // Orange changed to cyan due to compatability issues with my terminal
   // Only 8 colours included on my local machine, widest compatability also

   const char colours[6] = {'R','O','Y','G','B','P'};
   std::string codes[6] = {"\u001b[31m","\u001b[36m","\u001b[33m","\u001b[32m","\u001b[34m", "\u001b[35m"};

   std::string getEscapeCode(char c);

};

#endif // ASSIGN2_TILE_H
