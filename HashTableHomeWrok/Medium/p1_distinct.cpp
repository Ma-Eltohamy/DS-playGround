#include <iostream>
#include <unordered_map>
#include <unordered_set>

// int numberDistictSubString(const std::string &str) {
//   std::unordered_set<std::string> res{};
//   int strSize{(int)str.size()};
//
//   for (int i = 0; i < strSize; ++i)   // O(L)
//     for (int j = i; j < strSize; ++j) // O(L)
//       res.insert(str.substr(i, j - i + 1));   // O(L)
//
//   // Over all O(L^3)
//
//   return (int)res.size();
// }

class TrieNode {
public:
  const static int MAXCHAR = 26;
  TrieNode *arr[MAXCHAR];
  bool isWord{false};

  TrieNode() {
    for (int i = 0; i < MAXCHAR; ++i)
      arr[i] = nullptr;
  }
};

class Trie {
private:
  TrieNode *root;
  int distinctSubString{};

  void _insert(TrieNode *root, const std::string &str, int idx = 0) {
    if (idx == (int)str.size()) {
      root->isWord = true;
      return;
    }

    int pos{str[idx] - 'a'};
    if (!root->arr[pos]) {
      root->arr[pos] = new TrieNode;
      ++distinctSubString;
    }
    _insert(root->arr[pos], str, idx + 1);
  }

public:
  Trie() : root(new TrieNode) {}

  void insert(const std::string &str) {
    int strSize{(int)str.size()};
    for (int i = strSize - 1; i >= 0; --i)
      _insert(root, str.substr(i, strSize));
  }

  int numDistinctSubString() { return distinctSubString; }
};

int countDistinctSubString(const std::string &str) {
  Trie tt;
  tt.insert(str);
  return tt.numDistinctSubString();
}

// int numberDistictSubString(const std::string &str) {
//   std::unordered_set<std::string> res{};
//   int strSize{(int)str.size()};
//   std::string subStr{};
//
//   // O(L^3)
//   for (int i = 0; i < strSize; ++i) { // O(L)
//     subStr += str[i];
//     res.insert(subStr);                 // O(L)
//     res.insert(str.substr(i, strSize)); // O(L^2)
//   }
//
//   return (int)res.size();
// }

int main(int argc, char *argv[]) {
  // std::cout << numberDistictSubString("aaab") << '\n';
  std::cout << countDistinctSubString("aaab") << '\n';
  return 0;
}
