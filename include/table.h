#ifndef __TABLE_H__
#define __TABLE_H__


#include "gui.h"
#include "tools.h"
#include <vector>
#include "node.h"
#include "graph.h"
#include "guiTable.h"
#include <wx/stattext.h>

class guiTable : public frmTable
{
	public:
		guiTable( wxWindow* parent );

		void OnClose(wxCloseEvent& event) override;
		bool AddPage(const wxString &text, const wxString &labels);
		void DeleteAllPages();

	private:

		// frmTable* table;

};

class RightPanel : public wxPanel
{
public:
	RightPanel ( wxListbook * parent ) ;
	void OnSetText ( wxCommandEvent& event ) ;
	wxStaticText * m_text;
	wxStaticText * labels;

} ;



#endif // __TABLE_H__
