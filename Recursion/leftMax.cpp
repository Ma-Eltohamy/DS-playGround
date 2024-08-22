#include <iostream>

void leftMax(int arr[], int len) {
  if (len == 1)
    return;

  leftMax(arr, len - 1);

  if (arr[len] < arr[len - 1])
    arr[len] = arr[len - 1];
}
int main(int argc, char *argv[]) {
  int arr[5]{1, 8, 2, 10, 3};
  leftMax(arr, 5);
  for (int i = 0; i < 5; ++i)
    std::cout << arr[i] << ' ';
  std::cout << '\n';
  return 0;
}
