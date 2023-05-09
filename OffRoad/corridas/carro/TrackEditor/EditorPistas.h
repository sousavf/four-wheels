#pragma once

#pragma warning(disable: 4996)

#include "ODERequirements.h"
#include "ODEHeaders.h"
#include <vector>
#include <string>
#include <stdlib.h>
#include <vcclr.h>
#include "NewTrack.h"
#include "About.h"

using namespace System;
using namespace ODE;
using namespace std;

namespace TrackEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(int width, int length):name(new string()),segments(new vector< vector< ODETrackSegmentDefinition > >())
		{
			InitializeComponent();
			this->cbStraight->BackgroundImage = System::Drawing::Image::FromFile("imagens/Straight.gif");
			this->cbCurve90LeftToBottom->BackgroundImage = System::Drawing::Image::FromFile("imagens/Curve90LeftToBottom.gif");
			this->cbCurve90BottomToRight->BackgroundImage = System::Drawing::Image::FromFile("imagens/Curve90BottomToRight.gif");
			this->cbEmpty->BackgroundImage = System::Drawing::Image::FromFile("imagens/Empty.gif");
			this->cbStraightSide->BackgroundImage = System::Drawing::Image::FromFile("imagens/StraightSide.gif");
			this->cbStartStraightBack->BackgroundImage = System::Drawing::Image::FromFile("imagens/StartStraightBack.gif");
			this->cbStartStraightRight->BackgroundImage = System::Drawing::Image::FromFile("imagens/StartStraightRight.gif");
			this->cbStartStraightLeft->BackgroundImage = System::Drawing::Image::FromFile("imagens/StartStraightLeft.gif");
			this->cbStartStraightFront->BackgroundImage = System::Drawing::Image::FromFile("imagens/StartStraightFront.gif");
			this->cbCurve90TopToRight->BackgroundImage = System::Drawing::Image::FromFile("imagens/Curve90TopToRight.gif");
			this->cbCurve90LeftToFront->BackgroundImage = System::Drawing::Image::FromFile("imagens/Curve90LeftToFront.gif");
			this->cbRampStraightSideElevated->BackgroundImage = System::Drawing::Image::FromFile("imagens/RampStraightSideElevated.gif");
			this->cbRampStraightSideSunken->BackgroundImage = System::Drawing::Image::FromFile("imagens/RampStraightSideSunken.gif");
			this->cbRampStraightElevated->BackgroundImage = System::Drawing::Image::FromFile("imagens/RampStraightElevated.gif");
			this->cbRampStraightSunken->BackgroundImage = System::Drawing::Image::FromFile("imagens/RampStraightSunken.gif");
			newTrack(width, length, "Untitled", 0, 1);
			this->current = ODETrackSegmentDefinition::StartStraightFront;
			this->curDir = System::IO::Directory::GetCurrentDirectory();
		}

#pragma region Load Save

		bool Load(const char* filename, string &trackName
			, vector< vector< ODETrackSegmentDefinition > >& segDefinitions)
		{
			ODETrackSegmentDefinition seg = ODETrackSegmentDefinition::get(ODETrackSegmentDefinition::Empty);
			int width, length, s;
			char name[1000], c;

			ifstream ifile(filename);

			if (!ifile.is_open())
			{
				return false;
			}
			ifile.getline(name, 1000, ';');
			trackName = name;
			ifile >> length;
			ifile >> c;	// para ignorar ;
			ifile >> width;
			ifile >> c;	// para ignorar ;
			ifile >> s;
			ifile >> c;	// para ignorar ;
			groundSurface = (ODETrackSegmentDefinition::Surface)s;
			ifile >> s;
			ifile >> c;	// para ignorar ;
			sidelinesSurface = (ODETrackSegmentDefinition::Surface)s;
			segDefinitions.clear();
			
			for (int i = 0; i < length; i++)
			{
				segDefinitions.push_back(vector< ODETrackSegmentDefinition >());

				for (int j = 0; j < width; j++)
				{
					ifile >> seg;
					segDefinitions[i].push_back(ODETrackSegmentDefinition(seg));
				}
			}
			ifile.close();

			return true;
		}

		void Save(const char* filename, const string &trackName
			, const vector< vector< ODETrackSegmentDefinition > >& segDefinitions)
		{
			if (segDefinitions.size() <= 0)
			{
				return;
			}
			ofstream ofile(filename);

			ofile << trackName << ";";
			ofile << (int)segDefinitions.size() << ";";
			ofile << (int)segDefinitions[0].size() << ";";
			ofile << (int)this->groundSurface << ";";
			ofile << (int)this->sidelinesSurface << ";";
			ofile << endl;
			
			for (int i = 0; i < (int)segDefinitions.size(); i++)
			{
				for (int j = 0; j < (int)segDefinitions[i].size(); j++)
				{
					ofile << segDefinitions[i][j];
				}
				ofile << endl;
			}
			ofile.close();
		}

		void load(System::String^ filename)
		{
			vector< vector< ODETrackSegmentDefinition > > loadSegments, inverted;
			string file, trackName;

			To_string(filename, file);

			if (Load(file.c_str(), trackName, loadSegments))
			{
				setName(trackName.c_str());
				flipHorizontal(loadSegments, inverted);
				setTrack(inverted);
			}
		}
		
		void save(System::String^ filename)
		{
			vector< vector< ODETrackSegmentDefinition > > inverted;
			string file;

			To_string(filename, file);
			flipHorizontal(*this->segments, inverted);
			Save(file.c_str(), getName(), inverted);
		}

#pragma endregion

#pragma region flip

		void flipHorizontal(const vector< vector< ODETrackSegmentDefinition > > &segments
				, vector< vector< ODETrackSegmentDefinition > > &newSegments)
		{
			newSegments.clear();

			for (int i = 0; i < (int)segments.size(); i++)
			{
				newSegments.push_back(vector< ODETrackSegmentDefinition >());
				
				for (int j = 0; j < (int)segments[i].size(); j++)
				{
					newSegments[i].push_back(flipHorizontal(segments[i][(int)segments[i].size() - j - 1]));
				}
			}
		}

		ODETrackSegmentDefinition flipHorizontal(const ODETrackSegmentDefinition &seg)
		{
			ODETrackSegmentDefinition::Block b;

			switch (seg.getType())
			{
			case ODETrackSegmentDefinition::StartStraightLeft:
				b = ODETrackSegmentDefinition::StartStraightRight;
				break;

			case ODETrackSegmentDefinition::StartStraightRight:
				b = ODETrackSegmentDefinition::StartStraightLeft;
				break;

			case ODETrackSegmentDefinition::Curve90BottomToRight:
				b = ODETrackSegmentDefinition::Curve90LeftToBottom;
				break;

			case ODETrackSegmentDefinition::Curve90TopToRight:
				b = ODETrackSegmentDefinition::Curve90LeftToTop;
				break;

			case ODETrackSegmentDefinition::Curve90LeftToBottom:
				b = ODETrackSegmentDefinition::Curve90BottomToRight;
				break;

			case ODETrackSegmentDefinition::Curve90LeftToTop:
				b = ODETrackSegmentDefinition::Curve90TopToRight;
				break;
			
			default:
				b = seg.getType();
				break;
			}

			return ODETrackSegmentDefinition::get(b);
		}

#pragma endregion

