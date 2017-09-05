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
        int HighNumber;
        int numofguess;

        public Form1()
        {
            InitializeComponent();
        }

        private void GuessButton_Click(object sender, EventArgs e)
        {
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
         

            WhatGuess.Enabled = false;
            GuessBox.Enabled = false;
            GuessButton.Enabled = false;        }

        private void SetButton_Click(object sender, EventArgs e)
        {
            HighNumber = int.Parse(NumberBox.Text);

            numofguess = int.Parse(numericUpDown1.Text);

            r = new Random();

            sn = r.Next(1, HighNumber);

            rg = numofguess - 1;

            WhatGuess.Enabled = true;
            GuessBox.Enabled = true;
            GuessButton.Enabled = true;
            groupBox1.Enabled = false;

            DisplayLabel.Text = "Number of allowed Guesses = " + numofguess + "\n You are guessing a number between 1 and " + HighNumber;
        }

        private void GuessButton_Click_1(object sender, EventArgs e)
        {
            int guess;
            int fg;

            fg = numofguess - rg;

            bool allOK = int.TryParse(GuessBox.Text, out guess);

            if (allOK == true)
            {
                if (rg > 0)
                {

                    if (guess == sn)
                    {
                        DisplayLabel.Text = "Correct \n The answer was " + sn + "\n You guessed the secret number in " + fg + " guesses.";
                        sn = r.Next(1, HighNumber);
                        rg = numofguess - 1;

                        WhatGuess.Enabled = false;
                        GuessBox.Enabled = false;
                        GuessButton.Enabled = false;
                        groupBox1.Enabled = true;

                    }
                    else if (guess < sn)
                    {
                        DisplayLabel.Text = "Too Low, Please try again.  \n Remaining Guesses = " + rg;
                        rg--;
                    }
                    else if (guess > sn)
                    {
                        DisplayLabel.Text = "Too High, Please try again. \n Remaining Guesses = " + rg;
                        rg--;
                    }
                    else if (guess > HighNumber)
                    {
                        DisplayLabel.Text = "This value is outside of the range \n Remaining Guesses = " + rg;
                        rg--;
                    }
                    else
                    {
                        DisplayLabel.Text = "This is not a valid guess";
                    }
                    }
                else if (rg == 0)
                {
                    DisplayLabel.Text = "You ran out of guesses. \n Better luck next time.";
                    WhatGuess.Enabled = false;
                    GuessBox.Enabled = false;
                    GuessButton.Enabled = false;
                    groupBox1.Enabled = true;
                }
                }
            else if (allOK == false)
            {
                DisplayLabel.Text = "That is not a valid entry";
            }
                
        }
    }
}
