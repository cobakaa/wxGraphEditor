#ifndef __CUSTOM_DIALOG__
#define __CUSTOM_DIALOG__

#include <wx/wx.h>
#include "tools.h"

class CustomDialog : public wxDialog
{
public:
  CustomDialog(const wxString& title);

  void OnOkClicked(wxCommandEvent & event);
  void OnDir(wxCommandEvent & event);
  void OnUndir(wxCommandEvent & event);


  GraphMode GetGraphMode();

private:
    GraphMode gmode = directed;

};

#endif