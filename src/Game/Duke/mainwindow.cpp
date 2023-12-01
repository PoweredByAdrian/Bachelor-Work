#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupBoard();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupBoard()
{
    // Connect the existing buttons to the slot
    connect(ui->a1, &QPushButton::clicked, this, [=]() {
        handleBoardClick(1, 1);
    });

    connect(ui->a2, &QPushButton::clicked, this, [=]() {
        handleBoardClick(1, 2);
    });

    // Repeat for other buttons...

}

void MainWindow::handleBoardClick(int row, int col)
{
    // Handle the chessboard click for the given row and column
    // You can update the game state, check for legal moves, etc.
    // For now, let's print a message to the console
    qDebug() << "Clicked on chessboard square (" << row << ", " << col << ")";
}
