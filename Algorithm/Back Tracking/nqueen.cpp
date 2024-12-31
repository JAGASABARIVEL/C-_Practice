#include "iostream"
#include <vector>

using namespace std;


class NQueenSolution {

    public:
        int board_size;
        NQueenSolution(int size) : board_size(size) {}
        bool isSafeToPlace(vector<vector<int>> & board, int row, int col) {

            for (int i=0; i<col; i++) {
                if (board[row][i]) {
                    return false;
                }
            }

            for (int i=row, j=col; i >= 0 && j >= 0; i--, j--) {
                if (board[i][j]) {
                    return false;
                }
            }

            for (int i=0, j=0; i <board_size && j < board_size; i++, j++) {
                if (board[i][j]) {
                    return false;
                }
            }

            for (int i=row, j=col; i < board_size && j >= 0; i++, j--) {
                if (board[i][j]) {
                    return false;
                }
            }

            for (int i=row, j=col; i >= 0 && j < board_size; i--, j++) {
                if (board[i][j]) {
                    return false;
                }
            }

            return true;
        }

        bool solveNqueenUntil(vector<vector<int>> & board, int col) {
            if (col >= board_size) {
                return true;
            }

            for (int i=0; i<board_size; i++) {
                if (isSafeToPlace(board, i, col)) {
                    board[i][col] = 1;
                    if (solveNqueenUntil(board, col+1)) {
                        return true;
                    }
                    board[i][col] = 0;
                }
            }
            return false;
        }

        void display_solution(vector<vector<int>> board) {
            for (int i=0; i < board_size; i++) {
                for (int j=0; j< board_size; j++) {
                    cout << board[i][j] << " | ";
                }
                cout << endl;
            }
        }

        bool solveNqueen() {
            vector<vector<int>> board(this->board_size, vector<int>(this->board_size, 0));
            if (solveNqueenUntil(board, 0) == false) {
                cout << "No solution exists" << endl;
                return false;
            }
            display_solution(board);
            return true;
        }
};


int main() {
    NQueenSolution n_queen_solution(4);
    n_queen_solution.solveNqueen();
    return 0;
}