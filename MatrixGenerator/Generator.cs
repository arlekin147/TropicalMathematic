using System;

namespace MatrixGenerator
{
    public class Generator
    {
        public Matrix GenerateSimpleMatrix(int rows, int collumns)
        {
            var matrixElements = new int[rows][];

            for(int i = 0; i < rows; ++i)
            {
                matrixElements[i] = new int[collumns];
                for(int j = 0; j < collumns; ++j)
                {
                    matrixElements[i][j] = Program.Random.Next();
                }
            }

            var matrix = new Matrix();
            matrix.Elements = matrixElements;
            return matrix;
        }

        public Matrix GenerateBlockDiagonalMatrix(int rows, int collumns, int maxBlockSize, int filler = 0)
        {
            var leftSize = collumns;
            var currentPoint = (i: 0, j: 0);
            var elements = new int[rows][];

            for(int i = 0; i < rows; ++i)
            {
                elements[i] = new int[collumns];
            }

            for(int i = 0; i < rows; ++i)
            {
                for(int j = 0; j < collumns; ++j)
                {
                    elements[i][j] = filler;
                }
            }

            while(leftSize != 0)
            {
                var curerntBlockSize = 0;
                while(curerntBlockSize == 0 || curerntBlockSize > maxBlockSize) curerntBlockSize = (Program.Random.Next() % leftSize) + 1;
                for(int i = 0; i < curerntBlockSize; ++i)
                {
                    for(int j = 0; j < curerntBlockSize; ++j)
                    {
                        elements[currentPoint.i + i][currentPoint.j + j] = Program.Random.Next();
                    }
                }

                currentPoint.i += curerntBlockSize;
                currentPoint.j += curerntBlockSize;
                leftSize -= curerntBlockSize;
            }

            var matrix = new Matrix();
            matrix.Elements = elements;
            return matrix;
        }

        public Matrix GenerateThreeDiagonalMartix(int rows, int collumns, int filler)
        {
            var matrixElements = new int[rows][];

            for(int i = 0; i < rows; ++i)
            {
                matrixElements[i] = new int[collumns];
                for(int j = 0; j < collumns; ++j)
                {
                    matrixElements[i][j] =  Math.Abs(i - j) < 2 ? Program.Random.Next() : filler;
                }
            }

            var matrix = new Matrix();
            matrix.Elements = matrixElements;
            return matrix;
        }
    }
}