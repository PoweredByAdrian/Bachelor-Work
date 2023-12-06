#include "connectionmanager.h"

class MainWindow;

ConnectionManager::ConnectionManager(QObject *parent)
    : QObject(parent)
{
}

void ConnectionManager::connectCellButton(Cell *cell, QPushButton *button)
{
    buttonCellMap.insert(button, cell);
    connect(button, &QPushButton::clicked, this, &ConnectionManager::handleCellButtonClicked);
}

void ConnectionManager::connectPlayerButton(QPushButton *button, figureBag *bag, const QString &playerName)
{
    buttonBagMap.insert(button, bag);
    connect(button, &QPushButton::clicked, this, &ConnectionManager::handlePlayerButtonClicked);
}

void ConnectionManager::handleCellButtonClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (clickedButton && buttonCellMap.contains(clickedButton)) {
        Cell *clickedCell = buttonCellMap.value(clickedButton);
        emit cellClicked(clickedCell->getRow(), clickedCell->getCol());
    }
}

void ConnectionManager::handlePlayerButtonClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (clickedButton && buttonBagMap.contains(clickedButton)) {
        figureBag *bag = buttonBagMap.value(clickedButton);
        emit playerButtonClicked(bag, clickedButton);
    }
}


