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

void sortArray(std::array < int, g_arrayElements > & array) {

  // Перебираем каждый элемент массива (кроме последнего, он уже будет отсортирован к тому времени, когда мы до него доберемся)
  for (int startIndex = 0; startIndex < g_arrayElements - 1; ++startIndex) {
    // В переменной smallestIndex хранится индекс наименьшего значения, которое мы нашли в этой итерации.
    // Начнем с того, что наименьший элемент в этой итерации - это первый элемент (индекс 0)
    int smallestIndex = startIndex;

    // Затем ищем элемент меньше нашего smallestIndex в оставшейся части массива
    for (int currentIndex = startIndex + 1; currentIndex < g_arrayElements; ++currentIndex) {
      // Если нашли элемент, который меньше нашего наименьшего элемента
      if (array[currentIndex] < array[smallestIndex])
        // то записываем/запоминаем его
        smallestIndex = currentIndex;
    }

    // smallestIndex теперь является наименьшим элементом в оставшейся части массива.
    // Меняем местами наше стартовое наименьшее значение с тем, которое мы обнаружили
    std::swap(array[startIndex], array[smallestIndex]);
  }
}

template < class T >
  T HandleMatrix(vector < vector < T >> & M) {
    int i, j;
    T sum_prod = 0;
    for (i = 0; i < M.size(); i++) {
      T prod = 1;
      for (j = 0; j < M[i].size(); j++) {
        prod *= M[i][j];
      }
      sum_prod += prod;
      //cout << "\nHM " << i;
    }
    return sum_prod;
  }

template < class T >
  T LoopUnrolling(vector < vector < T >> & M) {
    int i, j;
    T sum_prod = 0;
    for (i = 0; i < M.size(); i++) {
      T prod1 = 1;
      T prod2 = 1;
      T prod3 = 1;
      //T prod4 = 1;
      //T prod5 = 1;
      for (j = 0; j < M[i].size(); j += 3)
      //for (j = 0; j < M[i].size(); j+=5)
      {
        prod1 *= M[i][j];
        prod2 *= M[i][j + 1];
        prod3 *= M[i][j + 2];
        //prod4 *= M[i][j+3];
        //prod5 *= M[i][j+4];
      }
      sum_prod += prod1 * prod2 * prod3;
      //sum_prod += prod1 * prod2 * prod3*prod4*prod5;
    }
    return sum_prod;
  }

int main() {
  std::array < int, g_arrayElements > array;
  for (int i = 0; i < g_arrayElements; ++i)
    array[i] = g_arrayElements - i;

  /*vector<vector<double>> matrix;
  int i, j;
  for (i = 0; i < 2500; i++)
  {
  	vector<double> v;
  	for (j = 0; j < 2500; j++)
  	{
  		v.push_back(cos(i+j));
  	}
  	matrix.push_back(v);
  	//cout << "\nPush " << i;
  }*/

  Timer t;

  //std::sort(array.begin(), array.end());
  sortArray(array);

  std::cout << "Time taken (sort array): " << t.elapsed() << '\n';

  t.reset();

  //double res = HandleMatrix(matrix);

  std::cout << "Time taken (HandleMatrix): " << t.elapsed() << '\n';

  t.reset();

  //double res = LoopUnrolling(matrix);

  std::cout << "Time taken (LoopUnrolling): " << t.elapsed() << '\n';

  char c1;
  std::cin >> c1;
  return 0;
}