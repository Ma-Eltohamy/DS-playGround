#include <functional>
#include <iostream>
#include <queue>
#include <vector>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
int main(int argc, char *argv[]) {
  std::vector<ListNode *> v{new ListNode(15), new ListNode(10),
                            new ListNode(3)};
  std::priority_queue<ListNode *> pq;
  pq.push(v[0]);
  pq.push(v[1]);
  pq.push(v[2]);
  std::cout << pq.top()->val << '\n';
  pq.pop();
  std::cout << pq.top()->val << '\n';
  // std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
  // pq.push(1);
  // pq.push(2);
  // pq.push(3);
  // pq.push(4);
  // pq.push(5);
  // while (!pq.empty())
  //   std::cout << pq.top() << ' ', pq.pop();
  // std::cout << '\n';

  return 0;
}
