#include "Dialog.h"


Dialog::Dialog(wxWindow *parent) 
: wxDialog(parent, wxID_ANY, wxT("About"), wxDefaultPosition, wxSize(300, 200),232) {

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

	wxButton *okButton = new wxButton(this, wxID_OK, wxT("OK"));

	hbox->Add(okButton, 1, wxCENTRE);
	vbox->Add(hbox, 25, wxLEFT | wxTOP, 100);

	SetSizer(vbox);

	Connect(wxEVT_PAINT, wxPaintEventHandler(Dialog::Draw));
	
	wxBitmap bmp_wind(wxT("miet.png"), wxBITMAP_TYPE_PNG);
	wxStaticBitmap *p_bmp = new wxStaticBitmap(this, wxID_ANY, bmp_wind, wxPoint(20, 20));

	Centre();
	SetBackgroundColour(*wxWHITE);

}

void Dialog::Draw(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	wxFont fontName(15, wxFONTFAMILY_SWISS, wxNORMAL, wxBOLD);
	dc.SetFont(fontName);
	dc.DrawText(wxT("SimBuLaX"), wxPoint(100, 20));
	wxFont fontSign(8, wxFONTFAMILY_SWISS, wxNORMAL, wxBOLD);
	dc.SetFont(fontSign);
	dc.DrawText(wxT("Copyright © 2016\n     Version 2.0"), wxPoint(100, 50));
	Centre();
}
