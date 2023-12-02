#ifndef FIGUREBAG_H
#define FIGUREBAG_H

#include <QList>
#include "figure.h"

class figureBag
{
public:
    figureBag();

    void setPieces(QList<Figure*> pieces);
    Figure* takeRandomPiece();

private:
    QList<Figure*> pieces;
};

#endif // FIGUREBAG_H
