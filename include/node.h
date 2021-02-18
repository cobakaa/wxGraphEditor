#ifndef __NODE__
#define __NODE__

#include "gui.h"

class Node 
{
    public:

        Node();
        Node(wxPoint pt, wxCoord rad);
        Node(const Node& node);

        wxPoint& GetPoint();
        wxCoord& GetRad();
        bool& GetPainted();
        bool& GetGrabbed();

        Node& operator=(const Node& rvalue);



    private:
        wxPoint pt;
        wxCoord rad;
        bool painted;
        bool grabbed;
};



#endif
