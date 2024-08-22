#include <iostream>
#include <queue>

class LastKNumbersSumStream {
private:
  int k{}, sum{};
  std::queue<int> q;

public:
  LastKNumbersSumStream(int k) : k(k), sum(0) {}

  int next(int newNum) {
    if (q.size() == k)
      sum -= q.front(), q.pop();
    sum += newNum;
    q.push(newNum);
    return sum;
  }
};
int main(int argc, char *argv[]) {
  // some operations
  LastKNumbersSumStream processor(4);
  int num;
  while (std::cin >> num)
    std::cout << "Sum of last K numbers " << processor.next(num) << '\n';
  return 0;
}
