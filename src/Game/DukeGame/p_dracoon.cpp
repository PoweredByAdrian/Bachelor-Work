#include "p_dracoon.h"

p_Dracoon::p_Dracoon(QObject *parent)
    : Figure{parent}
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