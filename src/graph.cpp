#include "../include/graph.h"

Graph::Graph() {
    nodes = {};
    arcs = {};
    connectivity_matrix = {{}};
    gm = gnone;

}

std::vector<std::vector<int>> Graph::BuildConnMatrix() {
    return {{}};
}

Graph::Graph(std::vector<Node> nodes, std::vector<std::pair<int, int>> arcs) {
    nodes = nodes;
    arcs = arcs;
    connectivity_matrix = BuildConnMatrix();
    gm = gnone;
}

std::vector<Node>& Graph::GetNodes() {
    return nodes;
}

bool Graph::HaveIntersection(wxPoint pt, wxCoord r) {
    Node n = Node(pt, r);
    bool inter = false;

    for (auto& i : nodes) {
        if (i.GetPainted() && (sqr(i.GetRad() + n.GetRad()) >= sqr(i.GetPoint().x - n.GetPoint().x) + sqr(i.GetPoint().y - n.GetPoint().y))) { // intersection
            inter = true;
            break;
        }
    }

    return inter;
}

void Graph::AddNode(Node n) {
    n.GetPainted() = true;
    nodes.push_back(n);
    //add building matrix
}

int Graph::GetIntersectionInd(wxPoint pt) {
    int cnt = 0;
    bool getInter = false;

    for (auto& i : nodes) {
        if (i.GetPainted() && (sqr(i.GetRad()) > sqr(i.GetPoint().x - pt.x) + sqr(i.GetPoint().y - pt.y))) { // intersection
                // i.GetPainted() = false;
            getInter = true;
            break;
        }
        cnt++;
    }
    return getInter ? cnt : -1;
}

void Graph::DeleteNode(wxPoint pt) {
    
    int cnt = GetIntersectionInd(pt);

    if (!nodes.empty() && (cnt >= 0)) {
        nodes.erase(nodes.begin() + cnt);
    }

    //add building matrix
}