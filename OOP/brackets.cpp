#include <iostream>

using namespace std;

class Stack {
  int max_, top_;
  char elems_[100];

public:

  Stack() {
    max_ = 100;
    top_ = 0;
  }

  void push(char new_element) {
    if (isFull()) {
      return;
    }

    elems_[top_++] = new_element;
  }

  char pop() {
    if (isEmpty()) {
      return - 1;
    }

    return elems_[top_--];
  }


  char peek() {
    if(isEmpty()) {
      return -1;
    }
    return elems_[top_ - 1];
  }

  int top() {
    return top_;
  }

  bool isFull() {
    if (top_ == max_) {
      return true;
    }

    return false;
  }

  bool isEmpty() {
    if (top_ == 0) {
      return true;
    }

    return false;
  }

  int hasValidTopPointer() {
    if (top_ < 0) {
      return 1;
    } else if (top_ > max_) {
      return 2;
    }

    return 0;
  }
};

int main() {
  Stack brackets;

  char comment[256];

  bool good = true;
  char next;
  while(true) {
    cin >> next;

    if(next == '/') {
      char fol = cin.peek();
      if (fol == '/') {
        cin.getline(comment, 256);
      } else if (fol == '*') {
        do {
          cin.ignore(256, '*');
          cin >> fol;
        } while (fol != '/');
      }
    }

    if (!cin) {
      break;
    }

    if (next == '}') {
      if (brackets.peek() == '{') {
        brackets.pop();
      } else {
        good = false;
        break;
      }
    } else if (next == ']') {
      if (brackets.peek() == '[') {
        brackets.pop();
      } else {
        good = false;
        break;
      }
    } else if (next == ')') {
      if (brackets.peek() == '(') {
        brackets.pop();
      } else {
        good = false;
        break;
      }
    } else {
      if (next == '{' ||
          next == '[' ||
          next == '(')
          brackets.push(next);
    }
  }

  if (good && brackets.top() == 0) {
    cout << "All good!" << endl;
  } else {
    cout << "Error in brackets!" << endl;
  }

  return 0;
}
