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
        void AddConnection();
        void AddArc(int x, int y);
        void DeleteArc(int x, int y);

        const std::vector<std::pair<int, int>>& GetArcs();
        const std::vector<std::vector<int>>& GetConnMatrix();

        GraphMode& GetGraphMode();

        void Clear();

        bool Empty();



    private:
        std::vector<Node> nodes;
        std::vector<std::pair<int, int>> arcs;
        GraphMode gm;
        std::vector<std::vector<int>> connectivity_matrix;
};


#endif