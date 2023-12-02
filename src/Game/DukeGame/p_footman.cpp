#include "p_footman.h"

p_Footman::p_Footman(QObject *parent)
    : Figure{parent}
{}

bool p_Footman::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_Footman::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
