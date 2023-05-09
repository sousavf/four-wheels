#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace TrackEditor
{
	public ref class NewTrack : public System::Windows::Forms::Form
	{
	public:
		NewTrack(void)
		{
			InitializeComponent();
			this->cbPista->SelectedIndex = 0;
			this->cbExterior->SelectedIndex = 1;
		}

		int getWidth()
		{
			return System::Convert::ToInt32(this->nLargura->Value);
		}

		int getLength()
		{
			return System::Convert::ToInt32(this->nComprimento->Value);
		}

		int getGroundSurface() 
		{
			return this->cbPista->SelectedIndex;
		}

		int getSidelinesSurface()
		{
			return this->cbExterior->SelectedIndex;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~NewTrack()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::SplitContainer^  splitContainer2;
	private: System::Windows::Forms::Button^  bOk;

	private: System::Windows::Forms::Button^  bCancel;
	private: System::Windows::Forms::SplitContainer^  splitContainer3;
	private: System::Windows::Forms::GroupBox^  gpTamanho;
	private: System::Windows::Forms::GroupBox^  gpSuperficie;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::Label^  lblLargura;
	private: System::Windows::Forms::Label^  lblComprimento;
	private: System::Windows::Forms::NumericUpDown^  nLargura;
	private: System::Windows::Forms::NumericUpDown^  nComprimento;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
	private: System::Windows::Forms::Label^  lblPista;
	private: System::Windows::Forms::Label^  lblExterior;
	private: System::Windows::Forms::ComboBox^  cbPista;

	private: System::Windows::Forms::ComboBox^  cbExterior;

	private: System::ComponentModel::IContainer^  components;



	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->splitContainer3 = (gcnew System::Windows::Forms::SplitContainer());
			this->gpTamanho = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->nLargura = (gcnew System::Windows::Forms::NumericUpDown());
			this->nComprimento = (gcnew System::Windows::Forms::NumericUpDown());
			this->lblLargura = (gcnew System::Windows::Forms::Label());
			this->lblComprimento = (gcnew System::Windows::Forms::Label());
			this->gpSuperficie = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->lblPista = (gcnew System::Windows::Forms::Label());
			this->lblExterior = (gcnew System::Windows::Forms::Label());
			this->cbPista = (gcnew System::Windows::Forms::ComboBox());
			this->cbExterior = (gcnew System::Windows::Forms::ComboBox());
			this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			this->bOk = (gcnew System::Windows::Forms::Button());
			this->bCancel = (gcnew System::Windows::Forms::Button());
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->splitContainer3->Panel1->SuspendLayout();
			this->splitContainer3->Panel2->SuspendLayout();
			this->splitContainer3->SuspendLayout();
			this->gpTamanho->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->nLargura))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->nComprimento))->BeginInit();
			this->gpSuperficie->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->splitContainer2->Panel1->SuspendLayout();
			this->splitContainer2->Panel2->SuspendLayout();
			this->splitContainer2->SuspendLayout();
			this->SuspendLayout();
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->splitContainer1->IsSplitterFixed = true;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Name = L"splitContainer1";
			this->splitContainer1->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->splitContainer3);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->splitContainer2);
			this->splitContainer1->Size = System::Drawing::Size(219, 234);
			this->splitContainer1->SplitterDistance = 195;
			this->splitContainer1->SplitterWidth = 1;
			this->splitContainer1->TabIndex = 0;
			this->splitContainer1->TabStop = false;
			// 
			// splitContainer3
			// 
			this->splitContainer3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer3->Location = System::Drawing::Point(0, 0);
			this->splitContainer3->Name = L"splitContainer3";
			this->splitContainer3->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer3.Panel1
			// 
			this->splitContainer3->Panel1->Controls->Add(this->gpTamanho);
			this->splitContainer3->Panel1->Padding = System::Windows::Forms::Padding(6);
			// 
			// splitContainer3.Panel2
			// 
			this->splitContainer3->Panel2->Controls->Add(this->gpSuperficie);
			this->splitContainer3->Panel2->Padding = System::Windows::Forms::Padding(6);
			this->splitContainer3->Size = System::Drawing::Size(219, 195);
			this->splitContainer3->SplitterDistance = 94;
			this->splitContainer3->SplitterWidth = 1;
			this->splitContainer3->TabIndex = 0;
			this->splitContainer3->TabStop = false;
			// 
			// gpTamanho
			// 
			this->gpTamanho->Controls->Add(this->tableLayoutPanel1);
			this->gpTamanho->Dock = System::Windows::Forms::DockStyle::Fill;
			this->gpTamanho->Location = System::Drawing::Point(6, 6);
			this->gpTamanho->Name = L"gpTamanho";
			this->gpTamanho->Size = System::Drawing::Size(207, 82);
			this->gpTamanho->TabIndex = 0;
			this->gpTamanho->TabStop = false;
			this->gpTamanho->Text = L"Tamanho";
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				100)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
				100)));
			this->tableLayoutPanel1->Controls->Add(this->nLargura, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->nComprimento, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->lblLargura, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->lblComprimento, 0, 1);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(3, 16);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->Padding = System::Windows::Forms::Padding(6);
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(201, 63);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// nLargura
			// 
			this->nLargura->Dock = System::Windows::Forms::DockStyle::Fill;
			this->nLargura->Location = System::Drawing::Point(98, 9);
			this->nLargura->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {50, 0, 0, 0});
			this->nLargura->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {4, 0, 0, 0});
			this->nLargura->Name = L"nLargura";
			this->nLargura->Size = System::Drawing::Size(94, 20);
			this->nLargura->TabIndex = 2;
			this->nLargura->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {6, 0, 0, 0});
			// 
			// nComprimento
			// 
			this->nComprimento->Dock = System::Windows::Forms::DockStyle::Fill;
			this->nComprimento->Location = System::Drawing::Point(98, 34);
			this->nComprimento->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {50, 0, 0, 0});
			this->nComprimento->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {4, 0, 0, 0});
			this->nComprimento->Name = L"nComprimento";
			this->nComprimento->Size = System::Drawing::Size(94, 20);
			this->nComprimento->TabIndex = 3;
			this->nComprimento->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {6, 0, 0, 0});
			// 
			// lblLargura
			// 
			this->lblLargura->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblLargura->Location = System::Drawing::Point(9, 6);
			this->lblLargura->Name = L"lblLargura";
			this->lblLargura->Size = System::Drawing::Size(83, 25);
			this->lblLargura->TabIndex = 0;
			this->lblLargura->Text = L"Largura:";
			this->lblLargura->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblComprimento
			// 
			this->lblComprimento->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblComprimento->Location = System::Drawing::Point(9, 31);
			this->lblComprimento->Name = L"lblComprimento";
			this->lblComprimento->Size = System::Drawing::Size(83, 26);
			this->lblComprimento->TabIndex = 1;
			this->lblComprimento->Text = L"Comprimento:";
			this->lblComprimento->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// gpSuperficie
			// 
			this->gpSuperficie->Controls->Add(this->tableLayoutPanel2);
			this->gpSuperficie->Dock = System::Windows::Forms::DockStyle::Fill;
			this->gpSuperficie->Location = System::Drawing::Point(6, 6);
			this->gpSuperficie->Name = L"gpSuperficie";
			this->gpSuperficie->Size = System::Drawing::Size(207, 88);
			this->gpSuperficie->TabIndex = 0;
			this->gpSuperficie->TabStop = false;
			this->gpSuperficie->Text = L"Superficie";
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				100)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 
				100)));
			this->tableLayoutPanel2->Controls->Add(this->lblPista, 0, 0);
			this->tableLayoutPanel2->Controls->Add(this->lblExterior, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->cbPista, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->cbExterior, 1, 1);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->Location = System::Drawing::Point(3, 16);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->Padding = System::Windows::Forms::Padding(6);
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(201, 69);
			this->tableLayoutPanel2->TabIndex = 0;
			// 
			// lblPista
			// 
			this->lblPista->AutoSize = true;
			this->lblPista->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblPista->Location = System::Drawing::Point(9, 6);
			this->lblPista->Name = L"lblPista";
			this->lblPista->Size = System::Drawing::Size(83, 28);
			this->lblPista->TabIndex = 0;
			this->lblPista->Text = L"Pista:";
			this->lblPista->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblExterior
			// 
			this->lblExterior->AutoSize = true;
			this->lblExterior->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblExterior->Location = System::Drawing::Point(9, 34);
			this->lblExterior->Name = L"lblExterior";
			this->lblExterior->Size = System::Drawing::Size(83, 29);
			this->lblExterior->TabIndex = 1;
			this->lblExterior->Text = L"Exterior:";
			this->lblExterior->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// cbPista
			// 
			this->cbPista->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cbPista->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbPista->FormattingEnabled = true;
			this->cbPista->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"Cascalho", L"Relva", L"Neve", L"Gelo"});
			this->cbPista->Location = System::Drawing::Point(98, 9);
			this->cbPista->Name = L"cbPista";
			this->cbPista->Size = System::Drawing::Size(94, 21);
			this->cbPista->TabIndex = 2;
			// 
			// cbExterior
			// 
			this->cbExterior->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cbExterior->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cbExterior->FormattingEnabled = true;
			this->cbExterior->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"Cascalho", L"Relva", L"Neve", L"Gelo"});
			this->cbExterior->Location = System::Drawing::Point(98, 37);
			this->cbExterior->Name = L"cbExterior";
			this->cbExterior->Size = System::Drawing::Size(94, 21);
			this->cbExterior->TabIndex = 3;
			// 
			// splitContainer2
			// 
			this->splitContainer2->Dock = System::Windows::Forms::DockStyle::Right;
			this->splitContainer2->IsSplitterFixed = true;
			this->splitContainer2->Location = System::Drawing::Point(19, 0);
			this->splitContainer2->Name = L"splitContainer2";
			// 
			// splitContainer2.Panel1
			// 
			this->splitContainer2->Panel1->Controls->Add(this->bOk);
			this->splitContainer2->Panel1->Padding = System::Windows::Forms::Padding(6);
			// 
			// splitContainer2.Panel2
			// 
			this->splitContainer2->Panel2->Controls->Add(this->bCancel);
			this->splitContainer2->Panel2->Padding = System::Windows::Forms::Padding(6);
			this->splitContainer2->Size = System::Drawing::Size(200, 38);
			this->splitContainer2->SplitterDistance = 100;
			this->splitContainer2->SplitterWidth = 1;
			this->splitContainer2->TabIndex = 0;
			this->splitContainer2->TabStop = false;
			// 
			// bOk
			// 
			this->bOk->Dock = System::Windows::Forms::DockStyle::Fill;
			this->bOk->Location = System::Drawing::Point(6, 6);
			this->bOk->Name = L"bOk";
			this->bOk->Size = System::Drawing::Size(88, 26);
			this->bOk->TabIndex = 0;
			this->bOk->Text = L"OK";
			this->bOk->UseVisualStyleBackColor = true;
			this->bOk->Click += gcnew System::EventHandler(this, &NewTrack::bOk_Click);
			// 
			// bCancel
			// 
			this->bCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->bCancel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->bCancel->Location = System::Drawing::Point(6, 6);
			this->bCancel->Name = L"bCancel";
			this->bCancel->Size = System::Drawing::Size(87, 26);
			this->bCancel->TabIndex = 0;
			this->bCancel->Text = L"Cancel";
			this->bCancel->UseVisualStyleBackColor = true;
			this->bCancel->Click += gcnew System::EventHandler(this, &NewTrack::bCancel_Click);
			// 
			// NewTrack
			// 
			this->AcceptButton = this->bOk;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->bCancel;
			this->ClientSize = System::Drawing::Size(219, 234);
			this->Controls->Add(this->splitContainer1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"NewTrack";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Nova pista";
			this->TopMost = true;
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			this->splitContainer1->ResumeLayout(false);
			this->splitContainer3->Panel1->ResumeLayout(false);
			this->splitContainer3->Panel2->ResumeLayout(false);
			this->splitContainer3->ResumeLayout(false);
			this->gpTamanho->ResumeLayout(false);
			this->tableLayoutPanel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->nLargura))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->nComprimento))->EndInit();
			this->gpSuperficie->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->splitContainer2->Panel1->ResumeLayout(false);
			this->splitContainer2->Panel2->ResumeLayout(false);
			this->splitContainer2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void bOk_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->DialogResult = System::Windows::Forms::DialogResult::OK;
				 this->Close();
			 }

private: System::Void bCancel_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			 this->Close();
		 }
};
}
