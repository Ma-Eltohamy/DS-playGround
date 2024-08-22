#include <iostream>
#include <vector>
class Trie {
private:
  const static int MAX_CHARS{26};
  Trie *children[MAX_CHARS];
  bool isLeaf{false};

public:
  Trie() {
    for (int i = 0; i < MAX_CHARS; ++i)
      children[i] = nullptr;
  }

  ~Trie() {
    for (int i = 0; i < MAX_CHARS; ++i)
      if (children[i]) {
        children[i]->~Trie();
        delete children[i];
        children[i] = nullptr;
      }
  }

  void insert(const std::string &str) {
    Trie *curTrie{this};
    int strSize{(int)str.size()};
    int pos{};

    for (int i = 0; i < strSize; ++i) {
      pos = str[i] - 'a';
      if (!curTrie->children[pos])
        curTrie->children[pos] = new Trie;
      curTrie = curTrie->children[pos];
    }
    curTrie->isLeaf = true;
  }

  void _getAllStrings(std::vector<std::string> &res, std::string &word) {
    for (int i = 0; i < MAX_CHARS; ++i) {
      if (children[i]) {
        word += 'a' + i;
        if (children[i]->isLeaf)
          res.push_back(word);
        children[i]->_getAllStrings(res, word);
        word.pop_back();
      }
    }
  }

  // void get_all_strings(vector<string> &res, string cur_str = "") {
  //   if (isLeaf)
  //     res.push_back(cur_str);
  //
  //   for (int i = 0; i < MAX_CHAR; ++i)
  //     if (child[i])
  //       child[i]->get_all_strings(res, cur_str + (char)(i + 'a'));
  // }

  void getAllStrings(std::vector<std::string> &res) {
    std::string word{};
    _getAllStrings(res, word);
  }
};
int main(int argc, char *argv[]) {
  // some operatinos
  Trie root;

  root.insert("ab");
  root.insert("abcd");
  root.insert("abf");
  root.insert("bcd");
  root.insert("xn");
  root.insert("xyz");

  std::vector<std::string> res;
  root.getAllStrings(res);
  for (int i = 0; i < (int)res.size(); ++i)
    std::cout << res[i] << '\n';

  return 0;
}
