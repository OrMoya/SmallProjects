#include "cMain.h"
#include <windows.h>

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(22222, OnStepClicked)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Game of Life")
{
	
	btn = new wxButton * [nFieldWidth * nFieldHeight];
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);
	wxPanel* leftPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
	leftPanel->SetBackgroundColour(wxColor(100, 100, 100));
	play = new wxButton(leftPanel, 22222, "Step", wxPoint(10,10), wxSize(150, 50));

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(leftPanel, 1, wxEXPAND | wxALL);

	cells = new int[nFieldWidth * nFieldHeight];
	cellsNewGen = new int[nFieldWidth * nFieldHeight];

	for (int i = 0; i < nFieldWidth; i++) {
		for (int j = 0; j < nFieldHeight; j++) {
			btn[j * nFieldWidth + i] = new wxButton(this, 10000 + (j * nFieldWidth + i));
			grid->Add(btn[j * nFieldWidth + i], 1, wxEXPAND | wxALL); //fill grid by columns

			btn[j * nFieldWidth + i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			cells[j * nFieldWidth + i] = 0;																	//fill Array by columns
			cellsNewGen[j * nFieldWidth + i] = 0;															//fill Array by columns
			btn[j * nFieldWidth + i]->SetBackgroundColour(wxColor(225, 225, 225));
			btn[j * nFieldWidth + i]->SetForegroundColour(wxColor(225, 225, 225));
		}
	}
	sizer->Add(grid, 5, wxEXPAND | wxALL);
	this->SetSizerAndFit(sizer);
	grid->Layout();
}


cMain::~cMain() {

}

void cMain::OnButtonClicked(wxCommandEvent& evt) {

	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;

	if (cells[y * nFieldWidth + x] == 0) {
		btn[y * nFieldWidth + x]->SetBackgroundColour(*wxYELLOW);
		btn[y * nFieldWidth + x]->SetForegroundColour(*wxYELLOW);
		cells[y * nFieldWidth + x] = 1;
	}
	else {
		btn[y * nFieldWidth + x]->SetBackgroundColour(wxColor(225,225,225));
		btn[y * nFieldWidth + x]->SetForegroundColour(wxColor(225, 225, 225));
		cells[y * nFieldWidth + x] = 0;
	}

}

void cMain::OnStepClicked(wxCommandEvent& evt)
{
	int neighbors = 0;
	for (int i = 0; i < nFieldHeight; i++) {
		for (int j = 0; j < nFieldHeight; j++) {
			for (int k = -1; k < 2; k++) {
				for (int l = -1; l < 2; l++) {
					if (i + k >= 0 && i + k < nFieldWidth && j + l >= 0 && j + l < nFieldHeight)
					{
						if (k == 0 && l == 0)
							neighbors = neighbors;
						else if (cells[(j + l) * nFieldHeight + (i + k)] == 1)
							neighbors++;
					}
				}
			}
			if (cells[j * nFieldHeight + i] == 1 && (neighbors == 3 || neighbors == 2)) 
				cellsNewGen[j * nFieldHeight + i] = 1;
			else if (cells[j * nFieldHeight + i] == 0 && neighbors == 3)
				cellsNewGen[j * nFieldHeight + i] = 1;
			else 
				cellsNewGen[j * nFieldHeight + i] = 0;
			neighbors = 0;
		}
	}

	for (int i = 0; i < nFieldHeight * nFieldWidth; i++) {
		cells[i] = cellsNewGen[i];
		cellsNewGen[i] = 0;

	}

	for (int i = 0; i < nFieldHeight; i++) {
		for (int j = 0; j < nFieldHeight; j++) {
			if (cells[j * nFieldWidth + i] == 1) {
				btn[j * nFieldWidth + i]->SetBackgroundColour(*wxYELLOW);
				btn[j * nFieldWidth + i]->SetForegroundColour(*wxYELLOW);
			}
			else {
				btn[j * nFieldWidth + i]->SetBackgroundColour(wxColor(225, 225, 225));
				btn[j * nFieldWidth + i]->SetForegroundColour(wxColor(225, 225, 225));
			}
		}
	}
}