namespace guessing_game_1
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.NumberBox = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.SetButton = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.WhatGuess = new System.Windows.Forms.Label();
            this.GuessButton = new System.Windows.Forms.Button();
            this.GuessBox = new System.Windows.Forms.TextBox();
            this.DisplayLabel = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NumberBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.NumberBox);
            this.groupBox1.Controls.Add(this.numericUpDown1);
            this.groupBox1.Controls.Add(this.SetButton);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Location = new System.Drawing.Point(13, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(393, 187);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Settings";
            // 
            // NumberBox
            // 
            this.NumberBox.Increment = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.NumberBox.Location = new System.Drawing.Point(269, 99);
            this.NumberBox.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.NumberBox.Name = "NumberBox";
            this.NumberBox.Size = new System.Drawing.Size(89, 26);
            this.NumberBox.TabIndex = 4;
            this.NumberBox.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Location = new System.Drawing.Point(269, 32);
            this.numericUpDown1.Minimum = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(89, 26);
            this.numericUpDown1.TabIndex = 3;
            this.numericUpDown1.Value = new decimal(new int[] {
            5,
            0,
            0,
            0});
            // 
            // SetButton
            // 
            this.SetButton.Location = new System.Drawing.Point(23, 142);
            this.SetButton.Name = "SetButton";
            this.SetButton.Size = new System.Drawing.Size(348, 39);
            this.SetButton.TabIndex = 2;
            this.SetButton.Text = "Set";
            this.SetButton.UseVisualStyleBackColor = true;
            this.SetButton.Click += new System.EventHandler(this.SetButton_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(23, 101);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(240, 20);
            this.label4.TabIndex = 1;
            this.label4.Text = "Number will be between 1 and ... ";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(33, 34);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(208, 20);
            this.label3.TabIndex = 0;
            this.label3.Text = "Number of allowed guesses:";
            // 
            // WhatGuess
            // 
            this.WhatGuess.AutoSize = true;
            this.WhatGuess.Location = new System.Drawing.Point(12, 216);
            this.WhatGuess.Name = "WhatGuess";
            this.WhatGuess.Size = new System.Drawing.Size(145, 20);
            this.WhatGuess.TabIndex = 11;
            this.WhatGuess.Text = "Whats your guess?";
            // 
            // GuessButton
            // 
            this.GuessButton.Location = new System.Drawing.Point(163, 250);
            this.GuessButton.Name = "GuessButton";
            this.GuessButton.Size = new System.Drawing.Size(103, 36);
            this.GuessButton.TabIndex = 10;
            this.GuessButton.Text = "Guess";
            this.GuessButton.UseVisualStyleBackColor = true;
            this.GuessButton.Click += new System.EventHandler(this.GuessButton_Click_1);
            // 
            // GuessBox
            // 
            this.GuessBox.Location = new System.Drawing.Point(12, 255);
            this.GuessBox.Name = "GuessBox";
            this.GuessBox.Size = new System.Drawing.Size(136, 26);
            this.GuessBox.TabIndex = 9;
            // 
            // DisplayLabel
            // 
            this.DisplayLabel.AutoSize = true;
            this.DisplayLabel.Location = new System.Drawing.Point(8, 314);
            this.DisplayLabel.Name = "DisplayLabel";
            this.DisplayLabel.Size = new System.Drawing.Size(13, 20);
            this.DisplayLabel.TabIndex = 12;
            this.DisplayLabel.Text = " ";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(420, 425);
            this.Controls.Add(this.DisplayLabel);
            this.Controls.Add(this.WhatGuess);
            this.Controls.Add(this.GuessButton);
            this.Controls.Add(this.GuessBox);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Final Guessing Game";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NumberBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.NumericUpDown NumberBox;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.Button SetButton;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label WhatGuess;
        private System.Windows.Forms.Button GuessButton;
        private System.Windows.Forms.TextBox GuessBox;
        private System.Windows.Forms.Label DisplayLabel;
    }
}

