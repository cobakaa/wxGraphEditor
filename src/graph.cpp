#include "../include/graph.h"

#include <iostream>

Graph::Graph() {
    nodes = {};
    arcs = {};
    connectivity_matrix = {{}};
    gm = gnone;

}

std::vector<std::vector<int>> Graph::BuildConnMatrix() {
    std::vector<std::vector<int>> matrix;

    matrix.resize(nodes.size());

    for (auto& i : matrix) {
        i.resize(nodes.size());
    }

    for (int i = 0; i < nodes.size(); ++i) {
        for (int j = 0; j < nodes.size(); j++) {
            matrix[i][j] = 0;
        }
    }

    for (auto& i : arcs) {
        matrix[i.first][i.second] = 1;
        if (gm == undirected) {
            matrix[i.second][i.first] = 1;
        }
    }

    // for (int i = 0; i < matrix.size(); ++i) {
    //     for (int j = 0; j < matrix.size(); ++j) {
    //         std::cout << matrix[i][j] << " ";
    //     }
    //     std::cout << '\n';
    // }
    // std::cout << '\n';

    return matrix;
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
    // Node n = Node(pt, r);
    bool inter = false;

    for (auto& i : nodes) {
        if (i.GetPainted() && !i.GetGrabbed() && (sqr(i.GetRad() + r) >= sqr(i.GetPoint().x - pt.x) + sqr(i.GetPoint().y - pt.y))) { // intersection
            inter = true;
            break;
        }
    }

    return inter;
}

void Graph::AddNode(Node n) {
    n.GetPainted() = true;
    nodes.push_back(n);
    connectivity_matrix = BuildConnMatrix();

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


    if (cnt >= 0) {
        
        for (auto it = arcs.begin(); it != arcs.end();) {
            if ((*it).first == cnt || (*it).second == cnt) {
                it = arcs.erase(it);
            } else {
                it++;
            }
        }


        if (!nodes.empty()) {
            nodes.erase(nodes.begin() + cnt);
        }

        for (auto it = arcs.begin(); it != arcs.end(); it++) {
            if ((*it).first > cnt) {
                (*it).first -= 1;
            }
            if ((*it).second > cnt) {
                (*it).second -= 1;
            }
        }

        connectivity_matrix = BuildConnMatrix();
    }
    
    //add building matrix
}

void Graph::Clear() {
    nodes.clear();
    arcs.clear();
    gm = gnone;
    connectivity_matrix.clear();
}

bool Graph::Empty() {
    return nodes.empty();
}

void Graph::AddArc(int x, int y) {

    std::pair<int, int> p = std::make_pair(x, y);
    bool exists = false;

    for (auto it = arcs.begin(); it != arcs.end(); it++) {
        if (*it == p) {
            exists = true;
            break;
        }
    }

    if (!exists) {
        arcs.push_back(p);
    }

    connectivity_matrix = BuildConnMatrix();
    
}

const std::vector<std::pair<int, int>>& Graph::GetArcs() {
    return arcs;
}

const std::vector<std::vector<int>>& Graph::GetConnMatrix() {
    return connectivity_matrix;
}

GraphMode& Graph::GetGraphMode() {
    return gm;
}