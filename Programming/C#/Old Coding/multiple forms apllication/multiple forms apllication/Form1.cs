using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace multiple_forms_apllication
{
    public partial class Form1 : Form
    {

        string address = "123 Straight Street" , suburb = " Balmain", postcode = "2050";

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form2 fa = new Form2 ();
            fa.ShowDialog (this);

            if(fa.DialogResult == DialogResult.OK)
            {
                address = fa.address;
                suburb = fa.Suburb;
                postcode = fa.postcode;

                labelAddress.Text = address + ", " + suburb + ", " + postcode;
            }
            else if (fa.DialogResult == DialogResult.Cancel)
            {

            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            labelAddress.Text = address + ", " + suburb + ", " + postcode;
        }
    }
}
