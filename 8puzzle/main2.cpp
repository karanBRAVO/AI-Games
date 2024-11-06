#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

class EightPuzzle {
  const static int board_dim = 3;

  int arr[board_dim][board_dim] = {{2, 3, 5}, {1, 0, 4}, {7, 8, 6}};
  map<int, vector<string>> valid_moves = {
      {1, {"R", "D"}},      {2, {"L", "R", "D"}},      {3, {"L", "D"}},
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

  void ai_play() {
    draw_board(arr);

    int current_state[board_dim][board_dim];
    for (int i = 0; i < board_dim; i++) {
      for (int j = 0; j < board_dim; j++) {
        current_state[i][j] = arr[i][j];
      }
    }

    set<string> visited;

    take_machine_input(visited, current_state, "");
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
          update_board(es, es - 1, arr);
        } else if (s == "R") {
          update_board(es, es + 1, arr);
        } else if (s == "U") {
          update_board(es, es - board_dim, arr);
        } else if (s == "D") {
          update_board(es, es + board_dim, arr);
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
        if (board[i][j] != c) {
          if (c == 9 && board[i][j] == 0) {
            continue;
          }
          return false;
        }
      }
    }
    return true;
  }

  void update_board(int from, int to, int board[board_dim][board_dim]) {
    int f_row = (from - 1) / board_dim;
    int f_col = (from - 1) % board_dim;
    int t_row = (to - 1) / board_dim;
    int t_col = (to - 1) % board_dim;
    swap(board[f_row][f_col], board[t_row][t_col]);
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

private:
  string board_to_string(int board[board_dim][board_dim]) {
    string s;
    for (int i = 0; i < board_dim; i++)
      for (int j = 0; j < board_dim; j++)
        s += to_string(board[i][j]) + ",";
    return s;
  }

  void take_machine_input(set<string> &visited,
                          int curr_state[board_dim][board_dim], string path) {
    // check win
    bool cw = check_win(curr_state);
    if (cw) {
      cout << "\nPath: " << path << endl;
      return;
    }

    // check for visited
    string board_str = board_to_string(curr_state);
    if (visited.count(board_str)) {
      return;
    }
    visited.insert(board_str);

    // get empty spot
    int es = get_empty_spot(curr_state);

    // get valid moves
    vector<string> vm = valid_moves[es];

    int next_state[board_dim][board_dim];
    for (int i = 0; i < board_dim; i++) {
      for (int j = 0; j < board_dim; j++) {
        next_state[i][j] = curr_state[i][j];
      }
    }

    int f_row = (es - 1) / board_dim;
    int f_col = (es - 1) % board_dim;
    int to, t_row, t_col;

    for (const auto &m : vm) {
      // move to
      if (m == "L") {
        to = es - 1;
      } else if (m == "R") {
        to = es + 1;
      } else if (m == "U") {
        to = es - board_dim;
      } else if (m == "D") {
        to = es + board_dim;
      }

      t_row = (to - 1) / board_dim;
      t_col = (to - 1) % board_dim;

      // update the board
      swap(next_state[f_row][f_col], next_state[t_row][t_col]);

      // go for updated board
      take_machine_input(visited, next_state, path + m);

      // reset board
      swap(next_state[f_row][f_col], next_state[t_row][t_col]);
    }

    visited.erase(board_str);
  }
};

int main() {
  EightPuzzle ep;

  //   // start the game
  //   ep.start();

  ep.ai_play();

  return 0;
}