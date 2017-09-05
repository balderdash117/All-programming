using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Burger_Program
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
           if (comboBox1.Text == "Double Cheese Burger")
           {
                Burger MyFirstBurger = new Burger();

                MyFirstBurger.BurgerName = "Double Cheese Burger";
                MyFirstBurger.BurgerPrice = 4.50;
                MyFirstBurger.BurgerSize = "L";

                listBox1.Items.Add(MyFirstBurger.BurgerName +" $"+ MyFirstBurger.BurgerPrice);
            }

            else if (comboBox1.Text == "Big Mac")
            {
                Burger MySecondBurger = new Burger();

                MySecondBurger.BurgerName = "Big Mac";
                MySecondBurger.BurgerPrice = 2.50;
                MySecondBurger.BurgerSize = "L";

                listBox1.Items.Add(MySecondBurger.BurgerName + " $" + MySecondBurger.BurgerPrice);
            }
            else if (comboBox1.Text == "Works Burger")
            {
                Burger MyThirdBurger = new Burger();

                MyThirdBurger.BurgerName = "Works Burger";
                MyThirdBurger.BurgerPrice = 7.50;
                MyThirdBurger.BurgerSize = "L";

                listBox1.Items.Add(MyThirdBurger.BurgerName + " $" + MyThirdBurger.BurgerPrice);
            }
            else
            {
                MessageBox.Show("You Have not selected a Burger to add to your order");
            }

        }
    }
}
