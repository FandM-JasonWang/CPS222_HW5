#ifndef BETTERPRIORITYQUEUE_H
#define BETTERPRIORITYQUEUE_H

#include "Graph.h"
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

// This is used for the items in the BetterPriorityQueue
struct BPQNode {
	int pri = INT_MAX;
	bool visited = false;
	nodekey_t gnode = INVALID_NODE_KEY;
	
	bool operator<(const BPQNode &other) const {
		if (pri != other.pri) {
			return pri < other.pri;
		}
		return gnode < other.gnode;
	}

	bool operator>(const BPQNode &other) const {
		if (pri != other.pri) {
			return pri > other.pri;
		}
		return gnode > other.gnode;
	}
	
	bool operator==(const BPQNode &other) const {
		return this->gnode == other.gnode;
	}
};

class BetterPriorityQueue : public priority_queue<BPQNode, vector<BPQNode>, greater<BPQNode>> {
public:
    using priority_queue<BPQNode, vector<BPQNode>, greater<BPQNode>>::priority_queue;

    BetterPriorityQueue() = default;

    bool Contains(const BPQNode& node) const;
    bool Update(const BPQNode& dummy);
    string ToString() const;
    static string BPQNodeToString(const BPQNode& node);
};

#endif
