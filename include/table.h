#ifndef __TABLE_H__
#define __TABLE_H__


#include "gui.h"
#include "tools.h"
#include <vector>
#include "node.h"
#include "graph.h"
#include "guiTable.h"

class guiTable : public frmTable
{
	public:
		guiTable( wxWindow* parent );

		void OnClose(wxCloseEvent& event) override;
		bool AddPage(const wxString &text);
		void DeleteAllPages();

	private:

		// frmTable* table;

};


#endif // __TABLE_H__
