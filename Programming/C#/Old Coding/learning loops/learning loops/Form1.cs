using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace learning_loops
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            for (int i = 1; i <= 10; i++)
            {
                MessageBox.Show(i.ToString());
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            for (int i = 10; i >= 1; i--)
            {
                MessageBox.Show(i.ToString());
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            int i = 1;
            while (i <= 10)
            {
                MessageBox.Show(i.ToString());
                i++;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int i = 10;
            while (i >= 1)
            {
                MessageBox.Show(i.ToString());
                i--;
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            int i = 1;
            do
            {
                MessageBox.Show(i.ToString());
                i++;
            } while (i <= 10);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            int i = 10;
            do
            {
                MessageBox.Show(i.ToString());
                i--;
            } while (i >= 1);
        }
    }
}
