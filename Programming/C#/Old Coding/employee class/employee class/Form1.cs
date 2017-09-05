using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace employee_class
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            double pay;
            double totalpay;

            totalpay = 0;

            //first employee

            employee_s firstemployee = new employee_s();

            firstemployee.name = "Sean";
            firstemployee.rate = 23.75;

            pay = firstemployee.rate * int.Parse(hoursworked.Text);

            MessageBox.Show(firstemployee.name + " $" + pay);

            totalpay = totalpay + pay;

            //second employee

            employee_s secondemployee = new employee_s();

            secondemployee.name = "Lynette";
            secondemployee.rate = 27.5;

            pay = secondemployee.rate * int.Parse(hoursworked.Text);

            MessageBox.Show(secondemployee.name + " $" + pay);

            totalpay = totalpay + pay;

            //third employee

            employee_s thirdemployee = new employee_s();

            thirdemployee.name = "Rhiannon";
            thirdemployee.rate = 31.45;

            pay = thirdemployee.rate * int.Parse(hoursworked.Text);

            MessageBox.Show(thirdemployee.name + " $" + pay);

            totalpay = totalpay + pay;

            //final message box

            MessageBox.Show("The total outgoing pay from the business this week was: $" + totalpay);

        }
    }
}
