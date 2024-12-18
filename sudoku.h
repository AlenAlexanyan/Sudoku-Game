#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <iostream>
#include <cmath>

class Sudoku {
private:
    unsigned short size; // Size of the board (e.g., 9 for a 9x9 board)
    unsigned short root; 
    std::vector<std::vector<int>> Board; // Dynamic 2D matrix
    std::vector<std::vector<bool>> ColumnBoard;
    std::vector<std::vector<bool>> SquareBoard;
    std::vector<int> NumberCount;
    void Generator();
    bool IsSelectNumberCount() const; 
    bool IsGiveMeBoard() const;
    void GiveMeBoard();
    void GiveMeNumberCount();
    void CheckingSize();
    void CheckingBoard();
    void GenerateNumberCountRow();
public:
    // Constructor to initialize the board size and allocate memory
    Sudoku();

    // Function to display the Sudoku board
    void displayBoard() const;

    void Play();

    // Other functions like solving, validating, etc. can be added later
};

#endif
