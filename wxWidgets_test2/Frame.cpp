#include "Frame.h"
#include "Dialog.h"
#include "Info.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <sstream>

#define wxID_DRAW_SHOW 101
#define wxID_DRAW_HIDE 102
#define wxID_DRAW_INFO 103

Frame::Frame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(960, 720)) {

	// === MENU ===
	p_menubar = new wxMenuBar;
	// Menu "File"
	p_menuFile = new wxMenu;
	p_menubar->Append(p_menuFile, wxT("&File"));
	p_menuFile->Append(wxID_OPEN, wxT("&Open\tCtrl+O"));
	p_menuFile->Append(wxID_EXIT, wxT("&Exit\tAlt+X"));

	// Menu "Traces"
	p_menuDraw = new wxMenu;
	p_menubar->Append(p_menuDraw, wxT("&Traces"));
	p_menuDraw->Append(wxID_DRAW_SHOW, wxT("&Show data"));
	p_menuDraw->Append(wxID_DRAW_HIDE, wxT("&Hide data"));
	p_menuDraw->Append(wxID_DRAW_INFO, wxT("&Info"));

	//menu "Help"
	p_menuHelp = new wxMenu;
	p_menubar->Append(p_menuHelp, wxT("&Help"));
	p_menuHelp->Append(wxID_HELP, wxT("About"));

	SetMenuBar(p_menubar);

	Connect(wxEVT_PAINT, wxPaintEventHandler(Frame::OnPaint));
	
	Connect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED,      wxCommandEventHandler (Frame::OnOpen));
	Connect(wxID_HELP, wxEVT_COMMAND_MENU_SELECTED,      wxCommandEventHandler (Frame::OnMenu_AboutHelp));
	Connect(wxID_DRAW_INFO, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler (Frame::OnInfo));
	Connect(wxID_DRAW_SHOW, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler (Frame::OnShow));
	Connect(wxID_DRAW_HIDE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler (Frame::OnHide));
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler (Frame::OnMenu_FileExit));

	if (!flag)
	{
		CreateStatusBar(3);
		SetStatusText(wxT("Ready!"), 0);
	}	
	SetBackgroundColour(RGB(0, 0, 0));
	Centre();
}
void Frame::OnOpen(wxCommandEvent &evt)
{
	char c;
	if (flag) { 
		flag = 0; 
		SetBackgroundColour(RGB(0, 0, 0));
		vecCoor.clear();
		vecNeg.clear();
		vecPos.clear();
		vecWireName.clear();
	}
	wxFileDialog * openFileDialog = new wxFileDialog(this);
	if (openFileDialog->ShowModal() == wxID_OK) {
		wxString fileName = openFileDialog->GetPath();
		std::ifstream in_file;
		std::noskipws(in_file);

		std::stringstream path;
		path << fileName.c_str();
		std::string path_str = path.str();

		in_file.open(path_str);
		std::string str;
		std::string word;
		std::vector <wxString> array;
		array.clear();
		
		while (!in_file.eof()) {

			in_file.get(c);
			vecCoor.push_back(c);
	
		}
	}
	if (!flag) {
		SetStatusText(wxT("Download!"), 0);
	}
	flag = 1;
	
	Refresh();
}
void Frame::OnMenu_FileExit(wxCommandEvent &evt) { Close(); }

void Frame::OnShow(wxCommandEvent &evt) {
	if (flag) {
		signal = true;
		Refresh();
		SetStatusText(wxT("Logic level ON"), 0);
	}
	else {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("Error! Please, download file!"), wxT("Error"), wxOK | wxICON_ERROR);
		dial->ShowModal();
	}
}
void Frame::OnHide(wxCommandEvent &evt) {
	if (flag) {
		signal = false;
		Refresh();
		SetStatusText(wxT("Logic level OFF"), 0);
	}
	else{
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("Error! Please, download file!"), wxT("Error"), wxOK | wxICON_ERROR);
		dial->ShowModal();
	}
}
void Frame::OnInfo(wxCommandEvent &evt) {
	if (flag) {
		Info inf(NULL, vecWireName, vecPos, vecNeg);
		inf.ShowModal();
	}
	else {
		wxMessageDialog *dial = new wxMessageDialog(NULL,
			wxT("Error! Please, download file!"), wxT("Error"), wxOK | wxICON_ERROR);
		dial->ShowModal();
	}
	
}

