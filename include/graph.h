#ifndef __GRAPH__
#define __GRAPH__

#include <vector>
#include "node.h"
#include "tools.h"
#include <algorithm>

class Graph {

    public:
        Graph();

        std::vector<std::vector<int>> BuildConnMatrix();

        Graph(wxVector<Node> nodes, std::vector<std::pair<int, int>> arcs);

        wxVector<Node>& GetNodes();

        bool HaveIntersection(wxPoint pt, wxCoord r);
        void AddNode(wxPoint pt, wxCoord r, wxString label = "");
        void DeleteNode(wxPoint pt);
        int GetIntersectionInd(wxPoint pt);
        // void AddConnection();
        void AddArc(int x, int y);
        void DeleteArc(int x, int y);

        const std::vector<std::pair<int, int>>& GetArcs();
        const std::vector<std::vector<int>>& GetConnMatrix();

        GraphMode& GetGraphMode();

        void Clear();

        bool Empty();

        wxString GraphToMGF();
        void BuildComponents();
        void dfs1 (int v);
        void dfs2 (int v);
        void BuildIncidents();

        const std::vector<std::vector<int>>& GetComponents();




    private:
        wxVector<Node> nodes;
        std::vector<std::pair<int, int>> arcs;
        GraphMode gm;
        std::vector<std::vector<int>> connectivity_matrix;


        std::vector <std::vector<int>> g, gr;
        std::vector<bool> used;
        std::vector<int> order, component;
        std::vector<std::vector<int>> components;
};


#endif