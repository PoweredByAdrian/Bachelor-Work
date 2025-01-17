#ifndef CELL_H
#define CELL_H


#include "figure.h"

class Cell
{
public:
    explicit Cell(int row = NULL, int col = NULL);


    Figure *getFigure() const;
    void setFigure(Figure *figure);
    bool hasFigure() const;
    PieceType getFigureType() const;
    int getRow() const {return x;}
    int getCol() const {return y;};


signals:
    void figureStateChanged();

private:
    int x;
    int y;
    Figure *figure;


};

#endif // CELL_H