#pragma region setTrack
		void setTrack(const vector< vector< ODETrackSegmentDefinition > > &loadSegments)
		{
			int width, length;

			this->tbTrack->ColumnStyles->Clear();
			this->tbTrack->RowStyles->Clear();
			this->tbTrack->Controls->Clear();
			this->segments->clear();
			length = loadSegments.size();
			width = (loadSegments.size() > 0 ? loadSegments[0].size() : 0);
			this->tbTrack->ColumnCount = width;
			this->tbTrack->RowCount = length;

			for (int i = 0; i < width; i++)
			{
				this->tbTrack->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50)));
			}

			for (int i = 0; i < length; i++)
			{
				this->tbTrack->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			}
			
			for (int i = 0; i < length; i++)
			{
				this->segments->push_back(vector< ODETrackSegmentDefinition >());

				for (int j = 0; j < width; j++)
				{
					(*this->segments)[i].push_back(loadSegments[i][j]);
					this->tbTrack->Controls->Add(
						newButton((*this->segments)[i][j].getType(), j, i
						, this->curDir + "\\"), j, i);
				}
			}
			hasStart = ODETrackValidator::hasStart(loadSegments);
			setWidth(width);
			setLength(length);
			this->ddGroundSurface->SelectedIndex = (int)this->groundSurface;
			this->ddSidelinesSurface->SelectedIndex = (int)this->sidelinesSurface;
		}

#pragma endregion

#pragma region get set

		void setGroundSurface(int i)
		{
			this->ddGroundSurface->SelectedIndex = i;
		}

		void setSidelinesSurface(int i)
		{
			this->ddSidelinesSurface->SelectedIndex = i;
		}

		ODETrackSegmentDefinition::Surface getSurface(System::String^ s)
		{
			if (s == "Cascalho")
			{
				return ODETrackSegmentDefinition::Gravel;
			}

			if (s == "Relva")
			{
				return ODETrackSegmentDefinition::Grass;
			}

			if (s == "Neve")
			{
				return ODETrackSegmentDefinition::Snow;
			}

			if (s == "Gelo")
			{
				return ODETrackSegmentDefinition::Ice;
			}

			return ODETrackSegmentDefinition::Gravel;
		}

		ODETrackSegmentDefinition::Surface getGroundSurface()
		{
			return getSurface(this->ddGroundSurface->SelectedText);
		}

		ODETrackSegmentDefinition::Surface getSidelinesSurface()
		{
			return getSurface(this->ddSidelinesSurface->SelectedText);
		}

		void setName(const char *name)
		{
			*this->name = name;
			this->txtNome->Text = gcnew System::String(name);
		}

		void setName(System::String^ name)
		{
			To_string(name, *this->name);
			this->txtNome->Text = name;
		}

		string getName()
		{
			To_string(this->txtNome->Text, *this->name);
			return *(this->name);
		}

		int getWidth()
		{
			return this->width;
		}

		int getLength()
		{
			return this->length;
		}

		void setWidth(int w)
		{
			this->width = w;
			this->lblTamanho->Text = w + "x" + getLength();
		}

		void setLength(int l)
		{
			this->length = l;
			this->lblTamanho->Text = getWidth() + "x" + l;
		}

#pragma endregion

#pragma region destrutor finalizador

		~Form1()
		{
			this->!Form1();
		}

		!Form1()
		{
			if (components)
			{
				delete this->components;
			}
			delete this->name;
			delete this->segments;
		}

#pragma endregion

#pragma region atributos

	protected: 
		string *name;
		vector< vector< ODETrackSegmentDefinition > > *segments;
		ODETrackSegmentDefinition::Surface groundSurface;
		ODETrackSegmentDefinition::Surface sidelinesSurface;
		ODETrackSegmentDefinition::Block current;
		int width, length;
		System::String^ curDir;
		bool hasStart;

#pragma endregion

#pragma region newtrack

		void newTrack(int width, int length, System::String^ name
			, int ground, int sidelines)
		{
			this->tbTrack->ColumnStyles->Clear();
			this->tbTrack->RowStyles->Clear();
			this->tbTrack->Controls->Clear();
			this->tbTrack->ColumnCount = width;
			this->tbTrack->RowCount = length;
			this->segments->clear();

			for (int i = 0; i < width; i++)
			{
				this->tbTrack->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50)));
			}

			for (int i = 0; i < length; i++)
			{
				this->tbTrack->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			}

			for (int i = 0; i < length; i++)
			{
				this->segments->push_back(vector< ODETrackSegmentDefinition >());

				for (int j = 0; j < width; j++)
				{
					(*this->segments)[i].push_back(ODETrackSegmentDefinition::get(ODETrackSegmentDefinition::Empty));
					this->tbTrack->Controls->Add(newButton((*this->segments)[i][j].getType(), j, i), j, i);
				}
			}
			setName(name);
			this->ddGroundSurface->SelectedIndex = ground;
			this->ddSidelinesSurface->SelectedIndex = sidelines;
			this->groundSurface = (ODETrackSegmentDefinition::Surface)ground;
			this->sidelinesSurface = (ODETrackSegmentDefinition::Surface)sidelines;
			this->cbStartStraightFront->Checked = true;
			this->current = ODETrackSegmentDefinition::StartStraightFront;
			setWidth(width);
			setLength(length);
			hasStart = false;
		}

#pragma endregion

#pragma region getimage

		System::Drawing::Image^ getImage(ODETrackSegmentDefinition::Block b)
		{
			return getImage("", b);
		}

		System::Drawing::Image^ getImage(System::String^ dir
			, ODETrackSegmentDefinition::Block b)
		{
			switch (b)
			{
			case ODETrackSegmentDefinition::Curve90TopToRight:
				return System::Drawing::Image::FromFile(dir + "imagens\\Curve90TopToRight.gif");

			case ODETrackSegmentDefinition::Curve90LeftToTop:
				return System::Drawing::Image::FromFile(dir + "imagens\\Curve90LeftToFront.gif");

			case ODETrackSegmentDefinition::Curve90LeftToBottom:
				return System::Drawing::Image::FromFile(dir + "imagens\\Curve90LeftToBottom.gif");

			case ODETrackSegmentDefinition::Curve90BottomToRight:
				return System::Drawing::Image::FromFile(dir + "imagens\\Curve90BottomToRight.gif");

			case ODETrackSegmentDefinition::StraightSide:
				return System::Drawing::Image::FromFile(dir + "imagens\\StraightSide.gif");

			case ODETrackSegmentDefinition::Straight:
				return System::Drawing::Image::FromFile(dir + "imagens\\Straight.gif");

			case ODETrackSegmentDefinition::StartStraightRight:
				return System::Drawing::Image::FromFile(dir + "imagens\\StartStraightRight.gif");

			case ODETrackSegmentDefinition::StartStraightLeft:
				return System::Drawing::Image::FromFile(dir + "imagens\\StartStraightLeft.gif");

			case ODETrackSegmentDefinition::StartStraightFront:
				return System::Drawing::Image::FromFile(dir + "imagens\\StartStraightFront.gif");

			case ODETrackSegmentDefinition::StartStraightBack:
				return System::Drawing::Image::FromFile(dir + "imagens\\StartStraightBack.gif");

			case ODETrackSegmentDefinition::RampStraightElevated:
				return System::Drawing::Image::FromFile(dir + "imagens\\RampStraightElevated.gif");

			case ODETrackSegmentDefinition::RampStraightSunken:
				return System::Drawing::Image::FromFile(dir + "imagens\\RampStraightSunken.gif");

			case ODETrackSegmentDefinition::RampStraightSideElevated:
				return System::Drawing::Image::FromFile(dir + "imagens\\RampStraightSideElevated.gif");

			case ODETrackSegmentDefinition::RampStraightSideSunken:
				return System::Drawing::Image::FromFile(dir + "imagens\\RampStraightSideSunken.gif");

			case ODETrackSegmentDefinition::Empty:
			default:
				return System::Drawing::Image::FromFile(dir + "imagens\\Empty.gif");
			}
		}

#pragma endregion

