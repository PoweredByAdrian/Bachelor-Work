#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "gameconfigure.h"
#include "figure.h"

#include "DebugManager.h"
#include "movesimulator.h"




class GameLogic
{
public:
    GameLogic();

    bool handleSingleCoordAction(int x, int y);
    PieceType getPieceGeneratedRequest(PlayerTeam team);

    // Define a callback function type
    using ActionCompletedCallback = std::function<void(int, int, PieceType, PlayerTeam)>;
    using SwitchPlayerCallback = std::function<void(PlayerTeam)>;

    // Set the callback function
    void setActionCompletedCallback(const ActionCompletedCallback& callback);
    void setSwitchPlayerCallback(const SwitchPlayerCallback& callback);

    PlayerTeam getCurrentPlayer() const {return currentPlayer;}

    GameConfigure* getGC(){return this->gc;}

private:
    bool getTurnRequest(int srcX, int srcY, int dstX, int dstY);

    void moveFigure(int srcX, int srcY, int dstX, int dstY);
    void commandFigure(int srcX, int srcY, int dstX, int dstY);
    void killFigure(int row, int col);
    void placeFigure(int row, int col);

    //#######################
    bool addFigure(int x, int y);

    void firstClick(int x, int y);
    bool secondClick(int x, int y);
    bool thirdClick(int x, int y);
    //#######################



    bool selfGuard();
    bool isGuard();

    Figure* dukeA;
    Figure* dukeB;


    GameConfigure *gc;

    Figure* newPiece;


    bool hasFirstCoord = false;
    int firstCoordX;
    int firstCoordY;
    int secondCoordX;
    int secondCoordY;

    // Member variable to store the callback
    ActionCompletedCallback actionCompletedCallback;
    SwitchPlayerCallback switchPlayerCallback;

    void switchTurn();  // Switch the turn to the other player
    PlayerTeam currentPlayer;

    DebugManager *dm;

    void filterValidMoves(Cell *cells[6][6], Figure::MoveResult result);

    int placedPiecesCounter = 0;  // Count of pieces placed (reset to 0 after reaching 3)
    int firstTurnCounter = 0;     // Count of first turn (reset to 0 after reaching 2)

    bool firstTurnDone = false;

    bool striked = false;
    bool commandRequest = false;

    Figure::MoveResult result;



};

#endif // GAMELOGIC_H
