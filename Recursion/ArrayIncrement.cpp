#include <iostream>

void arrayIncrement(int arr[], int len) {
  if (len == 1)
    return;

  arr[len - 1] += len - 1;
  arrayIncrement(arr, len - 1);
}
int main(int argc, char *argv[]) {
  int arr[5]{1, 8, 2, 10, 3};
  arrayIncrement(arr, 5);
  for (int i = 0; i < 5; ++i)
    std::cout << arr[i] << ' ';
  std::cout << '\n';
  return 0;
}
