// TropicalMathematic.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Matrix.h"


int main()
{
	setlocale(LC_ALL, "Rus");
	int str, col;
	std::cout << "Введите кол-во строк матрицы матрицы\n";
	std::cin >> str;
	std::cout << "Введите кол-во столбцов матрицы матрицы\n";
	std::cin >> col; 
	Matrix input(str, col);
	input.MatrixInput();
	system("cls");
	std::cout << "Вы ввели матрицу \n";
	input.MatrixOutput();
	Matrix downMatrix = input;
	downMatrix.searchDownMatrix();
	downMatrix.getAnswer(input);
	getch();
    return 0;
}

