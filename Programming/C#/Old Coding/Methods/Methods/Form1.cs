using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Methods
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            linechange("You clicked button 1");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            linechange("You clicked button 2");
        }

        private void linechange(string message1)
        {
            textBox1.Text = message1;
        }

    }
}
