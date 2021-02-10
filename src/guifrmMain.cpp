#include "../include/guifrmMain.h"
#include <wx/dc.h>
#include <wx/wx.h>
#include "../include/tools.h"
#include "../include/node.h"

guifrmMain::guifrmMain( wxWindow* parent )
:
frmMain( parent )
{
    mode = add;
    nodes =  {};
    grabbed_ind = -1;
}


void guifrmMain::DrawCircle(wxMouseEvent &event) {

    const wxPoint pt = wxGetMousePosition();
    wxCoord x = pt.x - m_panel6->GetScreenPosition().x;
    wxCoord y = pt.y - m_panel6->GetScreenPosition().y;

    switch (mode) {
        case add: 
        {
            AddCircle(wxPoint(x, y), 15);
            
            Render();
            break;
       }

       case mdelete:
       {
            DeleteCircle(wxPoint(x, y));

            // m_panel6->Refresh();
            Render();
            break;
       }

       case repos:
       {
            nodes[grabbed_ind].GetGrabbed() = false;
            grabbed_ind = -1;
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

void guifrmMain::Render() {
    // m_panel6->Refresh();
    m_panel6->Refresh();
    m_panel6->Update();

    for (auto& i : nodes) {
        if (i.GetPainted()) {
            wxClientDC dc(m_panel6);
            dc.DrawCircle(i.GetPoint().x, i.GetPoint().y, i.GetRad());
        }
    }
    
}


void guifrmMain::AddCircle(wxPoint pt, wxCoord r) {
    Node n = Node(pt, r);
    bool noInter = true;
    
    for (auto& i : nodes) {
        if (i.GetPainted() && (sqr(i.GetRad() + n.GetRad()) >= sqr(i.GetPoint().x - n.GetPoint().x) + sqr(i.GetPoint().y - n.GetPoint().y))) { // intersection
            noInter = false;
            break;
        }
    }

    if (noInter) {
        n.GetPainted() = true;
        nodes.push_back(n);
    }
}


void guifrmMain::DeleteCircle(wxPoint pt) {
    int cnt = 0;
    bool getInter = false;

    for (auto& i : nodes) {
        if (i.GetPainted() && (sqr(i.GetRad()) > sqr(i.GetPoint().x - pt.x) + sqr(i.GetPoint().y - pt.y))) { // intersection
                // i.GetPainted() = false;
            getInter = true;
            break;
        }
        cnt++;
    }
            
    if (!nodes.empty() && getInter) {
        nodes.erase(nodes.begin() + cnt);
    }
}

void guifrmMain::ReposMode( wxCommandEvent& event ) {
    if (mode == repos) {
        mode = none;
    } else {
        mode = repos;
    }
}

void guifrmMain::GpabCircle( wxMouseEvent& event ) {
    if (mode == repos && !nodes.empty()) {
        const wxPoint pt = wxGetMousePosition();
        wxCoord x = pt.x - m_panel6->GetScreenPosition().x;
        wxCoord y = pt.y - m_panel6->GetScreenPosition().y;

        int cnt = 0;

        for (auto& i : nodes) {
            if (i.GetPainted() && (sqr(i.GetRad()) > sqr(i.GetPoint().x - x) + sqr(i.GetPoint().y - y))) { // intersection
                    // i.GetPainted() = false;
                break;
            }
            cnt++;
        }

        
            grabbed_ind = cnt;
            nodes[grabbed_ind].GetGrabbed() = true;
    }
}

void guifrmMain::MotionCircle( wxMouseEvent& event ) {
    
    if (mode == repos) {
        const wxPoint pt = wxGetMousePosition();
        wxCoord x = pt.x - m_panel6->GetScreenPosition().x;
        wxCoord y = pt.y - m_panel6->GetScreenPosition().y;

        bool inter = false;
        if (grabbed_ind != -1) {
            for (auto& i : nodes) {
                if (!i.GetGrabbed() && (sqr(i.GetPoint().x - x) + sqr(i.GetPoint().y - y) < 
                sqr(i.GetRad() * 2))) {
                    inter = true;
                    break;
                }
            }

            if (!inter) {
                nodes[grabbed_ind].GetPoint().x = x;
                nodes[grabbed_ind].GetPoint().y = y;
            }

            Render();
        }
    }
}