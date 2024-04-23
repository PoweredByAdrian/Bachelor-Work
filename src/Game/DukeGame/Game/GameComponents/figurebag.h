#ifndef FIGUREBAG_H
#define FIGUREBAG_H

#include <QList>
#include "Figures/figure.h"


class figureBag
{
public:
    explicit figureBag(PlayerTeam playerteam);

    Figure* takeRandomPiece();

    // Check if the bag is empty
    bool isEmpty() const;

    std::vector<PieceType>piecesInBag();

private:
    QList<Figure*> pieces;
    // Initialize the bag with pieces
    void initialize();
    PlayerTeam team;
    bool dukeDelivered;

    char footmanCounter = 0;
};

#endif // FIGUREBAG_H
