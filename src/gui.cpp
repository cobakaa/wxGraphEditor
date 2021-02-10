///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

frmMain::frmMain( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	m_toolBar1 = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL );
	m_tool1 = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("../../img/add.bmp"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_tool2 = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("../../img/delete.bmp"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_tool3 = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("../../img/repos.bmp"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_toolBar1->Realize();

	bSizer2->Add( m_toolBar1, 0, wxEXPAND, 5 );

	m_panel6 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer2->Add( m_panel6, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer2 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( m_tool1->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( frmMain::AddMode ) );
	this->Connect( m_tool2->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( frmMain::DeleteMode ) );
	this->Connect( m_tool3->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( frmMain::ReposMode ) );
	m_panel6->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( frmMain::GpabCircle ), NULL, this );
	m_panel6->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( frmMain::DrawCircle ), NULL, this );
	m_panel6->Connect( wxEVT_MOTION, wxMouseEventHandler( frmMain::MotionCircle ), NULL, this );
}

frmMain::~frmMain()
{
	// Disconnect Events
	this->Disconnect( m_tool1->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( frmMain::AddMode ) );
	this->Disconnect( m_tool2->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( frmMain::DeleteMode ) );
	this->Disconnect( m_tool3->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( frmMain::ReposMode ) );
	m_panel6->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( frmMain::GpabCircle ), NULL, this );
	m_panel6->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( frmMain::DrawCircle ), NULL, this );
	m_panel6->Disconnect( wxEVT_MOTION, wxMouseEventHandler( frmMain::MotionCircle ), NULL, this );

}
