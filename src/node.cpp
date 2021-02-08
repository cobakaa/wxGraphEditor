#include <node.h>
#include <guifrmMain.h>
#include <gui.h>

Node::Node(wxPoint pt, wxCoord rad) : pt(pt), rad(rad) 
{
    painted = false;
}


wxPoint Node::GetPoint() {
    return pt;
}

wxCoord Node::GetRad() {
    return rad;
}

bool& Node::GetPainted() {
    return painted;
}