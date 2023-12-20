#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "gameconfigure.h"
#include "figure.h"

class GameLogic
{
public:
    GameLogic();

    bool getTurnRequest(int srcX, int srcY, int dstX, int dstY);
    PieceType getPieceGeneratedRequest(PlayerTeam team);

private:

    void moveFigure(int srcX, int srcY, int dstX, int dstY);
    void commandFigure(int srcX, int srcY, int dstX, int dstY);
    void killFigure(int row, int col);
    void placeFigure(int row, int col, Figure* newPiece);

    Figure* dukeA;
    Figure* dukeB;


    GameConfigure *gc;
};

#endif // GAMELOGIC_H
