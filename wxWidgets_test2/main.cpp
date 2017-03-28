#include <wx/wx.h>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "rpcrt4.lib")

#pragma comment(lib, "wxmsw30ud_gl.lib")
#pragma comment(lib, "wxzlibd.lib")
#pragma comment(lib, "wxpngd.lib")
#pragma comment(lib, "wxbase30ud.lib")
#pragma comment(lib, "wxmsw30ud_core.lib")
#pragma comment(lib, "wxzlibd.lib")
#pragma comment(lib, "wxpngd.lib")

#include "Frame.h"

class MyApp : public wxApp {
public:
	virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
	wxImage::AddHandler(new wxPNGHandler);

	Frame *frame = new Frame(wxT("SimBuLaX"));
	frame->Show(true);

	return true;
}
