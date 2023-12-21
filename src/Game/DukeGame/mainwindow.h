#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>


#include <QLabel>
#include "enums.h"


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

    QPushButton *getGridButton(int row, int col);
    QPushButton *getPlayerAButton(){return this->playerAButton;}
    QPushButton *getPlayerBButton(){return this->playerBButton;}

public slots:
    void setButtonText(int row, int col, PieceType type, PlayerTeam team);
private:
    void setupBoard();
    void setupPlayers();

    Ui::MainWindow *ui;
    QGridLayout *boardLayout;

    QLabel *selectedPlayerLabel;
    QLabel *selectedPieceLabelPlayerA;
    QLabel *selectedPieceLabelPlayerB;

    QPushButton *playerAButton;
    QPushButton *playerBButton;

    QString pieceTypeToString(PieceType type);

    PlayerTeam currentPlayer;
};
#endif // MAINWINDOW_H





















