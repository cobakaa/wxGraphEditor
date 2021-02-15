#include "../include/customDialog.h"


CustomDialog::CustomDialog(const wxString & title)
       : wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(260, 220))
{

  wxPanel *panel = new wxPanel(this, -1);

  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

  wxStaticBox *st = new wxStaticBox(panel, -1, wxT("Type"), 
      wxPoint(5, 5), wxSize(240, 150));
  rb = new wxRadioButton(panel, -1, 
      wxT("Directed graph"), wxPoint(25, 55), wxDefaultSize, wxRB_GROUP);

 rb1 = new wxRadioButton(panel, -1, 
      wxT("Undirected graph"), wxPoint(25, 85));

  okButton = new wxButton(this, -1, wxT("Ok"), 
      wxDefaultPosition, wxSize(70, 30));


  hbox->Add(okButton, 1);

  vbox->Add(panel, 1);
  vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

  SetSizer(vbox);

  this->Connect(okButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CustomDialog::OnOkClicked));
  this->Connect(rb->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(CustomDialog::OnDir));
  this->Connect(rb1->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(CustomDialog::OnUndir));

  Centre();
  ShowModal();

   Destroy(); 
}

CustomDialog::~CustomDialog() {
    this->Disconnect(okButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CustomDialog::OnOkClicked));
    this->Disconnect(rb->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(CustomDialog::OnDir));
    this->Disconnect(rb1->GetId(), wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(CustomDialog::OnUndir));
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