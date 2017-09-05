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
        double qn;
        double fp;
        double ft;
        double tax;
        double price;
        bool staff;
        string chocbox;

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            staff = checkBox1.Checked;
            chocbox = comboBox1.Text;     
            qn = int.Parse(numericUpDown1.Text);
            fn = FirstName.Text;
            ln = LastName.Text;
            switch (chocbox)
            {
                case "Crunchy":
                        price = 3.5;
                        break;
                case "Snickers":
                        price = 2.5;
                        break;
                case "Mars Bar":
                        price = 2.9;
                        break;
                case "Flake":
                        price = 2.3;
                        break;
                case "twix":
                        price = 3.4;
                        break;
                case "Cherry Ripe":
                        price = 2.6;
                        break;
                default:
                        MessageBox.Show("You have not selected a chocolate to purchase.");
                        break;
            }

            if (staff == true)
            {           
                   fp = qn * price / 2;         
            }
            else if (staff == false)
            {
                fp = qn * price;
            }           

            MessageBox.Show(fn + " " + ln + " will spend $" + fp);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            staff = checkBox1.Checked;
            tax = 0.25;
            qn = int.Parse(numericUpDown1.Text);
            fn = FirstName.Text;
            ln = LastName.Text;

            if (staff == true)
            {
                fp = qn * price / 2;
                ft = fp * tax;
            }
            else if (staff == false)
            {
                fp = qn * price;
                ft = fp * tax;
            }     
      
            MessageBox.Show("The tax " + fn + " " + ln + " is paying $" + ft);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Thankyou for using this program.");
            Application.Exit();
        }
    }
}
