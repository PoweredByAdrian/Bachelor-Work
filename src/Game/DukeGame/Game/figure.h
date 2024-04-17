#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QPair>
#include <tuple>
#include "enums.h"


class Cell; // Forward declaration

class Figure
{

public:

    struct MoveResult {
        QPair<int, int> currentPosition;
        QList<std::tuple<MoveTypes, int, int>> validMoves;
    };

    explicit Figure(PlayerTeam team, PieceType type);

    PlayerTeam getTeam() const { return team; }
    void setTeam(PlayerTeam newTeam);
    void setCell(Cell *newCell);
    Cell *getCell() const;

    bool isFlipped() const {return flipped;}

    void flip(){flipped = !flipped;}

    /*virtual*/ bool isValidMove(std::vector<std::vector<Cell*>>& cells, int row, int col); // Pure virtual function for move validation
    virtual MoveResult markAvailableJumps(std::vector<std::vector<Cell*>>& cells) const = 0; // New virtual function to mark available jumps

    // New method to check if the figure is a duke
    virtual bool isDuke() const { return type() == Duke; }

    // Factory method to create specific types of figures
    static Figure* createFigure(PlayerTeam team, PieceType type);

    // Abstract method to get the type of the figure
    virtual PieceType type() const = 0;

protected:
    PlayerTeam team;
    Cell *cell; // Reference to the cell the figure is on
    bool flipped;
    int direction;
};

#endif // FIGURE_H





















