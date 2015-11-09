namespace elsys {
  class Student {

  };

  class Teacher {

  };
};

namespace tues {
  class Student {

  };

  class Teacher {

  };
};

int foo() {
  using namespace tues;
  return 0;
}

int main () {
  foo();
  elsys::Teacher t1;
  tues::Teacher t2;

  using elsys::Student;
  Student st1;

  using namespace std;
  using namespace elsys;
  return 0;
}
