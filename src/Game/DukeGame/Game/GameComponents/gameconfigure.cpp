#include "gameconfigure.h"

GameConfigure::GameConfigure()
    : playerA(nullptr), playerB(nullptr), bagPlayerA(nullptr), bagPlayerB(nullptr), dukeA(nullptr), dukeB(nullptr),
    guardPlayerA(false), guardPlayerB(false), currentTeam(NoTeam), firstTurnA(0), firstTurnB(0), status(InProgress)
{
}

void GameConfigure::setupBoard(){
    createCells();
    createPlayers();
    this->currentTeam = TeamA;
}

void GameConfigure::createCells(){
    cells.resize(6, std::vector<Cell*>(6));
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

void GameConfigure::updateDukeA(Figure* duke){
    dukeA = duke;
}
void GameConfigure::updateDukeB(Figure* duke){
    dukeB = duke;
}


GameState GameConfigure::getState(){
    GameState state;

    state.firstTurnA = this->firstTurnA;
    state.firstTurnB = this->firstTurnB;
    state.currentPlayer = this->currentTeam;

    std::vector<std::vector<std::tuple<PieceType, PlayerTeam, bool>>> board;

    state.playerABag = this->bagPlayerA->piecesInBag();
    state.playerBBag = this->bagPlayerB->piecesInBag();
    state.playerA_UnderGuard = this->guardPlayerA;
    state.playerB_UnderGuard = this->guardPlayerB;
    if(this->dukeA == nullptr){
        state.dukeCoordA = std::make_pair(-1, -1);
    }
    else{
        state.dukeCoordA = std::make_pair(this->dukeA->getCell()->getRow(), this->dukeA->getCell()->getCol());
    }
    if(this->dukeB == nullptr){
        state.dukeCoordB = std::make_pair(-1, -1);
    }
    else{
        state.dukeCoordB = std::make_pair(this->dukeB->getCell()->getRow(), this->dukeB->getCell()->getCol());
    }


    // Loop to iterate through each row of the 2D vector
    for (size_t i = 0; i < cells.size(); ++i) {
        std::vector<std::tuple<PieceType, PlayerTeam, bool>> row;
        // Loop to iterate through each column of the current row
        for (size_t j = 0; j < cells[i].size(); ++j) {
            // Access the Cell object using the pointer
            Cell* cell = cells[i][j];

            if(cell->hasFigure()){
                row.emplace_back(cell->getFigure()->type(), cell->getFigure()->getTeam(), cell->getFigure()->isFlipped());
            }
            else{
                row.emplace_back(NoPiece, NoTeam, false);
            }

        }
        board.push_back(row);
    }

    state.status = this->status;

    state.board = board;

    return state;

}
