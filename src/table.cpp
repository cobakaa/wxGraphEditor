#include "../include/table.h"

guiTable::guiTable( wxWindow* parent ) : frmTable(parent) {

}

void guiTable::DeleteAllPages() {
    m_listbook1->DeleteAllPages();
}

void guiTable::OnClose(wxCloseEvent& event) {
    this->Hide();
}

bool guiTable::AddPage(const wxString &text, const wxString &labels) {
    // wxPanel* page = new wxPanel(m_listbook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
    RightPanel * rp = new RightPanel(m_listbook1);

    rp->m_text->SetLabel(wxT("Названия вершин компонент сильной связности графа"));
    rp->labels->SetLabel(labels);

    wxFont font = wxFont();
    font.MakeLarger();
    rp->m_text->SetFont(font);
    rp->labels->SetFont(font);
    
    return m_listbook1->AddPage(rp, text);
}

RightPanel::RightPanel ( wxListbook * parent )
: wxPanel ( parent, wxID_ANY, wxDefaultPosition,
wxDefaultSize, wxTAB_TRAVERSAL)
{
    m_text = new wxStaticText( this , -1, wxT ( "0" ) , wxPoint(100, 10), wxDefaultSize, wxALIGN_CENTRE);
    labels = new wxStaticText( this , -1, wxT ( "0" ) , wxPoint(100, 40), wxDefaultSize, wxALIGN_CENTRE);
}
