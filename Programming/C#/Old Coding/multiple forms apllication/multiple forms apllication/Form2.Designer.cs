namespace multiple_forms_apllication
{
    partial class Form2
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
            this.cancelbutton = new System.Windows.Forms.Button();
            this.savebutton = new System.Windows.Forms.Button();
            this.addresstextbox = new System.Windows.Forms.TextBox();
            this.suburbtextbox = new System.Windows.Forms.TextBox();
            this.postcodetextbox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // cancelbutton
            // 
            this.cancelbutton.Location = new System.Drawing.Point(145, 242);
            this.cancelbutton.Name = "cancelbutton";
            this.cancelbutton.Size = new System.Drawing.Size(105, 31);
            this.cancelbutton.TabIndex = 0;
            this.cancelbutton.Text = "Cancel";
            this.cancelbutton.UseVisualStyleBackColor = true;
            // 
            // savebutton
            // 
            this.savebutton.Location = new System.Drawing.Point(274, 242);
            this.savebutton.Name = "savebutton";
            this.savebutton.Size = new System.Drawing.Size(105, 31);
            this.savebutton.TabIndex = 1;
            this.savebutton.Text = "Save";
            this.savebutton.UseVisualStyleBackColor = true;
            // 
            // addresstextbox
            // 
            this.addresstextbox.Location = new System.Drawing.Point(37, 56);
            this.addresstextbox.Name = "addresstextbox";
            this.addresstextbox.Size = new System.Drawing.Size(265, 26);
            this.addresstextbox.TabIndex = 2;
            // 
            // suburbtextbox
            // 
            this.suburbtextbox.Location = new System.Drawing.Point(37, 136);
            this.suburbtextbox.Name = "suburbtextbox";
            this.suburbtextbox.Size = new System.Drawing.Size(145, 26);
            this.suburbtextbox.TabIndex = 3;
            // 
            // postcodetextbox
            // 
            this.postcodetextbox.Location = new System.Drawing.Point(207, 136);
            this.postcodetextbox.Name = "postcodetextbox";
            this.postcodetextbox.Size = new System.Drawing.Size(95, 26);
            this.postcodetextbox.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(37, 33);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(68, 20);
            this.label1.TabIndex = 5;
            this.label1.Text = "Address";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(37, 113);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(61, 20);
            this.label2.TabIndex = 6;
            this.label2.Text = "Suburb";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(203, 113);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(76, 20);
            this.label3.TabIndex = 7;
            this.label3.Text = "Postcode";
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(391, 285);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.postcodetextbox);
            this.Controls.Add(this.suburbtextbox);
            this.Controls.Add(this.addresstextbox);
            this.Controls.Add(this.savebutton);
            this.Controls.Add(this.cancelbutton);
            this.Name = "Form2";
            this.Text = "Form2";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button cancelbutton;
        private System.Windows.Forms.Button savebutton;
        private System.Windows.Forms.TextBox addresstextbox;
        private System.Windows.Forms.TextBox suburbtextbox;
        private System.Windows.Forms.TextBox postcodetextbox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
    }
}