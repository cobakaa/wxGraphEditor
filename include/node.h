#ifndef __NODE__
#define __NODE__

#include "gui.h"

class Node 
{
    public:

        Node();
        Node(wxPoint pt, wxCoord rad, wxString label = "");
        Node(const Node& node);

        wxPoint& GetPoint();
        wxCoord& GetRad();
        bool& GetPainted();
        bool& GetGrabbed();
        wxString& GetLabel();

        Node& operator=(const Node& rvalue);



    private:
        wxPoint pt;
        wxCoord rad;
        bool painted;
        bool grabbed;
        wxString label;
};



#endif
