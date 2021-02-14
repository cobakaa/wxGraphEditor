#include "../include/customDialog.h"


CustomDialog::CustomDialog(const wxString & title)
       : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(260, 220))
{

  wxPanel *panel = new wxPanel(this, -1);

  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

  wxStaticBox *st = new wxStaticBox(panel, -1, wxT("Type"), 
      wxPoint(5, 5), wxSize(240, 150));
  wxRadioButton *rb = new wxRadioButton(panel, 2, 
      wxT("Directed graph"), wxPoint(25, 55), wxDefaultSize, wxRB_GROUP);

  wxRadioButton *rb1 = new wxRadioButton(panel, 3, 
      wxT("Undirected graph"), wxPoint(25, 85));

  wxButton *okButton = new wxButton(this, 1, wxT("Ok"), 
      wxDefaultPosition, wxSize(70, 30));


  hbox->Add(okButton, 1);

  vbox->Add(panel, 1);
  vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

  SetSizer(vbox);

  Connect(1, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CustomDialog::OnOkClicked));
  Connect(2, wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(CustomDialog::OnDir));
  Connect(3, wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(CustomDialog::OnUndir));

  Centre();
  ShowModal();

  Destroy(); 
}

GraphMode CustomDialog::GetGraphMode() {
    return gmode;
}

void CustomDialog::OnOkClicked(wxCommandEvent & event) {
    this->Close();
}

void CustomDialog::OnDir(wxCommandEvent & event) {
    gmode = directed;
}

void CustomDialog::OnUndir(wxCommandEvent & event) {
    gmode = undirected;
}