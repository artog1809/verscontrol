// Lab1.1_Pavlova.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "testing.h"

int main()
{
    int n;
    bool lucky;
    int d1, d2, d3, d4, d5, d6;

    input_printf("Input number:");
    scanf_s("%d", &n);

    d6 = n / 100000;
    n = n - d6 * 100000;
  
    d5 = n / 10000;
    n = n - d5 * 10000;

    d4 = n / 1000;
    n = n - d4 * 1000;

    d3 = n / 100;
    n = n - d3 * 100;

    d2 = n / 10;
    n = n - d2 * 10;

    d1 = n;

    lucky = (d1 == d4) && (d2 == d5) && (d3 == d6);

    if (lucky) {

<<<<<<< HEAD:Pavlova4.cpp
        printf("Number is lucky"); // text
    }
    else  {

        printf("Number is not lucky"); // text22
=======
        printf("Number is lucky"); // print 222
    }
    else  {

        printf("Number is not lucky"); // print text 222
>>>>>>> 3997a206249cd0b9f9d2805957cd502489296d9e:Pavlova2.cpp
    }
    WAIT_ANY_KEY
}
