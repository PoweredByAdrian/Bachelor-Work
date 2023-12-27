#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "gameconfigure.h"
#include "figure.h"

#include "DebugManager.h"

class GameLogic
{
public:
    GameLogic();

    bool handleSingleCoordAction(int x, int y, PlayerTeam team);
    PieceType getPieceGeneratedRequest(PlayerTeam team);

    // Define a callback function type
    using ActionCompletedCallback = std::function<void(int, int, int, int, PieceType)>;
    using SwitchPlayerCallback = std::function<void(PlayerTeam)>;

    // Set the callback function
    void setActionCompletedCallback(const ActionCompletedCallback& callback);
    void setSwitchPlayerCallback(const SwitchPlayerCallback& callback);

    PlayerTeam getCurrentPlayer() const {return currentPlayer;}

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

    // Member variable to store the callback
    ActionCompletedCallback actionCompletedCallback;
    SwitchPlayerCallback switchPlayerCallback;

    void switchTurn();  // Switch the turn to the other player
    PlayerTeam currentPlayer;

    DebugManager *dm;
};

#endif // GAMELOGIC_H
