//
//  SudokuGenerator.cpp
//  sudoku generator
//
//  Created by yuvraj
//

#import "SudokuChecker.cpp"

#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <map>
#include <set>
#include <cmath>

class SudokuGenerator {
public:
    explicit SudokuGenerator(const unsigned long sudokuSize) :
            size(sudokuSize) {
        assert(size >= 2 && size <= 4);
        std::random_device r;
        randomEngine = std::default_random_engine(r());
        udistribution = std::uniform_int_distribution<unsigned long>(0, size * size - 1);
    }
    
    
    
    std::pair<std::vector<std::vector<char>>, std::vector<std::vector<char>>> sudoku(unsigned removeCount, double maxGenerationTime) {
        switch (size) {
            case 2: removeCount = std::min(11u, removeCount); break;
            case 3: removeCount = std::min(64u, removeCount); break;
            default: break;
        }
        std::vector<std::vector<char>> board;
        do { // Randomly Initialize Sudoku
            board = std::vector<std::vector<char>>(size * size, std::vector<char>(size * size, '.'));
            for (int i = 0; i < size; i++) {
                std::vector<char> s(size * size);
                for (int i = 0; i < size * size; i++) s[i] = digitals[i];
                std::shuffle(s.begin(), s.end(), std::default_random_engine(randomEngine));
                int cnt = 0;
                for (auto ii = i * size; ii < (i + 1) * size; ++ii) {
                    for (auto jj = i * size; jj < (i + 1) * size; ++jj) {
                        board[ii][jj] = s[cnt++];
                    }
                }
            }
            checker.solveSudoku(board);
        } while (!checker.isValidSudoku(board, true));
        
        std::vector<std::vector<char>> answer = board;
        std::pair<unsigned, std::vector<std::vector<char>>> deepestResult = {removeCount, board};
        dfs(board, removeCount, deepestResult, {time(nullptr), maxGenerationTime});
        return {deepestResult.second, answer};
    }
    
private:
    const std::string digitals = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ0";
    const unsigned long size;
    SudokuChecker checker;
    std::default_random_engine randomEngine;
    std::uniform_int_distribution<unsigned long> udistribution;
    
    bool dfs(std::vector<std::vector<char>> &board, unsigned removeCnt, std::pair<unsigned, std::vector<std::vector<char>>> &deepestBoard, const std::pair<time_t, double> &timeConditions) {
        if (removeCnt <= 0) {
            deepestBoard.first = 0;
            deepestBoard.second = board;
            return true;
        }
        if (difftime(time(nullptr), timeConditions.first) > timeConditions.second) { return false; }
        
        std::vector<std::vector<char>> copy;
        int repeatMaxCnt = board.size() * board.size(), i = 0, j = 0;
        std::map<int, std::set<int>> testedPosition;
        char origin;
        while (repeatMaxCnt--) {
            auto curTime = time(nullptr);
            if (difftime(time(nullptr), timeConditions.first) > timeConditions.second) { continue; }
            do {
                i = int(udistribution(randomEngine));
                j = int(udistribution(randomEngine));
            } while (board[i][j] == '.');
            auto st = testedPosition.find(i);
            if (st != testedPosition.end() && st->second.find(j) != st->second.end()) { continue; }
            testedPosition[i].insert(j);
            origin = board[i][j];
            bool vaild = true;
            for (int k = 0; k < size * size && vaild; k++) {
                bool flag = true;
                char c = digitals[k];
                // 
                if (board[i][j] == c) { flag = false; }
                // 
                for (int kk = 0; kk < size * size && flag; kk++) {
                    if (c == board[i][kk] || c == board[kk][j]) { flag = false; }
                }
                for (int ii = 0; ii < size && flag; ii++) {
                    for (int jj = 0; jj < size && flag; jj++) {
                        if (c == board[i / size * size + ii][j / size * size + jj]) { flag = false; }
                    }
                }
                if (!flag) { continue; }
                
                copy = board;
                copy[i][j] = c;
                checker.solveSudoku(copy);
                if (checker.isValidSudoku(copy, true)) {
                    vaild = false;
                }
            }
            if (!vaild) { continue; }
            
            board[i][j] = '.';
            if (deepestBoard.first > removeCnt - 1) {
                deepestBoard.first = removeCnt - 1;
                deepestBoard.second = board;
            }
            if (dfs(board, removeCnt - 1, deepestBoard, timeConditions)) {
                board[i][j] = origin;
                return true;
            }
        }
        return false;
    }
};
