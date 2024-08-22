#include <functional>
#include <iostream>
#include <queue>
#include <vector>

class KthLargest {
public:
  // We want the kth largest number so in other words we want
  // std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
  std::priority_queue<int> min_pq;
  int k;
  KthLargest(int k, std::vector<int> &nums) : k(k) {
    int numsSize{(int)nums.size()};

    for (int i = 0; i < numsSize; ++i) {
      min_pq.push(nums[i]);
      if (min_pq.size() > k)
        min_pq.pop();
    }
  }

  int add(int val) {
    min_pq.push(val);
    if (min_pq.size() > k)
      min_pq.pop();
    return min_pq.top();
  }
};

int main(int argc, char *argv[]) {
  std::vector<int> nums{};
  KthLargest kth(1, nums);
  std::cout << kth.add(-3) << '\n';
  std::cout << kth.add(-2) << '\n';
  std::cout << kth.add(-4) << '\n';
  std::cout << kth.add(0) << '\n';
  std::cout << kth.add(4) << '\n';
  return 0;
}
