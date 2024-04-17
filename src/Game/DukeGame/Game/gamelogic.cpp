#include "gamelogic.h"


GameLogic::GameLogic() : currentPlayer(PlayerTeam::TeamA), newPiece(nullptr) {

    gc = new GameConfigure();

    gc->setupBoard();




    dm = new DebugManager();
}
bool GameLogic::handleSingleCoordAction(int x, int y) {
    if (newPiece != nullptr) {
        return addFigure(x, y);

    } else {

        if(!firstTurnDone){
            return false;
        }

        if (!hasFirstCoord) {
            firstClick(x,y);
            return false;  // Continue waiting for the second coordinate
        } else if(!commandRequest) {

            return secondClick(x, y);
        } else{
            thirdClick(x, y);

            // Reset the first coordinate state
            hasFirstCoord = false;
            firstCoordX = 0;
            firstCoordY = 0;
            secondCoordX = 0;
            secondCoordY = 0;
            commandRequest = false;
            return false;

        }
    }

    // Case 3: Need 3 Coords - Add implementation when ready
    // ...

    // Default return
    return false;
}
bool GameLogic::addFigure(int x, int y){
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

        actionCompletedCallback(x, y, newPiece->type(), newPiece->getTeam());
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
}
void GameLogic::firstClick(int x, int y){
    // Store the first coordinate
    if(gc->getCell(x,y)->hasFigure() && currentPlayer == gc->getCell(x, y)->getFigure()->getTeam()){
        firstCoordX = x;
        firstCoordY = y;
        hasFirstCoord = true;

        //#######################
        //DEBUG
        std::vector<std::vector<Cell*>>& cells = gc->getCells();
        this->result = gc->getCell(x,y)->getFigure()->markAvailableJumps(cells);

        dm->printMoves(result);

        MoveSimulator *ms = new MoveSimulator();
        ms->updateBoard(this->gc);
        this->result = ms->simulateAndFilterMoves(gc->getCell(x,y)->getFigure());
        dm->printMoves(result);
        //DEBUG
        //#######################
    }
}
bool GameLogic::secondClick(int x, int y){
    bool isValid = getTurnRequest(firstCoordX, firstCoordY, x, y);

    if (isValid) {
        // ... existing code

        if(striked){

            actionCompletedCallback(firstCoordX, firstCoordY, gc->getCell(firstCoordX, firstCoordY)->getFigureType(), gc->getCell(firstCoordX, firstCoordY)->getFigure()->getTeam());
            actionCompletedCallback(x, y, NoPiece, NoTeam);

            striked = false;
        }
        else{
            // Emit the signal with information about the completed action
            actionCompletedCallback(firstCoordX, firstCoordY, NoPiece, NoTeam);
            actionCompletedCallback(x, y, gc->getCell(x, y)->getFigureType(), gc->getCell(x, y)->getFigure()->getTeam());
        }

        // Reset the first coordinate state
        hasFirstCoord = false;
        firstCoordX = 0;
        firstCoordY = 0;

        return true;
    }
    else if(commandRequest){
        return false;
    }
    else{
        // Reset the first coordinate state
        hasFirstCoord = false;
        firstCoordX = 0;
        firstCoordY = 0;
        return false;
    }
}
bool GameLogic::thirdClick(int x, int y){
    // Check if the list contains the specified move type and coordinates
    for (const auto& move : this->result.validMoves) {
        int moveRow = std::get<1>(move);
        int moveCol = std::get<2>(move);

        if((moveRow == x && moveCol == y) && (std::get<0>(move) == CommandTo)){
            moveFigure(secondCoordX, secondCoordY, x, y);

            gc->getCell(firstCoordX, firstCoordY)->getFigure()->flip();

            // if(this->selfGuard()){
            //     qDebug() << "selfGuard!";
            // }
            if(this->isGuard()){
                qDebug() << "isGuard!";
            }
            switchTurn();
            actionCompletedCallback(secondCoordX, secondCoordY, NoPiece, NoTeam);
            actionCompletedCallback(x, y, gc->getCell(x, y)->getFigureType(), gc->getCell(x, y)->getFigure()->getTeam());

            return true;
        }

    }
    return false;
}















