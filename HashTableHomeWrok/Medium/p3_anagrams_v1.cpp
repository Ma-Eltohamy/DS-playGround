#include <algorithm>
#include <iostream>
#include <unordered_set>

int countUniqueAnagrams(const std::string &str) {
  int strSize{(int)str.size()};
  std::unordered_set<std::string> st;

  for (int i = 0; i < strSize; ++i)
    for (int j = i; j < strSize; ++j) {
      std::string subString{str.substr(i, j - i + 1)};
      std::sort(subString.begin(), subString.end());
      st.insert(subString);
    }

  return (int)st.size();
}

int main(int argc, char *argv[]) {
  std::cout << countUniqueAnagrams("abba") << "\n";   // 6
  std::cout << countUniqueAnagrams("aaaaa") << "\n";  // 5
  std::cout << countUniqueAnagrams("abcba") << "\n";  // 9
  std::cout << countUniqueAnagrams("aabade") << "\n"; // 17
  return 0;
}
