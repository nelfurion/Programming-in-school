#include <iostream>
#include <list>

using namespace std;

void print(std::list<int> &l) {
  for (std::list<int>::iterator it = l.begin(); it != l.end(); ++it) {
    std::cout << *it <<std::endl;
  }
};

int main(int argc, char const *argv[]) {
  int a[] = {0,1,2,3,4,5,6,7,8,9};

  list<int> l1(a, a + 10);

  for (list<int>::iterator it = l1.begin(); it != l1.end(); ++it) {
    std::cout << *it << std::endl;
  }

  //print(l1);

  list<int>::iterator it = l1.begin();
  l1.insert(it, -10);
  it = l1.end();
  l1.insert(it, -10);
  print(l1);
  l1.erase(l1.begin(), l1.end());
  std::cout << "erased:" << std::endl;
  print(l1);

  /*push_back
   l1.size()
   push_front();
   list<int>::iterator it = l1.begin();
   insert(it, -10);
   it = end();
   insert(it, -10);*/
  return 0;
}
