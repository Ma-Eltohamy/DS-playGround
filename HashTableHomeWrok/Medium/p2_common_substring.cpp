#include <iostream>
#include <unordered_map>
#include <unordered_set>

int countSubStringMatch(const std::string &str1, const std::string &str2) {
  int res{};

  std::unordered_set<std::string> st1;
  int str1Size{(int)str1.size()};
  for (int i = 0; i < str1Size; ++i)
    for (int j = i; j < str1Size; ++j)
      st1.insert(str1.substr(i, j));

  int str2Size{(int)str2.size()};
  std::unordered_set<std::string> st2;
  for (int i = 0; i < str2Size; ++i)
    for (int j = i; j < str2Size; ++j)
      st2.insert(str2.substr(i, j));

  for (auto &str : st1)
    if (st2.count(str))
      ++res;

  return res;
}

int main(int argc, char *argv[]) {
  std::cout << countSubStringMatch("aaab", "aa") << '\n';
  std::cout << countSubStringMatch("aaab", "aa") << "\n";     // 2
  std::cout << countSubStringMatch("aaab", "ab") << "\n";     // 3
  std::cout << countSubStringMatch("aaaaa", "xy") << "\n";    // 0
  std::cout << countSubStringMatch("aaaaa", "aaaaa") << "\n"; // 5
  return 0;
}
