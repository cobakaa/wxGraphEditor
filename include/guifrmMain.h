#ifndef __guifrmMain__
#define __guifrmMain__

/**
@file
Subclass of frmMain, which is generated by wxFormBuilder.
*/

#include "gui.h"
#include "tools.h"
#include <vector>
#include "node.h"
#include "graph.h"

//// end generated include

/** Implementing frmMain */
class guifrmMain : public frmMain
{
	public:
		/** Constructor */
		guifrmMain( wxWindow* parent );
	//// end generated class members

	    void OnLMouseUP(wxMouseEvent &event) override;
		void AddMode( wxCommandEvent& event ) override;
		void DeleteMode( wxCommandEvent& event ) override;
		void OnLMouseDOWN( wxMouseEvent& event ) override;
		void ReposMode( wxCommandEvent& event ) override;
		void OnMouseMove( wxMouseEvent& event ) override;
		void NewFile( wxCommandEvent& event ) override;
		void RenderSize( wxSizeEvent& event ) override;
		void RenderMove( wxMoveEvent& event ) override;
		void RenderPaint( wxPaintEvent& event ) override;
		void OnEraseBackground(wxEraseEvent & event) {};
		void NodeZoom( wxMouseEvent& event ) override;
		void ConnectMode( wxCommandEvent& event ) override;
		void OnOpen( wxCommandEvent& event) override;
		void OnSaveAs(wxCommandEvent& event) override;

		void OnCloseMenu(wxCommandEvent& event) override;
		void OnClose(wxCloseEvent& event) override;

		void AddCircle(wxPoint pt, wxCoord r);
		void DeleteCircle(wxPoint p);

		void DrawPtrs(wxDC& dc, int first, int second);

		void Configure();

		Graph MGFToGraph(const wxString& str);

		void Unsaved();


	private:

		Mode mode;
		Graph graph;
		int grabbed_ind;
		// int grabbed_ind_con;
		wxPoint line_end;
		bool saved;

};


#endif // __guifrmMain__
