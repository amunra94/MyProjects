#pragma once

#include  <wx/wx.h>
#include  <fstream>
#include  <sstream>
#include  <istream>
#include  <vector>

class Frame : public wxFrame {

public:
	int flag = 0;
	bool signal = false;
	int w, h;
	
	Frame (const wxString& title);
	
	std::vector<wxString> vecCoor;
	std::vector<wxString> vecWireName;
	std::vector<wxString> vecPos;
	std::vector<wxString> vecNeg;
	
	wxSize size;
	
	void OnPaint (wxPaintEvent &event);
	void OnInfo  (wxCommandEvent &evt);
	void OnShow  (wxCommandEvent &evt);
	void OnHide  (wxCommandEvent &evt);
	void Paint   (int level, int wire);
	void OnOpen  (wxCommandEvent  &evt);
	void OnMenu_AboutHelp(wxCommandEvent  &evt);
	void OnMenu_FileExit(wxCommandEvent &evt);

	
private:
	wxMenuBar  *p_menubar;
	wxMenu     *p_menuFile;
	wxMenu     *p_menuDraw;
	wxMenu     *p_menuHelp;

};
