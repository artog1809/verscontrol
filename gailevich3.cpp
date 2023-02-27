// 09_Gailevich_Y_V.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "..\09_Gailevich_Y_V\Header.h"

#define MAX_STRING_AMOUNT 60
#define MAX_STRING_LENGTH 90
#define MAX_OPERATOR_LENGTH 10

int findFirstStringWithGivenOperator(char code[MAX_STRING_AMOUNT][MAX_STRING_LENGTH], char oper[MAX_OPERATOR_LENGTH], int StringAmount)
{
	int i=0; // Счетчик для цикла


	bool isLeftLetter, isRightLetter;

	char* Devider;

	for (i = 0; i < StringAmount; i ++) //Для каждой строки текста программы
	{
		if (strstr(code[i], oper) != NULL) 
		{
			
			Devider = strstr(code[i], oper);

			isRightLetter = isalnum(*(Devider + OperLength));


			if (isLeftLetter == 0 && isRightLetter == 0)
			{
				return i;
			}

		}
	}
	return -1;
}

int main()
{
	int M, OutputStringIndex;

	//-------Ввод данных-------------
	scanf_s("%d", M);

	if (M < 1 || M > 40)
	{
		printf("invalid input data");
		return 0;
	}

	for (int k = 0; k < M + 1; k++)
	{
		gets_s(InputText[k]);
	}

	gets_s(GivenOperator);

	char OperatorDevider[] = " ";
	char* SeparatedOperator;

	SeparatedOperator = strtok(GivenOperator, OperatorDevider);

	//-----Вызов главной вычислительной функции---------
	OutputStringIndex = findFirstStringWithGivenOperator(InputText, GivenOperatorCut, M);

	//-------Вывод результатов--------

	if (OutputStringIndex == -1)
	{
		printf("Operator Not Found");
	}
	else
	{
		printf("%d", OutputStringIndex);
	}

}

//Считать индекс текущего элемента равным нулю
	//Пока не пройдены все элементы строки

	//Если текущий элемент является разделителем
	
	//Иначе
	
		//Перейти к следующему элементу
	




