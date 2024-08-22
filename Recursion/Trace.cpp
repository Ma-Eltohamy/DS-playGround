#include <iostream>

void doSomething(int n) {
  if (n) {
    std::cout << n % 10;
    doSomething(n / 10);
  }
}
int main(int argc, char *argv[]) {
  doSomething(123456);
  std::cout << std::endl;
  return 0;
}
