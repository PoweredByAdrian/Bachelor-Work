#ifndef MOVESIMULATOR_H
#define MOVESIMULATOR_H

#include "gameconfigure.h"
#include "enums.h"
#include "cellinfo.h"


class MoveSimulator
{
public:

    struct finalMove {
        std::pair<int, int> firstCoord;
        std::pair<int, int> secondCoord;
        std::pair<int, int> thirdCoord;
    };

    struct BoardState {
        // Board representation (adapt based on your implementation)
        std::vector<std::vector<CellInfo>> simBoard;

        // Duke coordinates for each team
        std::pair<int, int> dukeA;
        std::pair<int, int> dukeB;
    };

    MoveSimulator();

    void setState(BoardState state){
        this->board = state.simBoard;
        this->dukeA = state.dukeA;
        this->dukeB = state.dukeB;
    }

    Figure::MoveResult simulateAndFilterMoves(Figure* figure);
    void simulateMove(int fromX, int fromY, int toX, int toY, MoveTypes type, /* coord for command */int commandX = NULL, int commandY = NULL);
    MoveSimulator::BoardState simulateMove(int row, int col, std::vector<std::vector<CellInfo>> board, std::tuple<MoveTypes, int, int> move);
    std::vector<std::vector<CellInfo>> simulateMove(int row, int col, std::vector<std::vector<CellInfo>>);
    void updateBoard(GameConfigure* gc);

    bool endGameCheck(GameConfigure* gconfig, PlayerTeam team);

    std::vector<std::vector<CellInfo>> getBoard(){return this->board;}

    BoardState loadBoard(GameConfigure* gameconfig);
    QList<QPair<int, int>> drawPieceCheck(PlayerTeam currentPlayer);

    void rollBackBoard(GameConfigure* gc = nullptr);
private:

    // Function to get the current state of the cell
    CellInfo getCellInfo(int row, int col) const {return board[row][col];};

    // Function to simulate placing a figure in a cell
    void placeFigure(int row, int col, PlayerTeam owner, PieceType figureType, bool isFlipped);

    // Function to simulate removing a figure from a cell
    void removeFigure(int row, int col);

    bool selfGuard(PlayerTeam currentPlayer);



    std::vector<std::vector<CellInfo>> board;



    std::vector<std::vector<Cell*>> cells;
    std::pair<int, int> dukeA;
    std::pair<int, int> dukeB;

    GameConfigure* gc;

    void printBoard();

};

#endif // MOVESIMULATOR_H
