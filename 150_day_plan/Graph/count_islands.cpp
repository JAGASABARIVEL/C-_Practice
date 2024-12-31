#include "iostream"
#include <vector>
#include <queue>

using namespace std;

void bfs(vector<vector<char>> & graph, vector<vector<bool>> & visited, int row, int col) {
    queue<pair<int, int>> Q;
    Q.push({row, col});
    visited[row][col] = true;

    int rows = graph.size();
    int cols = graph[0].size();

    vector<vector<int>> directions = {
        {0, -1}, {-1, 0}, {0, 1}, {1, 0}, 
    };

    while(!Q.empty()) {
        auto [current_row, current_col] = Q.front();
        Q.pop();
        for (auto direction : directions) {
            int new_row = current_row + direction[0];
            int new_col = current_col + direction[1];
            if (
                new_row >= 0 &&
                new_row < rows &&
                new_col >= 0 &&
                new_col < cols &&
                graph[new_row][new_col] == '1' &&
                !visited[new_row][new_col]
            ) {
                Q.push({new_row, new_col});
                visited[new_row][new_col] = true;
            }
        }
    }
}

int main() {

    vector<vector<int>> graph = {
        {0, 0, 1},
        {1, 0, 1},
        {0, 1, 1},
    };
    

    int rows = graph.size(); int cols = graph[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    int island = 0;

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            if (graph[i][j] == '1' && !visited[i][j]) {
                bfs(graph, visited, i, j);
                island += 1;
            }
        }
    }

    cout << "Island Count " << island;



    return 0;
}