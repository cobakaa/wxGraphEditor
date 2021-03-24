#include "../include/table.h"

guiTable::guiTable( wxWindow* parent ) : frmTable(parent) {

}

void guiTable::DeleteAllPages() {
    m_listbook1->DeleteAllPages();
}

void guiTable::OnClose(wxCloseEvent& event) {
    this->Hide();
}

bool guiTable::AddPage(const wxString &text) {
    wxNotebookPage* page = new wxNotebookPage(m_listbook1, wxID_ANY);
    return m_listbook1->AddPage(page, text);
}