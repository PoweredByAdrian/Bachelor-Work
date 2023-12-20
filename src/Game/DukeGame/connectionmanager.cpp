#include "connectionmanager.h"

class MainWindow;

ConnectionManager::ConnectionManager(QObject *parent, GameLogic* gl, MainWindow* mw)
    : QObject(parent)
{
    this->gl = gl;
    this->mw = mw;
}
void ConnectionManager::handleGridButtonClicked(int row, int col)
{

}
void ConnectionManager::handleBatgButtonClicked(PlayerTeam team)
{

}