#pragma region newbutton

		System::Windows::Forms::Button^ newButton(ODETrackSegmentDefinition::Block b
			, int x, int y)
		{
			return newButton(b, x, y, "");
		}

		System::Windows::Forms::Button^ newButton(ODETrackSegmentDefinition::Block b
			, int x, int y, System::String^ dir)
		{
			System::Windows::Forms::Button^ button1;

			button1 = (gcnew System::Windows::Forms::Button());
			button1->BackgroundImage = getImage(dir, b);
			button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			button1->Dock = System::Windows::Forms::DockStyle::Fill;
			button1->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			button1->Location = System::Drawing::Point(205, 0);
			button1->Margin = System::Windows::Forms::Padding(0);
			button1->Name = x + "," + y;
			button1->Size = System::Drawing::Size(206, 174);
			button1->TabIndex = 0;
			button1->UseVisualStyleBackColor = true;
			button1->MouseLeave += gcnew System::EventHandler(this, &Form1::button1_MouseLeave);
			button1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button1_MouseClick);
			button1->MouseHover += gcnew System::EventHandler(this, &Form1::button1_MouseHover);

			return button1;
		}

#pragma endregion

#pragma region atributos form

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  ficheiroToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  novaPistaToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  carregarToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  gravarToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  sobreToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  sairToolStripMenuItem;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SplitContainer^  splitContainer8;
	private: System::Windows::Forms::SplitContainer^  splitContainer12;
	private: System::Windows::Forms::SplitContainer^  splitContainer13;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  lblTamanho;
	private: System::Windows::Forms::SplitContainer^  splitContainer14;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  txtNome;
	private: System::Windows::Forms::CheckBox^  cbStraight;
	private: System::Windows::Forms::CheckBox^  cbCurve90LeftToBottom;
	private: System::Windows::Forms::CheckBox^  cbCurve90BottomToRight;
	private: System::Windows::Forms::CheckBox^  cbEmpty;
private: System::Windows::Forms::CheckBox^  cbRampStraightSideElevated;

	private: System::Windows::Forms::CheckBox^  cbRampStraightSunken;
	private: System::Windows::Forms::CheckBox^  cbRampStraightElevated;
private: System::Windows::Forms::CheckBox^  cbRampStraightSideSunken;

	private: System::Windows::Forms::CheckBox^  cbStraightSide;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
	private: System::Windows::Forms::CheckBox^  cbStartStraightBack;
	private: System::Windows::Forms::CheckBox^  cbStartStraightRight;
	private: System::Windows::Forms::CheckBox^  cbStartStraightLeft;
	private: System::Windows::Forms::CheckBox^  cbStartStraightFront;
	private: System::Windows::Forms::CheckBox^  cbCurve90TopToRight;
	private: System::Windows::Forms::CheckBox^  cbCurve90LeftToFront;
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	private: System::Windows::Forms::Label^  lblStatus;
	private: System::Windows::Forms::SplitContainer^  splitContainer2;
	private: System::Windows::Forms::SplitContainer^  splitContainer4;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::SplitContainer^  splitContainer5;
	private: System::Windows::Forms::SplitContainer^  splitContainer6;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ComboBox^  ddGroundSurface;
	private: System::Windows::Forms::SplitContainer^  splitContainer7;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  ddSidelinesSurface;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel3;
	private: System::Windows::Forms::TableLayoutPanel^  tbTrack;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
