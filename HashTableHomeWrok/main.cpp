#include <iostream>
#include <utility>
#include <vector>

int hashString(std::string str, int n) {
  long long nn = n;
  long long sum = 0;
  for (int i = 0; i < (int)str.size(); ++i)
    sum = (sum * 26 + str[i] - 'a') % nn;
  return sum % nn;
}

struct phoneEntry {
  const static int INTERNAL_LIMIT = 2147483647;
  std::string name{}, phoneNumber{};

  phoneEntry() {}
  phoneEntry(std::string name, std::string phoneNumber)
      : name(name), phoneNumber(phoneNumber) {}

  int hash() { return hashString(name, INTERNAL_LIMIT); }

  void print() { std::cout << "(" << name << ", " << phoneNumber << ")  "; }
};

class HashTable {
private:
  std::vector<std::vector<phoneEntry>> table;
  int size;

public:
  HashTable(int size) : size(size) { table.resize(size); }

  void put(phoneEntry userPhone) {
    int hashCode{userPhone.hash() % size};
    int bucketSize{(int)table[hashCode].size()};

    for (int i = 0; i < bucketSize; ++i)
      if (userPhone.name == table[hashCode][i].name) {
        table[hashCode][i] = userPhone;
        return;
      }

    table[hashCode].push_back(userPhone);
  }

  bool remove(phoneEntry userPhone) {
    int hashCode{userPhone.hash() % size};
    int bucketSize{(int)table[hashCode].size()};

    for (int i = 0; i < bucketSize; ++i)
      if (table[hashCode][i].name == userPhone.name) {
        std::swap(table[hashCode][bucketSize - 1], table[hashCode][i]);
        table[hashCode].pop_back();
        return true;
      }

    return false;
  }

  bool get(phoneEntry &userPhone) {
    int hashCode{(int)userPhone.hash() % size};
    int bucketSize{(int)table[hashCode].size()};

    for (int i = 0; i < bucketSize; ++i)
      if (table[hashCode][i].name == userPhone.name) {
        userPhone = table[hashCode][i];
        return true;
      }
    return false;
  }

  // phoneEntry &operator[](std::string key) { // key is user name
  //   int hashCode{hashString(key)};
  //   int bucketSize{(int)table[hashCode].size()};
  //
  //   for (int i = 0; i < bucketSize; ++i)
  //     if (key == table[hashCode][i].name)
  //       return table[hashCode][i];
  //
  //   phoneEntry *newUser{new phoneEntry};
  //   put(*newUser);
  //   return *newUser;
  // }

  void print() {
    int tableSize{(int)table.size()};
    int bucketSize{};

    for (int i = 0; i < tableSize; ++i) {
      bucketSize = (int)table[i].size();
      std::cout << "Hash " << i << ": ";
      for (int j = 0; j < bucketSize; ++j)
        table[i][j].print();

      std::cout << '\n';
    }
    std::cout << '\n';
  }
};
int main(int argc, char *argv[]) {
  HashTable table(3);
  table.put(phoneEntry("mostafa", "604-401-120"));
  table.put(phoneEntry("mostafa", "604-401-777")); // update
  table.put(phoneEntry("ali", "604-401-343"));
  table.put(phoneEntry("ziad", "604-401-17"));
  table.put(phoneEntry("hany", "604-401-758"));
  table.put(phoneEntry("belal", "604-401-550"));
  table.put(phoneEntry("john", "604-401-223"));

  phoneEntry e("mostafa", "");
  if (table.get(e))
    std::cout << e.phoneNumber << "\n"; // 604-401-777

  table.print();
  // Hash 0: (ali, 604-401-343)  (hany, 604-401-758)  (john, 604-401-223)
  // Hash 1: (mostafa, 604-401-777)  (ziad, 604-401-17)
  // Hash 2: (belal, 604-401-550)

  std::cout << table.remove(phoneEntry("smith", "")) << "\n"; // 0
  std::cout << table.remove(phoneEntry("hany", "")) << "\n";  // 1
  std::cout << table.remove(phoneEntry("belal", "")) << "\n"; // 1
  table.print();
  // Hash 0: (ali, 604-401-343)  (john, 604-401-223)
  // Hash 1: (mostafa, 604-401-777)  (ziad, 604-401-17)

  return 0;
}
