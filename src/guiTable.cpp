#include "../include/guiTable.h"

frmTable::frmTable( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	m_listbook1 = new wxListbook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLB_DEFAULT );

	#ifdef __WXGTK__ // Small icon style not supported in GTK
	wxListView* m_listbook1ListView = m_listbook1->GetListView();
	long m_listbook1Flags = m_listbook1ListView->GetWindowStyleFlag();
	if( m_listbook1Flags & wxLC_SMALL_ICON )
	{
		m_listbook1Flags = ( m_listbook1Flags & ~wxLC_SMALL_ICON ) | wxLC_ICON;
	}
	m_listbook1ListView->SetWindowStyleFlag( m_listbook1Flags );
	#endif

	bSizer1->Add( m_listbook1, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

    this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(frmTable::OnClose));


}

frmTable::~frmTable()
{
	// Disconnect Events
    this->Disconnect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(frmTable::OnClose));
	
}