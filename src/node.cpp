#include "../include/node.h"
#include "../include/guifrmMain.h"
#include "../include/gui.h"
#include <iostream>

Node::Node() : pt(wxPoint(0, 0)), rad(0) {
    painted = false;
    grabbed = false;
    label = "";
}

Node::Node(wxPoint pt_, wxCoord rad_, wxString label_) 
{
    pt = pt_;
    rad = rad_;
    std::cout << "Node created" << "\n";
    painted = false;
    grabbed = false;
    label = label_;
}

Node::Node(const Node& node) {
    pt = node.pt;
    rad = node.rad;
    painted = node.painted;
    grabbed = node.grabbed;
    label = node.label;
}

wxPoint& Node::GetPoint() {
    return pt;
}

wxCoord& Node::GetRad() {
    return rad;
}

bool& Node::GetPainted() {
    return painted;
}

bool& Node::GetGrabbed() {
    return grabbed;
}


Node& Node::operator=(const Node& rvalue) {
    if (this == &rvalue) {
            return *this;
        }
        pt = rvalue.pt;
        rad = rvalue.rad;
        painted = rvalue.painted;
        grabbed = rvalue.grabbed;
        label = rvalue.label;
        return *this;
}

wxString& Node::GetLabel() {
    return label;
}

