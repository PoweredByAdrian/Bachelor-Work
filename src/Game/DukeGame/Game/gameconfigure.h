#ifndef GAMECONFIGURE_H
#define GAMECONFIGURE_H

#include "cell.h"
#include "player.h"
#include "enums.h"
#include <vector>


class GameConfigure
{
public:
    GameConfigure();

    //Function to set up game backend
    void setupBoard();

    // Getters for necessary components
    Cell* getCell(int row, int col) const {return cells[row][col];};
    Player* getPlayerA() const { return playerA; }
    Player* getPlayerB() const { return playerB; }
    figureBag* getBagPlayerA() const { return bagPlayerA; }
    figureBag* getBagPlayerB() const { return bagPlayerB; }

    void updateDukeA(Cell *cell);
    void updateDukeB(Cell *cell);

    QList<QPair<int, int>> getPlacableCellsForNewPiece(PlayerTeam team);


    std::vector<std::vector<Cell*>>& getCells() {return cells; }
    Cell* getPlayerDuke(PlayerTeam player) const {return player == TeamA ? dukeCellA : dukeCellB;}

    bool guardPlayerA;
    bool guardPlayerB;

    bool canDrawFromBag(PlayerTeam player);

private:
    // Private member functions for setup
    void createCells();
    void createPlayers();

    // Private members representing game components
    std::vector<std::vector<Cell*>> cells;

    Player* playerA;
    Player* playerB;

    figureBag* bagPlayerA;
    figureBag* bagPlayerB;

    Cell *dukeCellA;
    Cell *dukeCellB;








};
#endif // GAMECONFIGURE_H

















