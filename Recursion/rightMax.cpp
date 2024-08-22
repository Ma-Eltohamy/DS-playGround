#include <iostream>

void rightMax(int arr[], int len) {
  if (len == 1)
    return;
  rightMax(arr + 1, len - 1);

  if (arr[0] < arr[1])
    arr[0] = arr[1];
}
// int rightMax(int arr[], int len) {
//   if (len == 1)
//     return arr[0];
//
//   int rightMaxNum{rightMax(arr + 1, len - 1)};
//   if (arr[0] < rightMaxNum)
//     arr[0] = rightMaxNum;
//   return arr[0];
// }
int main(int argc, char *argv[]) {
  int arr[5]{1, 8, 2, 10, 3};
  rightMax(arr, 5);
  for (int i = 0; i < 5; ++i)
    std::cout << arr[i] << ' ';
  std::cout << '\n';
  return 0;
}
