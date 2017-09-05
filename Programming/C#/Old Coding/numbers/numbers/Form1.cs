using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace numbers
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int Number1;
            int Number2;
            int TheAnswer;

            Number1 = int.Parse(number1textbox.Text);
            Number2 = int.Parse(number2textbox.Text);

            TheAnswer = Number1 + Number2;

            answertextbox.Text = TheAnswer.ToString();

        }
    }
}
