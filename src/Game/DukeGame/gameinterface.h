// gameinterface.h
#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include "figurebag.h"
#include "cell.h"
#include "gameconfigure.h"
#include <QObject>

class GameInterface : public QObject
{
    Q_OBJECT

public:
    explicit GameInterface(QObject *parent = nullptr);
    void setupGame(); // Initialize game components and connections

public slots:
    void handleCellClick(int row, int col);
    void handlePlayerButtonClick(figureBag *bag);
    // Add more slots for other interactions

private:
    GameConfigure* gc;
};

#endif // GAMEINTERFACE_H
