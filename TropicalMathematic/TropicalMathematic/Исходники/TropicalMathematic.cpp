// TropicalMathematic.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "Matrix.h"


int main()
{
	setlocale(LC_ALL, "Rus");
	int str, col;
	std::cout << "������� ���-�� ����� ������� �������\n";
	std::cin >> str;
	std::cout << "������� ���-�� �������� ������� �������\n";
	std::cin >> col; 
	Matrix input(str, col);
	input.MatrixInput();
	system("cls");
	std::cout << "�� ����� ������� \n";
	input.MatrixOutput();
	Matrix downMatrix = input;
	downMatrix.searchDownMatrix();
	downMatrix.getAnswer(input);
	getch();
    return 0;
}

