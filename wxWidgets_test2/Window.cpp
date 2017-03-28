#include "Window.h"

Window::Window(wxWindow *p_parent) : wxWindow(p_parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE) {
	Connect(wxEVT_PAINT, wxPaintEventHandler(Window::OnPaint));
	abc = 0;
}

void Window::OnPaint(wxPaintEvent &evt) {
	wxPaintDC dc(this);


	if (abc == 1) {
		//wxStaticText *p_text = new wxStaticText(this, wxID_ANY, wxT("Develop by\nGavrliov N.\n\n© MIET 2016\nAll right reserved."), wxPoint(30, 30));
		wxMessageBox(wxT("1"));
	}
	else if (abc == 2) {
		wxMessageBox(wxT("2"));
	}

	wxRect r = GetClientRect();
	r.Deflate(10);
	dc.DrawRectangle(r);
}

