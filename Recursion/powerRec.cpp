#include <iostream>

int power(int num, int p = 2) {
  if (p == 0)
    return 1;
  return power(num, p - 1) * num;
}
int main(int argc, char *argv[]) {
  std::cout << power(2, 1) << std::endl;
  return 0;
}
