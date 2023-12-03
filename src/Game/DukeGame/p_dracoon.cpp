#include "p_dracoon.h"

p_Dracoon::p_Dracoon(Figure::Team team, QObject *parent)
    : Figure(team, Figure::Dracoon, parent)
{}

bool p_Dracoon::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_Dracoon::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
