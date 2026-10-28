#include "Dijkstra.h"
#include "BetterPriorityQueue.h"
#include <climits>
#include <map>

// Big-O Time Complexity: O(E * V). Why? Because depends on my custom implementation.
// BPQ Update() use make_heap which is O(V), and we do it for E edges in the worst case.
// O(E * V) is bigger boss than node pop O(V log V), so final time is O(E * V).
// *Very (Underlined aggressively) straightforward, isn't it?

int dijkstra(nodekey_t start, nodekey_t end, const Graph *g) {
    if (g == nullptr) {
        return -1;
    }

    if (!g->IsPresent(start) || !g->IsPresent(end)) {
        return -1;
    }

    if (start == end) {
        return 0;
    }

    set<nodekey_t> all_nodes = g->GetNodes();
    map<nodekey_t, int> dist;

    for (nodekey_t node : all_nodes) {
        dist[node] = INT_MAX;
    }
    dist[start] = 0;

    BetterPriorityQueue bpq;
    for (nodekey_t node : all_nodes) {
        BPQNode item;
        item.gnode = node;
        item.pri = dist[node];
        bpq.push(item);
    }

    while (!bpq.empty()) {
        BPQNode current = bpq.top();
        bpq.pop();

        nodekey_t u = current.gnode;
        int current_dist = current.pri;

        if (current_dist == INT_MAX) {
            break; // Remaining nodes are unreachable
        }

        if (u == end) {
            return current_dist;
        }

        set<const GraphEdge*> neighbors = g->GetOutwardEdgesFrom(u);
        for (const GraphEdge* edge : neighbors) {
            nodekey_t v = edge->to;
            int weight = (int)edge->weight;

            if (current_dist != INT_MAX && current_dist + weight < dist[v]) {
                dist[v] = current_dist + weight;
                BPQNode dummy;
                dummy.gnode = v;
                dummy.pri = dist[v];
                if (bpq.Contains(dummy)) {
                    bpq.Update(dummy);
                }
            }
        }
    }

    return (dist[end] == INT_MAX) ? -1 : dist[end];
}
