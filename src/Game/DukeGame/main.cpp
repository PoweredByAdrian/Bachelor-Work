#include "Game\gameinterface.h"  // Include the declaration of GameInterface

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameInterface gameInterface;  // Create an instance of GameInterface
    gameInterface.startGame();    // Start the game using GameInterface
    return a.exec();
}
