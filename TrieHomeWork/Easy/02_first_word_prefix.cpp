#include <iostream>
#include <stack>

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

  void insert(std::string str) {
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

  bool wordExist(std::string str) {
    Trie *curTrie{this};
    int strSize{(int)str.size()};
    int pos{};

    for (int i = 0; i < strSize; ++i) {
      pos = str[i] - 'a';
      if (!curTrie->children[pos])
        return false;
      curTrie = curTrie->children[pos];
    }

    return curTrie->isLeaf;
  }

  std::string firstWordPrefix(const std::string &str) {
    std::string res{};
    Trie *curTrie{this};
    int strSize{(int)str.size()};
    int pos{};

    for (int i = 0; i < strSize; ++i) {
      pos = str[i] - 'a';

      if (curTrie->children[pos]) {
        res += 'a' + pos;
        if (curTrie->children[pos]->isLeaf)
          return res;
        curTrie = curTrie->children[pos];
      } else {
        break;
      }
    }
    return str;
  }
};
int main(int argc, char *argv[]) {
  // some operatinos
  Trie root;
  root.insert("xyz");
  root.insert("xyzeA");
  root.insert("a");
  root.insert("bc");

  std::cout << root.firstWordPrefix("x") << '\n';
  std::cout << root.firstWordPrefix("xyzabc") << '\n';

  return 0;
}
