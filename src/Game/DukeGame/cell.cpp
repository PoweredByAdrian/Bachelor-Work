#include "cell.h"

Cell::Cell(QObject *parent, int row, int col, QPushButton *newbutton)
    : QObject{parent}, figure(nullptr)
{
    x = row;
    y = col;
    button = newbutton;
}

Figure *Cell::getFigure() const
{
    return figure;
}

void Cell::setFigure(Figure *newFigure)
{
    if (figure != newFigure) {
        figure = newFigure;
        emit figureStateChanged();
    }
}

bool Cell::hasFigure() const
{
    return figure != nullptr;
}

PieceType Cell::getFigureType() const
{
    return figure ? figure->type() : NoPiece; // Assuming NoPiece is a default type
}
