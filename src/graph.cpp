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