#pragma endregion

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->splitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			this->splitContainer8 = (gcnew System::Windows::Forms::SplitContainer());
			this->splitContainer12 = (gcnew System::Windows::Forms::SplitContainer());
			this->splitContainer14 = (gcnew System::Windows::Forms::SplitContainer());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->txtNome = (gcnew System::Windows::Forms::TextBox());
			this->splitContainer13 = (gcnew System::Windows::Forms::SplitContainer());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->lblTamanho = (gcnew System::Windows::Forms::Label());
			this->tbTrack = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->splitContainer4 = (gcnew System::Windows::Forms::SplitContainer());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->splitContainer5 = (gcnew System::Windows::Forms::SplitContainer());
			this->splitContainer6 = (gcnew System::Windows::Forms::SplitContainer());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ddGroundSurface = (gcnew System::Windows::Forms::ComboBox());
			this->splitContainer7 = (gcnew System::Windows::Forms::SplitContainer());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->ddSidelinesSurface = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->cbStartStraightBack = (gcnew System::Windows::Forms::CheckBox());
			this->cbStartStraightRight = (gcnew System::Windows::Forms::CheckBox());
			this->cbStartStraightLeft = (gcnew System::Windows::Forms::CheckBox());
			this->cbStartStraightFront = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->cbRampStraightSideSunken = (gcnew System::Windows::Forms::CheckBox());
			this->cbRampStraightSideElevated = (gcnew System::Windows::Forms::CheckBox());
			this->cbRampStraightSunken = (gcnew System::Windows::Forms::CheckBox());
			this->cbRampStraightElevated = (gcnew System::Windows::Forms::CheckBox());
			this->cbCurve90LeftToBottom = (gcnew System::Windows::Forms::CheckBox());
			this->cbCurve90BottomToRight = (gcnew System::Windows::Forms::CheckBox());
			this->cbEmpty = (gcnew System::Windows::Forms::CheckBox());
			this->cbStraightSide = (gcnew System::Windows::Forms::CheckBox());
			this->cbStraight = (gcnew System::Windows::Forms::CheckBox());
			this->cbCurve90TopToRight = (gcnew System::Windows::Forms::CheckBox());
			this->cbCurve90LeftToFront = (gcnew System::Windows::Forms::CheckBox());
			this->lblStatus = (gcnew System::Windows::Forms::Label());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->ficheiroToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->novaPistaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->carregarToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gravarToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->sobreToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->sairToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->splitContainer2->Panel1->SuspendLayout();
			this->splitContainer2->Panel2->SuspendLayout();
			this->splitContainer2->SuspendLayout();
			this->splitContainer8->Panel1->SuspendLayout();
			this->splitContainer8->Panel2->SuspendLayout();
			this->splitContainer8->SuspendLayout();
			this->splitContainer12->Panel1->SuspendLayout();
			this->splitContainer12->Panel2->SuspendLayout();
			this->splitContainer12->SuspendLayout();
			this->splitContainer14->Panel1->SuspendLayout();
			this->splitContainer14->Panel2->SuspendLayout();
			this->splitContainer14->SuspendLayout();
			this->splitContainer13->Panel1->SuspendLayout();
			this->splitContainer13->Panel2->SuspendLayout();
			this->splitContainer13->SuspendLayout();
			this->splitContainer4->Panel1->SuspendLayout();
			this->splitContainer4->Panel2->SuspendLayout();
			this->splitContainer4->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->splitContainer5->Panel1->SuspendLayout();
			this->splitContainer5->Panel2->SuspendLayout();
			this->splitContainer5->SuspendLayout();
			this->splitContainer6->Panel1->SuspendLayout();
			this->splitContainer6->Panel2->SuspendLayout();
			this->splitContainer6->SuspendLayout();
			this->splitContainer7->Panel1->SuspendLayout();
			this->splitContainer7->Panel2->SuspendLayout();
			this->splitContainer7->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->tableLayoutPanel1->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// splitContainer1
			// 
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->splitContainer1->IsSplitterFixed = true;
			this->splitContainer1->Location = System::Drawing::Point(0, 24);
			this->splitContainer1->Name = L"splitContainer1";
			this->splitContainer1->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->splitContainer2);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->lblStatus);
			this->splitContainer1->Panel2->Padding = System::Windows::Forms::Padding(6);
			this->splitContainer1->Size = System::Drawing::Size(582, 461);
			this->splitContainer1->SplitterDistance = 435;
			this->splitContainer1->SplitterWidth = 1;
			this->splitContainer1->TabIndex = 0;
			this->splitContainer1->TabStop = false;
			// 
			// splitContainer2
			// 
			this->splitContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer2->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->splitContainer2->IsSplitterFixed = true;
			this->splitContainer2->Location = System::Drawing::Point(0, 0);
			this->splitContainer2->Name = L"splitContainer2";
			// 
			// splitContainer2.Panel1
			// 
			this->splitContainer2->Panel1->Controls->Add(this->splitContainer8);
			// 
			// splitContainer2.Panel2
			// 
			this->splitContainer2->Panel2->Controls->Add(this->splitContainer4);
			this->splitContainer2->Size = System::Drawing::Size(582, 435);
			this->splitContainer2->SplitterDistance = 444;
			this->splitContainer2->SplitterWidth = 1;
			this->splitContainer2->TabIndex = 0;
			// 
			// splitContainer8
			// 
			this->splitContainer8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer8->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitContainer8->IsSplitterFixed = true;
			this->splitContainer8->Location = System::Drawing::Point(0, 0);
			this->splitContainer8->Name = L"splitContainer8";
			this->splitContainer8->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer8.Panel1
			// 
			this->splitContainer8->Panel1->Controls->Add(this->splitContainer12);
			this->splitContainer8->Panel1->Padding = System::Windows::Forms::Padding(6);
			// 
			// splitContainer8.Panel2
			// 
			this->splitContainer8->Panel2->Controls->Add(this->tbTrack);
			this->splitContainer8->Panel2->Padding = System::Windows::Forms::Padding(6);
			this->splitContainer8->Size = System::Drawing::Size(444, 435);
			this->splitContainer8->SplitterDistance = 32;
			this->splitContainer8->SplitterWidth = 1;
			this->splitContainer8->TabIndex = 1;
			// 
			// splitContainer12
			// 
			this->splitContainer12->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer12->FixedPanel = System::Windows::Forms::FixedPanel::Panel2;
			this->splitContainer12->IsSplitterFixed = true;
			this->splitContainer12->Location = System::Drawing::Point(6, 6);
			this->splitContainer12->Name = L"splitContainer12";
			// 
			// splitContainer12.Panel1
			// 
			this->splitContainer12->Panel1->Controls->Add(this->splitContainer14);
			// 
			// splitContainer12.Panel2
			// 
			this->splitContainer12->Panel2->Controls->Add(this->splitContainer13);
			this->splitContainer12->Size = System::Drawing::Size(432, 20);
			this->splitContainer12->SplitterDistance = 276;
			this->splitContainer12->SplitterWidth = 15;
			this->splitContainer12->TabIndex = 0;
			// 
			// splitContainer14
			// 
			this->splitContainer14->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer14->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitContainer14->IsSplitterFixed = true;
			this->splitContainer14->Location = System::Drawing::Point(0, 0);
			this->splitContainer14->Name = L"splitContainer14";
			// 
			// splitContainer14.Panel1
			// 
			this->splitContainer14->Panel1->Controls->Add(this->label6);
			// 
			// splitContainer14.Panel2
			// 
			this->splitContainer14->Panel2->Controls->Add(this->txtNome);
			this->splitContainer14->Size = System::Drawing::Size(276, 20);
			this->splitContainer14->SplitterDistance = 40;
			this->splitContainer14->SplitterWidth = 1;
			this->splitContainer14->TabIndex = 0;
			// 
			// label6
			// 
			this->label6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label6->Location = System::Drawing::Point(0, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(40, 20);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Nome:";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// txtNome
			// 
			this->txtNome->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtNome->Location = System::Drawing::Point(0, 0);
			this->txtNome->Name = L"txtNome";
			this->txtNome->Size = System::Drawing::Size(235, 20);
			this->txtNome->TabIndex = 0;
			this->txtNome->TextChanged += gcnew System::EventHandler(this, &Form1::txtNome_TextChanged);
			// 
			// splitContainer13
			// 
			this->splitContainer13->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer13->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitContainer13->IsSplitterFixed = true;
			this->splitContainer13->Location = System::Drawing::Point(0, 0);
			this->splitContainer13->Name = L"splitContainer13";
			// 
			// splitContainer13.Panel1
			// 
			this->splitContainer13->Panel1->Controls->Add(this->label5);
			// 
			// splitContainer13.Panel2
			// 
			this->splitContainer13->Panel2->Controls->Add(this->lblTamanho);
			this->splitContainer13->Size = System::Drawing::Size(141, 20);
			this->splitContainer13->SplitterDistance = 55;
			this->splitContainer13->SplitterWidth = 1;
			this->splitContainer13->TabIndex = 0;
			// 
			// label5
			// 
			this->label5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label5->Location = System::Drawing::Point(0, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(55, 20);
			this->label5->TabIndex = 0;
			this->label5->Text = L"Tamanho:";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// lblTamanho
			// 
			this->lblTamanho->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblTamanho->Location = System::Drawing::Point(0, 0);
			this->lblTamanho->Name = L"lblTamanho";
			this->lblTamanho->Size = System::Drawing::Size(85, 20);
			this->lblTamanho->TabIndex = 0;
			this->lblTamanho->Text = L"5x5";
			this->lblTamanho->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// tbTrack
			// 
			this->tbTrack->ColumnCount = 2;
			this->tbTrack->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tbTrack->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tbTrack->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tbTrack->Location = System::Drawing::Point(6, 6);
			this->tbTrack->Name = L"tbTrack";
			this->tbTrack->RowCount = 2;
			this->tbTrack->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tbTrack->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tbTrack->Size = System::Drawing::Size(432, 390);
			this->tbTrack->TabIndex = 0;
			// 
			// splitContainer4
			// 
			this->splitContainer4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer4->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitContainer4->IsSplitterFixed = true;
			this->splitContainer4->Location = System::Drawing::Point(0, 0);
			this->splitContainer4->Name = L"splitContainer4";
			this->splitContainer4->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer4.Panel1
			// 
			this->splitContainer4->Panel1->Controls->Add(this->groupBox1);
			// 
			// splitContainer4.Panel2
			// 
			this->splitContainer4->Panel2->Controls->Add(this->groupBox3);
			this->splitContainer4->Size = System::Drawing::Size(137, 435);
			this->splitContainer4->SplitterDistance = 80;
			this->splitContainer4->SplitterWidth = 1;
			this->splitContainer4->TabIndex = 0;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->splitContainer5);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox1->Location = System::Drawing::Point(0, 0);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(6);
			this->groupBox1->Size = System::Drawing::Size(137, 80);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Superfície";
			// 
			// splitContainer5
			// 
			this->splitContainer5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer5->Location = System::Drawing::Point(6, 19);
			this->splitContainer5->Name = L"splitContainer5";
			this->splitContainer5->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// splitContainer5.Panel1
			// 
			this->splitContainer5->Panel1->Controls->Add(this->splitContainer6);
			// 
			// splitContainer5.Panel2
			// 
			this->splitContainer5->Panel2->Controls->Add(this->splitContainer7);
			this->splitContainer5->Size = System::Drawing::Size(125, 55);
			this->splitContainer5->SplitterDistance = 25;
			this->splitContainer5->SplitterWidth = 1;
			this->splitContainer5->TabIndex = 0;
			// 
			// splitContainer6
			// 
			this->splitContainer6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer6->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitContainer6->IsSplitterFixed = true;
			this->splitContainer6->Location = System::Drawing::Point(0, 0);
			this->splitContainer6->Name = L"splitContainer6";
			// 
			// splitContainer6.Panel1
			// 
			this->splitContainer6->Panel1->Controls->Add(this->label1);
			// 
			// splitContainer6.Panel2
			// 
			this->splitContainer6->Panel2->Controls->Add(this->ddGroundSurface);
			this->splitContainer6->Size = System::Drawing::Size(125, 25);
			this->splitContainer6->SplitterDistance = 46;
			this->splitContainer6->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(46, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Pista:";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// ddGroundSurface
			// 
			this->ddGroundSurface->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ddGroundSurface->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ddGroundSurface->Enabled = false;
			this->ddGroundSurface->FormattingEnabled = true;
			this->ddGroundSurface->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"Cascalho", L"Relva", L"Neve", L"Gelo"});
			this->ddGroundSurface->Location = System::Drawing::Point(0, 0);
			this->ddGroundSurface->Name = L"ddGroundSurface";
			this->ddGroundSurface->Size = System::Drawing::Size(75, 21);
			this->ddGroundSurface->TabIndex = 0;
			this->ddGroundSurface->TabStop = false;
			// 
			// splitContainer7
			// 
			this->splitContainer7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer7->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitContainer7->IsSplitterFixed = true;
			this->splitContainer7->Location = System::Drawing::Point(0, 0);
			this->splitContainer7->Name = L"splitContainer7";
			// 
			// splitContainer7.Panel1
			// 
			this->splitContainer7->Panel1->Controls->Add(this->label2);
			// 
			// splitContainer7.Panel2
			// 
			this->splitContainer7->Panel2->Controls->Add(this->ddSidelinesSurface);
			this->splitContainer7->Size = System::Drawing::Size(125, 29);
			this->splitContainer7->SplitterDistance = 46;
			this->splitContainer7->TabIndex = 0;
			// 
			// label2
			// 
			this->label2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label2->Location = System::Drawing::Point(0, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(46, 29);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Exterior:";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// ddSidelinesSurface
			// 
			this->ddSidelinesSurface->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ddSidelinesSurface->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ddSidelinesSurface->Enabled = false;
			this->ddSidelinesSurface->FormattingEnabled = true;
			this->ddSidelinesSurface->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"Cascalho", L"Relva", L"Neve", L"Gelo"});
			this->ddSidelinesSurface->Location = System::Drawing::Point(0, 0);
			this->ddSidelinesSurface->Name = L"ddSidelinesSurface";
			this->ddSidelinesSurface->Size = System::Drawing::Size(75, 21);
			this->ddSidelinesSurface->TabIndex = 0;
			this->ddSidelinesSurface->TabStop = false;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->tableLayoutPanel1);
			this->groupBox3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox3->Location = System::Drawing::Point(0, 0);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Padding = System::Windows::Forms::Padding(6);
			this->groupBox3->Size = System::Drawing::Size(137, 354);
			this->groupBox3->TabIndex = 1;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Segmentos";
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				100)));
			this->tableLayoutPanel1->Controls->Add(this->groupBox4, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->groupBox5, 0, 0);
			this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel1->Location = System::Drawing::Point(6, 19);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 57)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 43)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(125, 329);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->tableLayoutPanel2);
			this->groupBox4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox4->Location = System::Drawing::Point(3, 190);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Padding = System::Windows::Forms::Padding(6);
			this->groupBox4->Size = System::Drawing::Size(119, 136);
			this->groupBox4->TabIndex = 0;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Meta";
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				50)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				50)));
			this->tableLayoutPanel2->Controls->Add(this->cbStartStraightBack, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->cbStartStraightRight, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->cbStartStraightLeft, 0, 1);
			this->tableLayoutPanel2->Controls->Add(this->cbStartStraightFront, 0, 0);
			this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel2->GrowStyle = System::Windows::Forms::TableLayoutPanelGrowStyle::FixedSize;
			this->tableLayoutPanel2->Location = System::Drawing::Point(6, 19);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(107, 111);
			this->tableLayoutPanel2->TabIndex = 0;
			// 
			// cbStartStraightBack
			// 
			this->cbStartStraightBack->Appearance = System::Windows::Forms::Appearance::Button;
			this->cbStartStraightBack->AutoSize = true;
			this->cbStartStraightBack->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->cbStartStraightBack->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbStartStraightBack->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cbStartStraightBack->Location = System::Drawing::Point(56, 3);
			this->cbStartStraightBack->Name = L"cbStartStraightBack";
			this->cbStartStraightBack->Size = System::Drawing::Size(48, 49);
			this->cbStartStraightBack->TabIndex = 11;
			this->cbStartStraightBack->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbStartStraightBack->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->cbStartStraightBack->UseVisualStyleBackColor = false;
			this->cbStartStraightBack->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::cbStartStraightBack_MouseClick);
			// 
			// cbStartStraightRight
			// 
			this->cbStartStraightRight->Appearance = System::Windows::Forms::Appearance::Button;
			this->cbStartStraightRight->AutoSize = true;
			this->cbStartStraightRight->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->cbStartStraightRight->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbStartStraightRight->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cbStartStraightRight->Enabled = false;
			this->cbStartStraightRight->Location = System::Drawing::Point(3, 58);
			this->cbStartStraightRight->Name = L"cbStartStraightRight";
			this->cbStartStraightRight->Size = System::Drawing::Size(47, 50);
			this->cbStartStraightRight->TabIndex = 10;
			this->cbStartStraightRight->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbStartStraightRight->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->cbStartStraightRight->UseVisualStyleBackColor = false;
			this->cbStartStraightRight->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::cbStartStraightRight_MouseClick);
			// 
			// cbStartStraightLeft
			// 
			this->cbStartStraightLeft->Appearance = System::Windows::Forms::Appearance::Button;
			this->cbStartStraightLeft->AutoSize = true;
			this->cbStartStraightLeft->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->cbStartStraightLeft->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbStartStraightLeft->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cbStartStraightLeft->Enabled = false;
			this->cbStartStraightLeft->Location = System::Drawing::Point(56, 58);
			this->cbStartStraightLeft->Name = L"cbStartStraightLeft";
			this->cbStartStraightLeft->Size = System::Drawing::Size(48, 50);
			this->cbStartStraightLeft->TabIndex = 9;
			this->cbStartStraightLeft->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbStartStraightLeft->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->cbStartStraightLeft->UseVisualStyleBackColor = false;
			this->cbStartStraightLeft->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::cbStartStraightLeft_MouseClick);
			// 
			// cbStartStraightFront
			// 
			this->cbStartStraightFront->Appearance = System::Windows::Forms::Appearance::Button;
			this->cbStartStraightFront->AutoSize = true;
			this->cbStartStraightFront->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->cbStartStraightFront->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbStartStraightFront->Checked = true;
			this->cbStartStraightFront->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cbStartStraightFront->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cbStartStraightFront->Location = System::Drawing::Point(3, 3);
			this->cbStartStraightFront->Name = L"cbStartStraightFront";
			this->cbStartStraightFront->Size = System::Drawing::Size(47, 49);
			this->cbStartStraightFront->TabIndex = 8;
			this->cbStartStraightFront->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbStartStraightFront->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->cbStartStraightFront->UseVisualStyleBackColor = false;
			this->cbStartStraightFront->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::cbStartStraightFront_MouseClick);
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->tableLayoutPanel3);
			this->groupBox5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox5->Location = System::Drawing::Point(3, 3);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Padding = System::Windows::Forms::Padding(6);
			this->groupBox5->Size = System::Drawing::Size(119, 181);
			this->groupBox5->TabIndex = 1;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Geral";
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->ColumnCount = 3;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				33.33333F)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				33.33333F)));
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				33.33333F)));
			this->tableLayoutPanel3->Controls->Add(this->cbRampStraightSideSunken, 1, 3);
			this->tableLayoutPanel3->Controls->Add(this->cbRampStraightSideElevated, 0, 3);
			this->tableLayoutPanel3->Controls->Add(this->cbRampStraightSunken, 2, 2);
			this->tableLayoutPanel3->Controls->Add(this->cbRampStraightElevated, 2, 1);
			this->tableLayoutPanel3->Controls->Add(this->cbCurve90LeftToBottom, 1, 1);
			this->tableLayoutPanel3->Controls->Add(this->cbCurve90BottomToRight, 0, 1);
			this->tableLayoutPanel3->Controls->Add(this->cbEmpty, 2, 0);
			this->tableLayoutPanel3->Controls->Add(this->cbStraightSide, 1, 0);
			this->tableLayoutPanel3->Controls->Add(this->cbStraight, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->cbCurve90TopToRight, 0, 2);
			this->tableLayoutPanel3->Controls->Add(this->cbCurve90LeftToFront, 1, 2);
			this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tableLayoutPanel3->GrowStyle = System::Windows::Forms::TableLayoutPanelGrowStyle::FixedSize;
			this->tableLayoutPanel3->Location = System::Drawing::Point(6, 19);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 4;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 25)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(107, 156);
			this->tableLayoutPanel3->TabIndex = 0;
			// 
			// cbRampStraightSideSunken
			// 
			this->cbRampStraightSideSunken->Appearance = System::Windows::Forms::Appearance::Button;
			this->cbRampStraightSideSunken->AutoSize = true;
			this->cbRampStraightSideSunken->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->cbRampStraightSideSunken->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbRampStraightSideSunken->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cbRampStraightSideSunken->Location = System::Drawing::Point(38, 120);
			this->cbRampStraightSideSunken->Name = L"cbRampStraightSideSunken";
			this->cbRampStraightSideSunken->Size = System::Drawing::Size(29, 33);
			this->cbRampStraightSideSunken->TabIndex = 19;
			this->cbRampStraightSideSunken->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbRampStraightSideSunken->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->cbRampStraightSideSunken->UseVisualStyleBackColor = false;
			this->cbRampStraightSideSunken->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::cbStraightSideSunken_CheckedChanged);
			// 
			// cbRampStraightSideElevated
			// 
			this->cbRampStraightSideElevated->Appearance = System::Windows::Forms::Appearance::Button;
			this->cbRampStraightSideElevated->AutoSize = true;
			this->cbRampStraightSideElevated->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->cbRampStraightSideElevated->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbRampStraightSideElevated->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cbRampStraightSideElevated->Location = System::Drawing::Point(3, 120);
			this->cbRampStraightSideElevated->Name = L"cbRampStraightSideElevated";
			this->cbRampStraightSideElevated->Size = System::Drawing::Size(29, 33);
			this->cbRampStraightSideElevated->TabIndex = 18;
			this->cbRampStraightSideElevated->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbRampStraightSideElevated->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->cbRampStraightSideElevated->UseVisualStyleBackColor = false;
			this->cbRampStraightSideElevated->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::cbStraightSideElevated_CheckedChanged);
			// 
			// cbRampStraightSunken
			// 
			this->cbRampStraightSunken->Appearance = System::Windows::Forms::Appearance::Button;
			this->cbRampStraightSunken->AutoSize = true;
			this->cbRampStraightSunken->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->cbRampStraightSunken->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbRampStraightSunken->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cbRampStraightSunken->Location = System::Drawing::Point(73, 81);
			this->cbRampStraightSunken->Name = L"cbRampStraightSunken";
			this->cbRampStraightSunken->Size = System::Drawing::Size(31, 33);
			this->cbRampStraightSunken->TabIndex = 17;
			this->cbRampStraightSunken->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbRampStraightSunken->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->cbRampStraightSunken->UseVisualStyleBackColor = false;
			this->cbRampStraightSunken->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::cbRampStraightSunken_CheckedChanged);
			// 
			// cbRampStraightElevated
			// 
			this->cbRampStraightElevated->Appearance = System::Windows::Forms::Appearance::Button;
			this->cbRampStraightElevated->AutoSize = true;
			this->cbRampStraightElevated->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->cbRampStraightElevated->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbRampStraightElevated->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cbRampStraightElevated->Location = System::Drawing::Point(73, 42);
			this->cbRampStraightElevated->Name = L"cbRampStraightElevated";
			this->cbRampStraightElevated->Size = System::Drawing::Size(31, 33);
			this->cbRampStraightElevated->TabIndex = 16;
			this->cbRampStraightElevated->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbRampStraightElevated->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->cbRampStraightElevated->UseVisualStyleBackColor = false;
			this->cbRampStraightElevated->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::cbRampStraightElevated_CheckedChanged);
			// 
			// cbCurve90LeftToBottom
			// 
			this->cbCurve90LeftToBottom->Appearance = System::Windows::Forms::Appearance::Button;
			this->cbCurve90LeftToBottom->AutoSize = true;
			this->cbCurve90LeftToBottom->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->cbCurve90LeftToBottom->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbCurve90LeftToBottom->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cbCurve90LeftToBottom->Location = System::Drawing::Point(38, 42);
			this->cbCurve90LeftToBottom->Name = L"cbCurve90LeftToBottom";
			this->cbCurve90LeftToBottom->Size = System::Drawing::Size(29, 33);
			this->cbCurve90LeftToBottom->TabIndex = 11;
			this->cbCurve90LeftToBottom->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbCurve90LeftToBottom->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->cbCurve90LeftToBottom->UseVisualStyleBackColor = false;
			this->cbCurve90LeftToBottom->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::cbCurve90LeftToBottom_MouseClick);
			// 
			// cbCurve90BottomToRight
			// 
			this->cbCurve90BottomToRight->Appearance = System::Windows::Forms::Appearance::Button;
			this->cbCurve90BottomToRight->AutoSize = true;
			this->cbCurve90BottomToRight->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->cbCurve90BottomToRight->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbCurve90BottomToRight->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cbCurve90BottomToRight->Location = System::Drawing::Point(3, 42);
			this->cbCurve90BottomToRight->Name = L"cbCurve90BottomToRight";
			this->cbCurve90BottomToRight->Size = System::Drawing::Size(29, 33);
			this->cbCurve90BottomToRight->TabIndex = 10;
			this->cbCurve90BottomToRight->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbCurve90BottomToRight->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->cbCurve90BottomToRight->UseVisualStyleBackColor = false;
			this->cbCurve90BottomToRight->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::cbCurve90BottomToRight_MouseClick);
			// 
			// cbEmpty
			// 
			this->cbEmpty->Appearance = System::Windows::Forms::Appearance::Button;
			this->cbEmpty->AutoSize = true;
			this->cbEmpty->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->cbEmpty->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbEmpty->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cbEmpty->Location = System::Drawing::Point(73, 3);
			this->cbEmpty->Name = L"cbEmpty";
			this->cbEmpty->Size = System::Drawing::Size(31, 33);
			this->cbEmpty->TabIndex = 9;
			this->cbEmpty->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbEmpty->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->cbEmpty->UseVisualStyleBackColor = false;
			this->cbEmpty->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::cbEmpty_MouseClick);
			// 
			// cbStraightSide
			// 
			this->cbStraightSide->Appearance = System::Windows::Forms::Appearance::Button;
			this->cbStraightSide->AutoSize = true;
			this->cbStraightSide->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->cbStraightSide->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbStraightSide->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cbStraightSide->Location = System::Drawing::Point(38, 3);
			this->cbStraightSide->Name = L"cbStraightSide";
			this->cbStraightSide->Size = System::Drawing::Size(29, 33);
			this->cbStraightSide->TabIndex = 8;
			this->cbStraightSide->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbStraightSide->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->cbStraightSide->UseVisualStyleBackColor = false;
			this->cbStraightSide->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::cbStraightSide_MouseClick);
			// 
			// cbStraight
			// 
			this->cbStraight->Appearance = System::Windows::Forms::Appearance::Button;
			this->cbStraight->AutoSize = true;
			this->cbStraight->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->cbStraight->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbStraight->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cbStraight->Location = System::Drawing::Point(3, 3);
			this->cbStraight->Name = L"cbStraight";
			this->cbStraight->Size = System::Drawing::Size(29, 33);
			this->cbStraight->TabIndex = 7;
			this->cbStraight->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbStraight->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->cbStraight->UseVisualStyleBackColor = false;
			this->cbStraight->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::cbStraight_MouseClick);
			// 
			// cbCurve90TopToRight
			// 
			this->cbCurve90TopToRight->Appearance = System::Windows::Forms::Appearance::Button;
			this->cbCurve90TopToRight->AutoSize = true;
			this->cbCurve90TopToRight->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->cbCurve90TopToRight->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbCurve90TopToRight->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cbCurve90TopToRight->Location = System::Drawing::Point(3, 81);
			this->cbCurve90TopToRight->Name = L"cbCurve90TopToRight";
			this->cbCurve90TopToRight->Size = System::Drawing::Size(29, 33);
			this->cbCurve90TopToRight->TabIndex = 12;
			this->cbCurve90TopToRight->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbCurve90TopToRight->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->cbCurve90TopToRight->UseVisualStyleBackColor = false;
			this->cbCurve90TopToRight->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::cbCurve90TopToRight_MouseClick);
			// 
			// cbCurve90LeftToFront
			// 
			this->cbCurve90LeftToFront->Appearance = System::Windows::Forms::Appearance::Button;
			this->cbCurve90LeftToFront->AutoSize = true;
			this->cbCurve90LeftToFront->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->cbCurve90LeftToFront->CheckAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbCurve90LeftToFront->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cbCurve90LeftToFront->Location = System::Drawing::Point(38, 81);
			this->cbCurve90LeftToFront->Name = L"cbCurve90LeftToFront";
			this->cbCurve90LeftToFront->Size = System::Drawing::Size(29, 33);
			this->cbCurve90LeftToFront->TabIndex = 13;
			this->cbCurve90LeftToFront->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->cbCurve90LeftToFront->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->cbCurve90LeftToFront->UseVisualStyleBackColor = false;
			this->cbCurve90LeftToFront->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::cbCurve90LeftToFront_MouseClick);
			// 
			// lblStatus
			// 
			this->lblStatus->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblStatus->Location = System::Drawing::Point(6, 6);
			this->lblStatus->Name = L"lblStatus";
			this->lblStatus->Size = System::Drawing::Size(570, 13);
			this->lblStatus->TabIndex = 0;
			this->lblStatus->Text = L"Comece por colocar a meta";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->ficheiroToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(582, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ficheiroToolStripMenuItem
			// 
			this->ficheiroToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->novaPistaToolStripMenuItem, 
				this->toolStripSeparator1, this->carregarToolStripMenuItem, this->gravarToolStripMenuItem, this->toolStripSeparator2, this->sobreToolStripMenuItem, 
				this->sairToolStripMenuItem});
			this->ficheiroToolStripMenuItem->Name = L"ficheiroToolStripMenuItem";
			this->ficheiroToolStripMenuItem->Size = System::Drawing::Size(56, 20);
			this->ficheiroToolStripMenuItem->Text = L"Ficheiro";
			// 
			// novaPistaToolStripMenuItem
			// 
			this->novaPistaToolStripMenuItem->Name = L"novaPistaToolStripMenuItem";
			this->novaPistaToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
			this->novaPistaToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->novaPistaToolStripMenuItem->Text = L"Nova pista";
			this->novaPistaToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::novaPistaToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(172, 6);
			// 
			// carregarToolStripMenuItem
			// 
			this->carregarToolStripMenuItem->Name = L"carregarToolStripMenuItem";
			this->carregarToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->carregarToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->carregarToolStripMenuItem->Text = L"Carregar";
			this->carregarToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::carregarToolStripMenuItem_Click);
			// 
			// gravarToolStripMenuItem
			// 
			this->gravarToolStripMenuItem->Name = L"gravarToolStripMenuItem";
			this->gravarToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->gravarToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->gravarToolStripMenuItem->Text = L"Gravar";
			this->gravarToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::gravarToolStripMenuItem_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(172, 6);
			// 
			// sobreToolStripMenuItem
			// 
			this->sobreToolStripMenuItem->Name = L"sobreToolStripMenuItem";
			this->sobreToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::A));
			this->sobreToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->sobreToolStripMenuItem->Text = L"Sobre";
			this->sobreToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::sobreToolStripMenuItem_Click);
			// 
			// sairToolStripMenuItem
			// 
			this->sairToolStripMenuItem->Name = L"sairToolStripMenuItem";
			this->sairToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::X));
			this->sairToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->sairToolStripMenuItem->Text = L"Sair";
			this->sairToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::sairToolStripMenuItem_Click);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->DefaultExt = L"trk";
			this->saveFileDialog1->Filter = L"Pistas (*.trk)|*.trk";
			this->saveFileDialog1->RestoreDirectory = true;
			this->saveFileDialog1->Title = L"Guardar pista";
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::saveFileDialog1_FileOk);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->DefaultExt = L"trk";
			this->openFileDialog1->Filter = L"Pistas (*.trk)|*.trk";
			this->openFileDialog1->RestoreDirectory = true;
			this->openFileDialog1->Title = L"Carregar pista";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog1_FileOk);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(582, 485);
			this->Controls->Add(this->splitContainer1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->ShowIcon = false;
			this->Text = L"Editor de pistas";
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel2->ResumeLayout(false);
			this->splitContainer1->ResumeLayout(false);
			this->splitContainer2->Panel1->ResumeLayout(false);
			this->splitContainer2->Panel2->ResumeLayout(false);
			this->splitContainer2->ResumeLayout(false);
			this->splitContainer8->Panel1->ResumeLayout(false);
			this->splitContainer8->Panel2->ResumeLayout(false);
			this->splitContainer8->ResumeLayout(false);
			this->splitContainer12->Panel1->ResumeLayout(false);
			this->splitContainer12->Panel2->ResumeLayout(false);
			this->splitContainer12->ResumeLayout(false);
			this->splitContainer14->Panel1->ResumeLayout(false);
			this->splitContainer14->Panel2->ResumeLayout(false);
			this->splitContainer14->Panel2->PerformLayout();
			this->splitContainer14->ResumeLayout(false);
			this->splitContainer13->Panel1->ResumeLayout(false);
			this->splitContainer13->Panel2->ResumeLayout(false);
			this->splitContainer13->ResumeLayout(false);
			this->splitContainer4->Panel1->ResumeLayout(false);
			this->splitContainer4->Panel2->ResumeLayout(false);
			this->splitContainer4->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->splitContainer5->Panel1->ResumeLayout(false);
			this->splitContainer5->Panel2->ResumeLayout(false);
			this->splitContainer5->ResumeLayout(false);
			this->splitContainer6->Panel1->ResumeLayout(false);
			this->splitContainer6->Panel2->ResumeLayout(false);
			this->splitContainer6->ResumeLayout(false);
			this->splitContainer7->Panel1->ResumeLayout(false);
			this->splitContainer7->Panel2->ResumeLayout(false);
			this->splitContainer7->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

#pragma region toggle untogle

	 protected: void UntoggleButtons()
	 {
		this->cbStraight->Checked = false;
		this->cbCurve90LeftToBottom->Checked = false;
		this->cbCurve90BottomToRight->Checked = false;
		this->cbEmpty->Checked = false;
		this->cbStraightSide->Checked = false;
		this->cbStartStraightBack->Checked = false;
		this->cbStartStraightRight->Checked = false;
		this->cbStartStraightLeft->Checked = false;
		this->cbStartStraightFront->Checked = false;
		this->cbCurve90TopToRight->Checked = false;
		this->cbCurve90LeftToFront->Checked = false;
		this->cbRampStraightSideElevated->Checked = false;
		this->cbRampStraightSideSunken->Checked = false;
		this->cbRampStraightElevated->Checked = false;
		this->cbRampStraightSunken->Checked = false;
	 }

	protected: void Toggle(System::Windows::Forms::CheckBox^ cb)
	{
		if (cb->Checked)
		 {
			UntoggleButtons();
			cb->Checked = true;
		 }
	}

#pragma endregion

#pragma region eventos click

private: System::Void cbStraight_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 Toggle(this->cbStraight);
			 this->current = ODETrackSegmentDefinition::Straight;
		 }

