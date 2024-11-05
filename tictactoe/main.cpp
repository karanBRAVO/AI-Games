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
    draw_board();

    while (true) {
      // take inputs
      if (turn == "x") {
        take_user_input();
      } else if (turn == "o") {
        take_machine_input();
      }

      // display the board
      draw_board();

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

  void draw_board() {
    for (int i = 0; i < board_size; i++) {
      string s = "";
      for (int j = 0; j < board_size; j++) {
        s += m[arr[i][j]];
      }
      cout << "|" << s << "|\n";
    }
  }
};

int main() {
  TicTacToe t;

  // start the game
  t.start();

  return 0;
}