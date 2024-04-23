// DebugManager.h
#include <QDebug>
#include <QString>
#include <QList>
#include "GameComponents/Figures/figure.h"

class DebugManager {
public:
    void printMoves(Figure::MoveResult moves, bool cmdOnly = false);

    void printMoves(QList<QPair<int, int>> moves);
};