private: System::Void cbStraightSide_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 Toggle(this->cbStraightSide);
			 this->current = ODETrackSegmentDefinition::StraightSide;
		 }
private: System::Void cbEmpty_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 Toggle(this->cbEmpty);
			 this->current = ODETrackSegmentDefinition::Empty;
		 }
private: System::Void cbCurve90BottomToRight_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 Toggle(this->cbCurve90BottomToRight);
			 this->current = ODETrackSegmentDefinition::Curve90BottomToRight;
		 }
private: System::Void cbCurve90LeftToBottom_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 Toggle(this->cbCurve90LeftToBottom);
			 this->current = ODETrackSegmentDefinition::Curve90LeftToBottom;
		 }
private: System::Void cbCurve90TopToRight_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 Toggle(this->cbCurve90TopToRight);
			 this->current = ODETrackSegmentDefinition::Curve90TopToRight;
		 }
private: System::Void cbCurve90LeftToFront_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 Toggle(this->cbCurve90LeftToFront);
			 this->current = ODETrackSegmentDefinition::Curve90LeftToTop;
		 }
private: System::Void cbStartStraightFront_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 Toggle(this->cbStartStraightFront);
			 this->current = ODETrackSegmentDefinition::StartStraightFront;
		 }
private: System::Void cbStartStraightBack_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 Toggle(this->cbStartStraightBack);
			 this->current = ODETrackSegmentDefinition::StartStraightBack;
		 }
