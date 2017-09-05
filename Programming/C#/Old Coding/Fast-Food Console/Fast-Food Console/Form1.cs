using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Fast_Food_Console
{
    public partial class OrderConsole : Form
    {
        string size;
        string itemselectedname;
        double itemselectedprice;
        string totalprice;
        double finalprice;
        string drinkselected;
        double gst;
        double change;
        double cash;
        double ResultTotal;
        double mealprice;
        Form Form2;
        Form f2;
    
        public OrderConsole()
        {
            InitializeComponent();
            finalprice = 0.00;

            textBox1.Text = ("McDonalds Order " + Environment.NewLine + "--------------------------------------------");
            size = "";
            drinkselected = "";
            itemselectedname = "";
        }

                private void toolStripComboBox1_Click(object sender, EventArgs e)
        {

        }

                private void button32_Click(object sender, EventArgs e)
                {
                    textBox1.Text = textBox1.Text + (Environment.NewLine + "McDonalds Order " + Environment.NewLine + "----------------------------" );

                    
                }

                private void button22_Click(object sender, EventArgs e)
                {
                    //Cheese Burger

                    itemselectedname = button22.Text;
                    itemselectedprice = 2.50;

                    mealadd();
                    
                }
                private void additem()
                {
                    if (size == "")
                        textBox1.Text = textBox1.Text + (Environment.NewLine + itemselectedname + "     $" + itemselectedprice);
                    else
                        textBox1.Text = textBox1.Text + (Environment.NewLine + size + " " + drinkselected + "     $" + itemselectedprice);
                    
                    finalprice = finalprice + itemselectedprice;
                    gst = finalprice * 0.1;

                    values();

                    groupBox1.Enabled = true;
                    groupBox2.Enabled = true;
                    groupBox5.Enabled = false;                    
                    size = "";
                    drinkselected = "";
                    itemselectedname = "";
                                       
                }

                private void button25_Click(object sender, EventArgs e)
                {
                    //Double Cheese Burger

                    itemselectedname = button25.Text;
                    itemselectedprice = 3.00;

                    mealadd();
                }

                private void button1_Click(object sender, EventArgs e)
                {

                }

                private void generic_Click(object sender, EventArgs e)
                {
                    if (CashEntered.Text == "0")
                        CashEntered.Clear();
                    Button b = (Button)sender;
                    CashEntered.Text = CashEntered.Text + b.Text;
                }

                private void Form1_Load(object sender, EventArgs e)
                {
                    
                }

                private void button18_Click(object sender, EventArgs e)
                {
                    if (checkBox1.Checked == true)
                        ResultTotal = (finalprice + gst) * 0.7;
                    else
                        ResultTotal = finalprice + gst;
                    cash = int.Parse(CashEntered.Text);
                    label3.Text = "$" + ResultTotal;
                    groupBox1.Enabled = false;
                    groupBox2.Enabled = false;
                    groupBox5.Enabled = false;
                    groupBox4.Enabled = true;
             
                }

                private void button23_Click(object sender, EventArgs e)
                {
                    //Fillet o Fish Burger

                    itemselectedname = button23.Text;
                    itemselectedprice = 2.75;

                    mealadd();
                }

                private void button26_Click(object sender, EventArgs e)
                {
                    //Mac Angus Burger

                    itemselectedname = button26.Text;
                    itemselectedprice = 2.80;

                    mealadd();
                }

                private void button24_Click(object sender, EventArgs e)
                {
                    //Mac Oz Burger

                    itemselectedname = button24.Text;
                    itemselectedprice = 3.00;

                    mealadd();
                }

                private void button27_Click(object sender, EventArgs e)
                {
                    //Quarter Pounder Burger

                    itemselectedname = button27.Text;
                    itemselectedprice = 3.25;

                    mealadd();
                }
        //drinks
                private void button30_Click(object sender, EventArgs e)
                {
                    //coke

                    drinkselected = button30.Text;
                    itemselectedprice = 2.00;

                    additem();
                    
                }

                private void button29_Click(object sender, EventArgs e)
                {
                    //fanta

                    drinkselected = button29.Text;
                    itemselectedprice = 1.75;

                    additem();
                    
                }

                private void button28_Click(object sender, EventArgs e)
                {
                    //sprite

                    drinkselected = button28.Text;
                    itemselectedprice = 1.50;

                    additem();
                    
                }

                private void button31_Click(object sender, EventArgs e)
                {
                    //water

                    drinkselected = button31.Text;
                    itemselectedprice = 1.00;

                    additem();
                    
                }

                private void button33_Click(object sender, EventArgs e)
                {
                    MessageBox.Show("Thankyou for using this program.");
                    Application.Exit();
                }

                private void button34_Click(object sender, EventArgs e)
                {
                    cash = double.Parse(CashEntered.Text); 
                    change = cash - ResultTotal;
                    MessageBox.Show ("You paid " + CashEntered.Text + "\n" + "You owed " + ResultTotal.ToString("0.00") + "\n" + "You recieved " + change );
                    CashEntered.Text = "0";                    
                    groupBox1.Enabled = true;
                    groupBox2.Enabled = true;
                    groupBox5.Enabled = true;
                    groupBox4.Enabled = false;
                    label3.Text = "$0.00";
                    label7.Text = "$0.00";
                    label9.Text = "$0.00";
                    checkBox1.Checked = false;
                    MessageBox.Show ("Next Order");                    
                    textBox1.Clear();
                    textBox1.Text = ("McDonalds Order " + Environment.NewLine + "--------------------------------------------");
                    
                }

                private void button32_Click_1(object sender, EventArgs e)
                {
                    size = "";
                    itemselectedprice = 0;
                    textBox1.Clear();
                    textBox1.Text = ("McDonalds Order " + Environment.NewLine + "--------------------------------------------");
                    ResultTotal = 0;
                    gst = 0;
                    finalprice = 0;
                    checkBox1.Checked = false;

                    values();
                    
                }

                private void button35_Click(object sender, EventArgs e)
                {
                    Form2 = f2;
                    f2 = new Form2();
                    f2.ShowDialog();
                }

                private void multiway_click ()
                {
                    
                    groupBox1.Enabled = false;
                    groupBox5.Enabled = true;
                    MessageBox.Show ("Please select a burger for the meal or just a drink");
                                      
                }

                private void button19_Click(object sender, EventArgs e)
                {
                    size = "Small";
                    multiway_click();
                }

                private void button20_Click(object sender, EventArgs e)
                {
                    size = "Medium";
                    multiway_click();
                }

                private void button21_Click(object sender, EventArgs e)
                {
                    size = "Large";
                    multiway_click();
                }

                private void button30_Click_1(object sender, EventArgs e)
                {
                    //coke

                    drinkselected = button30.Text;
                    drinkprice();
                    if (itemselectedname == "")
                        additem();
                    else
                    {
                        finalmeal();
                    }
                }

                private void button29_Click_1(object sender, EventArgs e)
                {
                    //fanta

                    drinkselected = button29.Text;
                    drinkprice();
                    if (itemselectedname == "")
                        additem();
                    else
                    {
                        finalmeal();
                    }
                    
                }
                private void drinkprice ()
                {
                    if (size == "Small")
                        itemselectedprice = 1.50;
                    else if (size == "Medium")
                        itemselectedprice = 2.00;
                    else if (size == "Large")
                        itemselectedprice = 3.00;
                }

                private void button28_Click_1(object sender, EventArgs e)
                {
                    //sprite

                    drinkselected = button28.Text;
                    drinkprice();
                    if (itemselectedname == "")
                        additem();
                    else
                    {
                        finalmeal();
                    }
                }

                private void button31_Click_1(object sender, EventArgs e)
                {
                    //water

                    drinkselected = button31.Text;
                    drinkprice();
                    if (itemselectedname == "")
                        additem();
                    else
                    {
                        finalmeal();
                    }
                    
                }
                private void values()
                {
                    totalprice = finalprice.ToString();

                    label7.Text = "$" + totalprice;
                    label9.Text = "$" + gst.ToString();
                }
                private void mealadd()
                {
                    if (size == "")
                        additem();
                    else
                    {
                        groupBox1.Enabled = false;
                        groupBox2.Enabled = false;
                        groupBox5.Enabled = true;
                        MessageBox.Show("Please select a drink for the meal.");
                    }
                        
                }
                private void finalmeal()
                {
                    switch (size)
                    {
                        case "Small":
                            mealprice = 3.50;
                            break;
                        case "Medium":
                            mealprice = 5.00;
                            break;
                        case "Large":
                            mealprice = 7.50;
                            break;
                    }
                    groupBox1.Enabled = true;
                    groupBox2.Enabled = true;
                    groupBox5.Enabled = false;
                    textBox1.Text = textBox1.Text + (Environment.NewLine + size + " " + itemselectedname + " meal w/ " + size + " " + drinkselected + "     $" + mealprice);

                    finalprice = finalprice + mealprice;
                    gst = finalprice * 0.1;

                    values();

                    size = "";
                    drinkselected = "";
                    itemselectedname = "";
                }
    }
}
