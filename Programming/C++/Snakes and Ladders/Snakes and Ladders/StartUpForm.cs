using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Snakes_and_Ladders
{
    public partial class StartUpForm : Form
    {
        public StartUpForm()
        {
            InitializeComponent();
        }

        private void ButtonBegin_Click(object sender, EventArgs e)
        {
            int NumberOfPlayers;
            NumberOfPlayers = (int)numericUpDown1.Value;
            
            Form1 FormMain = new Form1();
            FormMain.PlayersNumber = NumberOfPlayers;
            FormMain.Show();
            this.Hide();
            
        }
    }
}
