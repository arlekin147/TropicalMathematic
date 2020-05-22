// TropicalMathematic.cpp: определяет точку входа для консольного приложения.
//
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "stdafx.h"
#include "Matrix.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>

using namespace rapidjson;

int main()
{
	std::string json = "[{\"Rows\":2,\"Elements\":[[1, 2], [3, 4]]}]";
	std::ifstream t("result.json");
	std::string str2;

	t.seekg(0, std::ios::end);
	str2.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str2.assign((std::istreambuf_iterator<char>(t)),
				std::istreambuf_iterator<char>());

	// std::cout << str2;

	Document document;
	document.Parse(str2.c_str());
	const Value &a = document.GetArray();
	int numberOfMatrixes = document.Size();
	std::cout << "Size: " << numberOfMatrixes << std::endl;
	auto matrix = a[0].GetObject()["Elements"].GetArray();
	auto array = a[0].GetObject()["Elements"].GetArray();

	auto size = a[0].GetObject()["Rows"].GetInt();

	std::cout << document.GetArray().Size();
	std::cout << document.Size();

	Tropical_Int **parsedMatrix;
	std::vector<Matrix> tropicalMatrixes;
	for (int n = 0; n < a.Size(); ++n)
	{
		auto size = a[n].GetObject()["Rows"].GetInt();
		auto matrix = a[n].GetObject()["Elements"].GetArray();

		parsedMatrix = new Tropical_Int *[size];
		for (int i = 0; i < size; ++i)
		{
			parsedMatrix[i] = new Tropical_Int[size];
			for (int j = 0; j < size; ++j)
			{
				parsedMatrix[i][j] = Tropical_Int(matrix[i][j].GetInt());
			}
		}

		tropicalMatrixes.push_back(Matrix(parsedMatrix, size));
	}

	std::cout << parsedMatrix[0][0];

	// for (SizeType i = 0; i < matrix.Size(); i++) // Uses SizeType instead of size_t
	// 	for(SizeType j = 0; j < matrix.Size(); ++j)
	// 		printf("a[%d][%d] = %d " , i, j, matrix[i][j].GetInt());
	// 	std::cout << std::endl;

	setlocale(LC_ALL, "Rus");
	int str, col;
	// std::cout << "Input number of rows\n";
	// std::cin >> str;
	// std::cout << "Input number of collumns\n";
	// std::cin >> col;
	// Matrix input(parsedMatrix, size);
	// input.MatrixInput();
	// Matrix downMatrix(parsedMatrix, size); //= input;
	for (auto matrix : tropicalMatrixes)
	{
		matrix.searchDownMatrix();
	}
	// downMatrix.getAnswer(input);
	std::cout << "Finish";
	getch();
	return 0;
}