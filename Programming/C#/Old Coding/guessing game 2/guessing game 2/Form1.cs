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
        Random r;
        int sn;
        int rg;

        public Form1()
        {
            InitializeComponent();
        }

        private void GuessButton_Click(object sender, EventArgs e)
        {
            int guess;
            
            bool allOK = int.TryParse(GuessBox.Text, out guess);

            if (allOK == true)
            {

                if (guess == sn)
                {
                    MessageBox.Show("Correct" + '\n' + "The answer was " + sn);
                    sn = r.Next(1, 10);
                    rg = 9;
                }
                else if (guess < sn)
                {
                    MessageBox.Show("Too Low, Please try again." + '\n' + "Remaining Guesses = " + rg);
                    rg--;
                }
                else if (guess > sn)
                {
                    MessageBox.Show("Too High, Please try again." + '\n' + "Remaining Guesses = " + rg);
                    rg--;
                }
                else if (guess > sn)
                {
                    MessageBox.Show("This value is outside of the range" + '\n' + "Remaining Guesses = " + rg);
                    rg--;
                }
                else
                {
                    MessageBox.Show("This is not a valid guess");
                }
            }
            else if (allOK == false)
            {
                MessageBox.Show("That is not a valid entry");
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            r = new Random();

            sn = r.Next(1, 10);

            rg = 9;        }
    }
}
