#include "../include/guifrmMain.h"
#include <wx/dc.h>
#include <wx/wx.h>
#include "../include/tools.h"
#include "../include/node.h"
#include "../include/customDialog.h"

#include <wx/dcbuffer.h>

wxCoord defaultRad = 15;

guifrmMain::guifrmMain( wxWindow* parent )
:
frmMain( parent )
{
    mode = none;
    graph = Graph();
    grabbed_ind = -1;
    gm = gnone;
}


void guifrmMain::OnLMouseUP(wxMouseEvent &event) {

    const wxPoint pt = wxGetMousePosition();
    wxCoord x = pt.x - m_panel6->GetScreenPosition().x;
    wxCoord y = pt.y - m_panel6->GetScreenPosition().y;

    m_panel6->CalcUnscrolledPosition(x, y, &x, &y);

    switch (mode) {
        case add: 
        {
            AddCircle(wxPoint(x, y), defaultRad);
            
            // RenderPaint();
            m_panel6->Refresh();
            m_panel6->Update();
            break;
       }

       case mdelete:
       {
            DeleteCircle(wxPoint(x, y));

            // m_panel6->Refresh();
            // Render();
            m_panel6->Refresh();
            m_panel6->Update();
            break;
       }

       case repos:
       {
            if (grabbed_ind != -1) {
                graph.GetNodes()[grabbed_ind].GetGrabbed() = false;
                grabbed_ind = -1;
            }
            break;
       }

       case none:
       {
           Configure();
           mode = add;
       }

    }

}

void guifrmMain::AddMode( wxCommandEvent& event ) {
    if (mode == add) {
        mode = none;
    } else {
        mode = add;
    }
}

void guifrmMain::DeleteMode( wxCommandEvent& event ) {
    if (mode == mdelete) {
        mode = none;
    } else {
        mode = mdelete;
    }
}


void guifrmMain::RenderPaint( wxPaintEvent& event ) {

    wxPaintDC dc(m_panel6);

    wxCoord x, y;

    for (auto& i : graph.GetNodes()) {
        if (i.GetPainted()) {
            m_panel6->CalcScrolledPosition(i.GetPoint().x, i.GetPoint().y, &x, &y);
            dc.DrawCircle(x, y, i.GetRad());
        }
    }
   
}

void guifrmMain::AddCircle(wxPoint pt, wxCoord r) {

    if (!graph.HaveIntersection(pt, r)) {
        graph.AddNode(Node(pt, r));
    }
}


void guifrmMain::DeleteCircle(wxPoint pt) {
    graph.DeleteNode(pt);
}

void guifrmMain::ReposMode( wxCommandEvent& event ) {
    if (mode == repos) {
        mode = none;
    } else {
        mode = repos;
    }
}

void guifrmMain::OnLMouseDOWN( wxMouseEvent& event ) { 

    const wxPoint pt = wxGetMousePosition();
    wxCoord x = pt.x - m_panel6->GetScreenPosition().x;
    wxCoord y = pt.y - m_panel6->GetScreenPosition().y;

    m_panel6->CalcUnscrolledPosition(x, y, &x, &y);

    if (mode == repos && !graph.GetNodes().empty()) {
        
            grabbed_ind = graph.GetIntersectionInd(wxPoint(x, y));
            graph.GetNodes()[grabbed_ind].GetGrabbed() = true;
    }


}

void guifrmMain::OnMouseMove( wxMouseEvent& event ) {
    
    if (mode == repos) {
        const wxPoint pt = wxGetMousePosition();
        wxCoord x = pt.x - m_panel6->GetScreenPosition().x;
        wxCoord y = pt.y - m_panel6->GetScreenPosition().y;

        m_panel6->CalcUnscrolledPosition(x, y, &x, &y);

        if (grabbed_ind != -1) {

            if (!graph.HaveIntersection(wxPoint(x, y), defaultRad)) {
                graph.GetNodes()[grabbed_ind].GetPoint().x = x;
                graph.GetNodes()[grabbed_ind].GetPoint().y = y;
            }

            m_panel6->Refresh();
            m_panel6->Update();
        }
    }
}

void guifrmMain::NewFile( wxCommandEvent& event ) {
    graph.GetNodes().clear();
    m_panel6->ClearBackground();
    Configure();
    
}

void guifrmMain::RenderSize( wxSizeEvent& event ) {

    m_panel6->Refresh();
    m_panel6->Update();
}

void guifrmMain::RenderMove( wxMoveEvent& event ) {

    m_panel6->Refresh();
    m_panel6->Update();
}

void guifrmMain::ConnectMode( wxCommandEvent& event ) {
    if (mode == mconnect) {
        mode = none;
    } else {
        mode = mconnect;
    }
}

void guifrmMain::NodeZoom( wxMouseEvent& event ) {
    wxCoord lines = event.GetWheelRotation() / event.GetWheelDelta();

    if (defaultRad + lines > 0) {
        defaultRad += lines;
    }

    for (auto& i : graph.GetNodes()) {
        i.GetRad() = defaultRad;
    }

    m_panel6->Refresh();
    m_panel6->Update();
}

void guifrmMain::Configure() {

    CustomDialog *custom = new CustomDialog(wxT("Choose graph type"));
    custom->ShowModal();
    if (custom->GetGraphMode() == directed) {
        m_panel6->GetParent()->SetLabel(wxT("Directed graph"));
        gm = directed;
    } else if (custom->GetGraphMode() == undirected) {
        m_panel6->GetParent()->SetLabel(wxT("Undirected graph"));
        gm = undirected;
    }

}