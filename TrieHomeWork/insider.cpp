#include <cstring>
#include <iostream>
#include <unordered_map>

class Trie {
private:
  // const static int MAX_CHARS{26};
  bool isLeaf{false};
  // Trie *children[MAX_CHARS];
  std::unordered_map<int, Trie *> children;

public:
  // Trie() { std::memset(children, 0, sizeof(children)); }
  Trie() {
    // for (int i = 0; i < MAX_CHARS; ++i)
    //   children[i] = nullptr;
  }

  void _insert(std::string str, int curIdx) {
    int pos{str[curIdx] - 'a'};

    if (curIdx == str.size()) {
      isLeaf = true;
      return;
    }

    if (!children[pos])
      children[pos] = new Trie;
    children[pos]->_insert(str, curIdx + 1);
  }

  void insert(std::string str) { _insert(str, 0); }

  bool _wordExist(std::string str, int curIdx) {
    int pos{str[curIdx] - 'a'};
    if (curIdx == str.size())
      return isLeaf;

    else if (!children[pos])
      return false;

    return children[pos]->_wordExist(str, curIdx + 1);
  }

  bool wordExist(std::string str) { return _wordExist(str, 0); }

  bool _prefixExist(std::string str, int curIdx) {
    int pos{str[curIdx] - 'a'};
    if (curIdx == str.size())
      return true;

    else if (!children[pos])
      return false;

    return children[pos]->_prefixExist(str, curIdx + 1);
  }

  bool prefixExist(std::string str) { return _prefixExist(str, 0); }
};
int main(int argc, char *argv[]) {
  Trie tt;
  tt.insert("mahmoud");
  tt.insert("mahmoud");
  std::cout << tt.wordExist("mahmo") << '\n';
  std::cout << tt.wordExist("mahmoud") << '\n';
  std::cout << tt.wordExist("ramy") << '\n';
  std::cout << tt.prefixExist("mahmo") << '\n';
  // Hello, world;
  return 0;
}
