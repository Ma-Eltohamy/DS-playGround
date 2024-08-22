#include <iostream>
#include <stack>

int scoreOfParentheses(std::string str) { // O(n) time O(n) memory
  std::stack<int> s;
  s.push(0);
  int last{};

  for (char c : str)
    if (c == '(')
      s.push(0);
    else {
      last = s.top();
      s.pop();

      if (last == 0)
        last = 1;
      else
        last *= 2;

      s.top() = s.top() + last;
    }
  return s.top();
}
int main(int argc, char *argv[]) {
  // some operations

  std::cout << scoreOfParentheses("(())") << '\n';
  std::cout << scoreOfParentheses("(()())") << '\n';
  std::cout << scoreOfParentheses("(()(()()))") << '\n';
  std::cout << scoreOfParentheses("(()((()()))(()()))") << '\n';
  return 0;
}
