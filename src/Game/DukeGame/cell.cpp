#include "cell.h"

Cell::Cell(QObject *parent)
    : QObject{parent}, hasFigureOnCell(false)
{
}

void Cell::setHasFigure(bool hasFigure)
{
    if (hasFigureOnCell != hasFigure) {
        hasFigureOnCell = hasFigure;
        emit figureStateChanged(hasFigure);
    }
}
