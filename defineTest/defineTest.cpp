#include <iostream>
#include <math.h>
#include <vector>
#include <array>
#include <chrono> // для функций из std::chrono
#include <algorithm> // для std::sort()

using namespace std;

#define MYMIN(X, Y)(X < Y ? X : Y)

int mymin(int a, int b) {
  return a < b ? a : b;
}

class Timer {
  private:
    // Псевдонимы типов используются для удобного доступа к вложенным типам
    using clock_t = std::chrono::high_resolution_clock;
  using second_t = std::chrono::duration < double, std::ratio < 1 > > ;

  std::chrono::time_point < clock_t > m_beg;

  public:
    Timer(): m_beg(clock_t::now()) {}

  void reset() {
    m_beg = clock_t::now();
  }

  double elapsed() const {
    return std::chrono::duration_cast < second_t > (clock_t::now() - m_beg).count();
  }
};

int main() {

  Timer t;

  int m = 0;
  for (int i = 0; i < 100000; i++) {
    m = MYMIN(i, i + 1);
  }

  std::cout << "Time taken (define): " << t.elapsed() << '\n';

  t.reset();

  m = 0;
  for (int i = 0; i < 100000; i++) {
    m = MYMIN(i, i + 1);
  }

  std::cout << "Time taken (define): " << t.elapsed() << '\n';

  t.reset();

  m = 0;
  for (int i = 0; i < 100000; i++) {
    m = MYMIN(i, i + 1);
  }

  std::cout << "Time taken (define): " << t.elapsed() << '\n';

  t.reset();

  m = 0;
  for (int i = 0; i < 100000; i++) {
    m = mymin(i, i + 1);
  }

  std::cout << "Time taken (function): " << t.elapsed() << '\n';

  t.reset();

  m = 0;
  for (int i = 0; i < 100000; i++) {
    m = mymin(i, i + 1);
  }

  std::cout << "Time taken (function): " << t.elapsed() << '\n';

  t.reset();

  m = 0;
  for (int i = 0; i < 100000; i++) {
    m = mymin(i, i + 1);
  }

  std::cout << "Time taken (function): " << t.elapsed() << '\n';

  char c1;
  std::cin >> c1;
  return 0;
}