#ifndef ACTION_H
#define ACTION_H

#include "../../Game/enums.h"
#include <qobject.h>

struct Action {
    MoveTypes moveType;
    QPair<int, int> currentPosition;
    QPair<int, int> nextPosition;
    QPair<int, int> cmdTo = std::make_pair(-1,-1);
};


#endif // ACTION_H
