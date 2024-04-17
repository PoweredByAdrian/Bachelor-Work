#ifndef CELLINFO_H
#define CELLINFO_H


#include "enums.h"

class CellInfo {
public:
    bool hasFigure;
    PlayerTeam owner;
    PieceType figureType;
    bool isFlipped;

    // Constructor to initialize the CellInfo
    CellInfo(bool hasFigure, PlayerTeam owner, PieceType figureType, bool isFlipped);
};

#endif // CELLINFO_H
