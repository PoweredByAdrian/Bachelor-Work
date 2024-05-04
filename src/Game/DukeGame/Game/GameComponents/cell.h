#ifndef CELL_H
#define CELL_H


#include "Figures/figure.h"

class Cell
{
public:
    explicit Cell(int row = NULL, int col = NULL);


    Figure *getFigure() const;
    void setFigure(Figure *figure);
    bool hasFigure() const;

    int getRow() const {return x;}
    int getCol() const {return y;};



private:
    int x;
    int y;
    Figure *figure;


};

#endif // CELL_H
