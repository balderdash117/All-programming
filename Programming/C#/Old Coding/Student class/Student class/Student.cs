using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Student_class
{
    class Student
    {
        private string _name;
        private int _age;
        private int _ID;
        private double _UAI;

        public Student()
        {
            resetStudent();
        }

        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }

        public int Age
        {
            get { return _age; }
            set { _age = value; }
        }

        public int ID
        {
            get { return _ID; }
            set { _ID = value; }
        }

        public double UAI
        {
            get { return _UAI; }
            set { _UAI = value; }
        }

        public void resetStudent()
        {
            _name = "StudentName";
            _age = 17;
            _ID = 0000;
            _UAI = 90;

        }
    }
}
