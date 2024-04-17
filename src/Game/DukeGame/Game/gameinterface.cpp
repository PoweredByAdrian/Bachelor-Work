#include "gameinterface.h"

GameInterface::GameInterface(QObject *parent)
{

}

void GameInterface::startGame() {
    // Start the game logic, manage UI interactions, etc.
    mw.show();  // Show the main window
    gl = new GameLogic();
    cm = new ConnectionManager(this, gl, &mw);
}
