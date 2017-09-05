namespace WindowsFormsApplication4
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label5 = new System.Windows.Forms.Label();
            this.ResulttextBox = new System.Windows.Forms.TextBox();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.plusbutton = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.number2textbox = new System.Windows.Forms.TextBox();
            this.number1textbox = new System.Windows.Forms.TextBox();
            this.ansbutton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(518, 82);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(55, 20);
            this.label5.TabIndex = 23;
            this.label5.Text = "Result";
            // 
            // ResulttextBox
            // 
            this.ResulttextBox.Location = new System.Drawing.Point(497, 105);
            this.ResulttextBox.Name = "ResulttextBox";
            this.ResulttextBox.Size = new System.Drawing.Size(100, 26);
            this.ResulttextBox.TabIndex = 22;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(359, 154);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(57, 43);
            this.button3.TabIndex = 21;
            this.button3.Text = "/";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(359, 105);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(57, 43);
            this.button4.TabIndex = 20;
            this.button4.Text = "*";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(222, 154);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(57, 43);
            this.button2.TabIndex = 19;
            this.button2.Text = "-";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // plusbutton
            // 
            this.plusbutton.Location = new System.Drawing.Point(222, 105);
            this.plusbutton.Name = "plusbutton";
            this.plusbutton.Size = new System.Drawing.Size(57, 43);
            this.plusbutton.TabIndex = 18;
            this.plusbutton.Text = "+";
            this.plusbutton.UseVisualStyleBackColor = true;
            this.plusbutton.Click += new System.EventHandler(this.plusbutton_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(324, 82);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(128, 20);
            this.label4.TabIndex = 17;
            this.label4.Text = "Decimal (double)";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(203, 82);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(91, 20);
            this.label3.TabIndex = 16;
            this.label3.Text = "Integer (int)";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(262, 32);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 20);
            this.label2.TabIndex = 15;
            this.label2.Text = "Maths";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(35, 82);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(122, 20);
            this.label1.TabIndex = 14;
            this.label1.Text = "Type 2 numbers";
            // 
            // number2textbox
            // 
            this.number2textbox.Location = new System.Drawing.Point(48, 137);
            this.number2textbox.Name = "number2textbox";
            this.number2textbox.Size = new System.Drawing.Size(100, 26);
            this.number2textbox.TabIndex = 13;
            // 
            // number1textbox
            // 
            this.number1textbox.Location = new System.Drawing.Point(48, 105);
            this.number1textbox.Name = "number1textbox";
            this.number1textbox.Size = new System.Drawing.Size(100, 26);
            this.number1textbox.TabIndex = 12;
            // 
            // ansbutton
            // 
            this.ansbutton.Location = new System.Drawing.Point(508, 157);
            this.ansbutton.Name = "ansbutton";
            this.ansbutton.Size = new System.Drawing.Size(76, 40);
            this.ansbutton.TabIndex = 24;
            this.ansbutton.Text = "M+";
            this.ansbutton.UseVisualStyleBackColor = true;
            this.ansbutton.Click += new System.EventHandler(this.ansbutton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(657, 271);
            this.Controls.Add(this.ansbutton);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.ResulttextBox);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.plusbutton);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.number2textbox);
            this.Controls.Add(this.number1textbox);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox ResulttextBox;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button plusbutton;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox number2textbox;
        private System.Windows.Forms.TextBox number1textbox;
        private System.Windows.Forms.Button ansbutton;
    }
}

