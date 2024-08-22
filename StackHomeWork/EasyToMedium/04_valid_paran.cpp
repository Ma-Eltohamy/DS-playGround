#include <iostream>
#include <stack>

char foundMatch(char c) {
  if (c == ')')
    return '(';
  if (c == ']')
    return '[';
  return '{';
}

bool isValid(const std::string &str) {
  std::stack<char> s;

  for (char c : str) {
    if (c == '[' || c == '{' || c == '(')
      s.push(c);
    else {
      if (!s.empty() && foundMatch(c) == s.top())
        s.pop();
      else
        return false;
    }
  }
  return s.empty();
}

int main(int argc, char *argv[]) {
  std::cout << isValid("]") << std::endl;
  std::cout << isValid("){") << std::endl;
  std::cout << isValid("(())") << "\n";     // 1
  std::cout << isValid("(()[()])") << "\n"; // 1
  std::cout << isValid("(][)") << "\n";     // 0
  std::cout << isValid("(()") << "\n";      // 0
  std::cout << isValid("()(") << "\n";      // 0
  return 0;
}
