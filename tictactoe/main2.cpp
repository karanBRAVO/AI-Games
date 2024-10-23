#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>
using namespace std;

class TicTacToe {
  const static int board_size = 3;

  int arr[3][board_size];
  map<int, string> m;
  string turn;

public:
  TicTacToe() {
    cout << "# Welcome to Tic-Tac-Toe\n";
    for (int i = 0; i < board_size; i++) {
      for (int j = 0; j < board_size; j++) {
        arr[i][j] = -1;
      }
    }
    m = {{-1, "-"}, {1, "x"}, {0, "o"}};
    turn = "x"; // 'x' -> user | 'o' -> machine
  }

  ~TicTacToe() { cout << "Thanks for playing TicTacToe!\n"; }

public:
  void start() {
    draw_board(arr);

    while (true) {
      // take inputs
      if (turn == "x") {
        take_user_input();
      } else if (turn == "o") {
        take_machine_best_input();
        // take_machine_input();
      }

      // display the board
      draw_board(arr);

      // check for winning conditions
      bool cw = check_win();
      if (cw) {
        cout << (turn == "x" ? "You win!\n" : "Machine won the game\n");
        break;
      }

      // check for tie
      bool ct = check_tie();
      if (ct) {
        cout << "Tie\n";
        break;
      }

      // change the turn
      turn = turn == "o" ? "x" : "o";
    }
  }

private:
  void take_user_input() {
    int v;
    vector<int> vm = valid_moves();
    while (true) {
      cout << "Your turn: ";
      cin >> v;
      bool flag = false;
      for (auto _v : vm) {
        if (_v == v) {
          flag = true;
          break;
        }
      }
      if (flag) {
        update_board(v);
        break;
      } else {
        cout << "Please enter a valid position\n";
      }
    }
  }

  int get_random_number_in_range(int a, int b) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(a, b);
    return distrib(gen);
  }

  void take_machine_input() {
    vector<int> vm = valid_moves();
    int v = get_random_number_in_range(0, vm.size());
    update_board(vm[v]);
    cout << "Machine turn: " << vm[v] << endl;
  }

  void take_machine_best_input() {
    // current board state
    int current_state[board_size][board_size];
    for (int i = 0; i < board_size; i++) {
      for (int j = 0; j < board_size; j++) {
        current_state[i][j] = arr[i][j];
      }
    }

    int v = minimax(current_state, true).second;
    update_board(v);
    cout << "Machine turn: " << v << endl;
  }

  void update_board(int n) {
    int row = (n - 1) / board_size;
    int col = (n - 1) % board_size;
    arr[row][col] = (turn == "x" ? 1 : 0);
  }

  vector<int> valid_moves() {
    int c = 0;
    vector<int> a;
    for (int i = 0; i < board_size; i++) {
      for (int j = 0; j < board_size; j++) {
        c += 1;
        if (arr[i][j] == -1) {
          a.push_back(c);
        }
      }
    }
    return a;
  }

  bool check_win() {
    // '-' || '|'
    for (int i = 0; i < board_size; i++) {
      if (arr[i][0] != -1 && arr[i][1] != -1 && arr[i][2] != -1 &&
          ((arr[i][0] == 1 && arr[i][1] == 1 && arr[i][2] == 1) ||
           (arr[i][0] == 0 && arr[i][1] == 0 && arr[i][2] == 0))) {
        return true;
      }
      if (arr[0][i] != -1 && arr[1][i] != -1 && arr[2][i] != -1 &&
          ((arr[0][i] == 1 && arr[1][i] == 1 && arr[2][i] == 1) ||
           (arr[0][i] == 0 && arr[1][i] == 0 && arr[2][i] == 0))) {
        return true;
      }
    }
    // '\' || '/'
    if (arr[0][0] != -1 && arr[1][1] != -1 && arr[2][2] != -1 &&
        ((arr[0][0] == 1 && arr[1][1] == 1 && arr[2][2] == 1) ||
         (arr[0][0] == 0 && arr[1][1] == 0 && arr[2][2] == 0))) {
      return true;
    }
    if (arr[0][2] != -1 && arr[1][1] != -1 && arr[2][0] != -1 &&
        ((arr[0][2] == 1 && arr[1][1] == 1 && arr[2][0] == 1) ||
         (arr[0][2] == 0 && arr[1][1] == 0 && arr[2][0] == 0))) {
      return true;
    }
    return false;
  }

  bool check_tie() {
    for (int i = 0; i < board_size; i++) {
      for (int j = 0; j < board_size; j++) {
        if (arr[i][j] == -1) {
          return false;
        }
      }
    }
    return true;
  }

  void draw_board(int _arr[3][3]) {
    for (int i = 0; i < board_size; i++) {
      string s = "";
      for (int j = 0; j < board_size; j++) {
        s += m[_arr[i][j]];
      }
      cout << "|" << s << "|\n";
    }
  }

