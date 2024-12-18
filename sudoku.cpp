#include "sudoku.h"
#include <string>

Sudoku::Sudoku() {
    CheckingSize();
    Board.resize(size, std::vector<int>(size));
    ColumnBoard.resize(size, std::vector<bool>(size, true));
    SquareBoard.resize(size, std::vector<bool>(size, true));
    NumberCount.resize(size);
    Play();
}

// Function to display the current Sudoku board
void Sudoku::displayBoard() const
{
    if (!IsGiveMeBoard()) {
        for (size_t i = 0; i < size; ++i)
        {
            for (size_t j = 0; j < size; ++j)
            {
                std::cout << Board[i][j] << '\t';
            }
            std::cout << '\n';
        }
    }
}

void Sudoku::Play()
{
    if (IsGiveMeBoard())
    {
        CheckingBoard();
    }else {
        Generator();
    }
    
    displayBoard();
}

void Sudoku::Generator() {
    if (IsSelectNumberCount()) {
        GiveMeNumberCount();
    }else {
        GenerateNumberCountRow();
    }

    for (size_t i = 0; i < size; i++) {
        std::vector<int> numbers(size, true);
        for (size_t j = 0; j < ColumnBoard[i]; j++) {
            while (true) {
                int index = std::rand() % (size) + 1;
                int el = std::rand() % (size);
                if (numbers[el - 1] && ColumnBoard[el - 1][index] && SquareBoard[3 * (i / 3) + index / 3][el - 1]){
                    break;
                }
            }
        }
    }
}

bool Sudoku::IsSelectNumberCount() const
{
    if (IsGiveMeBoard())
    {
        NumberCount.clear();
        return false;
    }
    std::cout << "Do you want choose count of numbers\n
        If you want choose click 1\n
            Otherwise click 0\n ";
        unsigned ans;
    while (true)
    {
        std::cin >> ans;
        if (ans > 1)
        {
            std::cout << "Please click only 1 or 0\n";
        }

        return ans;
    }
}

bool Sudoku::IsGiveMeBoard() const
{
    std::cout << "Do you give me sudoku board or I generate\n
        If you give me click 1\n
            otherwise click 0\n ";
        unsigned int ans;
    while (true)
    {
        std::cin >> ans;
        if (ans > 1)
        {
            std::cout << "Please click only 1 or 0\n";
        }
        return ans;
    }
}

void Sudoku::GiveMeBoard()
{
    std::cout << "Write your board's numbers\n";
    for (size_t i = 0; i < size; ++i)
    {
        std::vector<int> CheckingRow(size, true);
        for (size_t j = 0; j < size; ++j)
        {
            unsigned short num;
            std::cin >> num;
            if (typeid(num) != typeid(int) && num > size && num < 0 && CheckingBoard[num])
            {
                std::cout << "Write only valid numbers\n";
                GiveMeBoard();
            }
            CheckingBoard[num] = false;
            Board[i][j] = num;
        }
        std::cout << '\n';
    }
}

void Sudoku::GiveMeNumberCount()
{
    std::cout << "Write every row's numbers count\n";
    for (size_t i = 0; i < size; i++)
    {
        unsigned short num;
        std::cin >> num;
        if (typeid(num) != typeid(num) && num > size && num < 0)
        {
            std::cout << "Write only valid numbers\n";
            GiveMeNumberCount();
        }
        NumberCount[i] = num;
    }
}

void Sudoku::CheckingSize()
{
    int boardSize;
    while (true)
    {
        std::cin >> boardSize;
        if (std::sqrt(boarSize) > int(std::sqrt(boarSize)) || typeid(boardSize) != typeid(int))
        {
            std::cout << "Give me valid size\n";
        }
        size = boardSize;
        root = std::sqrt(size);
        return;
    }
}

void Sudoku::CheckingBoard()
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (Board[i][j] > 0)
            {
                if (ColumnBoard[Board[i][j] - 1][j])
                {
                    ColumnBoard[Board[i][j] - 1][j] = false;
                }
                else
                {
                    std::cout << "It's invalid board.\nPlease give me another board\n";
                    GiveMeBoard();
                }
                if (SquareBoard[root * (i / 3) + j / 3][Board[i][j] - 1])
                {
                    SquareBoard[root * (i / 3) + j / 3][Board[i][j] - 1] = false;
                }
                else
                {
                    std::cout << "It's invalid board.\nPlease give me another board\n";
                    GiveMeBoard();
                }
            }
        }
    }
}

void Sudoku::GenerateNumberCountRow() {
    for (size_t i = 0; i < size; i++) {
        NumberCount[i] = std::rand() % (size + 1);
    }
}
