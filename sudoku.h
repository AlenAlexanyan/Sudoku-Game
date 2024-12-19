#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <iostream>
#include <cmath>
#include <limits>

class Sudoku {
private:
    unsigned short boardSize;                   // Size of the board (e.g., 9 for a 9x9 board)
    unsigned short subGridSize;                 // Root of boardSize (e.g., 3 for a 9x9 board)
    std::vector<std::vector<int>> board;        // Sudoku board (2D matrix)
    std::vector<std::vector<bool>> columnFlags; // Tracks column validity
    std::vector<std::vector<bool>> subGridFlags; // Tracks sub-grid validity
    std::vector<int> rowNumberCounts;           // Non-zero counts for each row

    void generateBoard();                       // Generates a random Sudoku board
    void promptUserForBoard();                  // Allows user to input their board
    void promptUserForRowCounts();              // Takes row-wise number counts from the user
    void validateBoardSize();                   // Validates and sets the board size
    void validateUserBoard();                   // Validates the provided Sudoku board
    void generateRandomRowCounts();             // Randomly generates row-wise number counts

    bool askIfUserProvidesBoard() const;        // Prompts if the user wants to provide a board
    bool askIfUserProvidesRowCounts() const;    // Prompts if the user wants to provide row counts

public:
    Sudoku();                                   // Constructor

    void displayBoard() const;                  // Displays the current Sudoku board
    void startGame();                           // Main game logic

    void displayColumnFlags() const; // Display the columnFlags matrix
    void displaySubGridFlags() const; // Display the subGridFlags matrix

};

#endif // SUDOKU_H