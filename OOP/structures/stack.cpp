#include <iostream>

using namespace std;

#define STACK_SIZE 10

class Stack {
  int top_;
  char elems_[STACK_SIZE];

public:

  Stack() {
    top_ = 0;
  }

  int push(char new_element) {
    if (is_full()) {
      cout << "OOP Stack is full :) :)" << endl;
      return -1;
    }

    elems_[top_++] = new_element;
    return 0;
  }

  char pop(int& val) {
    if (is_empty()) {
      return -1;
    }

    val = elems_[--top_];
    return 0;
  }

  char peek() {
    if(is_empty()) {
      cout << "Stack is empty" << endl;
      return -1;
    }
    return elems_[top_ - 1];
  }

  int top() {
    return top_;
  }

  bool is_full() {
    return top_ == STACK_SIZE;
  }

  bool is_empty() {
    return top_ == 0;
  }

  /*int hasValidTopPointer() {
    if (top_ < 0) {
      return 1;
    } else if (top_ > max_) {
      return 2;
    }

    return 0;
  }*/
};

int main() {

  Stack s;
  for (int i = 0; i < 15; i++) {
    if (s.push(i) == -1) {
      cout << "Error in push" << endl;
      break;
    }
  }

  while (true) {
    int val;

    if (s.pop(val) == -1) {
      cout << "Error in pop" << endl;
      break;
    }

    cout << val << endl;
  }

  return 0;
}
