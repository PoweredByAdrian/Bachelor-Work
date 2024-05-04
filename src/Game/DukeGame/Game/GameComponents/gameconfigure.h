#ifndef GAMECONFIGURE_H
#define GAMECONFIGURE_H

#include "cell.h"
#include "player.h"
#include "../enums.h"
#include "GameState.h"
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

    void updateDukeA(Figure* duke);
    void updateDukeB(Figure* duke);


    Figure* getPlayerDuke(PlayerTeam player) const {return player == TeamA ? dukeA : dukeB;}

    bool guardPlayerA;
    bool guardPlayerB;


    GameState getState();

    PlayerTeam getCurrentPlayer(){return this->currentTeam;};
    void setCurrentPlayer(PlayerTeam team){this->currentTeam = team;};

    void setTeam(PlayerTeam team){this->currentTeam = team;}

    int firstTurnA;
    int firstTurnB;

    GameStatus status;
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

    Figure *dukeA;
    Figure *dukeB;

    PlayerTeam currentTeam;










};
#endif // GAMECONFIGURE_H

















