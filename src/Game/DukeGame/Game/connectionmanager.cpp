#include "connectionmanager.h"

class MainWindow;

ConnectionManager::ConnectionManager(QObject *parent, GameLogic* gl, MainWindow* mw)
    : QObject(parent), team(NoTeam)
{
    this->gl = gl;
    this->mw = mw;
    connectButtons();

    this->PlayerA_AI = new Expectiminimax(1, PlayerTeam::TeamA);
    //FIXME this->PlayerB_AI = new Expectiminimax(1, PlayerTeam::TeamB);

    // Set the callback function
    gl->setActionCompletedCallback([this](int X, int Y, PieceType pieceType, PlayerTeam team) {
        handleActionCompleted(X, Y, pieceType, team);
    });

    gl->setSwitchPlayerCallback([this](PlayerTeam team) {
        handlePlayerSwitch(team);
    });
}
void ConnectionManager::handleGridButtonClicked(int row, int col)
{
    qDebug() << "Grid button pressed at row:" << row << "col:" << col;

    //TODO Find where to call AI
    if(team == TeamA && this->PlayerA_AI != nullptr){
        std::pair<int, int> nullPair = std::make_pair(-1, -1);
        MoveSimulator::finalMove nextMove = PlayerA_AI->chooseMove(gl->getGC());
        if(nextMove.secondCoord == nullPair){
            this->handleBagButtonClicked(TeamA);
            gl->handleSingleCoordAction(nextMove.firstCoord.first, nextMove.firstCoord.second);
        }
        else if(nextMove.thirdCoord == nullPair){
            gl->handleSingleCoordAction(nextMove.firstCoord.first, nextMove.firstCoord.second);
            gl->handleSingleCoordAction(nextMove.secondCoord.first, nextMove.secondCoord.second);
        }

        if(this->PlayerB_AI == nullptr){
            this->PlayerB_AI = new Expectiminimax(1, PlayerTeam::TeamB);
        }

    }
    else if(team == TeamB && this->PlayerB_AI != nullptr){
        std::pair<int, int> nullPair = std::make_pair(-1, -1);
        MoveSimulator::finalMove nextMove = PlayerB_AI->chooseMove(gl->getGC());
        if(nextMove.secondCoord == nullPair){
            this->handleBagButtonClicked(TeamB);
            gl->handleSingleCoordAction(nextMove.firstCoord.first, nextMove.firstCoord.second);
        }
        else if(nextMove.thirdCoord == nullPair){
            gl->handleSingleCoordAction(nextMove.firstCoord.first, nextMove.firstCoord.second);
            gl->handleSingleCoordAction(nextMove.secondCoord.first, nextMove.secondCoord.second);
        }

    }
    else{
        // Call the function with both sets of coordinates
        if(gl->handleSingleCoordAction(row, col)){

        }
    }

}
void ConnectionManager::handleBagButtonClicked(PlayerTeam team)
{
    qDebug() << "Player button pressed for team:" << (team == PlayerTeam::TeamA ? "A" : "B");

    PieceType newPieceType = gl->getPieceGeneratedRequest(team);
    mw->updateSelectedPieceLabel(newPieceType);
}
void ConnectionManager::handlePlayerSwitch(PlayerTeam team){
    mw->switchPlayerAndResetLabels(team);

    this->team = team;
}
void ConnectionManager::handleActionCompleted(int X, int Y, PieceType pieceType, PlayerTeam team) {
    mw->setButtonText(X, Y, pieceType, team);
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
