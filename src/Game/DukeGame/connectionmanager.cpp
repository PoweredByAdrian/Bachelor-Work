#include "connectionmanager.h"

class MainWindow;

ConnectionManager::ConnectionManager(QObject *parent, GameLogic* gl, MainWindow* mw)
    : QObject(parent)
{
    this->gl = gl;
    this->mw = mw;
    connectButtons();
}
void ConnectionManager::handleGridButtonClicked(int row, int col)
{
    qDebug() << "Grid button pressed at row:" << row << "col:" << col;

    // Call the function with both sets of coordinates
    gl->handleSingleCoordAction(row, col, TeamA);
}
void ConnectionManager::handleBagButtonClicked(PlayerTeam team)
{
    qDebug() << "Player button pressed for team:" << (team == PlayerTeam::TeamA ? "A" : "B");

    gl->getPieceGeneratedRequest(team);
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

    // Connect cellStateChanged to setButtonText
    connect(this, &ConnectionManager::cellStateChanged, mw, &MainWindow::setButtonText);
}
