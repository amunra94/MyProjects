#pragma once

#include <wx/wx.h>

class Window : public wxWindow {
public:
	int abc;
	Window(wxWindow *p_parent);
private:
	void OnPaint(wxPaintEvent &evt);
};

