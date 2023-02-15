#include <stdio.h>
#include "Tile.h"
#include <string>

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

Tile::~Tile()
{
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

int Tile::getRow()
{
    return this->row;
}

void Tile::setRow(int row)
{
    this->row = row;
}

int Tile::getCol()
{
    return this->col;
}

void Tile::setCol(int col)
{
    this->col = col;
}

void Tile::setTile(Tile *tile)
{
    this->color = tile->getColour();
    this->shape = tile->getShape();
    this->row = tile->getRow();
    this->col = tile->getCol();
}