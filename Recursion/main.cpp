#include <iostream>

bool isPrime(int n, int startNum = 2) {
  if (n <= 1 || n % 2 == 0 || n % startNum == 0)
    return false;

  if (startNum == n)
    return true;

  return isPrime(n, startNum + 1);
}
int countPrimes(int start, int end) {
  if (start <= 1 || end < start)
    return 0;

  if (isPrime(start))
    return countPrimes(start + 1, end) + 1;
  return countPrimes(start + 1, end);
}
int main(int argc, char *argv[]) {
  countPrimes(1, 10);
  std::cout << std::endl;
  return 0;
}
