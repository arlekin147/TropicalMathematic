#pragma once
#include <windows.h>
#include "Tropical_Int.h"
#include <climits>
#include <vector>
#include "threads/mingw.thread.h"
#include <thread>

class Matrix;
void startSolving(Matrix matrix, bool *allMatrixResolvable, Tropical_Int *answer, int currentAnswerPosition);

class Matrix
{

public:
	Matrix(int str, int col)
	{
		this->str = str;
		this->col = col;
		this->matrix = new Tropical_Int *[str];
		for (int i = 0; i < str; ++i)
		{
			this->matrix[i] = new Tropical_Int[col];
			for (int j = 0; j < col; ++j)
			{
				this->matrix[i][j] = 0;
			}
		}
		j = new bool[col];
		for (int i = 0; i < col; ++i)
		{						//Если в элементе массива с соответствующим номером стоит true =>
			this->j[i] = false; // этот столбец добавлен в множество j
		}
	}

	Matrix(Tropical_Int **matrix, int size)
	{
		this->str = size;
		this->col = size;

		this->matrix = new Tropical_Int *[str];
		for (int i = 0; i < str; ++i)
		{
			this->matrix[i] = new Tropical_Int[col];
			for (int j = 0; j < col; ++j)
			{
				this->matrix[i][j] = matrix[i][j];
			}
		}
		j = new bool[col];
		for (int i = 0; i < col; ++i)
		{						//Если в элементе массива с соответствующим номером стоит true =>
			this->j[i] = false; // этот столбец добавлен в множество j
		}
	}

