#include "guifrmMain.h"
#include <wx/dc.h>
#include <wx/wx.h>
#include <tools.h>
#include <node.h>

guifrmMain::guifrmMain( wxWindow* parent )
:
frmMain( parent )
{
    mode = add;
    nodes =  {};
}


void guifrmMain::DrawCircle(wxMouseEvent &event) {

    switch (mode) {
        case add: 
        {
            
            const wxPoint pt = wxGetMousePosition();
            wxCoord x = pt.x - m_panel6->GetScreenPosition().x;
            wxCoord y = pt.y - m_panel6->GetScreenPosition().y;
            Node n = Node(wxPoint(x, y), 10);
            bool noInter = true;
            for (auto i : nodes) {
                if (i.GetPainted() && (((i.GetRad() + n.GetRad()) * (i.GetRad() + n.GetRad())) >= 
                ((i.GetPoint().x - n.GetPoint().x) * (i.GetPoint().x - n.GetPoint().x) + (i.GetPoint().y - n.GetPoint().y) * (i.GetPoint().y - n.GetPoint().y)))) { // intersection
                    noInter = false;
                    break;
                }
            }

            if (noInter) {
                n.GetPainted() = true;
                nodes.push_back(n);
            }
            
            
            Render();
            break;
       }

       case mdelete:
       {
            
            const wxPoint pt = wxGetMousePosition();
            wxCoord x = pt.x - m_panel6->GetScreenPosition().x;
            wxCoord y = pt.y - m_panel6->GetScreenPosition().y;
            // int cnt = 0;

            for (auto& i : nodes) {
                if (i.GetPainted() && (i.GetRad() * i.GetRad() > (i.GetPoint().x - x) * (i.GetPoint().x - x) + (i.GetPoint().y - y) * (i.GetPoint().y - y))) { // intersection
                    i.GetPainted() = false;
                    break;
                }
                
            }
            
            // m_panel6->Refresh();
            Render();
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

    for (auto i : nodes) {
        if (i.GetPainted()) {
            wxClientDC dc(m_panel6);
            dc.DrawCircle(i.GetPoint().x, i.GetPoint().y, i.GetRad());
        }
    }

    
    
}