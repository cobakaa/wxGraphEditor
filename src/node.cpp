#include "../include/node.h"
#include "../include/guifrmMain.h"
#include "../include/gui.h"

Node::Node() : pt(wxPoint(0, 0)), rad(0) {
    painted = false;
}

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
