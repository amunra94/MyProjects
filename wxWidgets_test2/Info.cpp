#include "Info.h"
#include <string>
#include <sstream>
#include <cstring>


Info::Info(wxWindow *parent,std::vector <wxString> vecName, std::vector <wxString> vecPos, std::vector <wxString> vecNeg)
	: wxDialog(parent, wxID_ANY, wxT("Info"), wxDefaultPosition, wxSize(300, 250), 232) {

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	wxButton   *okButton = new wxButton(this, wxID_OK, wxT("OK"));
	
	size = GetSize();

	hbox->Add(okButton, 1, wxCENTRE);
	vbox->Add(hbox, 0, wxLEFT | wxTOP |wxALIGN_LEFT, 179);
	SetSizer(vbox);

	std::string str;
	std::ostringstream oss;
	oss << vecName.size();
	str =  oss.str();
	
	new wxStaticText(this, wxID_ANY, "Число графиков  =  " + str, wxPoint(size.x/80, size.y/40));
	new wxStaticText(this, wxID_ANY, "Фронты      Срезы ", wxPoint(size.x/5,size.y/10));
	for (int i = 0; i < vecName.size(); i++) {
		
		new wxStaticText(this, wxID_ANY, vecName[i], wxPoint(30,40+20*i));
		new wxStaticText(this, wxID_ANY, vecPos[i], wxPoint(size.x/4, 40 + 20 * i));
		new wxStaticText(this, wxID_ANY, vecNeg[i], wxPoint(size.x/2, 40 + 20 * i));
	}
	Centre();
}
