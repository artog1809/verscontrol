#include "constantInFunction.h"

constantInFunction::constantInFunction()
{
	this->name = "-1"; //������ ��� �������
	this->countInFunction = 0; //���������� ������� ������ ��������� �� ������� ������ 1
}


constantInFunction::constantInFunction(std::string _name, int _stringNum)
{
	this->name = _name; //������ ��� �������
	this->appearingStrings[0] = _stringNum; //�������� ������ ������� ��������� � �������� ������
}


constantInFunction::~constantInFunction()
{
}



/*
�������� ����� ������ ������ ��������� ������ ����� �������
*/
short constantInFunction::getAppearanceCount() 
{
	int a = 1;
	return this->countInFunction;
}

/*
* �������� ����� ������,� ������� ��������� �����������,�� ������� ����� �� �������
\param[in] index - ������ ������,��� ��������� ���������, � �������
*/
short constantInFunction::getAppearingString(int index) 
{
	if (index > 0 && index < countInFunction)
		return this->appearingStrings[index];
	else
		return -1;
}


/*
�������� ������� ��������� �� ����������� ������
\param[in] string - ����� ������,�� ������� ��������� ���������
*/
void constantInFunction::addNewAppearance(int string)	
{
	if (string > 0 && string<MAX_STRING_NUMBER)
		this->appearingStrings[countInFunction] = string;	//�������� ������� ��������� �� �������� ������,���� ��� �� ��������
	countInFunction += 1;	//��������� ����� ������ ���� ��������� � ������� �� 1
}

/*
������ ��� ���������
\param[in] name - ���,���������� ���������
*/
void constantInFunction::setName(std::string _name)
{
	this->name = _name;
}
