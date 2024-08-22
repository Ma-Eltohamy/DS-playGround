#include <iostream>

bool isPrefix(const std::string &main, const std::string &prefix,
              int startIdx = 0) {
  if (prefix.length() == startIdx)
    return true;

  if (main[startIdx] != prefix[startIdx])
    return false;

  return isPrefix(main, prefix, startIdx + 1);
}
int main(int argc, char *argv[]) {
  std::string main{"abcdefgh"};
  // std::string prefix{"abcd"};
  // std::string prefix{""};
  std::string prefix{"abd"};
  std::cout << isPrefix(main, prefix) << std::endl;
  return 0;
}
