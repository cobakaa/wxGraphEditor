#include "../include/tools.h"

wxCoord sqr(wxCoord x) {
	return x * x;
}

wxCoord min(wxCoord x, wxCoord y) {
	return (x > y) ? y : x;
}

wxCoord max(wxCoord x, wxCoord y) {
	return (x > y) ? x : y;
}