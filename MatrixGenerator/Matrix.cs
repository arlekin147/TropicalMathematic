using System.Linq;

namespace MatrixGenerator
{
    public class Matrix
    {
        public int Rows { get => Elements.Length; }
        public int Collumns {get => Elements[0].Length; }
        public int[][] Elements { get; set; }
    }
}