#include "iostream"
#include <queue>
#include <vector>

using namespace std;

void bfs(vector<vector<char>> & graph, int row, int col) {
    int rows = graph.size();
    int cols = graph[0].size();

    graph[row][col] = '#';

    vector<vector<int>> directions = {
        {0, -1}, {-1, 0}, {0, 1}, {1, 0},
    };

    queue<pair<int, int>> Q;
    Q.push({row, col});

    while(!Q.empty()) {
        auto [current_row, current_col] = Q.front();
        Q.pop();
        bool canMark = false;
        for (auto direction : directions) {
            int new_row = current_row + direction[0];
            int new_col = current_col + direction[1];
            cout << new_row << ", " << new_col << endl;
            if (
                new_row >= 0 &&
                new_row < rows &&
                new_col >= 0 &&
                new_col < cols &&
                graph[new_row][new_col] == 'O'
            ) {
                graph[new_row][new_col] = '#';
                Q.push({new_row, new_col});
            }
        }
    }
}

int main() {

    vector<vector<char>> board = {
        {'O','X','X','O','X'},
        {'X','O','O','X','O'},
        {'X','O','X','O','X'},
        {'O','X','O','O','O'},
        {'X','X','O','X','O'}
    };
    int rows = board.size();
    int cols = board[0].size();

    for (int i=0; i<cols; i++){
        if (board[0][i] == 'O') bfs(board, 0, i);
        if (board[rows - 1][i] == 'O') bfs(board, rows - 1, i);
    }

    for (int i=0; i<rows; i++){
        if (board[i][0] == 'O') bfs(board, i, 0);
        if (board[i][cols - 1] == 'O') bfs(board, i, cols - 1);
    }

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            if (board[i][j] == 'O') {
                board[i][j] = 'X';
            }
            if (board[i][j] == '#') {
                board[i][j] = 'O';
            }
        }
    }

    for (int i=0; i<rows; i++) {
        cout << "[ ";
        for (int j=0; j<cols; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "]," << endl;
    }

    return 0;
}