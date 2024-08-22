#include <iostream>

bool isPalindrome(int arr[], int len) {
  if (len == 1 || len == 0)
    return true;

  if (arr[0] != arr[len - 1])
    return false;

  return isPalindrome(arr + 1, len - 2);
}
int main(int argc, char *argv[]) {
  // int arr[5]{1, 8, 2, 10, 3};
  int arr[5]{1, 2, 2, 2, 1};
  std::cout << isPalindrome(arr, 5) << std::endl;
  for (int i = 0; i < 5; ++i)
    std::cout << arr[i] << ' ';
  std::cout << '\n';
  return 0;
}
