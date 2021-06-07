#include "../include/graph.h"

#include <iostream>

Graph::Graph() {
    // nodes.resize(1);
    nodes = {};
    arcs = {};
    connectivity_matrix = {{}};
    gm = gnone;
    used = {};
    component = {};
    order = {};
    components = {{}};
    g = {{}};
    gr = {{}};

}

std::vector<std::vector<int>> Graph::BuildConnMatrix() {
    std::vector<std::vector<int>> matrix;

    matrix.resize(nodes.size());

    for (auto& i : matrix) {
        i.resize(nodes.size());
    }

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); j++) {
            matrix[i][j] = 0;
        }
    }

    for (auto& i : arcs) {
        matrix[i.first][i.second] = 1;
        if (gm == undirected) {
            matrix[i.second][i.first] = 1;
        }
    }

    return matrix;
}

Graph::Graph(wxVector<Node> nodes, std::vector<std::pair<int, int>> arcs) {
    nodes = nodes;
    arcs = arcs;
    connectivity_matrix = BuildConnMatrix();
    gm = gnone;
    BuildComponents();
}

wxVector<Node>& Graph::GetNodes() {
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

void Graph::AddNode(wxPoint pt, wxCoord r, wxString label) {

    Node n = Node(pt, r, label);

    nodes.push_back(n);
    
    nodes[nodes.size() - 1].GetPainted() = true;
    connectivity_matrix = BuildConnMatrix();
    BuildComponents();

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
        BuildComponents();
    }
    
    //add building matrix
}

void Graph::Clear() {
    nodes.clear();
    arcs.clear();
    gm = gnone;
    connectivity_matrix.clear();
    BuildComponents();
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
        if (gm == undirected) {
            arcs.push_back({p.second, p.first});
        }
    }

    connectivity_matrix = BuildConnMatrix();
    BuildComponents();
    
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

void Graph::DeleteArc(int x, int y) {
    for (auto it = arcs.begin(); it != arcs.end(); it++) {
        if ((*it).first == x && (*it).second == y) {
            arcs.erase(it);
            break;
        }
    }

    if (gm == undirected) {
        for (auto it = arcs.begin(); it != arcs.end(); it++) {
            if ((*it).first == y && (*it).second == x) {
                arcs.erase(it);
                break;
            }
        }
    }

    connectivity_matrix = BuildConnMatrix();
    BuildComponents();
}

wxString Graph::GraphToMGF() {
    wxArrayString str;
    str.Add("{");
    str.Add("\"nodes\":[");

    for (auto& i : nodes) {
        str.Add("{\"pt.x\":\"");
        str.Add(std::to_string(i.GetPoint().x));
        str.Add("\",\"pt.y\":\"");
        str.Add(std::to_string(i.GetPoint().y));
        str.Add("\",\"rad\":\"");
        str.Add(std::to_string(i.GetRad())); 
        str.Add("\",\"painted\":\"");
        str.Add(std::to_string(i.GetPainted()));
        str.Add("\",\"grabbed\":\"");
        str.Add(std::to_string(i.GetGrabbed()));
        str.Add("\",\"label\":\"");
        str.Add(i.GetLabel());
        str.Add("\"},");
    }

    str.Add("],");

    str.Add("\"arcs\":[");

    for (auto& i : arcs) {
        str.Add("{\"first\":\"");
        str.Add(std::to_string(i.first));
        str.Add("\",\"second\":\"");
        str.Add(std::to_string(i.second));
        str.Add("\"},");
    }

    str.Add("],");
    str.Add("\"gm\":\"");
    str.Add((gm == directed) ? "directed" : "undirected");

    str.Add("\"}");


    return wxJoin(str, ' ');
}

void Graph::BuildComponents() {
    int n = nodes.size();
    components.clear();
    order.clear();
    BuildIncidents();

    used.assign (n, false);

	for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs1(i);
        }
    }

	used.assign (n, false);
	for (int i = 0; i < n; ++i) {
		int v = order[n-1-i];
		if (!used[v]) {
			dfs2 (v);
			components.push_back(component);

			component.clear();
		}
	}

    std::sort(components.begin(), components.end(), [](const std::vector<int>& x, const std::vector<int>& y) {
        int xmin = *x.begin(), ymin = *y.begin();
        for (const auto& i : x) {
            xmin = min(i, xmin);
        }

        for (const auto& i : y) {
            ymin = min(i, ymin);
        }
        return xmin < ymin;
    });
}

void Graph::dfs1(int v) {
    used[v] = true;
	for (size_t i = 0; i < g[v].size(); ++i)
		if (!used[ g[v][i] ]) {
            dfs1(g[v][i]);
        }
			
	order.push_back (v);
}

void Graph::dfs2 (int v) {
    used[v] = true;
	component.push_back(v);
	for (size_t i=0; i< gr[v].size(); ++i) {
        if (!used[ gr[v][i] ]) {
            dfs2 (gr[v][i]);
        }		
    }
}

void Graph::BuildIncidents() {
    g.assign(nodes.size(), {});
    gr.assign(nodes.size(), {});

    for (const auto& i : arcs) {
        g[i.first].push_back(i.second);
        gr[i.second].push_back(i.first);
    }
}

const std::vector<std::vector<int>>& Graph::GetComponents() {

    return components;
}