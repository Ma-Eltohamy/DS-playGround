#include <iostream>

int suffixSum(int arr[], int len, int n) {
  if (n <= 0 || n > len)
    return 0;

  return arr[len - n] + suffixSum(arr + (len - n) + 1, n - 1, n - 1);
}
int main(int argc, char *argv[]) {
  int arr[5]{1, 8, 2, 10, 3};
  std::cout << suffixSum(arr, 5, 2) << std::endl;
  for (int i = 0; i < 5; ++i)
    std::cout << arr[i] << ' ';
  std::cout << '\n';
  return 0;
}
