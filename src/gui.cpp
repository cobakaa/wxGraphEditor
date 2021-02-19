///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "../include/gui.h"

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

	m_tool4 = m_toolBar1->AddTool( wxID_ANY, wxT("tool"), wxBitmap( wxT("../../img/connect.bmp"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_toolBar1->Realize();

	bSizer2->Add( m_toolBar1, 0, wxEXPAND, 5 );

	m_panel6 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxTAB_TRAVERSAL|wxVSCROLL );
	
	m_panel6->SetScrollbars(10, 10, 6, 8);
	m_panel6->SetVirtualSize(wxSize(4000,4000));
	m_panel6->SetScrollRate( 5, 5 );
	
	m_panel6->EnableScrolling(true, true);
	m_panel6->SetDoubleBuffered(true);
	// m_panel6->SetScrollRate( 5, 5 );
	bSizer2->Add( m_panel6, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer2 );
	this->Layout();
	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("New File") ) + wxT('\t') + wxT("Ctrl+N"), wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem1 );
	wxMenuItem* m_menuItem3;
	m_menuItem3 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Open File...") ), wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem3 );
	wxMenuItem* m_menuItem4;
	m_menuItem4 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Save As...") ), wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem4 );
	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Exit") ), wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem2 );

	m_menubar1->Append( m_menu1, wxT("File") );

	this->SetMenuBar( m_menubar1 );


	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_MOVE, wxMoveEventHandler( frmMain::RenderMove ) );
	this->Connect( m_tool1->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( frmMain::AddMode ) );
	this->Connect( m_tool2->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( frmMain::DeleteMode ) );
	this->Connect( m_tool3->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( frmMain::ReposMode ) );
	this->Connect( m_tool4->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( frmMain::ConnectMode ) );
	m_panel6->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( frmMain::OnLMouseDOWN ), NULL, this );
	m_panel6->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( frmMain::OnLMouseUP ), NULL, this );
	m_panel6->Connect( wxEVT_MOTION, wxMouseEventHandler( frmMain::OnMouseMove ), NULL, this );
	m_panel6->Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( frmMain::NodeZoom ), NULL, this );
	m_panel6->Connect( wxEVT_PAINT, wxPaintEventHandler( frmMain::RenderPaint ), NULL, this );
	m_panel6->Connect( wxEVT_SIZE, wxSizeEventHandler( frmMain::RenderSize ), NULL, this );
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( frmMain::NewFile ), this, m_menuItem1->GetId());
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( frmMain::OnClose ), this, m_menuItem2->GetId()); // add quit bind
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( frmMain::OnOpen ), this, m_menuItem3->GetId()); 
	m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( frmMain::OnSaveAs ), this, m_menuItem4->GetId()); 
}

frmMain::~frmMain()
{
	// Disconnect Events
	this->Disconnect( wxEVT_MOVE, wxMoveEventHandler( frmMain::RenderMove ) );
	this->Disconnect( m_tool1->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( frmMain::AddMode ) );
	this->Disconnect( m_tool2->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( frmMain::DeleteMode ) );
	this->Disconnect( m_tool3->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( frmMain::ReposMode ) );
	this->Disconnect( m_tool4->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( frmMain::ConnectMode ) );
	m_panel6->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( frmMain::OnLMouseDOWN ), NULL, this );
	m_panel6->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( frmMain::OnLMouseUP ), NULL, this );
	m_panel6->Disconnect( wxEVT_MOTION, wxMouseEventHandler( frmMain::OnMouseMove ), NULL, this );
	m_panel6->Disconnect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( frmMain::NodeZoom ), NULL, this );
	m_panel6->Disconnect( wxEVT_PAINT, wxPaintEventHandler( frmMain::RenderPaint ), NULL, this );
	m_panel6->Disconnect( wxEVT_SIZE, wxSizeEventHandler( frmMain::RenderSize ), NULL, this );

}

