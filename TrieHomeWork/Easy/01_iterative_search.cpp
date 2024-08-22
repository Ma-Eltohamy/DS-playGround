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
};
int main(int argc, char *argv[]) {
  // some operatinos
  Trie root;
  root.insert("mahmoud");
  root.insert("abcd");
  root.insert("xyz");
  root.insert("abf");
  root.insert("xn");
  root.insert("ab");
  root.insert("bcd");

  std::cout << root.wordExist("xyz") << "\n";
  std::cout << root.wordExist("xy") << "\n";
  std::cout << root.wordExist("ramy") << '\n';
  std::cout << root.wordExist("mahmoud") << '\n';
  return 0;
}
