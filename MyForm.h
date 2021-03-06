#ifdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC

#include <vcclr.h>
#include <msclr\marshal_cppstd.h>
#include <string>
#include <SFML/Graphics.hpp>
#pragma once

using namespace std;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

typedef struct {
	string name; // Nama alat
	int kwh; // Kwh digunakan
	int duration; // Durasi / time slot digunakan
	int start_hour; // Batas jam awal
	int end_hour; // Batas jam akhir
	int p; // Wajib / opsional
	int n; // Banyak penyalaan
} Appliance;

typedef struct {
	int max;
	int kwh;
	int max_ktk;
	Appliance app[100];
} ELEMENT;

Appliance appliance[100];
Appliance sorted_appliance[100];
ELEMENT matrix[100][100];

namespace SmartGrid {

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::Button^  button1;


	public:

	public:

	private: System::Windows::Forms::Button^  button2;
	public:
		int sort_by_priority(Appliance *appliance, int n_appliance) {
			int max_id = 1;
			int temp;
			int max_kwh;
			int max_time;
			int max_part;
			int i = 1;
			int count = 0;
			while (i <= n_appliance) {
				if (appliance[i].p == 1) {
					count++;
					max_id = i;
				}
				i++;
			}
			if (count == 0) { // tidak ada wajib
				max_kwh = -1;
				i = 1;
				count = 0;
				while (i <= n_appliance) {
					if (appliance[i].p == 0) {
						if (max_kwh < appliance[i].kwh) {
							max_kwh = appliance[i].kwh;
							max_time = appliance[i].duration;
							max_id = i;
							count = 1;
						}
						else if (max_kwh == appliance[i].kwh) {
							max_time = appliance[i].duration;
							max_id = i;
							count++;
						}
					}
					i++;
				}
				if (count > 1) { // find max time
					i = 1;
					count = 0;
					while (i <= n_appliance) {
						if (appliance[i].kwh == max_kwh) {
							temp = appliance[i].kwh;
							if (max_time < temp) {
								max_time = temp;
								count = 1;
								max_part = appliance[i].n;
								max_id = i;
							}
							else if (max_time == temp) {
								count++;
								max_id = i;
								max_part = appliance[i].n;
							}
						}
						i++;
					}
					if (count > 1) { // find max part
						i = 1;
						while (i <= n_appliance) {
							if (appliance[i].kwh == max_kwh && appliance[i].duration == max_time) {
								temp = appliance[i].n;
								if (max_part < temp) {
									max_part = temp;
									max_id = i;
								}
							}
							i++;
						}
					}
					return max_id;
				}
				else
					return max_id;
			}
			else if (count > 1) { // wajib lebih dari 1, find max kwh
				max_kwh = -1;
				i = 1;
				count = 0;
				while (i <= n_appliance) {
					if (appliance[i].p == 1) {
						if (max_kwh < appliance[i].kwh) {
							max_kwh = appliance[i].kwh;
							max_time = appliance[i].duration;
							max_id = i;
							count = 1;
						}
						else if (max_kwh == appliance[i].kwh) {
							max_time = appliance[i].duration;
							max_id = i;
							count++;
						}
					}
					i++;
				}
				if (count > 1) { // find max time
					i = 1;
					count = 0;
					while (i <= n_appliance) {
						if (appliance[i].kwh == max_kwh) {
							temp = appliance[i].kwh;
							if (max_time < temp) {
								max_time = temp;
								count = 1;
								max_part = appliance[i].n;
								max_id = i;
							}
							else if (max_time == temp) {
								count++;
								max_id = i;
								max_part = appliance[i].n;
							}
						}
						i++;
					}
					if (count > 1) { // find max part
						i = 1;
						while (i <= n_appliance) {
							if (appliance[i].kwh == max_kwh && appliance[i].duration == max_time) {
								temp = appliance[i].n;
								if (max_part < temp) {
									max_part = temp;
									max_id = i;
								}
							}
							i++;
						}
					}
					return max_id;
				}
				else
					return max_id;
			}
			else
				return max_id;
		}

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = L"Text Files (*.txt*)|*.txt*";
			this->openFileDialog1->Title = L"Select Input File";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(42, 49);
			this->button1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(99, 30);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Input";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(177, 49);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(99, 30);
			this->button2->TabIndex = 2;
			this->button2->Text = L"About";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::about_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(315, 111);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"MyForm";
			this->Text = L"Smart Grid";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 System::IO::StreamReader ^ sr = gcnew
						 System::IO::StreamReader(openFileDialog1->FileName);
					 System::IO::StreamReader ^ show_all = gcnew
						 System::IO::StreamReader(openFileDialog1->FileName);
					 array<String^> ^line;
					 msclr::interop::marshal_context context;

