#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include "cell.h"
#include "figure.h"
#include "figurebag.h"
#include <QLabel>
#include "connectionmanager.h"
#include "enums.h"
#include "gameconfigure.h"

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
    void handlePlayerButtonClick(figureBag *bag, QPushButton* clickedButton);
    void handleCellFigureStateChanged();

private:
    void setupBoard();
    void setupPlayers();

    void setButtonText(Cell* cell, QPushButton* button);
    Ui::MainWindow *ui;
    QGridLayout *boardLayout;
    Figure *selectedFigure;




    QLabel *selectedPlayerLabel;
    QLabel *selectedPieceLabelPlayerA;
    QLabel *selectedPieceLabelPlayerB;

    QString pieceTypeToString(PieceType type);

    ConnectionManager *connectionManager;


    PlayerTeam currentPlayer;
    GameConfigure* gc;
};
#endif // MAINWINDOW_H





















