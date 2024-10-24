#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <vector>

using namespace std;

class DFS {
  map<int, vector<int>> graph = {
      {0, {1, 2}}, {1, {0, 2}}, {2, {0, 3, 4}}, {3, {2}}, {4, {2}}};
  const int start_node = 0;

public:
  DFS() {
    cout << "DFS execution started.\n";
    this->start();
  }

  ~DFS() { cout << "DFS execution done.\n"; }

private:
  void start() {
    auto start_time = chrono::high_resolution_clock::now();

    stack<int> stac;
    stac.push(start_node);
    set<int> visited;

    cout << "Traversal Order:\n";

    while (!stac.empty()) {
      int node = stac.top();
      stac.pop();

      if (visited.count(node) == 0) {
        cout << node << "\n";
        visited.insert(node);

        for (auto &n : graph.at(node)) {
          if (visited.count(n) == 0) {
            stac.push(n);
          }
        }
      }
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto duration =
        chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout << "Execution time: " << duration.count() << " ms\n";
  }
};

int main() {
  DFS DFS;
  return 0;
}
