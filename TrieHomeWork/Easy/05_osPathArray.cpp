#include <iostream>
#include <vector>

class Trie {
private:
  const static int MAX_CHARS{26};
  Trie *children[MAX_CHARS];
  bool isLeaf{false};

  void _insert(const std::string &str, int curIdx) {
    if (curIdx == (int)str.size()) {
      isLeaf = true;
      return;
    }

    int pos{str[curIdx] - 'a'};
    if (!children[pos])
      children[pos] = new Trie;
    children[pos]->_insert(str, curIdx + 1);
  }

  bool _isWord(const std::string &str, int curIdx) {
    if (curIdx == (int)str.size())
      return isLeaf;

    int pos{str[curIdx] - 'a'};
    if (!children[pos])
      return false;
    return children[pos]->_isWord(str, curIdx + 1);
  }

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

  void insert(const std::string &str) { _insert(str, 0); }

  bool isWord(const std::string &str) { return _isWord(str, 0); }

  void insertPath(const std::vector<std::string> &vec) {
    std::string fullPath{};
    int vecSize{(int)vec.size()};

    for (int i = 0; i < vecSize; ++i) {
      fullPath += vec[i];
      insert(fullPath);
    }
  }

  bool subPathExist(const std::vector<std::string> &vec) {
    std::string fullPath{};
    int vecSize{(int)vec.size()};

    for (int i = 0; i < vecSize; ++i)
      fullPath += vec[i];

    return isWord(fullPath);
  }
};
int main(int argc, char *argv[]) {
  // some operatinos

  Trie tree;

  std::vector<std::string> path;

  path = {"home", "software", "eclipse"};
  tree.insertPath(path);

  path = {"home", "software", "eclipse", "bin"};
  tree.insertPath(path);

  path = {"home", "installed", "gnu"};
  tree.insertPath(path);

  path = {"user", "mostafa", "tmp"};
  tree.insertPath(path);

  path = {"user", "mostafa", "tmp"};
  std::cout << tree.subPathExist(path) << "\n"; // 1

  path = {"user", "mostafa"};
  std::cout << tree.subPathExist(path) << "\n"; // 1

  path = {"user", "mostafa", "private"};
  std::cout << tree.subPathExist(path) << "\n"; // 0
  return 0;
}
