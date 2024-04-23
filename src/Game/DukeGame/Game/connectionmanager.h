#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include <QPushButton>
#include "gamelogic.h"
#include "mainwindow.h"

#include "../Algorithms/ExpMinMax/Expectiminimax.h"
#include "../Algorithms/MCTS/mctsnode.h"


class ConnectionManager : public QObject
{
    Q_OBJECT

public:
    explicit ConnectionManager(QObject *parent = nullptr, GameLogic* gl = nullptr, MainWindow *mw = nullptr);
    void handleActionCompleted(GameState state);
    void handlePlayerSwitch(PlayerTeam team);
private slots:
    void handleGridButtonClicked(int row, int col);
    void handleBagButtonClicked(PlayerTeam team);

private:
    PlayerTeam team;
    void connectButtons();
    void connectLabels();
    QHash<QPushButton*, Cell*> buttonCellMap;
    QHash<QPushButton*, figureBag*> buttonBagMap;

    GameLogic* gl;
    MainWindow* mw;
    GameState board;

    int firstButtonRow = -1;
    int firstButtonCol = -1;
    bool waitingForSecondButton = false;


    bool firstTurn = false;

    Expectiminimax* PlayerA_AI = nullptr;
    bool useMCTS = false;
    //MCTSNode* PlayerB_AI = nullptr;

};

#endif // CONNECTIONMANAGER_H
