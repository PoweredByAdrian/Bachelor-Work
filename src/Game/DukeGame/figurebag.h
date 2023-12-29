#ifndef FIGUREBAG_H
#define FIGUREBAG_H

#include <QList>
#include "figure.h"


class figureBag
{
public:
    explicit figureBag(PlayerTeam playerteam);

    Figure* takeRandomPiece();

    // Check if the bag is empty
    bool isEmpty() const;

private:
    QList<Figure*> pieces;
    // Initialize the bag with pieces
    void initialize();
    PlayerTeam team;
    bool dukeDelivered;

    char footmanCounter = 0;
};

#endif // FIGUREBAG_H
