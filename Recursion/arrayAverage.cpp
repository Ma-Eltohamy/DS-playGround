#include <iostream>

double arrayAverage(int arr[], int len) {
  if (len == 1)
    return arr[0];
  return (arr[0] + (arrayAverage(arr + 1, len - 1) * (len - 1))) / len;
}
int main(int argc, char *argv[]) {
  int arr[5]{1, 8, 2, 10, 3};
  std::cout << arrayAverage(arr, 5) << std::endl;
  return 0;
}
