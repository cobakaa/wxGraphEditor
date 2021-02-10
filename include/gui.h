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
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class frmMain
///////////////////////////////////////////////////////////////////////////////
class frmMain : public wxFrame
{
	private:

	protected:
		wxToolBar* m_toolBar1;
		wxToolBarToolBase* m_tool1;
		wxToolBarToolBase* m_tool2;
		wxPanel* m_panel6;

		// Virtual event handlers, overide them in your derived class
		virtual void AddMode( wxCommandEvent& event ) { event.Skip(); }
		virtual void DeleteMode( wxCommandEvent& event ) { event.Skip(); }
		virtual void DrawCircle( wxMouseEvent& event ) { event.Skip(); }


	public:

		frmMain( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Graphs"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 789,533 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~frmMain();

};