private: System::Void cbStartStraightRight_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 Toggle(this->cbStartStraightRight);
			 this->current = ODETrackSegmentDefinition::StartStraightRight;
		 }
private: System::Void cbStartStraightLeft_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 Toggle(this->cbStartStraightLeft);
			 this->current = ODETrackSegmentDefinition::StartStraightLeft;
		 }
private: System::Void cbStraightSideElevated_CheckedChanged(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 Toggle(this->cbRampStraightSideElevated);
			 this->current = ODETrackSegmentDefinition::RampStraightSideElevated;
		 }
private: System::Void cbStraightSideSunken_CheckedChanged(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 Toggle(this->cbRampStraightSideSunken);
			 this->current = ODETrackSegmentDefinition::RampStraightSideSunken;
		 }
private: System::Void cbRampStraightElevated_CheckedChanged(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 Toggle(this->cbRampStraightElevated);
			 this->current = ODETrackSegmentDefinition::RampStraightElevated;
		 }
private: System::Void cbRampStraightSunken_CheckedChanged(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 Toggle(this->cbRampStraightSunken);
			 this->current = ODETrackSegmentDefinition::RampStraightSunken;
		 }

#pragma endregion

#pragma region outros eventos

private: System::Void txtNome_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 To_string(this->txtNome->Text, *this->name);
		 }