					 // Baca line pertama
					 line = sr->ReadLine()->Split(',');
					 array<Char>^ Period = { '.' };
					 line[3] = line[3]->TrimEnd(Period);
					 int n_time_span = System::Convert::ToInt32(line[1]);
					 int line_length = n_time_span * 4;
					 int prog_count = System::Convert::ToInt32(line[2]);
					 int max_kwh = System::Convert::ToInt32(line[3]);
					 int b_limit, u_limit;

					 // Baca harga progresif listrik
					 for (int i = 1; i <= prog_count; i++) {
						 line = sr->ReadLine()->Split(',');
						 int j = 0;
						 while (j < line_length) {
							 b_limit = System::Convert::ToInt32(line[j]);
							 j++;
							 u_limit = System::Convert::ToInt32(line[j]);
							 j++;
							 for (int k = b_limit * 2; k <= u_limit * 2; k++) {
								 if (i == prog_count) {
									 matrix[i][k].max = max_kwh;
									 if (i == 1)
										 matrix[i][k].max_ktk = max_kwh;
									 else
										 matrix[i][k].max_ktk = max_kwh - matrix[i - 1][k].max;
								 }
								 else {
									 matrix[i][k].max = System::Convert::ToInt32(line[j]);
									 if (i == 1)
										 matrix[i][k].max_ktk = matrix[i][k].max;
									 else
										 matrix[i][k].max_ktk = matrix[i][k].max - matrix[i - 1][k].max;

								 }
								 line[j + 1] = line[j + 1]->TrimEnd(Period);
								 matrix[i][k].kwh = System::Convert::ToInt32(line[j + 1]);
							 }
							 j += 2;
						 }
					 }

					 // Baca appliance
					 line[0] = sr->ReadLine();
					 int n_appliance = System::Convert::ToInt32(line[0]);
					 for (int i = 1; i <= n_appliance; i++) {
						 line = sr->ReadLine()->Split(',');
						 appliance[i].name = context.marshal_as<std::string>(line[0]);
						 appliance[i].kwh = System::Convert::ToInt32(line[1]);
						 appliance[i].duration = System::Convert::ToInt32(line[2]);
						 appliance[i].start_hour = System::Convert::ToInt32(line[3]);
						 appliance[i].end_hour = System::Convert::ToInt32(line[4]);
						 if (context.marshal_as<std::string>(line[5]) == " wajib")
							 appliance[i].p = 1;
						 else
							 appliance[i].p = 0;
						 appliance[i].n = System::Convert::ToInt32(line[6]->TrimEnd(Period));
					 }

