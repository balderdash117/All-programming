namespace If_statements
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
            this.label1 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.Binarybutton = new System.Windows.Forms.Button();
            this.Multiwaybutton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(60, 56);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(94, 20);
            this.label1.TabIndex = 0;
            this.label1.Text = "Set color to:";
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "red",
            "blue",
            "purple",
            "green"});
            this.comboBox1.Location = new System.Drawing.Point(189, 48);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 28);
            this.comboBox1.TabIndex = 1;
            // 
            // Binarybutton
            // 
            this.Binarybutton.Location = new System.Drawing.Point(189, 134);
            this.Binarybutton.Name = "Binarybutton";
            this.Binarybutton.Size = new System.Drawing.Size(165, 33);
            this.Binarybutton.TabIndex = 2;
            this.Binarybutton.Text = "Binary Selection";
            this.Binarybutton.UseVisualStyleBackColor = true;
            this.Binarybutton.Click += new System.EventHandler(this.Binarybutton_Click);
            // 
            // Multiwaybutton
            // 
            this.Multiwaybutton.Location = new System.Drawing.Point(189, 173);
            this.Multiwaybutton.Name = "Multiwaybutton";
            this.Multiwaybutton.Size = new System.Drawing.Size(165, 35);
            this.Multiwaybutton.TabIndex = 3;
            this.Multiwaybutton.Text = "Multiway Selection";
            this.Multiwaybutton.UseVisualStyleBackColor = true;
            this.Multiwaybutton.Click += new System.EventHandler(this.Multiwaybutton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(467, 294);
            this.Controls.Add(this.Multiwaybutton);
            this.Controls.Add(this.Binarybutton);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Button Binarybutton;
        private System.Windows.Forms.Button Multiwaybutton;
    }
}