#pragma endregion

#pragma region tochar string

	protected: bool To_CharStar( String^ source, char*& target )
	{
		int len = (( source->Length+1) * 2);
		target = new char[ len ];
		pin_ptr<const wchar_t> wch = PtrToStringChars( source );
		return wcstombs( target, wch, len ) != -1;
	}

	protected: bool To_string( String^ source, string &target )
	{
		int len = (( source->Length+1) * 2);
		char *ch = new char[ len ];
		bool result ;
		{
			pin_ptr<const wchar_t> wch = PtrToStringChars( source );
			result = wcstombs( ch, wch, len ) != -1;
		}
		target = ch;
		delete ch;
		return result ;
	}

#pragma endregion

#pragma region validacao

private: System::Void button1_MouseHover(System::Object^  sender, System::EventArgs^  e) {
			 int x, y;

			 getWidthLength((System::Windows::Forms::Button^)sender, x, y);

			 if (!ODETrackValidator::isValid(ODETrackSegmentDefinition::get(this->current)
				 , x, y, *this->segments))
			 {
				 ((System::Windows::Forms::Button^)sender)->FlatAppearance->BorderColor = System::Drawing::Color::Red;
			 }
			 else
			 {
				 ((System::Windows::Forms::Button^)sender)->FlatAppearance->BorderColor = System::Drawing::Color::Green;
			 }
		 }

