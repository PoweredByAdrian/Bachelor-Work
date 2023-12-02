#include "p_seer.h"

p_Seer::p_Seer(QObject *parent)
    : Figure{parent}
{}

bool p_Seer::isValidMove(Cell *destination) const
{
    // Implementation for validating normal moves
    // ...
}

void p_Seer::markAvailableJumps()
{
    // Implementation for marking cells where the Duke can jump
    // ...
}
