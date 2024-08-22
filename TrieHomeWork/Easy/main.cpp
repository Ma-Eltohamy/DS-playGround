#include <iostream>
#include <unordered_map>
#include <vector>

class Trie {
private:
  std::unordered_map<std::string, Trie *> dirs;
  bool isLeaf{false};

public:
  Trie() {}

  ~Trie() {

    for (auto &dir : dirs) {
      dir.second->~Trie();
      delete dir.second;
      dir.second = nullptr;
    }
  }

  void insertPath(const std::vector<std::string> &vec) {
    int vecSize{(int)vec.size()};
    Trie *curTrie{this};
    for (int i = 0; i < vecSize; ++i) {
      if (!dirs.count(vec[i]))
        dirs[vec[i]] = new Trie;
      curTrie = dirs[vec[i]];
    }
    curTrie->isLeaf = true;
  }

  bool subPathExist(const std::vector<std::string> &vec) {
    int vecSize{(int)vec.size()};
    Trie *curTrie{this};

    for (int i = 0; i < vecSize; ++i) {
      if (!dirs.count(vec[i]))
        return false;
      curTrie = dirs[vec[i]];
    }
    return true;
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

  path = {"user", "most"};
  std::cout << tree.subPathExist(path) << "\n"; // 0

  path = {"user", "mostafa", "private"};
  std::cout << tree.subPathExist(path) << "\n"; // 0
  return 0;
}