private: System::Void button1_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
			 ((System::Windows::Forms::Button^)sender)->FlatAppearance->BorderColor = System::Drawing::Color::Black;
		 }

private: System::Void button1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 int x, y;

			 getWidthLength((System::Windows::Forms::Button^)sender, x, y);

			 if (ODETrackValidator::isValid(ODETrackSegmentDefinition::get(this->current)
				 , x, y, *this->segments))
			 {
				 (*this->segments)[y][x] = ODETrackSegmentDefinition::get(this->current);
				 getButton(this->tbTrack, x, y)->BackgroundImage = getImage(this->current);
				
				 if (!hasStart && ODETrackValidator::hasStart(*this->segments))
				 {
					 hasStart = true;
					 this->lblStatus->Text = "Vermelho significa que a colocação desse tipo de segmento invalida a pista e verde que é permitida";
				 }
			 }
		 }

#pragma endregion

#pragma region getbutton

		 System::Windows::Forms::Button^ getButton(System::Windows::Forms::TableLayoutPanel^ tbTrack
			 , int x, int y)
		 {
			int x2, y2;

			for (int i = 0; i < tbTrack->Controls->Count; i++)
			{
				getWidthLength(tbTrack->Controls[i]->Name, x2, y2);

				if ( (x == x2) && (y == y2) )
				{
					return (System::Windows::Forms::Button^)tbTrack->Controls[i];
				}
			}

			System::Windows::Forms::Button^ button1;

			return button1;
		 }

#pragma endregion

#pragma region getwidth length

		 void getWidthLength(System::Windows::Forms::Button^ b, int &x, int &y)
		 {
			 cli::array< System::String^ >^ s;

			 s = ((System::Windows::Forms::Button^)b)->Name->Split(',');
			 x = System::Convert::ToInt32(s->GetValue(0));
			 y = System::Convert::ToInt32(s->GetValue(1));
		 }

		 void getWidthLength(System::String^ name, int &x, int &y)
		 {
			 cli::array< System::String^ >^ s;

			 s = name->Split(',');
			 x = System::Convert::ToInt32(s->GetValue(0));
			 y = System::Convert::ToInt32(s->GetValue(1));
		 }

#pragma endregion

#pragma region menu

private: System::Void novaPistaToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 NewTrack n;

			 n.ShowDialog();

			 if (n.DialogResult == System::Windows::Forms::DialogResult::OK)
			 {
				 newTrack(n.getWidth(), n.getLength(), "Untitled", n.getGroundSurface(), n.getSidelinesSurface());
			 }
		 }

private: System::Void gravarToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->saveFileDialog1->ShowDialog();
		 }

private: System::Void sairToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->Close();
		 }

private: System::Void saveFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 this->save(saveFileDialog1->FileNames[0]);
		 }

private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 this->load(this->openFileDialog1->FileNames[0]);
		 }

private: System::Void carregarToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->openFileDialog1->ShowDialog();
		 }
private: System::Void sobreToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 About f;

			 f.ShowDialog();
		 }

#pragma endregion
};
}

