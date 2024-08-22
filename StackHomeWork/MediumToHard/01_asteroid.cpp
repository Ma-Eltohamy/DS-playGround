#include <iostream>
#include <stack>
#include <vector>

std::vector<int>
asteroidCollision(std::vector<int> &asteroids) { // O(n) time O(n) space
  std::stack<int> s;                             // just hold the idx

  int asteroidsLength = asteroids.size();
  int stackTop{};
  for (int i = 0; i < asteroidsLength; ++i) {
    if (asteroids[i] > 0)
      s.push(i);
    else
      while (!s.empty()) {
        stackTop = asteroids[s.top()];
        if (asteroids[i] + stackTop <= 0) {
          asteroids[s.top()] = 0;
          s.pop();
        }
        if (asteroids[i] + stackTop >= 0) {
          asteroids[i] = 0;
          break;
        }
      }
  }

  std::vector<int> result{};
  for (int i = 0; i < asteroidsLength; ++i)
    if (asteroids[i] != 0)
      result.push_back(asteroids[i]);
  return result;
  // asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), 0),
  //                 asteroids.end());
  // return asteroids;
}
int main(int argc, char *argv[]) {
  // some operations
  // std::vector<int> v{5, 10, -5}; // T
  // std::vector<int> v{8, -8}; // T
  // std::vector<int> v{10, 2, -5}; // T
  std::vector<int> v{-2, -1, 1, 2}; // T
  std::vector<int> result{asteroidCollision(v)};
  for (int i = 0; i < (int)result.size(); ++i)
    std::cout << result[i] << ' ';
  std::cout << '\n';

  return 0;
}
