#include <iostream>
#include <stack>

int reverseNum(int num) {
  if (num >= -9 && num <= 9)
    return -1;

  std::stack<int> s;
  while (num)
    s.push(num % 10), num /= 10;

  int digits{1}, result{0};
  while (!s.empty()) {
    result += s.top() * digits;
    digits *= 10;
    s.pop();
  }
  return result;
}
int main(int argc, char *argv[]) {
  std::cout << reverseNum(1234) << std::endl;
  std::cout << reverseNum(-1234) << std::endl;
  return 0;
}