	~Matrix()
	{
		delete[] this->matrix;
	}
	Matrix &operator=(const Matrix &mx)
	{
		for (int i = 0; i < this->str; ++i)
		{
			for (int j = 0; j < this->col; ++j)
			{
				this->matrix[i][j] = mx.matrix[i][j];
			}
		}
		for (int i = 0; i < this->col; ++i)
		{
			this->j[i] = mx.j[i];
		}
		return *this;
	}
	Matrix(const Matrix &mx)
	{
		this->str = mx.str;
		this->col = mx.col;
		this->matrix = new Tropical_Int *[str];
		for (int i = 0; i < str; ++i)
		{
			this->matrix[i] = new Tropical_Int[col];
			for (int j = 0; j < col; ++j)
			{
				this->matrix[i][j] = 0;
			}
		}
		j = new bool[col];
		for (int i = 0; i < this->str; ++i)
		{
			for (int j = 0; j < this->col; ++j)
			{
				this->matrix[i][j] = mx.matrix[i][j];
			}
		}
		for (int i = 0; i < this->col; ++i)
		{
			this->j[i] = mx.j[i];
		}
	}
	void MatrixInput()
	{
		for (int i = 0; i < this->str; i++)
		{
			std::cout << "Input a row with number " << i << std::endl;
			for (int j = 0; j < this->col; ++j)
			{
				std::cin >> this->matrix[i][j];
			}
		}
	}
	void MatrixOutput()
	{
		for (int i = 0; i < this->str; ++i)
		{
			for (int j = 0; j < this->col; ++j)
			{
				std::cout << this->matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
	void addInJ(int num)
	{
		this->j[num] = true;
	}
	bool conatinsInJ(int num)
	{
		return this->j[num];
	}
	bool searchMin(int num, bool mode)
	{ //true - минимум строгий / false - нестрогий
		int numOfMin;
		bool result = true;
		bool first = true;
		Tropical_Int min = INT_MAX;
		for (int i = 0; i < this->col; ++i)
		{
			if (this->matrix[num][i] < min)
			{
				min = this->matrix[num][i];
				numOfMin = i;
			}
		}
		for (int i = 0; i < this->col; ++i)
		{
			if (this->matrix[num][i] == min && !this->conatinsInJ(i))
			{
				numOfMin = i;
				if (first)
					first = false;
				else
					return false;
			}
		}
		if (!this->conatinsInJ(numOfMin))
		{
			if (mode)
			{
				this->addInJ(numOfMin);
			}
			return true;
		}
		else
			return false;
	}
	void searchDownMatrix()
	{
		bool flag;
		do
		{
			do
			{
				flag = false;
				for (int i = 0; i < this->str && !flag; ++i)
				{
					flag = this->searchMin(i, 1);
				}
			} while (flag);
			Tropical_Int constant = searchConstant();
			if (constant == 0)
				break;
			for (int i = 0; i < this->str; ++i)
			{
				for (int j = 0; j < this->col; ++j)
				{
					if (!this->conatinsInJ(j))
					{
						this->matrix[i][j] /= constant;
					}
				}
			}
			if (!this->jIsFool())
			{
				this->jFree();
				for (int i = 0; (i < this->str) && !(flag = searchMin(i, 0)); ++i)
					;
			}
			else
				flag = false;
		} while (flag);
	}
	void jFree()
	{
		for (int i = 0; i < this->col; ++i)
			this->j[i] = false;
	}
	Tropical_Int searchConstant()
	{
		Tropical_Int constant = INT_MAX;
		for (int i = 0; i < this->str; ++i)
			if (searchMinWithoutJ(i) > searchMinInJ(i))
				constant -= (searchMinWithoutJ(i) / searchMinInJ(i));
		return constant;
	}
	Tropical_Int searchMinInJ(int num)
	{
		int first;
		for (first = 0; first < this->col && !this->conatinsInJ(first); ++first)
			;
		Tropical_Int result = this->matrix[num][first];
		for (int i = 0; i < this->col; ++i)
		{
			if (this->conatinsInJ(i))
				result -= this->matrix[num][i];
		}
		return result;
	}
	Tropical_Int searchMinWithoutJ(int num)
	{
		int first;
		for (first = 0; first < this->col && this->conatinsInJ(first); ++first)
			;
		Tropical_Int result = this->matrix[num][first];
		for (int i = 0; i < this->col; ++i)
		{
			if (!this->conatinsInJ(i))
				result -= this->matrix[num][i];
		}
		return result;
	}

	bool jIsFool()
	{ //true если j максимальное / false если нет
		bool result = true;
		for (int i = 0; i < this->col && result; ++i)
			result = this->j[i];
		return result;
	}

	void getAnswer(Matrix mx)
	{
		if (!this->jIsFool())
		{
			std::cout << "Answer is : ";
			for (int i = 0; i < this->col; ++i)
			{
				std::cout << this->matrix[0][i] / mx.matrix[0][i] << " ";
			}
		}
		else
			std::cout << "This system is unresolvable\n";
	}

	bool rightGetAnswer(Matrix mx, Tropical_Int *answer)
	{
		if (this->jIsFool())
			return false;
		// answer = new Tropical_Int[mx.str];
		for (int i = 0; i < mx.str; ++i)
		{
			answer[i] = this->matrix[0][i] / mx.matrix[0][i];
		}
		return true;
	}

	bool blockDiagonalSolving(Tropical_Int *answer)
	{
		auto subMatrixes = getBlocks();

		int currentAnswerPosition = 0;
		bool *allMatrixResolvable = new bool;
		*allMatrixResolvable = true;
		std::vector<std::thread*> threads;
		for (auto subMatrix : subMatrixes)
		{
			std::thread* resolving = new std::thread(startSolving, subMatrix, allMatrixResolvable, answer, currentAnswerPosition);
			threads.push_back(resolving);

			currentAnswerPosition += subMatrix.str;
		}

		for(int i = 0; i < threads.size(); ++i)
		{
			threads[i]->join();
		}
		return *allMatrixResolvable;
	}

	Tropical_Int **matrix;
	int str, col;

private:
	bool *j;

	std::vector<Matrix> getBlocks()
	{
		auto leftSize = this->str;
		auto currentIPosition = 0;
		auto currentJPosition = 0;
		std::vector<Matrix> subMatrixes;
		while (leftSize)
		{
			auto currentSize = 0;
			for (int j = currentJPosition; this->matrix[currentIPosition][j] != 2147483647 && j != this->str; ++j, ++currentSize);
			Tropical_Int **subMatrix = new Tropical_Int *[currentSize];
			for (int i = currentIPosition; i < currentIPosition + currentSize; ++i)
			{
				subMatrix[i - currentIPosition] = new Tropical_Int[currentSize];
				for (int j = currentJPosition; j < currentJPosition + currentSize; ++j)
				{
					subMatrix[i - currentIPosition][j - currentJPosition] = this->matrix[i][j];
				}
			}

			subMatrixes.push_back(Matrix(subMatrix, currentSize));

			leftSize -= currentSize;
			currentIPosition += currentSize;
			currentJPosition += currentSize;
		}
		return subMatrixes;
	}
};

void startSolving(Matrix matrix, bool *allMatrixResolvable, Tropical_Int *answer, int currentAnswerPosition)
{
	Matrix matrixCopy(matrix.matrix, matrix.str);
	matrix.searchDownMatrix();
	auto isSubSystemResolvable = matrix.rightGetAnswer(matrixCopy, answer + currentAnswerPosition);
	if (!isSubSystemResolvable)
		*allMatrixResolvable = false;
}