					 // Sort appliance & insert to sorted_appliance
					 for (int i = 1; i <= n_appliance; i++) {
						 int max_id = sort_by_priority(appliance, n_appliance);
						 sorted_appliance[i].name = appliance[max_id].name;
						 sorted_appliance[i].kwh = appliance[max_id].kwh;
						 sorted_appliance[i].duration = appliance[max_id].duration;
						 sorted_appliance[i].start_hour = appliance[max_id].start_hour;
						 sorted_appliance[i].end_hour = appliance[max_id].end_hour;
						 sorted_appliance[i].p = appliance[max_id].p;
						 sorted_appliance[i].n = appliance[max_id].n;
						 appliance[max_id].p = -1;
					 }
					 int temp_hrg;
					 int idx_hrgKol;
					 int b;
					 int excess;
					 bool redzone; //Kalo ini true, berarti kalo alatnya masuk bakal lewat batas
					 redzone = false;
					 for (int i = 1; i <= n_appliance; i++) {
						 for (int x = 1; x <= sorted_appliance[i].n; x++) {
							 //Cari Slot Termurah Berdasarkan Release dan Deadline
							 temp_hrg = 2000000;
							 idx_hrgKol = 0;
							 for (int a = sorted_appliance[i].start_hour * 2; a < sorted_appliance[i].end_hour * 2; a++) {
								 b = 1;
								 while (matrix[b][a].max_ktk <= 0) {
									 b++;
								 }
								 if (matrix[b][a].kwh < temp_hrg) {
									 temp_hrg = matrix[b][a].kwh;
									 idx_hrgKol = a;
								 }
							 }
							 //Masukin Appliance ke Dalam Slot Termurah dst.
							 //Memastikan durasi appliance ketika dimasukkan tidak lebih dari time slot yang ada
							 if ((idx_hrgKol + sorted_appliance[i].duration - 1) > 47) {
								 excess = (idx_hrgKol + sorted_appliance[i].duration - 1) - 47;
								 idx_hrgKol = idx_hrgKol - excess;
							 }
							 if ((idx_hrgKol + sorted_appliance[i].duration - 1) > sorted_appliance[i].end_hour * 2 - 1) {
								 excess = (idx_hrgKol + sorted_appliance[i].duration - 1) - sorted_appliance[i].end_hour * 2 - 1;
								 idx_hrgKol = idx_hrgKol - excess;
							 }
							 if (x > 1) { // Kasus penyalaan > 1 kali
								 int rpt_excess = 0;
								 bool stack_front = false;
								 bool stack_back = false;
								 bool first = true;
								 int idx_Akh;
								 int idx_Awl;
								 for (int c = idx_hrgKol; c <= (idx_hrgKol + sorted_appliance[i].duration - 1); c++) {
									 b = 1;
									 while (matrix[b][c].max_ktk <= 0) {
										 b++;
									 }
									 if (matrix[b][c].app[i].name == sorted_appliance[i].name) {
										 rpt_excess += 1;
										 if (first) {
											 idx_Awl = c;
											 idx_Akh = idx_Awl + sorted_appliance[i].duration - 1;
											 first = false;
										 }
										 if (matrix[b][c - 1].app[i].name != sorted_appliance[i].name)
											 stack_back = true;
										 if (matrix[b][c + 1].app[i].name != sorted_appliance[i].name)
											 stack_front = true;
										 if (stack_back && stack_front) {
											 if (idx_Awl == sorted_appliance[i].start_hour * 2) {
												 stack_back = false;
											 }
											 if (idx_Akh == (sorted_appliance[i].end_hour * 2) - 1) {
												 stack_front = false;
											 }
										 }
									 }
									 if (!stack_back && !stack_front){
										 if (matrix[b - 1][c].app[i].name == sorted_appliance[i].name) {
											 rpt_excess += 1;
											 stack_back = true;
											 if (first) {
												 idx_Awl = c;
												 idx_Akh = idx_Awl + sorted_appliance[i].duration - 1;
												 first = false;
											 }
											 if (matrix[b][c - 1].app[i].name != sorted_appliance[i].name)
												 stack_back = true;
											 if (matrix[b][c + 1].app[i].name != sorted_appliance[i].name)
												 stack_front = true;
											 if (stack_back && stack_front) {
												 if (idx_Awl == sorted_appliance[i].start_hour * 2) {
													 stack_back = false;
												 }
												 if (idx_Akh == (sorted_appliance[i].end_hour * 2) - 1) {
													 stack_front = false;
												 }
											 }
										 }
									 }
								 }
								 if (stack_back) {
									 idx_hrgKol = idx_hrgKol - rpt_excess;
								 }
								 if (stack_front) {
									 idx_hrgKol = idx_hrgKol + rpt_excess;
								 }
								 if (idx_hrgKol < (sorted_appliance[i].start_hour * 2)) {
									 redzone = true;
									 rpt_excess = ((sorted_appliance[i].start_hour * 2)) - idx_hrgKol;
									 if (idx_Akh + rpt_excess <= (sorted_appliance[i].end_hour * 2) - 1) {
										 redzone = false;
										 int s = idx_hrgKol + rpt_excess;
										 int f = idx_Akh + 1;
										 for (int c = s; c <= (idx_hrgKol + sorted_appliance[i].duration - 1); c++) {
											 b = 1;
											 int free_space;
											 int isi_kwh = sorted_appliance[i].kwh;
											 while (matrix[b][c].max_ktk <= 0) {
												 b++;
											 }
											 free_space = 0;
											 for (int d = b; d <= prog_count; d++) {
												 free_space = free_space + matrix[d][c].max_ktk;
											 }
											 if (sorted_appliance[i].kwh > free_space)
												 redzone = true; //Slot yg akan dimasuki alat bakal lewat batas
										 }
										 for (int c = f; c <= idx_Akh + rpt_excess; c++) {
											 b = 1;
											 int free_space;
											 int isi_kwh = sorted_appliance[i].kwh;
											 while (matrix[b][c].max_ktk <= 0) {
												 b++;
											 }
											 free_space = 0;
											 for (int d = b; d <= prog_count; d++) {
												 free_space = free_space + matrix[d][c].max_ktk;
											 }
											 if (sorted_appliance[i].kwh > free_space)
												 redzone = true; //Slot yg akan dimasuki alat bakal lewat batas
										 }
										 while (s <= (idx_hrgKol + sorted_appliance[i].duration - 1) && !redzone){
											 b = 1;
											 int isi_kwh = sorted_appliance[i].kwh;
											 while (matrix[b][s].max_ktk <= 0) {
												 b++;
											 }
											 while (isi_kwh > 0) {
												 if (matrix[b][s].max_ktk > isi_kwh) {
													 matrix[b][s].max_ktk = matrix[b][s].max_ktk - isi_kwh;
													 isi_kwh = 0;
													 matrix[b][s].app[i].name = sorted_appliance[i].name;
													 matrix[b][s].app[i].kwh = sorted_appliance[i].kwh;
													 matrix[b][s].app[i].duration = sorted_appliance[i].duration;
													 matrix[b][s].app[i].start_hour = sorted_appliance[i].start_hour;
													 matrix[b][s].app[i].end_hour = sorted_appliance[i].end_hour;
													 matrix[b][s].app[i].p = sorted_appliance[i].p;
													 matrix[b][s].app[i].n = sorted_appliance[i].n;
												 }
												 else {
													 isi_kwh = isi_kwh - matrix[b][s].max_ktk;
													 matrix[b][s].max_ktk = 0;
													 matrix[b][s].app[i].name = sorted_appliance[i].name;
													 matrix[b][s].app[i].kwh = sorted_appliance[i].kwh;
													 matrix[b][s].app[i].duration = sorted_appliance[i].duration;
													 matrix[b][s].app[i].start_hour = sorted_appliance[i].start_hour;
													 matrix[b][s].app[i].end_hour = sorted_appliance[i].end_hour;
													 matrix[b][s].app[i].p = sorted_appliance[i].p;
													 matrix[b][s].app[i].n = sorted_appliance[i].n;
												 }
												 b++;
											 }
											 s++;
										 }
										 while (f <= idx_Akh + rpt_excess && !redzone){
											 b = 1;
											 int isi_kwh = sorted_appliance[i].kwh;
											 while (matrix[b][f].max_ktk <= 0) {
												 b++;
											 }
											 while (isi_kwh > 0) {
												 if (matrix[b][f].max_ktk > isi_kwh) {
													 matrix[b][f].max_ktk = matrix[b][f].max_ktk - isi_kwh;
													 isi_kwh = 0;
													 matrix[b][f].app[i].name = sorted_appliance[i].name;
													 matrix[b][f].app[i].kwh = sorted_appliance[i].kwh;
													 matrix[b][f].app[i].duration = sorted_appliance[i].duration;
													 matrix[b][f].app[i].start_hour = sorted_appliance[i].start_hour;
													 matrix[b][f].app[i].end_hour = sorted_appliance[i].end_hour;
													 matrix[b][f].app[i].p = sorted_appliance[i].p;
													 matrix[b][f].app[i].n = sorted_appliance[i].n;
												 }
												 else {
													 isi_kwh = isi_kwh - matrix[b][s].max_ktk;
													 matrix[b][f].max_ktk = 0;
													 matrix[b][f].app[i].name = sorted_appliance[i].name;
													 matrix[b][f].app[i].kwh = sorted_appliance[i].kwh;
													 matrix[b][f].app[i].duration = sorted_appliance[i].duration;
													 matrix[b][f].app[i].start_hour = sorted_appliance[i].start_hour;
													 matrix[b][f].app[i].end_hour = sorted_appliance[i].end_hour;
													 matrix[b][f].app[i].p = sorted_appliance[i].p;
													 matrix[b][f].app[i].n = sorted_appliance[i].n;
												 }
												 b++;
											 }
											 f++;
										 }
									 }
								 }
								 if ((idx_hrgKol + sorted_appliance[i].duration - 1) > (sorted_appliance[i].end_hour * 2) - 1) {
									 redzone = true;
									 rpt_excess = (idx_hrgKol + sorted_appliance[i].duration - 1) - ((sorted_appliance[i].end_hour * 2) - 1);
									 if (idx_Awl - rpt_excess >= (sorted_appliance[i].start_hour * 2)) {
										 redzone = false;
										 int s = idx_hrgKol;
										 int f = idx_Awl - rpt_excess;
										 for (int c = s; c <= (idx_hrgKol + sorted_appliance[i].duration - 1) - rpt_excess; c++) {
											 b = 1;
											 int free_space;
											 int isi_kwh = sorted_appliance[i].kwh;
											 while (matrix[b][c].max_ktk <= 0) {
												 b++;
											 }
											 free_space = 0;
											 for (int d = b; d <= prog_count; d++) {
												 free_space = free_space + matrix[d][c].max_ktk;
											 }
											 if (sorted_appliance[i].kwh > free_space)
												 redzone = true; //Slot yg akan dimasuki alat bakal lewat batas
										 }
										 for (int c = f; c <= idx_Awl - 1; c++) {
											 b = 1;
											 int free_space;
											 int isi_kwh = sorted_appliance[i].kwh;
											 while (matrix[b][c].max_ktk <= 0) {
												 b++;
											 }
											 free_space = 0;
											 for (int d = b; d <= prog_count; d++) {
												 free_space = free_space + matrix[d][c].max_ktk;
											 }
											 if (sorted_appliance[i].kwh > free_space)
												 redzone = true; //Slot yg akan dimasuki alat bakal lewat batas
										 }
										 while (s <= ((idx_hrgKol + sorted_appliance[i].duration - 1) - rpt_excess) && !redzone){
											 b = 1;
											 int isi_kwh = sorted_appliance[i].kwh;
											 while (matrix[b][s].max_ktk <= 0) {
												 b++;
											 }
											 while (isi_kwh > 0) {
												 if (matrix[b][s].max_ktk > isi_kwh) {
													 matrix[b][s].max_ktk = matrix[b][s].max_ktk - isi_kwh;
													 isi_kwh = 0;
													 matrix[b][s].app[i].name = sorted_appliance[i].name;
													 matrix[b][s].app[i].kwh = sorted_appliance[i].kwh;
													 matrix[b][s].app[i].duration = sorted_appliance[i].duration;
													 matrix[b][s].app[i].start_hour = sorted_appliance[i].start_hour;
													 matrix[b][s].app[i].end_hour = sorted_appliance[i].end_hour;
													 matrix[b][s].app[i].p = sorted_appliance[i].p;
													 matrix[b][s].app[i].n = sorted_appliance[i].n;
												 }
												 else {
													 isi_kwh = isi_kwh - matrix[b][s].max_ktk;
													 matrix[b][s].max_ktk = 0;
													 matrix[b][s].app[i].name = sorted_appliance[i].name;
													 matrix[b][s].app[i].kwh = sorted_appliance[i].kwh;
													 matrix[b][s].app[i].duration = sorted_appliance[i].duration;
													 matrix[b][s].app[i].start_hour = sorted_appliance[i].start_hour;
													 matrix[b][s].app[i].end_hour = sorted_appliance[i].end_hour;
													 matrix[b][s].app[i].p = sorted_appliance[i].p;
													 matrix[b][s].app[i].n = sorted_appliance[i].n;
												 }
												 b++;
											 }
											 s++;
										 }
										 while (f <= idx_Awl - 1 && !redzone){
											 b = 1;
											 int isi_kwh = sorted_appliance[i].kwh;
											 while (matrix[b][f].max_ktk <= 0) {
												 b++;
											 }
											 while (isi_kwh > 0) {
												 if (matrix[b][f].max_ktk > isi_kwh) {
													 matrix[b][f].max_ktk = matrix[b][f].max_ktk - isi_kwh;
													 isi_kwh = 0;
													 matrix[b][f].app[i].name = sorted_appliance[i].name;
													 matrix[b][f].app[i].kwh = sorted_appliance[i].kwh;
													 matrix[b][f].app[i].duration = sorted_appliance[i].duration;
													 matrix[b][f].app[i].start_hour = sorted_appliance[i].start_hour;
													 matrix[b][f].app[i].end_hour = sorted_appliance[i].end_hour;
													 matrix[b][f].app[i].p = sorted_appliance[i].p;
													 matrix[b][f].app[i].n = sorted_appliance[i].n;
												 }
												 else {
													 isi_kwh = isi_kwh - matrix[b][s].max_ktk;
													 matrix[b][f].max_ktk = 0;
													 matrix[b][f].app[i].name = sorted_appliance[i].name;
													 matrix[b][f].app[i].kwh = sorted_appliance[i].kwh;
													 matrix[b][f].app[i].duration = sorted_appliance[i].duration;
													 matrix[b][f].app[i].start_hour = sorted_appliance[i].start_hour;
													 matrix[b][f].app[i].end_hour = sorted_appliance[i].end_hour;
													 matrix[b][f].app[i].p = sorted_appliance[i].p;
													 matrix[b][f].app[i].n = sorted_appliance[i].n;
												 }
												 b++;
											 }
											 f++;
										 }
									 }
								 }
							 }
							 int s = idx_hrgKol;
							 for (int c = idx_hrgKol; c <= (idx_hrgKol + sorted_appliance[i].duration - 1); c++) {
								 b = 1;
								 int free_space;
								 int isi_kwh = sorted_appliance[i].kwh;
								 while (matrix[b][c].max_ktk <= 0) {
									 b++;
								 }
								 free_space = 0;
								 for (int d = b; d <= prog_count; d++) {
									 free_space = free_space + matrix[d][c].max_ktk;
								 }
								 if (sorted_appliance[i].kwh > free_space)
									 redzone = true; //Slot yg akan dimasuki alat bakal lewat batas
							 }
							 while ((s <= (idx_hrgKol + sorted_appliance[i].duration - 1)) && !redzone){
								 b = 1;
								 int isi_kwh = sorted_appliance[i].kwh;
								 while (matrix[b][s].max_ktk <= 0) {
									 b++;
								 }
								 while (isi_kwh > 0) {
									 if (matrix[b][s].max_ktk > isi_kwh) {
										 matrix[b][s].max_ktk = matrix[b][s].max_ktk - isi_kwh;
										 isi_kwh = 0;
										 matrix[b][s].app[i].name = sorted_appliance[i].name;
										 matrix[b][s].app[i].kwh = sorted_appliance[i].kwh;
										 matrix[b][s].app[i].duration = sorted_appliance[i].duration;
										 matrix[b][s].app[i].start_hour = sorted_appliance[i].start_hour;
										 matrix[b][s].app[i].end_hour = sorted_appliance[i].end_hour;
										 matrix[b][s].app[i].p = sorted_appliance[i].p;
										 matrix[b][s].app[i].n = sorted_appliance[i].n;
									 }
									 else {
										 isi_kwh = isi_kwh - matrix[b][s].max_ktk;
										 matrix[b][s].max_ktk = 0;
										 matrix[b][s].app[i].name = sorted_appliance[i].name;
										 matrix[b][s].app[i].kwh = sorted_appliance[i].kwh;
										 matrix[b][s].app[i].duration = sorted_appliance[i].duration;
										 matrix[b][s].app[i].start_hour = sorted_appliance[i].start_hour;
										 matrix[b][s].app[i].end_hour = sorted_appliance[i].end_hour;
										 matrix[b][s].app[i].p = sorted_appliance[i].p;
										 matrix[b][s].app[i].n = sorted_appliance[i].n;
									 }
									 b++;
								 }
								 s++;
							 }
						 }
					 }

