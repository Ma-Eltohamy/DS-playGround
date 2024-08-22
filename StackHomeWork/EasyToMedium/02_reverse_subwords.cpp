#include <iostream>
#include <stack>

std::string reverseSubWords(std::string line) {
  if (line.length() == 0)
    return "";

  std::stack<char> s;
  line += ' ';
  int lineLength{(int)line.length()};
  for (int i = 0, j = 0; i < lineLength; ++i) {
    if (line[i] == ' ') {
      for (; !s.empty(); ++j) {
        line[j] = s.top();
        s.pop();
      }
      j = i + 1;
    } else
      s.push(line[i]);
  }
  return line;
}
int main(int argc, char *argv[]) {
  std::string line;
  getline(std::cin, line);

  std::cout << reverseSubWords(line) << "\n";
  // some operations
  return 0;
}
