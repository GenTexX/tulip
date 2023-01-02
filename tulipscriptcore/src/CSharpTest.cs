using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

struct Teststruct
{
    public int x;  
}

namespace tulip {

    internal class CSharpTest
    {

        private static float myStaticFloat = 1.0f;

        public bool myPublicBool = true;
        public char myPublicChar = 'a';
        public byte myPublicByte = 1;
        public sbyte myPublicSByte = 1;
        public short myPublicShort = 1;
        public ushort myPublicUShort = 1;
        public int myPublicInt = 1;
        public uint myPublicUInt = 1;
        public long myPublicLong = 1;
        public ulong myPublicULong = 1;
        public float myPublicFloat = 1;
        public double myPublicDouble = 1;
        public decimal myPublicDecimal = 1.2345M;
        public string myPublicString = "Hallo";
        public Teststruct myPublicStruct = new Teststruct();
        private string m_name;

        private int[] myArray = { 0, 1, 2 };
        private int[,] myMultiArray = { { 0, 1, 2 }, { 0, 1, 2 } };

        private CSharpTest myClassInstance = null;
        private Object myObject = null;

        private Func<int> myFucntion;

        public static string Name { get => ""; set {  } }

        public CSharpTest() { }

        public void printFloat()
        {
            Console.WriteLine("Hello from C# {0:F}", Math.Sin(myPublicFloat));
        }

        public float incrementFloat(float val)
        {
            myPublicFloat += val;
            return myPublicFloat;
        }


        public void incrementFloat(double val, float val2)
        {

        }

    }

}