// gameinterface.h
#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H


#include "mainwindow.h"
#include "gamelogic.h"
#include "connectionmanager.h"
#include <QObject>

class GameInterface : public QObject
{
    Q_OBJECT

public:
    explicit GameInterface(QObject *parent = nullptr);
    void startGame();

private:
    MainWindow mw;
    GameLogic* gl;
    ConnectionManager* cm;
};

#endif // GAMEINTERFACE_H
