#include "guifrmMain.h"
#include <wx/dc.h>
#include <wx/wx.h>
#include <tools.h>
#include <node.h>

guifrmMain::guifrmMain( wxWindow* parent )
:
frmMain( parent )
{
    mode = none;
    nodes =  {};
}


void guifrmMain::DrawCircle(wxMouseEvent &event) {
    if (mode == add) {
        
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
            wxClientDC dc(m_panel6);
            dc.DrawCircle(n.GetPoint().x, n.GetPoint().y, n.GetRad());
            n.GetPainted() = true;
            nodes.push_back(n);
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