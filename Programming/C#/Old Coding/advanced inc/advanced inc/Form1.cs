﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace advanced_inc
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            button1.Text = "0";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int presscount;

            presscount = int.Parse(button1.Text);

            presscount = presscount + int.Parse(benbx1.Value.ToString());

            button1.Text = presscount.ToString();


        }
    }
}