#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Функция для нахождения перекрестного произведения двух векторов
int CrossProduct(vector<double>& A)
{
	// Хранит коэффициент направления X вектора 1
	int X1 = (A[2] - A[0]);

	// Хранит коэффициент направления Y вектора 1
	int Y1 = (A[3] - A[1]);

	// Хранит коэффициент направления X вектора 2
	int X2 = (A[4] - A[0]);

	// Хранит коэффициент направления Y вектора 2
	int Y2 = (A[5] - A[1]);

	// Возвращает перекрестное произведение
	return (X1 * Y2 - Y1 * X2);
}


// Функция для проверки того, является многоугольник выпуклым или нет
bool isPolygonConvex(vector<double>& points)
{
	// Хранит количество ребер в полигоне
	int N = points.size();

	// Хранит направление перекрестного произведения предыдущих пройденных ребер
	int prev = 0;

	// Хранит направление перекрестного произведения текущих пройденных ребер
	int curr = 0;

	// Проход по массиву
	for (int i = 0; i < points.size() - 1; i += 2) {

		// Хранит три смежных ребра многоугольника
		vector<double> temp = { points[i % N], points[(i + 1) % N],
			points[(i + 2) % N], points[(i + 3) % N],
			points[(i + 4) % N], points[(i + 5) % N]
		};

		// Обновление curr
		curr = CrossProduct(temp);

		// Если curr не равен 0
		if (curr != 0) {

			// Если направление перекрестного произведения всех соседних ребер не совпадает
			if (curr * prev < 0) {
				return false;
			}
			else {
				// Обновление curr
				prev = curr;
			}
		}
	}
	return true;
}

int main(const int argc, char* argv[])
{
	//----------ПРОВЕРКА ОШИБОК РАБОТЫ С ФАЙЛАМИ----------

	if (argc == 1)
	{
		cout << "The input file is specified incorrectly. It is possible that the file at the specified location does not exist.\n";
		return 0;
	}

	//Выдать ошибку, если выходной файл не указан в аргументах командной строки
	if (argc == 2)
	{
		cout << "The output file is specified incorrectly. It is possible that the file at the specified location does not exist..\n";
		return 0;
	}

	ifstream inputFile;	//Файл ввода

	inputFile.open(argv[1]);

	if (!inputFile.is_open()) //Выдать ошибку,если входной файл невозможно открыть
	{
		cout << "The input file cannot be opened. The file may have the wrong extension.\n";
		return 0;
	}

	ofstream outputFile;//Файл вывода

	outputFile.open(argv[2]);

	if (!outputFile.is_open()) //Выдать ошибку,если выходной файл невозможно открыть
	{
		cout << "The output data file cannot be opened. The file may have the wrong extension.\n";
		return 0;
	}
	else
	{
		outputFile.trunc;
	}

	string inStr; //Переменная считывающая данные из файла ввода

	int numberOfPolygons; //Количество многоугольников

	vector<vector<double>> initialCoordinatesVector; //двумерный вектор (вектор векторов)

	vector<vector<double>> totalCoordinatesVector;

	int numberOfVertices; //количество вершин в многоугольнике

	double coordinateItself; //сама координата

	while (!inputFile.eof())
	{
		inStr = "";
		inputFile >> inStr;

		numberOfPolygons = std::stoi(inStr); //считывание количества многоугольников из файла ввода

		if (numberOfPolygons < 0)
		{
			outputFile << "The number of polygons is incorrectly specified.";
			return 0;
		}
		else if (numberOfPolygons == 0)
		{
			outputFile << "There are no polygons on the plane.";
			return 0;
		}

		initialCoordinatesVector.resize(numberOfPolygons);

		for (int i = 0; i < numberOfPolygons; i++)
		{
			inputFile >> inStr;

			numberOfVertices = std::stoi(inStr); //считывание количества вершин в многоугольнике из файла ввода

			if (numberOfVertices < 3) //если количество вершин меньше трех - не получится замкнутой фигуры
			{
				outputFile << "The number of vertices in " << i + 1 << " polygon is incorrectly specified.";
				return 0;
			}

			initialCoordinatesVector[i].resize(2 * numberOfVertices);

			for (int j = 0; j < (2 * numberOfVertices); j++)
			{
				inputFile >> inStr;

				coordinateItself = std::stod(inStr);//считывание координаты из файла ввода

				initialCoordinatesVector[i][j] = coordinateItself;
			}
		}
	}

	//-----------------ПРОВЕРКА МНОГОУГОЛЬНИКА НА ВЫПУКЛОСТЬ, ЕСЛИ ВЕРШИН БОЛЬШЕ, ЧЕМ 4
	for (int i = 0; i < numberOfPolygons; i++)
	{
		if (numberOfVertices > 4)
		{
			if (isPolygonConvex(initialCoordinatesVector[i]) == 0)
			{
				outputFile << "Polygon specified " << i + 1 << " is non-convex." << endl;
				return 0;
			}
		}
	}

	outputFile.close();
	return 0;
}
