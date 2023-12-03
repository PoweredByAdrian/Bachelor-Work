#include "p_general.h"

p_General::p_General(Figure::Team team, QObject *parent)
    : Figure(team, Figure::General, parent)
{}

bool p_General::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_General::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
