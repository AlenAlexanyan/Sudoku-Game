#include "sudoku.h"


Sudoku::Sudoku(unsigned short boardSize): size(boardSize) {
    if (root - int(root) > 0){
        std::cout << "Invalid number";
    }
    Board.resize(size, std::vector<int>(size, 0));
    ColumnBoard.resize(size, std::vector<bool>(size, true));
    SquareBoard.resize(size, std::vector<bool>(size, true));
}

// Function to display the current Sudoku board
void Sudoku::displayBoard() const 
{
    for (const auto& row : Board) 
    {
        for (const auto& cell : row) 
        {
            std::cout << (cell == 0 ? "." : std::to_string(cell)) << " ";
        }
        std::cout << std::endl;
    }
}

void Sudoku::Generator(std::vector<int> v) {

}