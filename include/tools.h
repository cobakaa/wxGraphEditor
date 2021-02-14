#ifndef __TOOLS__
#define __TOOLS__

#include <wx/dc.h>

enum Mode {
    add,
    mdelete,
    repos,
    mconnect,
    none
};

wxCoord sqr(wxCoord x);

wxCoord min(wxCoord x, wxCoord y);
wxCoord max(wxCoord x, wxCoord y);

#endif