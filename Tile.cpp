#include <stdio.h>
#include "Tile.h"
#include <string>

Tile::Tile(char color, int shape, int row, int column)
{
    this->color = color;
    this->shape = shape;
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

std::string Tile::getEscapeCode(char c){

    // iterate through TileColour
    // If tile colour char matches TileColour char return

    std::string colour; 

    for (int i = 0; i<6; i++){
        if(c == this->colours[i])
            return this->codes[i];
    }

    return "";
};