#ifndef CELL_H
#define CELL_H

#include <QObject>
#include "figure.h"
#include <QPushButton>

class Cell : public QObject
{
    Q_OBJECT
public:
    explicit Cell(QObject *parent = nullptr, int row = NULL, int col = NULL, QPushButton *button = nullptr);

    Figure *getFigure() const;
    void setFigure(Figure *figure);
    bool hasFigure() const;
    PieceType getFigureType() const;
    int getRow() const {return x;}
    int getCol() const {return y;};
    QPushButton *getButton() const {return button;};

signals:
    void figureStateChanged();

private:
    int x;
    int y;
    Figure *figure;
    QPushButton *button;

};

#endif // CELL_H
