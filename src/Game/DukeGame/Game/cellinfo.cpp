#include "cellinfo.h"

CellInfo::CellInfo(bool hasFigure, PlayerTeam owner, PieceType figureType, bool isFlipped)
    : hasFigure(hasFigure), owner(owner), figureType(figureType), isFlipped(isFlipped) {}