void GameLogic::setActionCompletedCallback(const ActionCompletedCallback& callback) {
    actionCompletedCallback = callback;
}
void GameLogic::setSwitchPlayerCallback(const SwitchPlayerCallback& callback) {
    switchPlayerCallback = callback;
}
PieceType GameLogic::getPieceGeneratedRequest(PlayerTeam team){

    if(newPiece != nullptr){
        return newPiece->type();
    }
    MoveSimulator *ms = new MoveSimulator();
    if(team == TeamA && team == currentPlayer){
        if(gc->getPlacableCellsForNewPiece(currentPlayer).isEmpty()){
            return NoPiece;
        }

        if(firstTurnDone){
            ms->updateBoard(this->gc);
            if(ms->drawPieceCheck(team).isEmpty()){
                return NoPiece;
            }
        }
        newPiece = gc->getBagPlayerA()->takeRandomPiece();
        if(gc->getBagPlayerA()->isEmpty()){
            return NoPiece;
        }
    }
    else if(team == TeamB && team == currentPlayer){
        if(gc->getPlacableCellsForNewPiece(currentPlayer).isEmpty()){
            return NoPiece;
        }
        if(firstTurnDone){
            ms->updateBoard(this->gc);
            if(ms->drawPieceCheck(team).isEmpty()){
                return NoPiece;
            }
        }
        newPiece = gc->getBagPlayerB()->takeRandomPiece();
        if(gc->getBagPlayerB()->isEmpty()){
            return NoPiece;
        }
    }
    else{
        return NoPiece;
    }
    return newPiece->type();
}
bool GameLogic::getTurnRequest(int srcX, int srcY, int dstX, int dstY){


    Figure* selectedPiece = gc->getCell(srcX, srcY)->getFigure();


    bool valid = false;
    bool movement = false;
    bool attack = false;
    bool cmd = false;

    // Check if the list contains the specified move type and coordinates
    for (const auto& move : this->result.validMoves) {
        int moveRow = std::get<1>(move);
        int moveCol = std::get<2>(move);

        if ((moveRow == dstX && moveCol == dstY) &&
            (std::get<0>(move) == Move || std::get<0>(move) == Jump || std::get<0>(move) == Slide || std::get<0>(move) == JumpSlide)) {
            movement = true;
            break;
        }

        if((moveRow == dstX && moveCol == dstY) && (std::get<0>(move) == Strike)){
            attack = true;
            break;
        }

        if((moveRow == dstX && moveCol == dstY) && (std::get<0>(move) == CommandFrom)){
            cmd = true;
            break;
        }

    }

    if(movement){
        moveFigure(srcX, srcY, dstX, dstY);
        valid = true;

    }
    else if(attack){
        killFigure(dstX,dstY);
        valid = true;
        striked = true;
    }
    else if(cmd){
        secondCoordX = dstX;
        secondCoordY = dstY;
        commandRequest = true;
        dm->printMoves(this->result, true);
        return false;
    }

    if(valid){
        selectedPiece->flip();
        if(this->isGuard()){
            qDebug() << "isGuard!";
            this->currentPlayer == TeamA ? gc->guardPlayerB = true : gc->guardPlayerA = true;
            MoveSimulator *ms = new MoveSimulator();
            if(ms->endGameCheck(gc, this->currentPlayer == TeamA ? TeamB : TeamA)){
              qDebug() << "GAME OVER!";
            }

        }
        else{
            this->currentPlayer == TeamA ? gc->guardPlayerB = false : gc->guardPlayerA = false;
        }
        switchTurn();
    }

    return valid;
}

void GameLogic::moveFigure(int srcX, int srcY, int dstX, int dstY){
    Figure* selectedPiece = gc->getCell(srcX, srcY)->getFigure();

    if(gc->getCell(dstX, dstY)->hasFigure() && gc->getCell(dstX, dstY)->getFigure()->getTeam() != currentPlayer){
        killFigure(dstX, dstY);
    }

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

bool GameLogic::isGuard(){
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            Cell* c = gc->getCell(row, col);
            if(c->hasFigure()){
                Figure* f = c->getFigure();
                if(f->getTeam() == currentPlayer){
                    Cell* dukecell = gc->getPlayerDuke(currentPlayer == TeamA ? TeamB : TeamA);
                    if(f->isValidMove(gc->getCells(), dukecell->getRow(), dukecell->getCol())){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


