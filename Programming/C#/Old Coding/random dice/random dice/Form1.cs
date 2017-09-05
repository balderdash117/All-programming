using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace random_dice
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            MessageBox.Show(Randomizer(50).ToString());


        }

        private int Randomizer(int Max)
        {
            int randomnumber;
            int NowTime = 5;

            if (NowTime < Max)
                randomnumber = NowTime;
            else randomnumber = NowTime % Max;

            return randomnumber;
        }
    }
}
