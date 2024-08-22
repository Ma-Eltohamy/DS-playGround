#include <iostream>
#include <stack>
#include <vector>

std::vector<int> dailyTemperatures(std::vector<int> &temperatures) {
  std::stack<int> s;
  int length = temperatures.size();
  std::vector<int> res(length);

  for (int i = length - 1; i >= 0;
       --i) { // O(n) time O(n) memory
              // because the element entered and got out just and only one time
    while (!s.empty() && temperatures[i] >= temperatures[s.top()])
      s.pop();

    if (!s.empty())
      res[i] = s.top() - i;
    s.push(i);
  }
  return res;
}
int main(int argc, char *argv[]) {
  // some operations

  std::vector<int> v{73, 74, 75, 71, 69, 72, 76, 73};
  // std::vector<int> v{73, 74, 75, 71, 69, 72, 76, 73};
  // std::vector<int> v{30, 40, 50, 60};
  // std::vector<int> v{30, 60, 90};
  // std::vector<int> v{30};
  // std::vector<int> v{};
  std::vector<int> res = dailyTemperatures(v);
  for (int i = 0; i < res.size(); ++i)
    std::cout << res[i] << ' ';
  std::cout << '\n';
  return 0;
}
