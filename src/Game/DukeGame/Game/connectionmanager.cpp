#include "connectionmanager.h"
#include <chrono>

class MainWindow;

ConnectionManager::ConnectionManager(QObject *parent, GameLogic* gl, MainWindow* mw)
    : QObject(parent), team(NoTeam)
{
    this->gl = gl;
    this->mw = mw;
    connectButtons();

    //this->PlayerA_AI = new Expectiminimax(2, PlayerTeam::TeamA);


    this->useMCTS = true;
    //this->PlayerB_AI = new MCTSNode();
    //FIXME this->PlayerB_AI = new Expectiminimax(1, PlayerTeam::TeamB);

    // Set the callback function
    gl->setActionCompletedCallback([this](GameState state) {
        handleActionCompleted(state);
    });
}
void ConnectionManager::handleGridButtonClicked(int row, int col)
{
    qDebug() << "Grid button pressed at row:" << row << "col:" << col;

    std::pair<int, int> nullPair = std::make_pair(-1, -1);
    //TODO Find where to call AI
    if(team == TeamA && this->PlayerA_AI != nullptr){

        auto startTime = std::chrono::high_resolution_clock::now();


        FinalMove nextMove = PlayerA_AI->chooseMove(this->board);
        auto endTime = std::chrono::high_resolution_clock::now();

        // Calculate the duration (elapsed time)
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

        // Output the duration
        qDebug() << "Execution time: " << duration.count() << " milliseconds";


        qDebug() << "#Final move:" << nextMove.firstCoord.first << ":" << nextMove.firstCoord.second << "..." << nextMove.secondCoord.first << ":" << nextMove.secondCoord.second << "..." << nextMove.thirdCoord.first << ":" << nextMove.thirdCoord.second << "#";
        if(nextMove.secondCoord == nullPair){
            this->handleBagButtonClicked(TeamA);
            gl->handleSingleCoordAction(nextMove.firstCoord.first, nextMove.firstCoord.second);
        }
        else if(nextMove.thirdCoord == nullPair){
            gl->handleSingleCoordAction(nextMove.firstCoord.first, nextMove.firstCoord.second);
            gl->handleSingleCoordAction(nextMove.secondCoord.first, nextMove.secondCoord.second);
        }
        //TODO command


    }
    else if(team == TeamB && this->useMCTS){

        Action act;
        MCTSNode* root = new MCTSNode(this->board, act, nullptr);
        MCTSNode* selectedNode = root->bestAction();
        act = selectedNode->parentAction;

        if(act.moveType == Draw){
            this->handleBagButtonClicked(TeamB);
            gl->handleSingleCoordAction(act.currentPosition.first, act.currentPosition.second);
        }
        else if(act.cmdTo == nullPair){
            gl->handleSingleCoordAction(act.currentPosition.first, act.currentPosition.second);
            gl->handleSingleCoordAction(act.nextPosition.first, act.nextPosition.second);
        }
        //TODO command

    }
    else{
        // Call the function with both sets of coordinates
        gl->handleSingleCoordAction(row, col);
    }


}
void ConnectionManager::handleBagButtonClicked(PlayerTeam team)
{
    qDebug() << "Player button pressed for team:" << (team == PlayerTeam::TeamA ? "A" : "B");

    PieceType newPieceType = gl->getPieceGeneratedRequest(team);
    mw->updateSelectedPieceLabel(newPieceType);
}
void ConnectionManager::handleActionCompleted(GameState state) {
    this->board = state;
    this->team = state.currentPlayer;
    mw->updateUI(state);
}


void ConnectionManager::connectButtons() {


    // Connect grid buttons to handleGridButtonClicked
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            QPushButton *gridButton = mw->getGridButton(row, col);  // Assuming you have a method to get grid buttons
            connect(gridButton, &QPushButton::clicked, this, [this, row, col]() {
                handleGridButtonClicked(row, col);
            });
        }
    }

    // Connect player buttons to handleBagButtonClicked
    connect(mw->getPlayerAButton(), &QPushButton::clicked, this, [this]() {
        handleBagButtonClicked(PlayerTeam::TeamA);
    });

    connect(mw->getPlayerBButton(), &QPushButton::clicked, this, [this]() {
        handleBagButtonClicked(PlayerTeam::TeamB);
    });
}
