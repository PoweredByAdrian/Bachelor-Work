#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include <QPushButton>
#include "cell.h"
#include "figurebag.h"


class ConnectionManager : public QObject
{
    Q_OBJECT

public:
    explicit ConnectionManager(QObject *parent = nullptr);

    void connectCellButton(Cell *cell, QPushButton *button);
    void connectPlayerButton(QPushButton *button, figureBag *bag, const QString &playerName);

signals:
    void cellClicked(int row, int col);
    void playerButtonClicked(figureBag *bag, QPushButton* clickedButton);

private slots:
    void handleCellButtonClicked();
    void handlePlayerButtonClicked();

private:
    QHash<QPushButton*, Cell*> buttonCellMap;
    QHash<QPushButton*, figureBag*> buttonBagMap;

};

#endif // CONNECTIONMANAGER_H
