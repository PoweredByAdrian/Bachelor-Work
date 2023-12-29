#include "gamelogic.h"

GameLogic::GameLogic() : currentPlayer(PlayerTeam::TeamA), newPiece(nullptr) {

    gc = new GameConfigure();

    gc->setupBoard();


    dm = new DebugManager();
}
bool GameLogic::handleSingleCoordAction(int x, int y) {
    if (newPiece != nullptr) {
        QList<QPair<int, int>> placableCells = gc->getPlacableCellsForNewPiece(currentPlayer);
        QPair<int, int> targetCoord(x, y);
        if(placableCells.contains(targetCoord)){

            if(newPiece->isDuke()){
                if(newPiece->getTeam() == TeamA){
                    gc->updateDukeA(gc->getCell(x, y));
                }
                else if(newPiece->getTeam() == TeamB){
                    gc->updateDukeB(gc->getCell(x, y));
                }
            }

            actionCompletedCallback(x, y, x, y, newPiece->type(), newPiece->getTeam());
            placeFigure(x, y);

            ++placedPiecesCounter;

            if(!firstTurnDone){
                // Check if the placed pieces counter reaches 3
                if (placedPiecesCounter == 3) {
                    // Reset placed pieces counter
                    placedPiecesCounter = 0;

                    // Increment first turn counter
                    ++firstTurnCounter;
                    switchTurn();
                }

                if(firstTurnCounter == 2){
                    firstTurnDone = true;
                }
            }else{
               switchTurn();
            }

            return true;
        }
        else{
            return false;
        }

    } else {

        if(!firstTurnDone){
            return false;
        }

        if (!hasFirstCoord) {
            // Store the first coordinate
            if(gc->getCell(x,y)->hasFigure() && currentPlayer == gc->getCell(x, y)->getFigure()->getTeam()){
                firstCoordX = x;
                firstCoordY = y;
                hasFirstCoord = true;
            }

            return false;  // Continue waiting for the second coordinate
        } else {

            bool isValid = getTurnRequest(firstCoordX, firstCoordY, x, y);



            if (isValid) {
                // ... existing code

                // Emit the signal with information about the completed action
                actionCompletedCallback(firstCoordX, firstCoordY, x, y, gc->getCell(x, y)->getFigureType(), gc->getCell(x, y)->getFigure()->getTeam());
                // Reset the first coordinate state
                hasFirstCoord = false;
                firstCoordX = 0;
                firstCoordY = 0;

                return true;
            }
            else{
                // Reset the first coordinate state
                hasFirstCoord = false;
                firstCoordX = 0;
                firstCoordY = 0;
                return false;
            }
        }
    }

    // Case 3: Need 3 Coords - Add implementation when ready
    // ...

    // Default return
    return false;
}
void GameLogic::setActionCompletedCallback(const ActionCompletedCallback& callback) {
    actionCompletedCallback = callback;
}
void GameLogic::setSwitchPlayerCallback(const SwitchPlayerCallback& callback) {
    switchPlayerCallback = callback;
}
PieceType GameLogic::getPieceGeneratedRequest(PlayerTeam team){

    if(team == TeamA && team == currentPlayer){
        if(gc->getPlacableCellsForNewPiece(currentPlayer).isEmpty()){
            return NoPiece;
        }
        newPiece = gc->getBagPlayerA()->takeRandomPiece();
    }
    else if(team == TeamB && team == currentPlayer){
        if(gc->getPlacableCellsForNewPiece(currentPlayer).isEmpty()){
            return NoPiece;
        }
        newPiece = gc->getBagPlayerB()->takeRandomPiece();
    }
    else{
        return NoPiece;
    }

    return newPiece->type();
}
bool GameLogic::getTurnRequest(int srcX, int srcY, int dstX, int dstY){

    Figure* selectedPiece = gc->getCell(srcX, srcY)->getFigure();

    Cell* (*cells)[6][6] = gc->getCells();
    Figure::MoveResult result = selectedPiece->markAvailableJumps(*cells);

    dm->printMoves(result);

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

    if(valid){
        selectedPiece->flip();
        switchTurn();
    }

    return valid;
}

void GameLogic::moveFigure(int srcX, int srcY, int dstX, int dstY){
    Figure* selectedPiece = gc->getCell(srcX, srcY)->getFigure();

    gc->getCell(dstX, dstY)->setFigure(selectedPiece);
    gc->getCell(srcX, srcY)->setFigure(nullptr);

    gc->getCell(dstX, dstY)->getFigure()->setCell(gc->getCell(dstX, dstY));

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


void GameLogic::placeFigure(int row, int col){
    gc->getCell(row, col)->setFigure(newPiece);
    gc->getCell(row, col)->getFigure()->setCell(gc->getCell(row, col));
    newPiece = nullptr;
}


void GameLogic::switchTurn() {
    // Toggle between TeamA and TeamB
    currentPlayer = (currentPlayer == PlayerTeam::TeamA) ? PlayerTeam::TeamB : PlayerTeam::TeamA;
    switchPlayerCallback(currentPlayer);
}
