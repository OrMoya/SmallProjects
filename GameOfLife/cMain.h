#pragma once
#include "wx/wx.h"


class cMain : public wxFrame
{
public: 
	cMain();
	~cMain();

public: 
	int nFieldWidth = 20;
	int nFieldHeight = 20;
	wxButton** btn;
	wxButton *play;
	int* cells = nullptr;
	int* cellsNewGen = nullptr;
	int* temp = nullptr;

	void OnButtonClicked(wxCommandEvent& evt);
	void OnStepClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

