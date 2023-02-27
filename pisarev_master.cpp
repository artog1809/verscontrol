#include <iostream>
#include <cstdlib>
using namespace std;

// Проверить попадание в круг.
bool inCircle(float x, float y,
  float cx, float cy, float r)
  // координаты центра круга и его радиус
{
  // Константы -- после инициализации значения не изменяются.
  const float dx = x - cx,
              dy = y - cy;

  return dx * dx + dy * dy <= r * r;
}

// Проверить попадание в прямоугольник.
bool inRectangle(float x, float y,
  float left, float right, float bottom, float top)
  // координаты левой, правой, нижней и верхней граней
{
  return left <= x && x <= right // && -- "и"
    && bottom <= y && y <= top;
}

// Проверить попадание в заданную фигуру.
bool inFigure(float x, float y)
{
  // фигура может быть представлена как пересечение полуплоскости и
  // объединения трёх фигур: двух прямоугольников и сегмента круга
  return (inRectangle(x, y,  2.0,  4.0, -5.0, 5.0)
       || inRectangle(x, y, -4.0, -2.0, -5.0, 5.0) // || -- "или"
       || inCircle(x, y, -2.0, 0.0, 5.0)) && x >= -4.0;
}


int main()
{
  cout << "Enter a sequence of coordinates x, y: ";
  // Определение переменных; условие продолжения; последнее действие на каждом повторении.
  for (double x = 0, y = 0; cin >> x >> y;)
  {
    cout << "(" << x << ", " << y << ") " <<
      (inFigure(x, y)? "is": "is not") // "тернарный оператор": условие в выражении
      << " inside the figure" << endl;
  }
  return EXIT_SUCCESS;
}