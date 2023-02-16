#include <stdio.h>
#include "Tile.h"
#include <string>

struct TileColour{

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

   std::string getEscapeCode(char c){

        // iterate through TileColour
        // If tile colour char matches TileColour char return

        std::string colour; 

        for (int i = 0; i<6; i++){
            if(c == colours[i])
                return codes[i];
        }

        return "";
    };
} escapeCodes;

Tile::Tile(char color, int shape, int row, int column)
{
    this->color = color;
    this->shape = shape;
    this->row = row;
    this->col = column;
}

Tile::Tile(char color, int shape)
{
    this->color = color;
    this->shape = shape;
}

Tile::Tile()
{
    this->color = ' ';
    this->shape = 0;
    this->row = 0;
    this->col = 0;
}

char Tile::getColour()
{
    return this->color;
}

void Tile::setColour(char color)
{
    this->color = color;
}

int Tile::getShape()
{
    return this->shape;
}

void Tile::setShape(int shape)
{
    this->shape = shape;
}

void Tile::setTile(Tile *tile)
{
    this->color = tile->getColour();
    this->shape = tile->getShape();
}