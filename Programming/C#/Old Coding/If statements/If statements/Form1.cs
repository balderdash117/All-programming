using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace If_statements
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Binarybutton_Click(object sender, EventArgs e)
        {
            string color = comboBox1.Text;

            if (color == "red")
            {
                this.BackColor = Color.Red;
            }
            else if (color == "blue")
            {
                this.BackColor = Color.Blue;
            }  
            else if (color == "green")
            {
                this.BackColor = Color.Green;
            }
            else if (color == "purple")
            {
                this.BackColor = Color.Purple;
            }
            else
            {
                MessageBox.Show("You did not select a color"); 
            }    

            
        }

        private void Multiwaybutton_Click(object sender, EventArgs e)
        {
            string color = comboBox1.Text;

            switch (color)
            {
                case "red":
                    this.BackColor = Color.Red;
                    break;
                case "blue":
                    this.BackColor = Color.Blue;
                    break;
                case "green":
                    this.BackColor = Color.Green;
                    break;
                case "purple":
                    this.BackColor = Color.Purple;
                    break;
                default:
                    MessageBox.Show("You did not select a color");
                    break;


            }        

        }
    }
}
