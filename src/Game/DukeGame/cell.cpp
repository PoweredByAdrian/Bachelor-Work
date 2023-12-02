#include "cell.h"

Cell::Cell(QObject *parent)
    : QObject{parent}, figure(nullptr)
{
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
