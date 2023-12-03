#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>

class Cell; // Forward declaration
class p_Duke;

class Figure : public QObject
{
    Q_OBJECT

public:
    enum Team {
        TeamA,
        TeamB
    };

    enum PieceType {
        Assassin,
        Bowman,
        Champion,
        Dracoon,
        Duke,
        Footman,
        General,
        Knight,
        Marshall,
        Pikeman,
        Priest,
        Seer,
        Wizard,


        NoPiece
    };

    explicit Figure(Team team, PieceType type, QObject *parent = nullptr);

    Team getTeam() const { return team; }
    void setTeam(Team newTeam);
    void setCell(Cell *newCell);
    Cell *getCell() const;

    virtual bool isValidMove(Cell *destination) const = 0; // Pure virtual function for move validation
    virtual void markAvailableJumps() = 0; // New virtual function to mark available jumps

    // New method to check if the figure is a duke
    virtual bool isDuke() const { return type() == Duke; }

    // Factory method to create specific types of figures
    static Figure* createFigure(Team team, PieceType type, QObject *parent = nullptr);

    // Abstract method to get the type of the figure
    virtual PieceType type() const = 0;

private:
    Team team;
    Cell *cell; // Reference to the cell the figure is on
};

#endif // FIGURE_H
