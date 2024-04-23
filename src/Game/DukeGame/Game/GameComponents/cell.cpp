#include "cell.h"

Cell::Cell(int row, int col)
    : figure(nullptr)
{
    x = row;
    y = col;
}

Figure *Cell::getFigure() const
{
    return figure;
}

void Cell::setFigure(Figure *newFigure)
{
    if (figure != newFigure) {
        figure = newFigure;
        if(newFigure != nullptr){
            figure->setCell(this);
        }
    }
}

bool Cell::hasFigure() const
{
    return figure != nullptr;
}

PieceType Cell::getFigureType() const
{
    return figure ? figure->type() : NoPiece;
}
