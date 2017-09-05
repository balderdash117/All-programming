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
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();

            cancelbutton.DialogResult = DialogResult.Cancel;
            savebutton.DialogResult = DialogResult.OK;
        }

        public string address
        {
            get
            {
                return addresstextbox.Text;
            }
        }

        public string Suburb
        {
            get
            {
                return suburbtextbox.Text;
            }
        }

        public string postcode
        {
            get
            {
                return postcodetextbox.Text;
            }
        }

        
    }
}
