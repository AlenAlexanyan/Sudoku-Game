#include "Sudoku.h"

// Constructor
Sudoku::Sudoku() {
    validateBoardSize();
    board.resize(boardSize, std::vector<int>(boardSize, 0));
    columnFlags.resize(boardSize, std::vector<bool>(boardSize, true));
    subGridFlags.resize(boardSize, std::vector<bool>(boardSize, true));
    rowNumberCounts.resize(boardSize, 0);
    startGame();
}

// Displays the Sudoku board
void Sudoku::displayBoard() const {
    int cellWidth = 4 ; // Adjusted width for better alignment of larger numbers
    int gridSeparatorWidth = subGridSize * (cellWidth * subGridSize + subGridSize - 1) - 1;

    std::string horizontalSeparator(gridSeparatorWidth, '-');

    for (size_t i = 0; i < boardSize; ++i) {
        for (size_t j = 0; j < boardSize; ++j) {
            if (j > 0 && j % subGridSize == 0) {
                std::cout << " | "; // Vertical separator
            }
            if (board[i][j] == 0) {
                std::cout << std::setw(cellWidth - 1) << "." << " "; // Align empty cells
            } else {
                std::cout << std::setw(cellWidth - 1) << board[i][j] << " "; // Align numbers
            }
        }
        std::cout << '\n';

        // Print horizontal separator for sub-grids
        if ((i + 1) % subGridSize == 0 && i + 1 < boardSize) {
            for (int k = 0; k < subGridSize; ++k) {
                if (k > 0) std::cout << " + "; // Separator between sub-grids
                std::cout << std::string(subGridSize * cellWidth, '-'); // Sub-grid line
            }
            std::cout << '\n';
        }
    }
}

// Starts the game
void Sudoku::startGame() {
    if (askIfUserProvidesBoard()) {
        promptUserForBoard();
        validateUserBoard();
    } else {
        generateBoard();
    }

    displayBoard();
    displayColumnFlags();
    displaySubGridFlags();
    
    std::cout << "\nWould you like to solve the board? (1 = Yes, 0 = No): ";
    bool response;
    std::cin >> response;
    if (response) {
        if (solve()) {
            std::cout << "\nSolved board:\n";
            displayBoard();
        } else {
            std::cout << "\nNo solution exists!\n";
        }
    }
}

// Find empty cell
bool Sudoku::findEmptyCell(int& row, int& col) const {
    for (row = 0; row < boardSize; row++) {
        for (col = 0; col < boardSize; col++) {
            if (board[row][col] == 0) return true;
        }
    }
    return false;
}

// Check if placement is valid using existing flag system
bool Sudoku::isValidPlacement(int row, int col, int num) const {
    int subgridIndex = (row / subGridSize) * subGridSize + col / subGridSize;
    return columnFlags[col][num - 1] && subGridFlags[subgridIndex][num - 1];
}

// Solve the Sudoku using backtracking and existing validation system
bool Sudoku::solve() {
    int row, col;
    
    // If no empty cell is found, we're done
    if (!findEmptyCell(row, col)) return true;
    
    // Try digits 1 to boardSize
    for (int num = 1; num <= boardSize; num++) {
        if (isValidPlacement(row, col, num)) {
            // Make tentative assignment
            board[row][col] = num;
            
            // Update flags
            int subgridIndex = (row / subGridSize) * subGridSize + col / subGridSize;
            columnFlags[col][num - 1] = false;
            subGridFlags[subgridIndex][num - 1] = false;
            
            // Return if success
            if (solve()) return true;
            
            // If failure, unmake & try again
            board[row][col] = 0;
            
            // Reset flags
            columnFlags[col][num - 1] = true;
            subGridFlags[subgridIndex][num - 1] = true;
        }
    }
    return false;
}

// Validates board size input
void Sudoku::validateBoardSize() {
    while (true) {
        std::cout << "Enter board size (must be a perfect square, e.g., 9 for 9x9): ";
        int inputSize;
        std::cin >> inputSize;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        int root = static_cast<int>(std::sqrt(inputSize));
        if (root * root != inputSize || inputSize <= 1) {
            std::cout << "The size must be a perfect square. Try again.\n";
            continue;
        }

        boardSize = inputSize;
        subGridSize = root;
        break;
    }
}

