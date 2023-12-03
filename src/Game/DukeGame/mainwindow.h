#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include "cell.h"
#include "figure.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleCellClick(int row, int col);
    void handlePlayerButtonClick();

private:
    Ui::MainWindow *ui;
    QGridLayout *boardLayout;
    Cell *cells[6][6];
    Figure *selectedFigure;

    void setButtonText(Cell* cell, QPushButton* button);

    void setupBoard();
    void setupPlayers();
};
#endif // MAINWINDOW_H
