//
//  main.cpp
//  sudoku generator
//
//  Created by YUVRAJ
//

#include <iostream>
#include "SudokuGenerator.cpp"

void print(const std::vector<std::vector<char>> &board) {
    const int size = sqrt(board.size());
    for (auto rowIdx = 0; rowIdx < board.size(); ++rowIdx) {
        if (rowIdx && rowIdx % size == 0) {
            for (int i = 0; i < size * size + size - 1; ++i) {
                std::cout << "-" << " ";
            }
            std::cout << "\n";
        }
        for (auto colIdx = 0; colIdx < board[rowIdx].size(); ++colIdx) {
            if (colIdx && colIdx % size == 0) { std::cout << "|" << " "; }
            std::cout << board[rowIdx][colIdx] << " ";
        }
        std::cout << "\n";
    }
}

int main(int argc, const char * argv[]) {
    int size, removeCellCount;
    double maxGenerationTime;
    std::cout << "Enter sudoku size(choose 2, 3 or 4) :(eg. 3)\n";
    std::cin >> size;
    
    std::cout << "Enter sudoku remove count:(eg. 60)\n";
    std::cin >> removeCellCount;
    
    std::cout << "Enter max generation time:(eg. 3)\n";
    std::cin >> maxGenerationTime;
    
    auto sudokuPair = SudokuGenerator(size).sudoku(removeCellCount, maxGenerationTime);
    auto sudoku = sudokuPair.first, answer = sudokuPair.second;
    int spaceCellCount = 0;
    for (auto row: sudoku) {
        for (char c: row) {
            if (c == '.') { spaceCellCount++; }
        }
    }
    std::cout << "Remove " << spaceCellCount << " Cells\n";
    std::cout << "Remain " << pow(size, 4) - spaceCellCount << " Cells\n";
    
    std::cout << "Sudoku Board:\n";
    print(sudoku);
    std::cout << "\nSudoku Answer:\n";
    print(answer);
    return 0;
}
