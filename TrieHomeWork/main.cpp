#include <cstring>
#include <iostream>
#include <vector>

class TrieNode {
private:
  static const int MAX_CHARS{26};

public:
  TrieNode *children[MAX_CHARS];
  bool isLeaf{false};
  // TrieNode() {
  //   for (int i = 0; i < MAX_CHARS; ++i)
  //     children[i] = nullptr;
  // }
};

class TrieTree {
private:
  TrieNode *root;

public:
  TrieTree() : root(new TrieNode) {}

  void _insert(TrieNode *root, std::string str, int curIdx) {
    if (curIdx == str.size()) {
      root->isLeaf = true;
      return;
    }

    int pos{str[curIdx] - 'a'};

    if (!root->children[pos])
      root->children[pos] = new TrieNode;
    _insert(root->children[pos], str, curIdx + 1);
  }

  void insert(std::string str) { _insert(root, str, 0); }

  bool _search(TrieNode *root, std::string str, int curIdx) {
    if (curIdx == str.size())
      return true;

    int pos{str[curIdx] - 'a'};
    if (!root->children[pos])
      return false;

    return _search(root->children[pos], str, curIdx + 1);
  }

  bool search(std::string str) { return _search(root, str, 0); }

  bool _wordExist(TrieNode *root, std::string str, int curIdx) {
    int pos{str[curIdx] - 'a'};
    if (curIdx == str.size())
      return root->isLeaf;

    else if (!root->children[pos])
      return false;

    return _wordExist(root->children[pos], str, curIdx + 1);
  }

  bool wordExist(std::string str) { return _wordExist(root, str, 0); }

  bool _prefixExist(TrieNode *root, std::string str, int curIdx) {
    if (curIdx == str.size())
      return true;

    int pos{str[curIdx] - 'a'};

    if (!root->children[pos])
      return false;

    return _prefixExist(root->children[pos], str, curIdx + 1);
  }

  bool prefixExist(std::string str) { return _prefixExist(root, str, 0); }

  void _allWords(TrieNode *root, std::string &str,
                 std::vector<std::string> &vec) {
    if (root->isLeaf) {
      vec.push_back(str);
      return;
    }

    for (int i = 0; i < 26; ++i)
      if (root->children[i]) {
        str += 'a' + i;
        _allWords(root->children[i], str, vec);
        str.pop_back();
      }
  }

  std::vector<std::string> allWords() {
    std::string word;
    std::vector<std::string> vec;
    _allWords(root, word, vec);
    return vec;
  }
};

int main(int argc, char *argv[]) {
  TrieTree tt;
  tt.insert("mahmoud");
  tt.insert("mahnoud");
  tt.insert("ahmed");
  tt.insert("mahmoud");
  std::cout << tt.wordExist("mahmo") << '\n';
  std::cout << tt.wordExist("mahmoud") << '\n';
  std::cout << tt.wordExist("ramy") << '\n';
  std::cout << tt.prefixExist("mahmo") << '\n';
  return 0;
}
