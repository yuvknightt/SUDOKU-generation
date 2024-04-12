//
//  DancingLinks.cpp
//  sudoku generator
//
//  Created by yuvraj
//

#include <vector>

class DancingLinks {
public:
    explicit DancingLinks(const std::vector<std::vector<bool>> &_matrix,  int _max_nodes) :
            cols(int(_matrix[0].size())),
            data(std::vector<Node>(_max_nodes)),
            col_size(std::vector<int>(_matrix[0].size() + 1)),
            free_idx(cols + 1) {
        for (int i = 0; i <= cols; i ++) {
            data[i].left = i - 1;
            data[i].right = i + 1;
            data[i].up = data[i].down = i;
        }
        data[0].left = cols;
        data[cols].right = 0;
        _init_with_matrix(_matrix);
    }

    ~DancingLinks() = default;

    bool solve() {return _solve();}

    std::vector<int> get_one_solution() const {return one_solution;}

    
private:

    class Node {
    public:
        int left, right, down, up;
        int col, row;
    };

    int cols;
    std::vector<Node> data;
    std::vector<int> col_size;
    int free_idx;
    std::vector<int> one_solution;

    void _insert(int &head, int &tail, int x, int y) {
        data[free_idx].col = y;
        data[free_idx].row = x;
        data[free_idx].left = tail;
        data[free_idx].right = head;
        data[free_idx].up = y;
        data[free_idx].down = data[y].down;
        data[data[free_idx].left].right = free_idx;
        data[data[free_idx].right].left = free_idx;
        data[data[free_idx].up].down = free_idx;
        data[data[free_idx].down].up = free_idx;
        col_size[y] ++;
        tail = free_idx ++;
    }

    void _init_with_matrix(const std::vector<std::vector<bool>> &_matrix) {
        int n = int(_matrix.size()), m = int(_matrix[0].size());
        for (int i = n - 1; i >= 0; i --) {
            int head = free_idx, tail = free_idx;
            for (int j = 0; j < m; j ++) {
                if (_matrix[i][j]) {
                    _insert(head, tail, i + 1, j + 1);
                }
            }
        }
    }


    void _remove(int p) {

        data[data[p].left].right = data[p].right;
        data[data[p].right].left = data[p].left;

        for (int i = data[p].down; i != p; i = data[i].down) {
            for (int j = data[i].right; j != i; j = data[j].right) {
                data[data[j].up].down = data[j].down;
                data[data[j].down].up = data[j].up;
                col_size[data[j].col] --;
            }
        }
    }

    void _resume(int p) {
        for (int i = data[p].up; i != p; i = data[i].up) {
            for (int j = data[i].left; j != i; j = data[j].left) {
                data[data[j].down].up = j;
                data[data[j].up].down = j;
                col_size[data[j].col] ++;
            }
        }
        data[data[p].right].left = p;
        data[data[p].left].right = p;
    }


    bool _empty() const {return !data[0].right;}


    int get_min_one_column() const {
        int ans = data[0].right;
        for (int i = data[0].right; i ; i = data[i].right) {
            if (col_size[i] < col_size[ans]) ans = i;
        }
        return ans;
    }

    bool _solve() {
        if (_empty()) return true;
        int p = get_min_one_column();
        _remove(p);
        for (int i = data[p].down; i != p; i = data[i].down) {
            one_solution.push_back(data[i].row);
            for (int j = data[i].right; j != i; j = data[j].right) _remove(data[j].col);
            if (_solve()) return true;
            for (int j = data[i].left; j != i; j = data[j].left) _resume(data[j].col);
            one_solution.pop_back();
        }
        _resume(p);
        return false;
    }
};
