#include "gamelogic.h"

GameLogic::GameLogic() {

    gc = new GameConfigure();

    gc->setupBoard();
}

void GameLogic::moveFigure(int srcX, int srcY, int dstX, int dstY){
    Figure* selectedPiece = gc->getCell(srcX, srcY)->getFigure();
    gc->getCell(dstX, dstY)->setFigure(selectedPiece);
    gc->getCell(srcX, srcY)->setFigure(nullptr);
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

//TODO Check if this can be elsewhere
void GameLogic::placeFigure(int row, int col, Figure* newPiece){
    QList<QPair<int, int>> cells;
    if(newPiece->getTeam() == TeamA){
       cells = newPiece->placableCells(dukeA->getCell());
    }
    else{
        cells = newPiece->placableCells(dukeA->getCell());
    }
    for (auto move = cells.begin(); move != cells.end();) {
        int targetRow = std::get<0>(*move);
        int targetCol = std::get<1>(*move);

        // Check if the target cell is within the board bounds [0, 6)
        if (targetRow >= 0 && targetRow < 6 && targetCol >= 0 && targetCol < 6) {
            // Check if the target cell has a figure
            if (gc->getCell(targetRow, targetCol)->hasFigure()) {
                move = cells.erase(move);
            } else {
                ++move;
            }
        } else {
            // If the target cell is outside the board, remove the move
            move = cells.erase(move);
        }
    }
}
