#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include "enums.h"

class Cell; // Forward declaration

class Figure : public QObject
{
    Q_OBJECT

public:

    explicit Figure(PlayerTeam team, PieceType type, QObject *parent = nullptr);

    PlayerTeam getTeam() const { return team; }
    void setTeam(PlayerTeam newTeam);
    void setCell(Cell *newCell);
    Cell *getCell() const;

    virtual bool isValidMove(Cell *destination) const = 0; // Pure virtual function for move validation
    virtual void markAvailableJumps() = 0; // New virtual function to mark available jumps

    // New method to check if the figure is a duke
    virtual bool isDuke() const { return type() == Duke; }

    // Factory method to create specific types of figures
    static Figure* createFigure(PlayerTeam team, PieceType type, QObject *parent = nullptr);

    // Abstract method to get the type of the figure
    virtual PieceType type() const = 0;

private:
    PlayerTeam team;
    Cell *cell; // Reference to the cell the figure is on
};

#endif // FIGURE_H
