#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <iomanip>

class Sudoku {
private:
    std::vector<std::vector<int>> board;
    std::vector<std::vector<bool>> columnFlags;
    std::vector<std::vector<bool>> subGridFlags;
    std::vector<int> rowNumberCounts;
    size_t boardSize;
    size_t subGridSize;

    void validateBoardSize();
    bool askIfUserProvidesBoard() const;
    void promptUserForBoard();
    void generateBoard();
    void validateUserBoard();
    bool askIfUserProvidesRowCounts() const;
    void promptUserForRowCounts();
    void generateRandomRowCounts();
    void displayColumnFlags() const;
    void displaySubGridFlags() const;
    bool findEmptyCell(int& row, int& col) const;
    bool isValidPlacement(int row, int col, int num) const;

public:
    Sudoku();
    void startGame();
    void displayBoard() const;
    bool solve();
};

#endif