///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/toolbar.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/scrolwin.h>
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/listbook.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class frmMain
///////////////////////////////////////////////////////////////////////////////
class frmTable : public wxFrame
{
	private:

	protected:
		

		// Virtual event handlers, overide them in your derived class
		wxListbook* m_listbook1;
        
        virtual void OnClose(wxCloseEvent& event) { event.Skip(); };


	public:

		frmTable( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Table"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800, 600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~frmTable();

};

