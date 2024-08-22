#include <iostream>
#include <unordered_map>

class Trie {
private:
  std::unordered_map<char, Trie *> children;
  bool isLeaf{false};

  void _insert(std::string &str, int curIdx) {
    if (curIdx == str.size()) {
      isLeaf = true;
      return;
    }

    if (!children[str[curIdx]])
      children[str[curIdx]] = new Trie;

    children[str[curIdx]]->_insert(str, curIdx + 1);
  }

  bool _search(std::string &str, int curIdx) {
    if (curIdx == str.size())
      return true;

    if (!children[str[curIdx]])
      return false;

    return children[str[curIdx]]->_search(str, curIdx + 1);
  }

public:
  Trie() {}

  void insert(std::string str) { _insert(str, 0); }

  bool search(std::string str) { return _search(str, 0); }
};

int main(int argc, char *argv[]) {
  Trie t;
  t.insert("mahmoud");
  t.insert("Ibrahim");

  std::cout << t.search("mahmoud") << '\n';
  std::cout << t.search("Mahmoud") << '\n';
  std::cout << t.search("Ibrahim") << '\n';
  return 0;
}
