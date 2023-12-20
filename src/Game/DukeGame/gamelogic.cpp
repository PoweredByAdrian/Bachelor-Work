#include "gamelogic.h"

GameLogic::GameLogic() {

    gc = new GameConfigure();

    gc->setupBoard();
}
PieceType GameLogic::getPieceGeneratedRequest(PlayerTeam team){

    if(team == TeamA){
        gc->getBagPlayerA()->takeRandomPiece();
    }
    else if(team == TeamB){
        gc->getBagPlayerB()->takeRandomPiece();
    }

}
bool GameLogic::getTurnRequest(int srcX, int srcY, int dstX, int dstY){

    Figure* selectedPiece = gc->getCell(srcX, srcY)->getFigure();

    Cell* (*cells)[6][6] = gc->getCells();
    Figure::MoveResult result = selectedPiece->markAvailableJumps(*cells);

    bool valid = false;
    bool movement = false;
    bool attack = false;

    // Check if the list contains the specified move type and coordinates
    for (const auto& move : result.validMoves) {
        int moveRow = std::get<1>(move);
        int moveCol = std::get<2>(move);

        if ((moveRow == dstX && moveCol == dstY) &&
            (std::get<0>(move) == Move || std::get<0>(move) == Jump || std::get<0>(move) == Slide || std::get<0>(move) == JumpSlide)) {
            movement = true;
            break;
        }

        if((moveRow == dstX && moveCol == dstY) && (std::get<0>(move) == Strike)){
            attack = true;
        }
    }

    if(movement){
        moveFigure(srcX, srcY, dstX, dstY);
        valid = true;
    }
    else if(attack){
        killFigure(dstX,dstY);
        valid = true;
    }

    selectedPiece->flip();
    return valid;
}

void GameLogic::moveFigure(int srcX, int srcY, int dstX, int dstY){
    Figure* selectedPiece = gc->getCell(srcX, srcY)->getFigure();

    gc->getCell(dstX, dstY)->setFigure(selectedPiece);
    gc->getCell(srcX, srcY)->setFigure(nullptr);

    if(selectedPiece->isDuke()){
        if(selectedPiece->getTeam() == TeamA){
            gc->updateDukeA(gc->getCell(dstX, dstY));
        }
        else if(selectedPiece->getTeam() == TeamB){
            gc->updateDukeB(gc->getCell(dstX, dstY));
        }
    }
};
void GameLogic::commandFigure(int srcX, int srcY, int dstX, int dstY){
    if(gc->getCell(dstX, dstY)->hasFigure()){
        killFigure(dstX, dstY);
        moveFigure(srcX, srcY, dstX, dstY);
    }
    else{
        moveFigure(srcX, srcY, dstX, dstY);
    }
};
void GameLogic::killFigure(int row, int col){
    gc->getCell(row, col)->setFigure(nullptr);
};


void GameLogic::placeFigure(int row, int col, Figure* newPiece){
    gc->getCell(row, col)->setFigure(newPiece);
}
