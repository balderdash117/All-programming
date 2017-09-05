using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace adder
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Double number1;
            Double number2;
            Double answer;

            number1 = Double.Parse(textBox1.Text);
            number2 = Double.Parse(textBox2.Text);

            answer = number1 + number2;
            
            MessageBox.Show(answer.ToString());
        }
    }
}
