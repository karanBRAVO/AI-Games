#include <chrono>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

class BFS {
  map<int, vector<int>> graph = {
      {0, {1, 2}}, {1, {0, 2}}, {2, {0, 3, 4}}, {3, {2}}, {4, {2}}};
  const int start_node = 0;

public:
  BFS() {
    cout << "BFS execution started.\n";
    this->start();
  }

  ~BFS() { cout << "BFS execution done.\n"; }

private:
  void start() {
    auto start_time = chrono::high_resolution_clock::now();

    // initialize the queue
    queue<int> q;
    // add the start node to the queue
    q.push(start_node);
    // visited set
    set<int> visited;

    // loop while q is not empty
    while (!q.empty()) {
      // pop the front node
      int node = q.front();
      q.pop();

      cout << node << "\n";
      // mark visited
      visited.insert(node);

      // go for the connected neighbours
      for (auto &n : graph.at(node)) {
        if (visited.count(n) == 0) {
          q.push(n);
          visited.insert(n);
        }
      }

      // visited set
      cout << "Visited: ";
      for (auto &v : visited) {
        cout << v << " ";
      }
      cout << "\n";
    }

    // Capture the end time
    auto end_time = chrono::high_resolution_clock::now();
    // Calculate the time difference
    auto duration =
        chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Execution time: " << duration.count() << " ms\n";
  }
};

int main() {
  BFS bfs;

  return 0;
}