#include <iostream>
#include <vector>

//using namespace std;

void print(std::vector<int> &v) {
  for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << *it <<std::endl;
  }
};

int main() {
  int a[] = {0,1,2,3,4,5,6,7,8,9};

  std::vector<int> v1(a, a + 10);
  std::cout << "v1 - size: " << v1.size() << std::endl;
  print(v1);

  std::vector<int>::iterator it = v1.begin();

  v1.insert(it, -1);
  print(v1);

  it = v1.end();
  v1.insert(it, 1000);
  print(v1);

  it = v1.begin();
  int* b = a;

  std::cout << "HERE: " << -**&++--it++-- << std::endl;
  -++*it++;
  v1.insert(it, 123123);
  print(v1);
  return 0;
}
