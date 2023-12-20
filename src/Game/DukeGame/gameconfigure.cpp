#include "gameconfigure.h"

GameConfigure::GameConfigure()
    : playerA(nullptr), playerB(nullptr), bagPlayerA(nullptr), bagPlayerB(nullptr)
{
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

void GameConfigure::updateDukeA(Cell *cell){
    dukeCellA = cell;
}
void GameConfigure::updateDukeB(Cell *cell){
    dukeCellB = cell;
}

QList<QPair<int, int>> GameConfigure::getPlacableCellsForNewPiece(PlayerTeam team){
    QList<QPair<int, int>> result;
    Cell* actualDuke;
    if(team == TeamA){
        if(dukeCellA == nullptr){
            result.append(QPair<int, int>(0, 2));
            result.append(QPair<int, int>(0, 3));
            return result;
        }
        else{
            actualDuke = dukeCellA;
        }
    }
    else{
        if(dukeCellB == nullptr){
            result.append(QPair<int, int>(5, 2));
            result.append(QPair<int, int>(5, 3));
            return result;
        }
        else{
            actualDuke = dukeCellB;
        }
    }

    result.append(QPair<int, int>(actualDuke->getRow(), actualDuke->getCol() + 1));
    result.append(QPair<int, int>(actualDuke->getRow(), actualDuke->getCol() - 1));
    result.append(QPair<int, int>(actualDuke->getRow() + 1, actualDuke->getCol()));
    result.append(QPair<int, int>(actualDuke->getRow() - 1, actualDuke->getCol()));

    for (auto move = result.begin(); move != result.end();) {
        int targetRow = std::get<0>(*move);
        int targetCol = std::get<1>(*move);

        // Check if the target cell is within the board bounds [0, 6)
        if (targetRow >= 0 && targetRow < 6 && targetCol >= 0 && targetCol < 6) {
            // Check if the target cell has a figure
            if (getCell(targetRow, targetCol)->hasFigure()) {
                move = result.erase(move);
            } else {
                ++move;
            }
        } else {
            // If the target cell is outside the board, remove the move
            move = result.erase(move);
        }
    }

    return result;
}
