#include "gamelogic.h"


GameLogic::GameLogic() : newPiece(nullptr) {

    gc = new GameConfigure();

    gc->setupBoard();

    gc->setTeam(TeamA);


    //DEBUG
    dm = new DebugManager();
}


PieceType GameLogic::getPieceGeneratedRequest(PlayerTeam team){

    if(newPiece != nullptr){
        return newPiece->type();
    }

    GameState state = this->gc->getState();

    MoveSimulator *ms = new MoveSimulator();
    ms->updateBoard(state);

    QList<QPair<int, int>> moves = ms->drawPieceCheck(team);
    dm->printMoves(moves);


    if(team == TeamA && team == state.currentPlayer){
        if(moves.empty()){
            delete ms;
            return NoPiece;
        }

        if(gc->getBagPlayerA()->isEmpty()){
            delete ms;
            return NoPiece;
        }

        newPiece = gc->getBagPlayerA()->takeRandomPiece();

    }
    else if(team == TeamB && team == state.currentPlayer){
        if(moves.empty()){
            delete ms;
            return NoPiece;
        }

        if(gc->getBagPlayerB()->isEmpty()){
            delete ms;
            return NoPiece;
        }

        newPiece = gc->getBagPlayerB()->takeRandomPiece();

    }
    else{
        delete ms;
        return NoPiece;
    }
    delete ms;
    return newPiece->type();
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
    // Default return
    return false;
}
bool GameLogic::addFigure(int x, int y){

    GameState state = gc->getState();
    MoveSimulator *ms = new MoveSimulator();
    ms->updateBoard(state);

    QList<QPair<int, int>> placableCells = ms->drawPieceCheck(state.currentPlayer, false);
    QPair<int, int> targetCoord(x, y);

    delete ms;


    if(placableCells.contains(targetCoord)){

        if(newPiece->isDuke()){
            if(newPiece->getTeam() == TeamA){
                gc->updateDukeA(newPiece);
            }
            else if(newPiece->getTeam() == TeamB){
                gc->updateDukeB(newPiece);
            }
        }

        placeFigure(x, y);
        ++placedPiecesCounter;

        if(!firstTurnDone){
            // Check if the placed pieces counter reaches 3
            if (this->gc->getState().currentPlayer == TeamA){
                this->gc->firstTurnA++;
            }
            if (this->gc->getState().currentPlayer == TeamB){
                this->gc->firstTurnB++;
            }
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

        if(gc->getState().currentPlayer == TeamA){
            gc->guardPlayerB = false;
        }
        else if(gc->getState().currentPlayer == TeamB){
            gc->guardPlayerA = false;
        }

        actionCompletedCallback(gc->getState());
        return true;
    }
    else{
        return false;
    }
}

void GameLogic::firstClick(int x, int y){
    // Store the first coordinate
    if(gc->getCell(x,y)->hasFigure() && gc->getCurrentPlayer() == gc->getCell(x, y)->getFigure()->getTeam()){
        firstCoordX = x;
        firstCoordY = y;
        hasFirstCoord = true;



        MoveSimulator *ms = new MoveSimulator();
        ms->updateBoard(this->gc->getState());
        this->result = ms->simulateAndFilterMoves(x, y);

        if(result.validMoves.empty()){
            hasFirstCoord = false;
        }

        delete ms;
        //DEBUG
        //#################################
        dm->printMoves(result);
    }
}

bool GameLogic::secondClick(int x, int y){
    bool isValid = getTurnRequest(firstCoordX, firstCoordY, x, y);

    if (isValid) {

        if(gc->getState().currentPlayer == TeamA){
            gc->guardPlayerB = false;
        }
        else if(gc->getState().currentPlayer == TeamB){
            gc->guardPlayerA = false;
        }
        actionCompletedCallback(gc->getState());


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


            switchTurn();
            if(gc->getState().currentPlayer == TeamA){
                gc->guardPlayerB = false;
            }
            else if(gc->getState().currentPlayer == TeamB){
                gc->guardPlayerA = false;
            }
            actionCompletedCallback(gc->getState());

            return true;
        }

    }
    return false;
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
    }
    else if(cmd){
        secondCoordX = dstX;
        secondCoordY = dstY;
        commandRequest = true;

        //DEBUG
        dm->printMoves(this->result, true);
        return false;
    }

    if(valid){
        selectedPiece->flip();
        switchTurn();
    }

    return valid;
}

void GameLogic::moveFigure(int srcX, int srcY, int dstX, int dstY){
    Figure* selectedPiece = gc->getCell(srcX, srcY)->getFigure();

    if(gc->getCell(dstX, dstY)->hasFigure()){
        killFigure(dstX, dstY);
    }

    gc->getCell(dstX, dstY)->setFigure(selectedPiece);
    gc->getCell(srcX, srcY)->setFigure(nullptr);

    if(selectedPiece->isDuke()){
        if(selectedPiece->getTeam() == TeamA){
            gc->updateDukeA(selectedPiece);
        }
        else if(selectedPiece->getTeam() == TeamB){
            gc->updateDukeB(selectedPiece);
        }
    }
};

void GameLogic::commandFigure(int srcX, int srcY, int dstX, int dstY){

    moveFigure(srcX, srcY, dstX, dstY);

};
void GameLogic::killFigure(int row, int col){
    delete gc->getCell(row, col)->getFigure();
    gc->getCell(row, col)->setFigure(nullptr);
};


void GameLogic::placeFigure(int row, int col){
    gc->getCell(row, col)->setFigure(newPiece);
    newPiece = nullptr;
}


void GameLogic::switchTurn() {

    if(this->firstTurnDone){
        bool guard = this->isGuard();
        gc->getCurrentPlayer() == TeamA ? gc->guardPlayerB = guard : gc->guardPlayerA = guard;
    }


    // Toggle between TeamA and TeamB
    gc->setCurrentPlayer(gc->getCurrentPlayer() == PlayerTeam::TeamA ? PlayerTeam::TeamB : PlayerTeam::TeamA);

}

bool GameLogic::isGuard(){
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            Cell* c = gc->getCell(row, col);
            if(c->hasFigure()){
                Figure* f = c->getFigure();
                if(f->getTeam() == gc->getCurrentPlayer()){
                    Cell* dukecell = gc->getPlayerDuke(gc->getCurrentPlayer() == TeamA ? TeamB : TeamA)->getCell();
                    if(f->isValidMove(gc->getState(), dukecell->getRow(), dukecell->getCol())){

                        MoveSimulator* ms = new MoveSimulator();

                        bool end = ms->endGameCheck(this->gc->getState());
                        if(end){
                            if(this->gc->getState().currentPlayer == TeamA){
                                this->gc->status = A_Win;
                            }
                            else{
                                this->gc->status = B_Win;
                            }
                        }

                        delete ms;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}










void GameLogic::setActionCompletedCallback(const ActionCompletedCallback& callback) {
    actionCompletedCallback = callback;

    actionCompletedCallback(gc->getState());
}


