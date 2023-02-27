#include <iostream>
//#include "testing.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru"); //кодировка 

	int x[4] = {};
	int y[4] = {};
	int a[3];
	int b[3];
	int r[3];
	int err = 0;

	printf("координаты:\n");


	for (int i = 1; i <= 3; i++)
	{
		scanf_s("%d", &x[i]);   //ввод координат треугольников
		scanf_s("%d", &y[i]);

		if (abs(x[i]) > 1000 || abs(y[i]) > 1000)   //диапазон 
		{
			err = 1;
		}
	}

	for (int i = 1; i <= 2; i++)
	{

		scanf_s("%d", &a[i]);	//ввод координат окружностей
		scanf_s("%d", &b[i]);
		scanf_s("%d", &r[i]);
		if (abs(a[i]) > 1000 || abs(b[i]) > 1000 || (r[i] < 1 || r[i]>50))	//диапазон
		{
			err = 1;
		}
	}

	int _in[3] = { 1,1,1 };
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 2; j++)
		{
			if ((x[i] - a[j]) * (x[i] - a[j]) + (y[i] - b[j]) * (y[i] - b[j]) > r[j] * r[j])
				_in[j] = 0;
		}
	}
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 3; j++)
		{
			if (i != j)
			{
				if (x[i] == x[j] && y[i] == y[j])
					err = 1;
			}
		}
	}
	if (x[1] == x[2] && x[2] == x[3])
		err = 1;
	if (y[1] == y[2] && y[2] == y[3])
		err = 1;

	if (x[2] != x[1])
	{
		double tmp = (double)(x[3] - x[1]) * (y[2] - y[1]) / (x[2] - x[1]) + y[1];
		if (tmp == y[3])
			err = 1;
	}
	if (err)
	{
		printf("invalid input data");
		return 0;
	}

	int _out = 1;

	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= 2; j++)
		{
			if ((x[i] - a[j]) * (x[i] - a[j]) + (y[i] - b[j]) * (y[i] - b[j]) < r[j] * r[j])
				_out = 0;
		}
	}

	for (int i = 1; i <= 3; i++)	//проверка
	{
		for (int j = 1; j <= 3; j++)
		{

			if (x[i] > a[1] + r[1] && x[j] < a[1] - r[1] && ((y[i] > a[1] + r[1] && y[j] < a[1] - r[1]) ||
				(y[j] > a[1] + r[1] && y[i] < a[1] - r[1])))
			{
				_out = 0;
			}
			if (x[i] > a[2] + r[2] && x[j] < a[2] - r[2] && ((y[i] > a[2] + r[2] && y[j] < a[2] - r[2]) ||
				(y[j] > a[2] + r[2] && y[i] < a[2] - r[2])))
			{
				_out = 0;
			}

			if (x[i] > a[2] + r[2] && x[j] < a[2] - r[2] && (y[i] == y[j] && a[2] - r[2]< y[i] && a[2] + r[2] > y[i])) //вторая окружность. если точки находятся на одной плоскости 
			{
				_out = 0;
			}
			if (x[i] > a[1] + r[1] && x[j] < a[1] - r[1] && (y[i] == y[j] && a[1] - r[1]< y[i] && a[1] + r[1] > y[i])) //первая окружность. если точки находятся на одной плоскости 
			{
				_out = 0;
			}

			if (y[i] > a[2] + r[2] && y[j] < a[2] - r[2] && (x[i] == x[j] && a[2] - r[2]< x[i] && a[2] + r[2] > x[i])) //вторая окружность. если точки находятся на одной плоскости 
			{
				_out = 0;
			}
			if (y[i] > a[1] + r[1] && y[j] < a[1] - r[1] && (x[i] == x[j] && a[1] - r[1]< x[i] && a[1] + r[1] > x[i])) //первая окружность. если точки находятся на одной плоскости 
			{
				_out = 0;
			}
		}
	}

	if (_in[1] || _in[2])
	{

		printf("1-треугольник внутри круга");
	}
	else if (_out)
	{
		printf("2 – треугольник вне кругов");
	}
	else
	{
		printf("3 – другие ситуации");
	}


}
/*1900:09:01
2038:12:31
*/