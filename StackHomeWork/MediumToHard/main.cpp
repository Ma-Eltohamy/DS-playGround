#include <iostream>
#include <stack>
#include <vector>

struct StackElement {
  int n;
  int result{-1};

  StackElement(int n = 1, int result = -1) : n(n), result(result) {}
};

int factorialStack(int n) {
  if (n <= 1)
    return 1;

  std::stack<StackElement> s;
  s.push(StackElement(n));
  StackElement cur(1);

  while (!s.empty()) {
    if (s.top().n == 1)
      s.top().result = 1;

    // go deep till reach to 1
    if (s.top().result < 0) {
      s.push(StackElement(s.top().n - 1));
      continue;
    }

    // go back high
    cur = s.top();
    s.pop();
    if (s.empty())
      break;
    s.top().result = cur.result * s.top().n;
  }
  return cur.result;
}
int main(int argc, char *argv[]) {
  // some operations

  std::cout << factorialStack(5) << std::endl;
  return 0;
}
