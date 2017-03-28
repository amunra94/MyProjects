#pragma once

#include <wx/wx.h>

class Dialog : public wxDialog {
public:
	Dialog(wxWindow *parent);

	void Draw(wxPaintEvent &event);
};
