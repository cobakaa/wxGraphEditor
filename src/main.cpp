// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


class wxMyApp : public wxApp

{

public:

    bool OnInit() override;

};


wxIMPLEMENT_APP(wxMyApp);


#include "../include/gui.h"
#include "../include/guifrmMain.h"

///////////////////////////////////////////////////////////////////////////



bool wxMyApp::OnInit()

{

    guifrmMain *frame;
    frame = new guifrmMain(NULL);

    frame->Show(true);

    return true;

}
