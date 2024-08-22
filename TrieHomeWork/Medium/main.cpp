#include <iostream>
#include <vector>
class MagicDictionary {
public:
  std::vector<std::string> dict;
  int dictSize{};
  MagicDictionary() {}

  void buildDict(std::vector<std::string> dictionary) {
    dict = dictionary;
    dictSize = (int)dictionary.size();
  }
  bool search(std::string searchWord) {
    int changes{};
    int searchWordSize{(int)searchWord.size()};
    for (int i = 0; i < dictSize; ++i, changes = 0) {
      if (searchWordSize == (int)dict[i].size()) {
        for (int j = 0; j < searchWordSize; ++j) {
          if (searchWord[j] != dict[i][j])
            ++changes;
        }
        if (changes == 1)
          return true;
      }
    }
    return false;
  }
};
int main(int argc, char *argv[]) {
  MagicDictionary md;
  std::vector<std::string> dict{"hello", "hallo", "leetcode", "judge"};
  md.buildDict(dict);
  std::cout << md.search("hello") << '\n';
  std::cout << md.search("hallo") << '\n';
  std::cout << md.search("hell") << '\n';
  std::cout << md.search("leetcodd") << '\n';
  std::cout << md.search("juage") << '\n';

  return 0;
}