private:
  pair<int, int> minimax(int state[3][3], bool isMax) {
    int cmw = get_score(state);
    if (cmw == 1 || cmw == -1) {
      return make_pair(cmw, -1);
    }

    vector<int> am = available_moves(state);
    if (am.empty()) {
      return make_pair(0, -1);
    }

    int score = isMax ? -1e6 : 1e6;
    int _m;

    for (auto m : am) {
      int row = (m - 1) / board_size;
      int col = (m - 1) % board_size;
      state[row][col] = isMax ? 0 : 1;

      int res = minimax(state, !isMax).first;
      if (res > score) {
        _m = m;
      }

      score = isMax ? max(score, res) : min(score, res);
      state[row][col] = -1;
    }

    return make_pair(score, _m);
  }

  vector<int> available_moves(int _arr[3][3]) {
    int c = 0;
    vector<int> a;
    for (int i = 0; i < board_size; i++) {
      for (int j = 0; j < board_size; j++) {
        c += 1;
        if (_arr[i][j] == -1) {
          a.push_back(c);
        }
      }
    }
    return a;
  }

  int get_score(int _arr[3][3]) {
    // '-' || '|'
    for (int i = 0; i < board_size; i++) {
      // machine win
      if (_arr[i][0] != -1 && _arr[i][1] != -1 && _arr[i][2] != -1 &&
          (_arr[i][0] == 0 && _arr[i][1] == 0 && _arr[i][2] == 0)) {
        return 1;
      }
      if (_arr[0][i] != -1 && _arr[1][i] != -1 && _arr[2][i] != -1 &&
          (_arr[0][i] == 0 && _arr[1][i] == 0 && _arr[2][i] == 0)) {
        return 1;
      }
      // user win
      if (_arr[i][0] != -1 && _arr[i][1] != -1 && _arr[i][2] != -1 &&
          (_arr[i][0] == 1 && _arr[i][1] == 1 && _arr[i][2] == 1)) {
        return -1;
      }
      if (_arr[0][i] != -1 && _arr[1][i] != -1 && _arr[2][i] != -1 &&
          (_arr[0][i] == 1 && _arr[1][i] == 1 && _arr[2][i] == 1)) {
        return -1;
      }
    }
    // '\' || '/'
    // machine win
    if (_arr[0][0] != -1 && _arr[1][1] != -1 && _arr[2][2] != -1 &&
        (_arr[0][0] == 0 && _arr[1][1] == 0 && _arr[2][2] == 0)) {
      return 1;
    }
    if (_arr[0][2] != -1 && _arr[1][1] != -1 && _arr[2][0] != -1 &&
        (_arr[0][2] == 0 && _arr[1][1] == 0 && _arr[2][0] == 0)) {
      return 1;
    }
    // user win
    if (_arr[0][0] != -1 && _arr[1][1] != -1 && _arr[2][2] != -1 &&
        (_arr[0][0] == 1 && _arr[1][1] == 1 && _arr[2][2] == 1)) {
      return -1;
    }
    if (_arr[0][2] != -1 && _arr[1][1] != -1 && _arr[2][0] != -1 &&
        (_arr[0][2] == 1 && _arr[1][1] == 1 && _arr[2][0] == 1)) {
      return -1;
    }

    // tie
    return 0;
  }
};

int main() {
  TicTacToe t;

  // start the game
  t.start();

  return 0;
}