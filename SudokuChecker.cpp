//
//  SudokuChecker.cpp
//  sudoku generator
//
//  Created by yuvraj
//


#include <vector>
#include <cmath>
#include "DancingLinks.cpp"

class SudokuChecker {
public:
    void solveSudoku(std::vector<std::vector<char>>& board) {
        const auto size = board.size();
        int cnt = 0;
        for (int i = 0; i < size; i ++) {
            for (int j = 0; j < size; j ++) {
                if (board[i][j] == '.') cnt ++;
            }
        }
        int idx = 0;
        int row[size * size * size], col[size * size * size], pl[size * size * size];
        std::vector<std::vector<bool>> rec(cnt * (size - 1) + size * size, std::vector<bool>(size * size * 4));
        for (int i = 0; i < size; i ++) {
            for (int j = 0; j < size; j ++) {
                int a = 0, b = int(size - 1);
                if (board[i][j] != '.') {
                    if (board[i][j] >= 'A' && board[i][j] <= 'Z') a = b = board[i][j] - 'B' + 10;
                    else a = b = board[i][j] - '1';
                }
                for (int k = a; k <= b; k ++) {
                    rec[idx][i * size + j] = true;
                    rec[idx][size * size + i * size + k] = true;
                    rec[idx][size * size * 2 + j * size + k] = true;
                    rec[idx][size * size * 3 + (i / (int)sqrt(size) * (int)sqrt(size) + j / (int)sqrt(size)) * size + k] = true;
                    row[idx + 1] = i;
                    col[idx + 1] = j;
                    pl[idx + 1] = k;
                    idx ++;
                }
            }
        }
        DancingLinks d(rec, int(size * size * size * 4));
        d.solve();
        for (auto x : d.get_one_solution()) {
            if (pl[x] < 9) board[row[x]][col[x]] = pl[x] + '1';
            else board[row[x]][col[x]] = pl[x] + 'B' - 10;
        }
    }

    bool isValidSudoku(std::vector<std::vector<char>>& board, bool isCompleted = true) {
        const unsigned long size = board.size(), cellSize = sqrt(size);
        
        std::vector<std::vector<int>> rows(size, std::vector<int>(size, 0));
        std::vector<std::vector<int>> columns(size, std::vector<int>(size, 0));
        std::vector<std::vector<std::vector<int>>> subboxes(cellSize, std::vector<std::vector<int>>(cellSize, std::vector<int>(size, 0)));
        
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                char c = board[i][j];
                if (c == '.') {
                    if (isCompleted) { return false; }
                    continue;
                }
                int index = c - '0' - 1;
                if (c >= 'A' && c <= 'Z') {
                    index = c - 'A' + 9;
                } else if (c == '0') {
                    index = 35;
                }
                rows[i][index]++;
                columns[j][index]++;
                subboxes[i / cellSize][j / cellSize][index]++;
                if (rows[i][index] > 1 || columns[j][index] > 1 || subboxes[i / cellSize][j / cellSize][index] > 1) {
                    return false;
                }
            }
        }
        return true;
    }
};
