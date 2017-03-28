#pragma once
#pragma once

#include <wx/wx.h>
#include <vector>

class Info : public wxDialog {
public:
	Info(wxWindow *parent,std::vector <wxString> vecName, std::vector <wxString> vecPos, std::vector <wxString> vecNeg);
	
	std::vector <wxString> vec;
	
	wxSize size;
};
