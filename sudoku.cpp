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
    for (unsigned short i = 0; i < boardSize; ++i) {
        if (i % subGridSize == 0 && i != 0) {
            std::cout << "------+-------+------\n"; // Separator between subgrids
        }

        for (unsigned short j = 0; j < boardSize; ++j) {
            if (j % subGridSize == 0 && j != 0) {
                std::cout << "| "; // Separator between subgrid columns
            }
            if (board[i][j] == 0) {
                std::cout << ". "; // Represent empty cells with a dot
            } else {
                std::cout << board[i][j] << " ";
            }
        }
        std::cout << "\n";
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
}

// Prompts user if they want to provide a board
bool Sudoku::askIfUserProvidesBoard() const {
    std::cout << "Do you want to provide a Sudoku board? (1 = Yes, 0 = No): ";
    unsigned int response;
    while (true) {
        std::cin >> response;
        if (std::cin.fail() || response > 1) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter 1 (Yes) or 0 (No): ";
        } else {
            return response == 1;
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
        if (root * root != inputSize) {
            std::cout << "The size must be a perfect square. Try again.\n";
            continue;
        }

        boardSize = inputSize;
        subGridSize = root;
        break;
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
        int placedNumbers = 0; // Track numbers placed in the current row

        while (placedNumbers < rowNumberCounts[i]) {
            int col = std::rand() % boardSize; // Random column
            int num = std::rand() % boardSize + 1; // Random number (1 to boardSize)

            int subgridIndex = (i / subGridSize) * subGridSize + col / subGridSize;

            // Check if the number can be placed in the cell
            if (!usedNumbers[num - 1] && columnFlags[col][num - 1] && subGridFlags[subgridIndex][num - 1] && board[i][col] == 0) {
                board[i][col] = num;
                usedNumbers[num - 1] = true;
                columnFlags[col][num - 1] = false;
                subGridFlags[subgridIndex][num - 1] = false;
                ++placedNumbers; // Increment the count of placed numbers
            }
        }
    }

}

// Prompts user to input row counts
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

// Validates the provided Sudoku board
void Sudoku::validateUserBoard() {
    for (size_t i = 0; i < boardSize; ++i) {
        for (size_t j = 0; j < boardSize; ++j) {
            int num = board[i][j];
            if (num > 0) {
                if (!columnFlags[j][num - 1] || !subGridFlags[(i / subGridSize) * subGridSize + j / subGridSize][num - 1]) {
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

// Asks user if they want to provide row counts
bool Sudoku::askIfUserProvidesRowCounts() const {
    std::cout << "Do you want to provide row counts? (1 = Yes, 0 = No): ";
    unsigned int response;
    while (true) {
        std::cin >> response;
        if (std::cin.fail() || response > 1) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter 1 (Yes) or 0 (No): ";
        } else {
            return response == 1;
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