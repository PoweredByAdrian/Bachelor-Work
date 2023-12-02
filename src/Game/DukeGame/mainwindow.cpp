#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , boardLayout(new QGridLayout)
    , selectedFigure(nullptr)
{
    ui->setupUi(this);
    setupBoard();
    setupPlayers();
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

    // Set spacing and margins to 0 to eliminate gaps
    boardLayout->setSpacing(0);
    boardLayout->setContentsMargins(0, 0, 0, 0);

    // Create cells and buttons dynamically
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            Cell *cell = new Cell(this);
            cells[row][col] = cell;

            // Create a button to represent the cell visually
            QPushButton *button = new QPushButton(this);

            // Set the size policy to make the button fill the available space
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            // Set a border style to create a grid-like appearance
            button->setStyleSheet("border: 1px solid black;");



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

            // Place initial figures on the sides
            if ((row == 0 && col == 0) || (row == 5 && col == 5)) {
                p_Duke *duke = new p_Duke(this);
                duke->setTeam((row == 0 && col == 0) ? Figure::TeamA : Figure::TeamB);
                cell->setFigure(duke);
            }


            // Set text and font properties
            button->setText(cell->hasFigure() ? "X" : "");
            button->setFont(QFont("Arial", 12, QFont::Bold));
        }
    }
}

void MainWindow::setupPlayers()
{
    // Create buttons for each player
    QPushButton *playerAButton = new QPushButton("Player A", this);
    QPushButton *playerBButton = new QPushButton("Player B", this);

    // Set vertical size policy to make the buttons fill the available vertical space
    playerAButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    playerBButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    // Connect button clicks to corresponding slots
    connect(playerAButton, &QPushButton::clicked, this, &MainWindow::handlePlayerButtonClick);
    connect(playerBButton, &QPushButton::clicked, this, &MainWindow::handlePlayerButtonClick);

    // Add buttons to the layout
    boardLayout->addWidget(playerAButton, 0, 6, 1, 1); // Adjust column span as needed
    boardLayout->addWidget(playerBButton, 5, 6, 1, 1); // Adjust column span as needed
}

void MainWindow::handlePlayerButtonClick()
{
    // Implement logic to handle player button clicks
    // For now, let's print a message to the console
    QPushButton *senderButton = qobject_cast<QPushButton *>(sender());
    if (senderButton) {
        qDebug() << "Clicked on Player Button: " << senderButton->text();
    }
}

void MainWindow::handleCellClick(int row, int col)
{
    Cell *clickedCell = cells[row][col];

    if (selectedFigure) {
        // Move the selected figure to the clicked cell
        if (!clickedCell->hasFigure()) {
            clickedCell->setFigure(selectedFigure);
            selectedFigure = nullptr;
        }
    } else {
        // Select the figure in the clicked cell (if any)
        if (clickedCell->hasFigure()) {

            selectedFigure = clickedCell->getFigure(); // Corrected line

            clickedCell->setFigure(nullptr);
        }
    }
}
