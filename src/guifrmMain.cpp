#include "../include/guifrmMain.h"
#include <wx/dc.h>
#include <wx/wx.h>
#include "../include/tools.h"
#include "../include/node.h"
#include "../include/customDialog.h"

#include <wx/dcbuffer.h>

wxCoord defaultRad = 20;

guifrmMain::guifrmMain( wxWindow* parent )
:
frmMain( parent )
{
    mode = none;
    graph = Graph();
    grabbed_ind = -1;
    gm = gnone;
    line_end = wxPoint(-1, -1);
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

        case mconnect:
        {
            if (grabbed_ind != -1) {
                line_end = m_panel6->CalcUnscrolledPosition(line_end);
                int second = graph.GetIntersectionInd(line_end);
                //line_end = wxPoint(-1, -1);
                if (second != -1) {
                    
                    graph.AddArc(grabbed_ind, second);
                
                }
                grabbed_ind = -1;

                m_panel6->Refresh();
                m_panel6->Update();
            }

            break;
        }

        case none:
        {
           Configure();
           mode = add;
           break;
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
    wxColour col1;
	col1.Set(wxT("#0c0c0c"));
	// wxBrush brush(wxColour(255, 255, 255), wxBRUSHSTYLE_TRANSPARENT);
	// dc.SetBrush(brush);
	dc.SetPen(wxPen(col1, 1, wxPENSTYLE_SOLID));

    wxCoord x, y, z, w;

    for (auto& i : graph.GetNodes()) {
        if (i.GetPainted()) {
            m_panel6->CalcScrolledPosition(i.GetPoint().x, i.GetPoint().y, &x, &y);
            dc.DrawCircle(x, y, i.GetRad());
        }
    }

    wxPoint start, end;
    
    for (const auto& i : graph.GetArcs()) {
        m_panel6->CalcScrolledPosition(graph.GetNodes()[i.first].GetPoint().x, graph.GetNodes()[i.first].GetPoint().y, &x, &y);
        m_panel6->CalcScrolledPosition(graph.GetNodes()[i.second].GetPoint().x, graph.GetNodes()[i.second].GetPoint().y, &z, &w);

        double cosa = (z - x) / sqrt(sqr(z - x) + sqr(w - y));
        double sina = (w - y) / sqrt(sqr(z - x) + sqr(w - y));

        start.x = x + defaultRad * cosa;
        start.y = y + defaultRad * sina;


        end.x = z - defaultRad * cosa;
        end.y = w - defaultRad * sina;

        
        dc.DrawLine(start, end);

        if (gm == directed) {

            wxPoint first, second;

            // if ((end.x - start.x) * (end.y - start.y) < 0) {

            //     first.x = end.x - defaultRad * cos(acos(cosa) + M_PI / 6);
            //     first.y = end.y - defaultRad * sin(asin(sina) - M_PI / 6);

            //     second.x = end.x - defaultRad * cos(acos(cosa) - M_PI / 6);
            //     second.y = end.y - defaultRad * sin(asin(sina) + M_PI / 6);
            // } else {
            //     first.x = end.x - defaultRad * cos(acos(cosa) + M_PI / 6);
            //     first.y = end.y - defaultRad * sin(asin(sina) + M_PI / 6);

            //     second.x = end.x - defaultRad * cos(acos(cosa) - M_PI / 6);
            //     second.y = end.y - defaultRad * sin(asin(sina) - M_PI / 6);
            // }

            first.x = end.x - defaultRad / 2 * cosa + defaultRad / 3 * sina;
            first.y = end.y - defaultRad / 2 * sina - defaultRad / 3 * cosa;

            second.x = end.x - defaultRad / 2 * cosa - defaultRad / 3 * sina;
            second.y = end.y - defaultRad / 2 * sina + defaultRad / 3 * cosa;

            dc.DrawLine(end, first);
            dc.DrawLine(end, second);
        }
    }

    if (grabbed_ind != -1 && mode == mconnect) {
        m_panel6->CalcScrolledPosition(graph.GetNodes()[grabbed_ind].GetPoint().x, graph.GetNodes()[grabbed_ind].GetPoint().y, &x, &y);
        line_end = m_panel6->CalcScrolledPosition(line_end);

        dc.DrawLine(wxPoint(x, y), line_end);

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

    if (mode == repos && !graph.Empty()) {
        
        grabbed_ind = graph.GetIntersectionInd(wxPoint(x, y));
        graph.GetNodes()[grabbed_ind].GetGrabbed() = true;

    } else if (mode == mconnect) {
        grabbed_ind = graph.GetIntersectionInd(wxPoint(x, y));
    }

}

void guifrmMain::OnMouseMove( wxMouseEvent& event ) {

    const wxPoint pt = wxGetMousePosition();
    wxCoord x = pt.x - m_panel6->GetScreenPosition().x;
    wxCoord y = pt.y - m_panel6->GetScreenPosition().y;

    m_panel6->CalcUnscrolledPosition(x, y, &x, &y);
    
    if (mode == repos) {

        if (grabbed_ind != -1) {

            if (!graph.HaveIntersection(wxPoint(x, y), defaultRad)) {
                graph.GetNodes()[grabbed_ind].GetPoint().x = x;
                graph.GetNodes()[grabbed_ind].GetPoint().y = y;
            }

            m_panel6->Refresh();
            m_panel6->Update();
        }
    } else if (mode == mconnect) {
        
        if (grabbed_ind != -1) {
            line_end = wxPoint(x, y);

            m_panel6->Refresh();
            m_panel6->Update();
        }
    }
}

void guifrmMain::NewFile( wxCommandEvent& event ) {
    graph.Clear();
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