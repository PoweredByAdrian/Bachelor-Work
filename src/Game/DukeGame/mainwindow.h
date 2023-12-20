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

public slots:
    void setButtonText(int row, int col, PieceType type, PlayerTeam team);
signals:
    void gridButtonPressed(int row, int col);
    void bagButtonPressed(PlayerTeam team);
private:
    void setupBoard();
    void setupPlayers();

    Ui::MainWindow *ui;
    QGridLayout *boardLayout;

    QLabel *selectedPlayerLabel;
    QLabel *selectedPieceLabelPlayerA;
    QLabel *selectedPieceLabelPlayerB;

    QString pieceTypeToString(PieceType type);

    PlayerTeam currentPlayer;
};
#endif // MAINWINDOW_H





















