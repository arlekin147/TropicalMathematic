using System;
using System.Collections;
using System.Collections.Generic;

namespace MatrixGenerator
{
    public class Generator
    {
        public Matrix GenerateSimpleMatrix(int rows, int collumns)
        {
            var matrixElements = new int[rows][];

            for (int i = 0; i < rows; ++i)
            {
                matrixElements[i] = new int[collumns];
                for (int j = 0; j < collumns; ++j)
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

            for (int i = 0; i < rows; ++i)
            {
                elements[i] = new int[collumns];
            }

            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < collumns; ++j)
                {
                    elements[i][j] = filler;
                }
            }

            while (leftSize != 0)
            {
                var curerntBlockSize = 0;
                while (curerntBlockSize == 0 || curerntBlockSize > maxBlockSize) curerntBlockSize = (Program.Random.Next() % leftSize) + 1;
                for (int i = 0; i < curerntBlockSize; ++i)
                {
                    for (int j = 0; j < curerntBlockSize; ++j)
                    {
                        elements[currentPoint.i + i][currentPoint.j + j] = Program.Random.Next() % 100;
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

            for (int i = 0; i < rows; ++i)
            {
                matrixElements[i] = new int[collumns];
                for (int j = 0; j < collumns; ++j)
                {
                    matrixElements[i][j] = Math.Abs(i - j) < 2 ? Program.Random.Next() : filler;
                }
            }

            var matrix = new Matrix();
            matrix.Elements = matrixElements;
            return matrix;
        }

        public Matrix GenerateBlockFavoriteMatrix(int rows, int collumns, int countOfBlocks, int filler)
        {
            var generator = new FavoriteGenerator().GetEnumerator();
            var leftSize = collumns;
            var currentPoint = (i: 0, j: 0);
            var elements = new int[rows][];

            for (int i = 0; i < rows; ++i)
            {
                elements[i] = new int[collumns];
            }

            for (int i = 0; i < rows; ++i)
            {
                for (int j = 0; j < collumns; ++j)
                {
                    elements[i][j] = filler;
                }
            }

            while (leftSize != 0)
            {
                var curerntBlockSize = 0;
                while (curerntBlockSize == 0 || curerntBlockSize > 4) curerntBlockSize = (Program.Random.Next() % leftSize) + 1;
                curerntBlockSize = 4;
                for (int i = 0; i < curerntBlockSize; ++i)
                {
                    for (int j = 0; j < curerntBlockSize; ++j)
                    {
                        generator.MoveNext();
                        elements[currentPoint.i + i][currentPoint.j + j] = generator.Current;
                        Console.WriteLine(generator.Current);
                    }
                    Console.WriteLine();
                }

                currentPoint.i += curerntBlockSize;
                currentPoint.j += curerntBlockSize;
                leftSize -= curerntBlockSize;
            }

            var matrix = new Matrix();
            matrix.Elements = elements;
            return matrix;
        }

        private class FavoriteGenerator : IEnumerable<int>
        {
            public IEnumerator<int> GetEnumerator()
            {
                while (true)
                {
                    Console.WriteLine("Gen" + 0);
                    yield return 0;
                    Console.WriteLine("Gen" + 1);
                    yield return 1;
                    Console.WriteLine("Gen" + 3);
                    yield return 3;
                    Console.WriteLine("Gen" + 3);
                    yield return 3;

                    Console.WriteLine("Gen" + 0);
                    yield return 0;
                    Console.WriteLine("Gen" + 0);
                    yield return 0;
                    Console.WriteLine("Gen" + 1);
                    yield return 1;
                    Console.WriteLine("Gen" + 3);
                    yield return 3;

                    Console.WriteLine("Gen" + 1);
                    yield return 1;
                    Console.WriteLine("Gen" + 0);
                    yield return 0;
                    Console.WriteLine("Gen" + 0);
                    yield return 0;
                    Console.WriteLine("Gen" + 2);
                    yield return 2;

                    Console.WriteLine("Gen" + 0);
                    yield return 0;
                    Console.WriteLine("Gen" + 1);
                    yield return 1;
                    Console.WriteLine("Gen" + 0);
                    yield return 0;
                    Console.WriteLine("Gen" + 2);
                    yield return 2;
                }
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return GetEnumerator();
            }
        }
    }
}