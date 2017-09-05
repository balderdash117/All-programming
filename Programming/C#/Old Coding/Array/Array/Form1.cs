using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Array
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string[] FirstNames = new string[3];
            string[] LastNames = new string[3];
            string[] Dateofbirth = new string[3];
            int[] Marks = new int[3];
            FirstNames[0] = "Grant";
            FirstNames[1] = "Bob";
            FirstNames[2] = "Bill";
            LastNames[0] = "Norman";
            LastNames[1] = "Punch";
            LastNames[2] = "Nicol";
            Dateofbirth[0] = "1/3/1997";
            Dateofbirth[1] = "6/4/1997";
            Dateofbirth[2] = "25/8/1997";
            Marks[0] = 70;
            Marks[1] = 90;
            Marks[2] = 55;
            for (int i = 0; i < 3; i++)
            {
                listBox1.Items.Add(FirstNames[i] + " " + LastNames[i] + " " + Dateofbirth[i] + "   " + Marks[i].ToString() + " masrks");
            }
        }
    }
}
