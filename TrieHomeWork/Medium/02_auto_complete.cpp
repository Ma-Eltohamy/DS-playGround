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

  Trie *isPrefix(const std::string &prefix) {
    Trie *curTrie{this};
    int pos{}, prefixSize{(int)prefix.size()};

    for (int i = 0; i < prefixSize; ++i) {
      pos = prefix[i] - 'a';
      if (!children[pos])
        return nullptr;
      curTrie = curTrie->children[pos];
    }
    return curTrie;
  }

  // void getAllWords(Trie *root, std::vector<std::string> &res,
  //                  std::string &word) {
  //   for (int i = 0; i < MAX_CHARS; ++i) {
  //     if (root->children[i]) {
  //       word += 'a' + i;
  //       if (root->children[i]->isLeaf)
  //         res.push_back(word);
  //       getAllWords(root->children[i], res, word);
  //       word.pop_back();
  //     }
  //   }
  // }

  void getAllWords(std::vector<std::string> &res, std::string &word) {
    for (int i = 0; i < MAX_CHARS; ++i) {
      if (children[i]) {
        word += 'a' + i;
        if (children[i]->isLeaf)
          res.push_back(word);
        children[i]->getAllWords(res, word);
        word.pop_back();
      }
    }
  }

  void autoComplete(const std::string &prefix, std::vector<std::string> &res) {
    Trie *curTrie{isPrefix(prefix)};
    if (!curTrie)
      return;

    if (curTrie->isLeaf)
      res.push_back(prefix);

    std::string word{prefix};
    curTrie->getAllWords(res, word);
  }
};
int main(int argc, char *argv[]) {
  // some operatinos
  Trie root;

  root.insert("abcd");
  root.insert("ab");
  root.insert("abx");
  root.insert("abyz");
  root.insert("xyz");
  root.insert("a");
  root.insert("bcd");

  std::vector<std::string> res;
  root.autoComplete("ab", res);
  for (int i = 0; i < (int)res.size(); ++i)
    std::cout << res[i] << '\n';

  return 0;
}
