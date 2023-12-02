#ifndef CELL_H
#define CELL_H

#include <QObject>

class Cell : public QObject
{
    Q_OBJECT
public:
    explicit Cell(QObject *parent = nullptr);

    bool hasFigure() const {return hasFigureOnCell; }
    void setHasFigure(bool hasFigure);

signals:
    void figureStateChanged(bool hasFigure);

private:
    bool hasFigureOnCell;

};

#endif // CELL_H
