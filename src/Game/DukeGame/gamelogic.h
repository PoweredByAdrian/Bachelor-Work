#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "gameconfigure.h"
#include "figure.h"

class GameLogic
{
public:
    GameLogic();

    bool handleSingleCoordAction(int x, int y, PlayerTeam team);
    PieceType getPieceGeneratedRequest(PlayerTeam team);

private:
    bool getTurnRequest(int srcX, int srcY, int dstX, int dstY);

    void moveFigure(int srcX, int srcY, int dstX, int dstY);
    void commandFigure(int srcX, int srcY, int dstX, int dstY);
    void killFigure(int row, int col);
    void placeFigure(int row, int col);

    Figure* dukeA;
    Figure* dukeB;


    GameConfigure *gc;

    Figure* newPiece;


    bool hasFirstCoord = false;
    int firstCoordX;
    int firstCoordY;
};

#endif // GAMELOGIC_H
