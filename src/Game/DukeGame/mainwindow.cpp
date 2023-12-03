#include "mainwindow.h"
#include "./ui_mainwindow.h"

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
            connect(cell, &Cell::figureStateChanged, this, [button, cell, this]() {
                setButtonText(cell, button);
            });

            // Add the button to the layout
            boardLayout->addWidget(button, row, col);

            // Place initial figures on the sides
            if (row == 0 && col == 0) {
                Figure *dukeA = Figure::createFigure(Figure::TeamA, Figure::Duke, this);
                cell->setFigure(dukeA);
            }
            // Place initial figures on the sides
            if (row == 5 && col == 5) {
                Figure *dukeB = Figure::createFigure(Figure::TeamA, Figure::Duke, this)  ;
                cell->setFigure(dukeB);
            }

            setButtonText(cell, button);


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

void MainWindow::setButtonText(Cell* cell, QPushButton* button){
    // Set text and font properties
    // Set text and font properties
    if (cell->hasFigure()) {
        Figure::PieceType pieceType = cell->getFigureType();

        // Convert the PieceType enum to a string for display
        QString pieceTypeText;
        switch (pieceType) {
        case Figure::Assassin:
            pieceTypeText = "Assassin";
            break;
        case Figure::Bowman:
            pieceTypeText = "Bowman";
            break;
        case Figure::Champion:
            pieceTypeText = "Champion";
            break;
        case Figure::Dracoon:
            pieceTypeText = "Dracoon";
            break;
        case Figure::Duke:
            pieceTypeText = "Duke";
            break;
        case Figure::Footman:
            pieceTypeText = "Footman";
            break;
        case Figure::General:
            pieceTypeText = "General";
            break;
        case Figure::Knight:
            pieceTypeText = "Knight";
            break;
        case Figure::Marshall:
            pieceTypeText = "Marshall";
            break;
        case Figure::Pikeman:
            pieceTypeText = "Pikeman";
            break;
        case Figure::Priest:
            pieceTypeText = "Priest";
            break;
        case Figure::Seer:
            pieceTypeText = "Seer";
            break;
        case Figure::Wizard:
            pieceTypeText = "Wizard";
            break;
        default:
            pieceTypeText = "U";
            break;
        }
        button->setText(pieceTypeText);
    } else {
        button->setText("");
    }
    button->setFont(QFont("Arial", 12, QFont::Bold));
}