					 // GUI
					 sf::RenderWindow window(sf::VideoMode(1200, 300), "Smart Grid Solution");

					 sf::RectangleShape green_block;
					 green_block.setFillColor(sf::Color::Green);
					 green_block.setOutlineColor(sf::Color::Black);
					 green_block.setOutlineThickness(2);
					 green_block.setSize(sf::Vector2f(13, 10));
					 green_block.setOrigin(-160, -10);

					 sf::Font font;
					 font.loadFromFile("arial.ttf");

					 sf::Text text;
					 text.setFont(font);
					 text.setCharacterSize(14);
					 text.setColor(sf::Color::Black);

					 while (window.isOpen())
					 {
						 sf::Event event;
						 while (window.pollEvent(event))
						 {
							 if (event.type == sf::Event::Closed)
								 window.close();
						 }

						 window.clear(sf::Color::White); // Draw time slot
						 text.setOrigin(-160, 0);
						 for (int i = 0; i <= 47; i++) {
							 text.setString(std::to_string(i));
							 text.setPosition(i * 21, 0);
							 window.draw(text);
						 }

						 text.setOrigin(0, -10);

						 for (int i = 1; i <= n_appliance; i++) {
							 text.setPosition(0, i * 20);
							 text.setString(sorted_appliance[i].name);
							 window.draw(text); // Draw appliance name
							 for (int j = 0; j <= 47; j++) {
								 for (int k = 1; k <= prog_count; k++) {
									 if (sorted_appliance[i].name == matrix[k][j].app[i].name) {
										 green_block.setPosition(j * 21, i * 20); // Draw green block
										 window.draw(green_block);
										 break;
									 }
								 }
							 }
						 }
						 window.display();
					 }

					 sr->Close();
				 }
	}

	private: System::Void about_Click(System::Object^  sender, System::EventArgs^  e) {
				 MessageBox::Show("Developed by:\nFreddy 13513007\nJuan 13513013\nCalvin 13513077");
	}
	};
}
