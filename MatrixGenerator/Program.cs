using System;
using System.Collections.Generic;
using System.IO;
using Newtonsoft.Json;

namespace MatrixGenerator
{
    class Program
    {
        public static Random Random = new Random();
        static void Main(string[] args)
        {
            Console.WriteLine("Input size of matrix");
            var size = int.Parse(Console.ReadLine());
            Console.WriteLine("Input number of matrixes");
            var number = int.Parse(Console.ReadLine());
            Console.WriteLine("Input typef of matrixes (0 - simple; 1 - block diagonal; 2 - three diagonals)");
            var type = int.Parse(Console.ReadLine());
            
            var generator = new Generator();
            var matrixes = new List<Matrix>();
            for(int i = 0; i < number; ++i)
            {
                switch(type)
                {
                    case 0:
                    {
                        matrixes.Add(generator.GenerateSimpleMatrix(size, size));
                        break;
                    }
                    case 1:
                    {
                        matrixes.Add(generator.GenerateBlockDiagonalMatrix(size, size, 4, int.MaxValue));
                        break;
                    }
                    case 2:
                    {
                        matrixes.Add(generator.GenerateThreeDiagonalMartix(size, size, int.MaxValue));
                        break;
                    }
                }
            }
            
            var json = JsonConvert.SerializeObject(matrixes);
            var file = File.CreateText("result.json");
            file.WriteLine(json);
            file.Close();
        }
    }
}
