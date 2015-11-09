#include <iostream>

using namespace std;

#define STACK_SIZE 10

class StackError {
  int status_;
public:
  StackError(int status) {
    status_ = status;
  }

  int get_status() {
    return status_;
  }
};

class Stack {
  int top_;
  char elems_[STACK_SIZE];

public:

  Stack() {
    top_ = 0;
  }

  void push(char new_element) {
    if (is_full()) {
      throw StackError(1);
    }

    elems_[top_++] = new_element;
  }

  char pop() {
    if (is_empty()) {
      throw StackError(2);
    }

    return elems_[--top_];
  }

  char peek() {
    if(is_empty()) {
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
    try {
      s.push(i);
    } catch (StackError ex) {
      cout << "Stack error catched" << endl;
    }
  }

  try {
    for (int i = 0; i < 15; i++) {
      s.push(i);
    }
    cout << "not executed" << endl;
  } catch (StackError ex) {
    cout << "Stack error catched" << endl;
  }

  try {
    while (true) {
      int i = s.pop();

      cout << i << endl;
    }
  } catch (StackError ex) {
    cout << "Stack error in pop" << endl;
    cout << "Status: " << ex.get_status() << endl;
  }


  return 0;
}
