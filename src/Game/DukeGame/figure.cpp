// figure.cpp
#include "figure.h"

Figure::Figure(QObject *parent)
    : QObject(parent), cell(nullptr)
{
}

void Figure::setTeam(Figure::Team team)
{
    this->team = team;
}

void Figure::setCell(Cell *cell)
{
    this->cell = cell;
}

Cell *Figure::getCell() const
{
    return cell;
}
