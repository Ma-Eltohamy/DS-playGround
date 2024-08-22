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

  // void insert(const std::string &str) {
  //   Trie *curTrie{this};
  //   int strSize{(int)str.size()};
  //   int pos{};
  //
  //   for (int i = 0; i < strSize; ++i) {
  //     pos = str[i] - 'a';
  //     if (!curTrie->children[pos])
  //       curTrie->children[pos] = new Trie;
  //     curTrie = curTrie->children[pos];
  //   }
  //   curTrie->isLeaf = true;
  // }

  bool isPrefix(std::string &prefix) {
    Trie *curTrie{this};
    int prefixSize{(int)prefix.size()};
    int pos{};

    for (int i = 0; i < prefixSize; ++i) {
      pos = prefix[i] - 'a';

      if (!curTrie->children[pos])
        return false;
      curTrie = curTrie->children[pos];
    }
    return true;
  }

  bool isWord(std::string str) {
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

  void insert(const std::string &str) {
    Trie *rootTrie{this};
    Trie *curTrie{this};
    int strSize{(int)str.size()};
    int pos{};

    // We can also reverse the string but I didn't prefere this way
    for (int i = strSize; i >= 0; --i) {
      curTrie = rootTrie;
      for (int j = i; j < strSize; ++j) {
        pos = str[j] - 'a';

        if (!curTrie->children[pos])
          curTrie->children[pos] = new Trie;
        curTrie = curTrie->children[pos];
      }
      curTrie->isLeaf = true;
    }
  }

  bool suffixExist(const std::string &suffix) {
    Trie *curTrie{this};
    int suffixSize{(int)suffix.size()};
    int pos{};

    for (int i = 0; i < suffixSize; ++i) {
      pos = suffix[i] - 'a';

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

  root.insert("abcd");
  root.insert("xyz");
  root.insert("abf");
  root.insert("xn");
  root.insert("ab");
  root.insert("bcd");
  root.insert("mahmoud");

  std::cout << root.suffixExist("cd") << "\n";      // 1
  std::cout << root.suffixExist("cc") << "\n";      // 0
  std::cout << root.suffixExist("mahmoud") << "\n"; // 1
  std::cout << root.suffixExist("mhmoud") << "\n";  // 0
  std::cout << root.suffixExist("moud") << "\n";    // 1
  std::cout << root.suffixExist("ud") << "\n";      // 1

  return 0;
}
