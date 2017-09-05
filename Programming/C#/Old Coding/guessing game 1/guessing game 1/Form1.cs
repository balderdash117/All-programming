using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace guessing_game_1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void GuessButton_Click(object sender, EventArgs e)
        {
            int guess  = int.Parse(GuessBox.Text);

            if (guess == 4)
            {
                MessageBox.Show("Correct");
            }
            else if (guess < 4)
            {
                MessageBox.Show("Too Low, Please try again.");
            }   
            else if (guess > 4)
            {
                MessageBox.Show("Too High, Please try again.");
            }
            else if (guess > 10)
            {
                MessageBox.Show("This value is outside of the range");  
            }
            else
            {
                MessageBox.Show("This is not a valid guess");
            }
        }
    }
}
