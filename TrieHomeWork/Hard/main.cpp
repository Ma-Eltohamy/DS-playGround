#include <iostream>
#include <vector>

class WordFilter {
public:
  std::vector<std::string> dict;
  int dictSize;

  WordFilter(std::vector<std::string> &words) {
    dict = words;
    dictSize = (int)words.size();
  }

  bool isPrefix(const std::string &prefix, const std::string &word) {
    int prefixSize{(int)prefix.size()};

    if (prefixSize > (int)word.size())
      return false;

    for (int i = 0; i < prefixSize; ++i)
      if (prefix[i] != word[i])
        return false;
    return true;
  }

  bool isSuffix(const std::string &suffix, const std::string &word) {
    int suffixSize{(int)suffix.size()};
    int wordSize = (int)word.size();

    if (suffixSize > (int)word.size())
      return false;

    for (int i = 0; i < suffixSize; ++i)
      if (suffix[suffixSize - 1 - i] != word[wordSize - 1 - i])
        return false;
    return true;
  }

  int f(std::string pref, std::string suff) {
    for (int i = dictSize - 1; i >= 0; --i)
      if (isPrefix(pref, dict[i]) && isSuffix(suff, dict[i]))
        return i;
    return -1;
  }
};

int main(int argc, char *argv[]) {
  std::vector<std::string> words{"apple"};
  std::string pref, suff;
  WordFilter *obj = new WordFilter(words);
  pref = 'a', suff = 'e';
  int param_1 = obj->f(pref, suff);
  std::cout << param_1 << '\n';
  return 0;
}
