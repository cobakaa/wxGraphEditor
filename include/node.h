#ifndef __NODE__
#define __NODE__

#include "gui.h"

class Node 
{
    public:

        Node();
        Node(wxPoint pt, wxCoord rad);
        wxPoint GetPoint();
        wxCoord GetRad();
        bool& GetPainted();


    private:
        wxPoint pt;
        wxCoord rad;
        bool painted;
};



#endif
