#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include <QPushButton>
#include "gamelogic.h"
#include "mainwindow.h"


class ConnectionManager : public QObject
{
    Q_OBJECT

public:
    explicit ConnectionManager(QObject *parent = nullptr, GameLogic* gl = nullptr, MainWindow *mw = nullptr);
signals:
    void cellStateChanged(int row, int col, PieceType type, PlayerTeam team);
private slots:
    void handleGridButtonClicked(int row, int col);
    void handleBatgButtonClicked(PlayerTeam team);
private:
    QHash<QPushButton*, Cell*> buttonCellMap;
    QHash<QPushButton*, figureBag*> buttonBagMap;

    GameLogic* gl;
    MainWindow* mw;
};

#endif // CONNECTIONMANAGER_H
