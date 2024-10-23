#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class EightPuzzle {
  const static int board_dim = 3;

  int arr[board_dim][board_dim] = {{1, 2, 3}, {5, 6, 0}, {7, 8, 4}};
  map<int, vector<string>> valid_moves = {
      {1, {"L", "D"}},      {2, {"L", "R", "D"}},      {3, {"L", "D"}},
      {4, {"U", "R", "D"}}, {5, {"U", "R", "D", "L"}}, {6, {"U", "D", "L"}},
      {7, {"U", "R"}},      {8, {"U", "R", "L"}},      {9, {"U", "L"}}};

public:
  EightPuzzle() { cout << "*** Welcome to 8 Puzzle Problem ***\n"; }

  ~EightPuzzle() { cout << "Thanks for playing 8 puzzle problem\n"; }

  void start() {
    draw_board(arr);

    while (true) {
      // take user input
      take_user_input();

      // redraw the board
      draw_board(arr);

      // check win
      bool cw = check_win(arr);
      if (cw) {
        cout << "You win!\n";
        break;
      }
    }
  }

private:
  void take_user_input() {
    string s;
    int es = get_empty_spot(arr);

    while (true) {
      cout << "(L|R|U|D): ";
      cin >> s;
      bool is_valid_move = isValidMove(es, s);

      if (is_valid_move) {
        if (s == "L") {
          update_board(es, es - 1);
        } else if (s == "R") {
          update_board(es, es + 1);
        } else if (s == "U") {
          update_board(es, es - board_dim);
        } else if (s == "D") {
          update_board(es, es + board_dim);
        }
        break;
      } else {
        cout << "not a valid move\n";
      }
    }
  }

  bool isValidMove(int n, string move) {
    vector<string> vm = valid_moves[n];
    for (auto m : vm) {
      if (m == move) {
        return true;
      }
    }
    return false;
  }

  int get_empty_spot(int board[board_dim][board_dim]) {
    int c = 0;
    for (int i = 0; i < board_dim; i++) {
      for (int j = 0; j < board_dim; j++) {
        c += 1;
        if (board[i][j] == 0) {
          return c;
        }
      }
    }
    return -1;
  }

  bool check_win(int board[board_dim][board_dim]) {
    int c = 0;
    for (int i = 0; i < board_dim; i++) {
      for (int j = 0; j < board_dim; j++) {
        c += 1;
        if (board[i][j] != j) {
          return false;
        }
      }
    }
    return true;
  }

  void update_board(int from, int to) {
    int f_row = (from - 1) / board_dim;
    int f_col = (from - 1) % board_dim;
    int t_row = (to - 1) / board_dim;
    int t_col = (to - 1) % board_dim;
    swap(arr[f_row][f_col], arr[t_row][t_col]);
  }

  void draw_board(int board[board_dim][board_dim]) {
    for (int i = 0; i < board_dim; i++) {
      string s = " ";
      for (int j = 0; j < board_dim; j++) {
        s += board[i][j] == 0 ? "O" : to_string(board[i][j]);
        s += " ";
      }
      cout << "|" << s << "|\n";
    }
  }
};

int main() {
  EightPuzzle ep;

  // start the game
  ep.start();

  return 0;
}