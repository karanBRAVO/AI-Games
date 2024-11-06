#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

class EightPuzzle {
  const static int board_dim = 3;

  vector<vector<int>> arr = {{1, 3, 6}, {5, 0, 2}, {4, 7, 8}};
  const vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
  const map<int, vector<char>> valid_moves = {
      {1, {'R', 'D'}},      {2, {'L', 'R', 'D'}},      {3, {'L', 'D'}},
      {4, {'U', 'R', 'D'}}, {5, {'U', 'R', 'D', 'L'}}, {6, {'U', 'D', 'L'}},
      {7, {'U', 'R'}},      {8, {'U', 'R', 'L'}},      {9, {'U', 'L'}}};

public:
  EightPuzzle() { cout << "*** Welcome to 8 Puzzle Problem ***\n"; }

  ~EightPuzzle() { cout << "Thanks for playing 8 puzzle problem\n"; }

  void ai_play() { take_machine_input(); }

private:
  void take_machine_input() {
    /*
    ALGORITHM:
    1. add the current state to queue
    2. loop while queue is not empty
        1. pop the first element from the queue
        2. check if it's the final (goal) state
        3. if final state then
            add to the path's array
        4. else
            for every next state add to the queue
     */

    queue<pair<vector<vector<int>>, string>> _q;
    vector<vector<int>> current_state(board_dim, vector<int>(board_dim));
    for (int i = 0; i < board_dim; i++) {
      for (int j = 0; j < board_dim; j++) {
        current_state[i][j] = arr[i][j];
      }
    }
    draw_board(current_state);
    _q.push(make_pair(current_state, ""));
    bfs(_q);
  }

  void bfs(queue<pair<vector<vector<int>>, string>> &q) {
    set<vector<vector<int>>> visited;

    while (!q.empty()) {
      vector<vector<int>> _state = q.front().first;
      string current_path = q.front().second;
      q.pop();

      if (visited.find(_state) != visited.end()) {
        continue;
      }
      visited.insert(_state);

      if (check_win(_state)) {
        if (!current_path.empty()) {
          cout << "\nMoves: " << current_path
               << "\nNumber of moves: " << current_path.size() << endl;
          trace_path(current_path);
        } else {
          cout << "Already at goal state\n";
        }
        break;
      }

      int es = get_empty_spot(_state);
      vector<char> vm = valid_moves.at(es);
      int f_row = (es - 1) / board_dim;
      int f_col = (es - 1) % board_dim;

      for (const auto &m : vm) {
        int to = get_next_pos(m, es);
        int t_row = (to - 1) / board_dim;
        int t_col = (to - 1) % board_dim;

        swap(_state[f_row][f_col], _state[t_row][t_col]);
        q.push(make_pair(_state, current_path + m));
        swap(_state[f_row][f_col], _state[t_row][t_col]);
      }
    }
  }

  void trace_path(string path) {
    for (int i = 0; i < path.size(); i++) {
      char m = path[i];
      int es = get_empty_spot(arr);
      int f_row = (es - 1) / board_dim;
      int f_col = (es - 1) % board_dim;
      int to = get_next_pos(m, es);
      int t_row = (to - 1) / board_dim;
      int t_col = (to - 1) % board_dim;
      swap(arr[f_row][f_col], arr[t_row][t_col]);
      draw_board(arr);
      cout << "\n";
    }
  }

  int get_next_pos(const char m, const int es) const {
    if (m == 'L') {
      return es - 1;
    } else if (m == 'R') {
      return es + 1;
    } else if (m == 'U') {
      return es - board_dim;
    } else if (m == 'D') {
      return es + board_dim;
    }
    return -1;
  }

  bool check_win(vector<vector<int>> board) {
    for (int i = 0; i < board_dim; i++) {
      for (int j = 0; j < board_dim; j++) {
        if (board[i][j] != goal[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  int get_empty_spot(vector<vector<int>> &board) const {
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

  void draw_board(vector<vector<int>> &board) const {
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

  ep.ai_play();

  return 0;
}