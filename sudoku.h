#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <iostream>
#include <cmath>

class Sudoku 
{
    private:
        unsigned short size; // Size of the board (e.g., 9 for a 9x9 board)
        float root = std::sqrt(size);
        std::vector<std::vector<int>> Board; // Dynamic 2D matrix
        std::vector<std::vector<bool>> ColumnBoard;
        std::vector<std::vector<bool>> SquareBoard;
        void Generator(std::vector<int> v = std::vector<int>(1,0));

    public:
        // Constructor to initialize the board size and allocate memory
        Sudoku(unsigned short boardSize);

        // Function to display the Sudoku board
        void displayBoard() const;

        // Other functions like solving, validating, etc. can be added later
};

#endif
