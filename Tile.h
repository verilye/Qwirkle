
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

// // Define a Colour type
// typedef char Colour;

// // Define a Shape type
// typedef int Shape;

class Tile
{
private:
   char color;
   int shape;
   int row;
   int col;

public:
   Tile();
   Tile(char color, int shape, int row, int column);
   Tile(char color, int shape);
   ~Tile();

   char getColour();
   int getShape();
   int getRow();
   int getCol();

   void setColour(char color);
   void setShape(int shape);
   void setRow(int row);
   void setCol(int col);

   void setTile(Tile *tile);
};

#endif // ASSIGN2_TILE_H
