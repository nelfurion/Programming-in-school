#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
  vector<int> v1;

  for (int i = 0; i < 3; i++) {
    v1.push_back(i);
  }

  for (int i = 0; i < v1.size(); i++) {
    cout << v1[i] << endl;
  }

  //tues first class learn hello wordl, next learn objects and classes, next learn data structures, iterators
  std::cout << "v1: capacity: " <<v1.capacity() << std::endl;
  //capacity doubles when limit reached

  vector<int>::iterator it;

  it = v1.begin(); // what begin is actually for
  cout << "it= " << *it << endl;
  it++;
  cout << "it= " << *it << endl;

  cout << "in loop" << endl;
  for (it = v1.begin(); it < v1.end(); it++) {
    cout << "it= " << *it << endl;
  }
  return 0;
}
