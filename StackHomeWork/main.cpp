#include <cctype>
#include <iostream>
#include <stack>

int precedence(char c) {
  if (c == '+' || c == '-')
    return 1;
  else if (c == '*' || c == '/')
    return 2;
  return 0;
}
std::string infixToPostfix(std::string &infix) {
  std::stack<char> s;
  std::string postfix;
  infix += '#';
  int length{(int)infix.length()};

  for (int i = 0; i < length; ++i) {
    if (std::isdigit(infix[i]))
      postfix += infix[i];
    else if (infix[i] == '(')
      s.push(infix[i]);
    else if (infix[i] == ')') {
      while (!s.empty() && s.top() != '(')
        postfix += s.top(), s.pop();
      s.pop(); // pop (
    } else {
      while (!s.empty() && precedence(s.top()) >= precedence(infix[i]))
        postfix += s.top(), s.pop();
      s.push(infix[i]);
    }
  }
  return postfix;
}
int main(int argc, char *argv[]) {
  // filteredStr means this str has been filtered and passed tests
  // std::string filteredStr{""};
  // std::string filteredStr{"1"};
  // std::string filteredStr{"1+3*5-8/2"};
  std::string filteredStr{"2+3-((5+2)*3)"};
  std::cout << infixToPostfix(filteredStr) << '\n';
  return 0;
}
