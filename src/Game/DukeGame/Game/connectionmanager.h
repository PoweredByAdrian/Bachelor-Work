#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include <QPushButton>
#include "gamelogic.h"
#include "mainwindow.h"

#include "../Algorithms/ExpMinMax/Expectiminimax.h"


class ConnectionManager : public QObject
{
    Q_OBJECT

public:
    explicit ConnectionManager(QObject *parent = nullptr, GameLogic* gl = nullptr, MainWindow *mw = nullptr);
    void handleActionCompleted(int X, int Y, PieceType pieceType, PlayerTeam team);
    void handlePlayerSwitch(PlayerTeam team);
private slots:
    void handleGridButtonClicked(int row, int col);
    void handleBagButtonClicked(PlayerTeam team);

private:
    void cellStateChanged(int row, int col, PieceType type, PlayerTeam team);
    PlayerTeam team;
    void connectButtons();
    void connectLabels();
    QHash<QPushButton*, Cell*> buttonCellMap;
    QHash<QPushButton*, figureBag*> buttonBagMap;

    GameLogic* gl;
    MainWindow* mw;

    int firstButtonRow = -1;
    int firstButtonCol = -1;
    bool waitingForSecondButton = false;




    Expectiminimax* PlayerA_AI;
    Expectiminimax* PlayerB_AI;

};

#endif // CONNECTIONMANAGER_H