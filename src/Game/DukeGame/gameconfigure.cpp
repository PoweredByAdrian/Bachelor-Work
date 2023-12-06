#include "gameconfigure.h"

GameConfigure::GameConfigure()
    : playerA(nullptr), playerB(nullptr), bagPlayerA(nullptr), bagPlayerB(nullptr)
{
    setupBoard();
}

void GameConfigure::setupBoard(){
    createCells();
    createPlayers();
}

void GameConfigure::createCells(){
    for (int x = 0; x < 6; ++x) {
        for (int y = 0; y < 6; ++y) {
            Cell *cell = new Cell(x, y);
            cells[x][y] = cell;
        }
    }
}

void GameConfigure::createPlayers(){
    Player* PlayerA = new Player(TeamA);
    bagPlayerA = PlayerA->getPieceBag();

    Player* PlayerB = new Player(TeamB);
    bagPlayerB = PlayerB->getPieceBag();
}
