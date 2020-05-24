// TropicalMathematic.cpp: определяет точку входа для консольного приложения.
//
#include <windows.h>
#include "stdafx.h"
#include "Matrix.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include "threads/mingw.thread.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
// #include "rapidjson/stringbuffer.h"

using namespace rapidjson;

void startSolving(Matrix matrix)
{
	std::cout << "Here" << std::endl;
	Matrix origin(matrix.matrix, matrix.str);
	// Matrix matrixForBlockDiagonal(origin.matrix, origin.str);
	Tropical_Int *blockDiagonalAnswer = new Tropical_Int[matrix.str];

	std::vector<Matrix*>* matrixesForSimpleSoultion = new std::vector<Matrix*>;
	std::vector<Matrix*>* matrixesForBlockSoultion = new std::vector<Matrix*>;

	for(int i = 0; i < 10000; ++i)
	{
		matrixesForSimpleSoultion->push_back(new Matrix(origin.matrix, origin.str));
		matrixesForBlockSoultion->push_back(new Matrix(origin.matrix, origin.str));
	}

	int start = GetTickCount();
	for (int i = 0; i < 10000; ++i)
	{
		(*matrixesForSimpleSoultion)[i]->searchDownMatrix();
	}
	int end = GetTickCount();
	std::cout << "Time of simple alghoritm" << end - start << std::endl;

	start = GetTickCount();
	for (int i = 0; i < 10000; ++i)
	{
		(*matrixesForBlockSoultion)[i]->blockDiagonalSolving(blockDiagonalAnswer);
	}
	end = GetTickCount();
	std::cout << "Time of multithread alghoritm" << end - start << std::endl;
 	Tropical_Int *answer = new Tropical_Int[matrix.str];
	// matrixesForSimpleSoultion[0].getAnswer(origin);
	// auto isResolvable = matrixForBlockDiagonal.rightGetAnswer(origin, answer);
	// if (isResolvable)
	// {
	// 	for (int i = 0; i < matrixForBlockDiagonal.str; ++i)
	// 	{
	// 		std::cout << blockDiagonalAnswer[i] << " ";
	// 	}
	// 	std::cout << std::endl;
	// }
	// else
	// {
	// 	std::cout << "Matrix is unresolvable" << std::endl;
	// }
	// matrix.getAnswer(origin);
}

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

	Document document;
	document.Parse(str2.c_str());
	const Value &a = document.GetArray();
	int numberOfMatrixes = document.Size();
	auto matrix = a[0].GetObject()["Elements"].GetArray();
	auto array = a[0].GetObject()["Elements"].GetArray();

	auto size = a[0].GetObject()["Rows"].GetInt();

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
		// for (int i = 0; i < 1000; ++i)
		// {
		// std::thread threadForSolving(startSolving, matrix);
		// threadForSolving.join();
		// }
		startSolving(matrix);
	}
	std::cout.flush();
	std::cout << "Finish";
	return 0;
}