void Frame::OnMenu_AboutHelp(wxCommandEvent &evt) {
	Dialog dlg(this);
	dlg.ShowModal();
}

void Frame::Paint(int level, int wire) {
	int switchs = vecCoor.size() / vecWireName.size();
	int drift_x = (size.x-size.x/5)/(switchs);
	int drift_y = (size.y)/(36 + vecWireName.size());
	int pos     = 0;
	int neg     = 0;

	wxPaintDC dc(this);
	dc.SetPen(*wxGREEN);
	wxFont fontName(size.x/80, wxFONTFAMILY_SWISS, wxNORMAL, wxBOLD);
	dc.SetFont(fontName);
	wxCoord x1 = size.x/20,           y1 = level;
	wxCoord x2 = size.x/20 + drift_x, y2 = level;
	dc.SetTextForeground(*wxYELLOW);
	dc.DrawText(vecWireName[wire], wxPoint(size.x / 40, level-30));
	wxFont fontSign((size.x + size.y)/180, wxFONTFAMILY_SWISS, wxNORMAL, wxBOLD);
	dc.SetTextForeground(*wxRED);
	dc.SetFont(fontSign);
	
	for (int i = wire; i < vecCoor.size(); i = i + vecWireName.size()) {
		if (i == vecCoor.size()-1) break;

		if (vecCoor[i] == '1' && y2 == level) {
			x1 = x2;
			y1 = y2;
			x2 = x2;
			y2 = y2 - drift_y;
			dc.DrawLine(x1, y1, x2, y2);
			x1 = x2;
			y1 = y2;
			x2 = x2 + drift_x;
			y2 = y2;
			dc.DrawLine(x1, y1, x2, y2);
			if (signal == true) {
				dc.DrawText("1", wxPoint(x2 - drift_x / 2 - 3, level - drift_y ));
			}
			pos++;
		}
		else if (vecCoor[i] == '1' && y2 == level - drift_y) {
				x1 = x2;
				y1 = y2;
				x2 = x2 + drift_x;
				y2 = y2;
				dc.DrawLine(x1, y1, x2, y2);
				if (signal == true) {
					dc.DrawText("1", wxPoint(x2 - drift_x / 2 - 3, level - drift_y ));
				}
			}
		if (vecCoor[i] == '0' && y2 == level - drift_y) {
			x1 = x2;
			y1 = y2;
			x2 = x2;
			y2 = y2 + drift_y;
			dc.DrawLine(x1, y1, x2, y2);
			x1 = x2;
			y1 = y2;
			x2 = x2 + drift_x;
			y2 = y2;
			dc.DrawLine(x1, y1, x2, y2);
			if (signal == true) {
				dc.DrawText("0", wxPoint(x2 - drift_x / 2 - 3, level - drift_y));
			}
			neg++;
		}
		else if (vecCoor[i] == '0' && y2 == level) {
				x1 = x2;
				y1 = y2;
				x2 = x2 + drift_x;
				y2 = y2;
				dc.DrawLine(x1, y1, x2, y2);
				if (signal == true) {
					dc.DrawText("0", wxPoint(x2 - drift_x / 2 - 3, level - drift_y));
				}
			}
	}
	std::ostringstream pss;
	pss << pos;
	vecPos.push_back(pss.str());
	std::ostringstream nss;
	nss << neg;
	vecNeg.push_back(nss.str());
}
void Frame::OnPaint(wxPaintEvent &event)
{
	size = GetSize();
	Refresh();
	
	if (flag) {
		int level = size.y / (1.5 * vecWireName.size());
		for (int i = 0; i < vecWireName.size(); i++) {
			Paint(level, i);
			level = level + size.y/vecWireName.size() - 10;
		}	
	}
	else {
		wxPaintDC dcb(this);
		
		wxFont fontName((size.x+size.y)/30, wxFONTFAMILY_SCRIPT, wxNORMAL, wxBOLD);
		dcb.SetFont(fontName);
		dcb.SetTextForeground(*wxYELLOW);
		dcb.DrawText(wxT("SimBuLaX"), wxPoint(size.x/3,size.y/3));
	
	}
}
