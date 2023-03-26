namespace tulip
{
    class Vecotr3
    {

        public float x;
        public float y;
        public float z;

        public Vecotr3()
        {
            this.x = 0.0f;
            this.y = 0.0f;
            this.z = 0.0f;
        }
        public Vecotr3(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public float sqlength()
        {
            return x * x + y * y + z * z;
        }

        public float length()
        {
            return (float)System.Math.Sqrt(sqlength());
        }

        public Vecotr3 normalize()
        {
            float length = this.length();
            float x = this.x / length;
            float y = this.y / length; 
            float z = this.z / length;
            return new Vecotr3(x, y, z);
        }

    }
}
