// DebugManager.h
#include <QDebug>
#include <QString>
#include <QList>
#include "figure.h"

class DebugManager {
public:
    void printMoves(Figure::MoveResult moves, bool cmdOnly = false);

};
