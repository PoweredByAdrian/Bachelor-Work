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

/*public slots:
    void handleCellClick(int row, int col);
    void handlePlayerButtonClick(figureBag *bag);*/
    // Add more slots for other interactions

private:
    MainWindow mainWindow;
    GameLogic* gl;
    ConnectionManager* cm;
};

#endif // GAMEINTERFACE_H
