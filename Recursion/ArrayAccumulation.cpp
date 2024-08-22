#include <iostream>

void arrayAccumulation(int arr[], int len) {
  if (len == 1)
    return;

  arrayAccumulation(arr, len - 1);
  arr[len - 1] += arr[len - 2];
}
// int arrayAccumulation(int arr[], int len) {
//   if (len == 1)
//     return arr[0];
//
//   return arr[len - 1] += arrayAccumulation(arr, len - 1);
// }
int main(int argc, char *argv[]) {
  int arr[5]{1, 8, 2, 10, 3};
  arrayAccumulation(arr, 5);
  for (int i = 0; i < 5; ++i)
    std::cout << arr[i] << ' ';
  std::cout << '\n';
  return 0;
}
