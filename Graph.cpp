#include "Graph.h"
#include <stdexcept>

Graph::~Graph() {
    // Delete all GraphEdge instances allocated on the heap
    for (const GraphEdge* edge : edge_list) {
        delete edge;
    }
    edge_list.clear();
}

void Graph::AddNode(nodekey_t key) {
    if (IsPresent(key)) {
        throw invalid_argument("Node already exists in the graph: " + to_string(key));
    }
    node_set.insert(key);
    node_order.push_back(key);
    outward_edges[key]; // initialize empty set of outward edges
}

const GraphEdge* Graph::AddEdge(nodekey_t fromNodeKey, nodekey_t toNodeKey, unsigned int weight) {
    if (!IsPresent(fromNodeKey)) {
        throw invalid_argument("Source node does not exist: " + to_string(fromNodeKey));
    }
    if (!IsPresent(toNodeKey)) {
        throw invalid_argument("Destination node does not exist: " + to_string(toNodeKey));
    }

    // Check if an outward edge from fromNodeKey to toNodeKey already exists
    for (const GraphEdge* existing : outward_edges[fromNodeKey]) {
        if (existing->to == toNodeKey) {
            throw invalid_argument("Edge already exists between nodes");
        }
    }

    // GraphEdge must be created on the heap as specified in Graph.h
    GraphEdge* new_edge = new GraphEdge{fromNodeKey, toNodeKey, weight};
    edge_list.push_back(new_edge);
    outward_edges[fromNodeKey].insert(new_edge);

    return new_edge;
}

bool Graph::IsPresent(nodekey_t key) const {
    return node_set.find(key) != node_set.end();
}

string Graph::NodesToString() const {
    string res = "[";
    for (size_t i = 0; i < node_order.size(); ++i) {
        if (i > 0) {
            res += ", ";
        }
        res += "(" + to_string(node_order[i]) + ")";
    }
    res += "]";
    return res;
}

string Graph::EdgesToString() const {
    string res = "[";
    for (size_t i = 0; i < edge_list.size(); ++i) {
        if (i > 0) {
            res += ", ";
        }
        res += "((" + to_string(edge_list[i]->from) + ")->(" + to_string(edge_list[i]->to) + ") w:" + to_string(edge_list[i]->weight) + ")";
    }
    res += "]";
    return res;
}

set<const GraphEdge*> Graph::GetOutwardEdgesFrom(nodekey_t nodeKey) const {
    auto it = outward_edges.find(nodeKey);
    if (it != outward_edges.end()) {
        return it->second;
    }
    return set<const GraphEdge*>();
}

set<nodekey_t> Graph::GetNodes() const {
    return node_set;
}

size_t Graph::Size() const {
    return edge_list.size();
}

size_t Graph::Order() const {
    return node_set.size();
}
