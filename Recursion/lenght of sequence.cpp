#include <iostream>

int sequence(int num) {
  if (num == 1)
    return 1;

  if (num % 2 == 0)
    return sequence(num / 2) + 1;
  else
    return sequence(3 * num + 1) + 1;
}
int main(int argc, char *argv[]) {
  std::cout << sequence(6) << std::endl;
  return 0;
}
