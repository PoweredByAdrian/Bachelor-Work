#ifndef CELL_H
#define CELL_H

#include <QObject>
#include "figure.h"

class Cell : public QObject
{
    Q_OBJECT
public:
    explicit Cell(QObject *parent = nullptr);

    Figure *getFigure() const;
    void setFigure(Figure *figure);

    bool hasFigure() const;

    Figure::PieceType getFigureType() const;

signals:
    void figureStateChanged();

private:
    Figure *figure;


};

#endif // CELL_H
