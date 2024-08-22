#include <algorithm>
#include <iostream>

int arrMax(int arr[], int len) {
  if (len == 1)
    return arr[0];
  return std::max(arr[0], arrMax(arr + 1, len - 1));
}
int main(int argc, char *argv[]) {
  int arr[5]{1, 8, 2, 10, 3};
  std::cout << arrMax(arr, 5) << std::endl;
  return 0;
}
