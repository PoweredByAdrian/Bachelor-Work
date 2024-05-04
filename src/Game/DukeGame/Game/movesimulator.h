#ifndef MOVESIMULATOR_H
#define MOVESIMULATOR_H

#include "GameComponents/Figures/figure.h"
#include "enums.h"
#include "qdebug.h"


class MoveSimulator
{
public:

    MoveSimulator();

    void updateBoard(GameState state);
    Figure::MoveResult simulateAndFilterMoves(int row, int col);
    void simulateMove(int fromX, int fromY, int toX, int toY, MoveTypes type, /* coord for command */int commandX = NULL, int commandY = NULL);
    void simulateDraw(int row, int col, PlayerTeam team);
    void rollBackBoard();
    GameState getBoard(){    //qDebug() << "Return board Representation:\n";
                             //this->printBoard();
                             return this->boardState;}
    bool endGameCheck(GameState state, bool startTurn = false);
    QList<QPair<int, int>> drawPieceCheck(PlayerTeam currentPlayer, bool emptyCheck = true);


    int getCounter(){return this->simulations;};
    void printBoard();
    void resetCounter();
private:

    // Function to simulate placing a figure in a cell
    void placeFigure(int row, int col, PlayerTeam owner, PieceType figureType, bool isFlipped);

    // Function to simulate removing a figure from a cell
    void removeFigure(int row, int col);

    bool selfGuard(PlayerTeam currentPlayer);

    GameState boardState;
    GameState defaultBoardState;



    int simulations;


};

#endif // MOVESIMULATOR_H
