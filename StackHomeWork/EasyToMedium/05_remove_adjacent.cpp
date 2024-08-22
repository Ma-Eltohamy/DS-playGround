#include <iostream>
#include <stack>

std::string removeDuplicates(std::string str) {
  std::stack<char> s;
  for (char c : str) {
    if (s.empty() || c != s.top())
      s.push(c);
    else
      s.pop();
  }

  std::string res;
  while (!s.empty()) {
    res = s.top() + res;
    s.pop();
  }
  return res;
}
int main(int argc, char *argv[]) {
  std::cout << removeDuplicates("abbacaac") << "\n";  // Empty
  std::cout << removeDuplicates("aabacaacd") << "\n"; // bad
  std::cout << removeDuplicates("abcddcba") << "\n";  // Empty
  return 0;
}
