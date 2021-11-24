#include <iostream>
#include <math.h>
#include <vector>
#include <array>
#include <chrono> // для функций из std::chrono
#include <algorithm> // для std::sort()

const int g_arrayElements = 10000; // общее количество всех элементов массива

using namespace std;

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

  int c[50];
  int a[50][50];
  int b[50];
  for (int i = 0; i < 50; i++) {
    b[i] = i;
    c[i] = i;
    for (int j = 0; j < 50; j++)
      a[i][j] = max(i, j);
  }
  t.reset();

  for (int i = 0; i < 50; i++)
    for (int j = 0; j < 50; j++)
      c[i] = c[i] + a[i][j] * b[j];

  std::cout << "Time taken (loop tiling 1): " << t.elapsed() << '\n';
  t.reset();

  for (int i = 0; i < 50; i += 2)
    for (int j = 0; j < 50; j += 2)
      for (int ii = i; ii < min(i + 2, 50); ii++)
        for (int jj = j; jj < min(j + 2, 50); jj++)
          c[ii] = c[ii] + a[ii][jj] * b[ii];

  std::cout << "Time taken (loop tiling 2): " << t.elapsed() << '\n';

  t.reset();

  int i, w, x[1000], y[1000];
  w = 0;
  for (i = 0; i < 1000; i++) {
    x[i] += y[i];
    if (w)
      y[i] = 0;
  }

  std::cout << "Time taken (loop unswitching 1): " << t.elapsed() << '\n';

  t.reset();

  if (w) {
    for (i = 0; i < 1000; i++) {
      x[i] += y[i];
      y[i] = 0;
    }
  } else {
    for (i = 0; i < 1000; i++) {
      x[i] += y[i];
    }
  }

  std::cout << "Time taken (loop unswitching 2): " << t.elapsed() << '\n';

  char c1;
  std::cin >> c1;
  return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"