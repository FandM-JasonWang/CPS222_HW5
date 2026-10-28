#include "BetterPriorityQueue.h"

bool BetterPriorityQueue::Contains(const BPQNode& node) const {
    for (const auto& item : this->c) {
        if (item.gnode == node.gnode) {
            return true;
        }
    }
    return false;
}

bool BetterPriorityQueue::Update(const BPQNode& dummy) {
    for (size_t i = 0; i < this->c.size(); ++i) {
        if (this->c[i].gnode == dummy.gnode) {
            // Only update if the new priority is smaller (decrease-key operation for Dijkstra)
            if (dummy.pri < this->c[i].pri) {
                this->c[i].pri = dummy.pri;

                // Re-heapify the underlying vector to maintain a valid binary min-heap
                make_heap(this->c.begin(), this->c.end(), greater<BPQNode>());
                return true;
            }
            return false;
        }
    }
    return false;
}

string BetterPriorityQueue::BPQNodeToString(const BPQNode& node) {
    return "(" + to_string(node.gnode) + ", pri: " + to_string(node.pri) + ")";
}

string BetterPriorityQueue::ToString() const {
    string result = "[";
    for (size_t i = 0; i < this->c.size(); ++i) {
        if (i > 0) {
            result += ", ";
        }
        result += BPQNodeToString(this->c[i]);
    }
    result += "]";
    return result;
}
