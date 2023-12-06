#include "gameinterface.h"

GameInterface::GameInterface(QObject *parent)
{
    gc = new GameConfigure();

    gc->setupBoard();
}
