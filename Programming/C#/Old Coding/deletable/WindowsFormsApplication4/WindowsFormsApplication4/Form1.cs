using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication4
{
        }
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

        private void plusbutton_Click(object sender, EventArgs e)
        {
            int plusresult;
        
            plusresult = int.Parse(number1textbox.Text) + int.Parse(number2textbox.Text);

            ResulttextBox.Text = plusresult.ToString();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int minusresult;

            minusresult = int.Parse(number1textbox.Text) - int.Parse(number2textbox.Text);

            ResulttextBox.Text = minusresult.ToString();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Double timesresult;

            timesresult = Double.Parse(number1textbox.Text) * Double.Parse(number2textbox.Text);

            ResulttextBox.Text = timesresult.ToString();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Double divideresult;

            divideresult = Double.Parse(number1textbox.Text) / Double.Parse(number2textbox.Text);

            ResulttextBox.Text = divideresult.ToString();
        }

        private void ansbutton_Click(object sender, EventArgs e)
        {
            int resulsttextbox;

            number2textbox.Text = ResulttextBox.Text;
        }
    }
}