// Prompts user if they want to provide a board
bool Sudoku::askIfUserProvidesBoard() const {
    std::cout << "Do you want to provide a Sudoku board? (1 = Yes, 0 = No): ";
    bool response;
    while (true) {
        std::cin >> response;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter 1 (Yes) or 0 (No): ";
        } else {
            return response;
        }
    }
}

// Prompts user to input the board
void Sudoku::promptUserForBoard() {
    std::cout << "Enter your Sudoku board numbers (row by row):\n";
    for (size_t i = 0; i < boardSize; ++i) {
        for (size_t j = 0; j < boardSize; ++j) {
            int num;
            std::cin >> num;

            if (num < 0 || num > boardSize) {
                std::cout << "Invalid input. Please enter a number between 0 and " << boardSize << ":\n";
                j--;
                continue;
            }
            board[i][j] = num;
        }
    }
}

// Generates a random Sudoku board
void Sudoku::generateBoard() {
    if (askIfUserProvidesRowCounts()) {
        promptUserForRowCounts();
    } else {
        generateRandomRowCounts();
    }

    for (size_t i = 0; i < boardSize; ++i) {
        std::vector<bool> usedNumbers(boardSize, false);
        int placedNumbers = 0;

        while (placedNumbers < rowNumberCounts[i]) {
            int col = std::rand() % boardSize;
            int num = std::rand() % boardSize + 1;

            int subgridIndex = (i / subGridSize) * subGridSize + col / subGridSize;

            if (!usedNumbers[num - 1] && columnFlags[col][num - 1] && 
                subGridFlags[subgridIndex][num - 1] && board[i][col] == 0) {
                board[i][col] = num;
                usedNumbers[num - 1] = true;
                columnFlags[col][num - 1] = false;
                subGridFlags[subgridIndex][num - 1] = false;
                ++placedNumbers;
            }
        }
    }
}

// Validates the provided Sudoku board
void Sudoku::validateUserBoard() {
    for (size_t i = 0; i < boardSize; ++i) {
        for (size_t j = 0; j < boardSize; ++j) {
            int num = board[i][j];
            if (num > 0) {
                if (!columnFlags[j][num - 1] || 
                    !subGridFlags[(i / subGridSize) * subGridSize + j / subGridSize][num - 1]) {
                    std::cout << "Invalid board. Please re-enter the board.\n";
                    promptUserForBoard();
                    validateUserBoard();
                    return;
                }
                columnFlags[j][num - 1] = false;
                subGridFlags[(i / subGridSize) * subGridSize + j / subGridSize][num - 1] = false;
            }
        }
    }
}

// Prompts user for row counts
void Sudoku::promptUserForRowCounts() {
    std::cout << "Enter the number of filled cells for each row:\n";
    for (size_t i = 0; i < boardSize; ++i) {
        int count;
        std::cin >> count;
        if (count < 0 || count > boardSize) {
            std::cout << "Invalid input. Please enter a number between 0 and " << boardSize << ":\n";
            --i;
            continue;
        }
        rowNumberCounts[i] = count;
    }
}

// Randomly generates row counts
void Sudoku::generateRandomRowCounts() {
    for (size_t i = 0; i < boardSize; ++i) {
        rowNumberCounts[i] = std::rand() % (boardSize + 1);
        std::cout << rowNumberCounts[i] << '\t' << '\n';
    }
}

// Asks user if they want to provide row counts
bool Sudoku::askIfUserProvidesRowCounts() const {
    std::cout << "Do you want to provide row counts? (1 = Yes, 0 = No): ";
    bool response;
    while (true) {
        std::cin >> response;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter 1 (Yes) or 0 (No): ";
        } else {
            return response;
        }
    }
}

// Displays the columnFlags matrix
void Sudoku::displayColumnFlags() const {
    std::cout << "\nColumn Flags Matrix:\n";
    for (const auto& col : columnFlags) {
        for (bool flag : col) {
            std::cout << (flag ? "T" : "F") << ' ';
        }
        std::cout << '\n';
    }
}

// Displays the subGridFlags matrix
void Sudoku::displaySubGridFlags() const {
    std::cout << "\nSub-grid Flags Matrix:\n";
    for (const auto& grid : subGridFlags) {
        for (bool flag : grid) {
            std::cout << (flag ? "T" : "F") << ' ';
        }
        std::cout << '\n';
    }
}