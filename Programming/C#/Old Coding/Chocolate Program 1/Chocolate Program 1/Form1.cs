using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Chocolate_Program_1
{
    public partial class Form1 : Form
    {

        string fn;
        string ln;
        int qn;
        double fp;
        double ft;
        double tax;

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
                             
            qn = int.Parse(numericUpDown1.Text);
            fp = qn * 3;
            fn = FirstName.Text;
            ln = LastName.Text;

            MessageBox.Show(fn + " " + ln + " will spend $" + fp);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            tax = 0.25;
            qn = int.Parse(numericUpDown1.Text);
            fp = qn * 3;
            fn = FirstName.Text;
            ln = LastName.Text;
            ft = fp * tax;

            MessageBox.Show("The tax " + fn + " " + ln + " is paying " + ft);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}
