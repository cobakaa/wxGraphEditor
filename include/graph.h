#ifndef __GRAPH__
#define __GRAPH__

#include <vector>
#include "node.h"
#include "tools.h"

class Graph {

    public:
        Graph();

        std::vector<std::vector<int>> BuildConnMatrix();

        Graph(std::vector<Node> nodes, std::vector<std::pair<int, int>> arcs);

        std::vector<Node>& GetNodes();

        bool HaveIntersection(wxPoint pt, wxCoord r);
        void AddNode(Node n);
        void DeleteNode(wxPoint pt);
        int GetIntersectionInd(wxPoint pt);



    private:
        std::vector<Node> nodes;
        std::vector<std::pair<int, int>> arcs;
        GraphMode gm;
        std::vector<std::vector<int>> connectivity_matrix;
};


#endif