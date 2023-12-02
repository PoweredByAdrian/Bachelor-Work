#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , boardLayout(new QGridLayout)
{
    ui->setupUi(this);
    setupBoard();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete boardLayout;
}

void MainWindow::setupBoard()
{
    // Set up the layout for the chessboard
    ui->centralwidget->setLayout(boardLayout);

    // Create cells and buttons dynamically
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            Cell *cell = new Cell(this);
            cells[row][col] = cell;

            // Create a button to represent the cell visually
            QPushButton *button = new QPushButton(this);
            button->setFixedSize(50, 50); // Adjust size as needed

            // Connect the button click to a slot for handling clicks
            connect(button, &QPushButton::clicked, this, [this, row, col]() {
                handleCellClick(row, col);
            });

            // Connect the cell's signal to update the button's appearance
            connect(cell, &Cell::figureStateChanged, this, [button, cell]() {
                button->setText(cell->hasFigure() ? "X" : "");
            });

            // Add the button to the layout
            boardLayout->addWidget(button, row, col);
        }
    }
}

void MainWindow::handleCellClick(int row, int col)
{
    // Handle the cell click for the given row and column
    // Toggle the presence of a game figure on the cell
    cells[row][col]->setHasFigure(!cells[row][col]->hasFigure());
    qDebug() << "Clicked on cell (" << row << ", " << col << ")";
}
