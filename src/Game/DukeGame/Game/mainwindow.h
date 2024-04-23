#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>


#include <QLabel>
#include "enums.h"
#include "GameComponents/GameState.h"

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

    void updateUI(GameState gamestate);

    QPushButton *getGridButton(int row, int col);
    QPushButton *getPlayerAButton(){return this->playerAButton;}
    QPushButton *getPlayerBButton(){return this->playerBButton;}




    void updateSelectedPieceLabel(PieceType pieceType);

private:
    void setButtonText(int row, int col, PieceType type, PlayerTeam team,  bool flipped);

    void switchPlayerAndResetLabels(PlayerTeam currTeam);

    void setupBoard();
    void setupPlayers();

    Ui::MainWindow *ui;
    QGridLayout *boardLayout;

    QLabel *selectedPlayerLabel;
    QLabel *selectedPieceLabelPlayerA;
    QLabel *selectedPieceLabelPlayerB;

    QLabel* playerAPiecesLabel;
    QLabel* playerBPiecesLabel;

    QPushButton *playerAButton;
    QPushButton *playerBButton;

    QString pieceTypeToString(PieceType type);

    void updatePlayerBag(PlayerTeam team, const std::vector<PieceType>& bag);

    PlayerTeam currentPlayer;
};
#endif // MAINWINDOW_H





















