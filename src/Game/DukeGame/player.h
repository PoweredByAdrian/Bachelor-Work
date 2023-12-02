#ifndef PLAYER_H
#define PLAYER_H

#include "figurebag.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

    void setPieceBag(figureBag* bag);
    figureBag* getPieceBag() const;

    Figure* getRandomPieceFromBag();

private:
    figureBag* figurebag;
signals:
};

#endif // PLAYER_H
