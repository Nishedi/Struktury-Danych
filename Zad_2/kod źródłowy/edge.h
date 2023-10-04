#pragma once
class Edge {
public:
    int src, dest, weight;
    Edge() {
        src = 0;
        dest = 0;
        weight = 0;
    }
    Edge(int src, int dest, int weight) {
        this->src = src; 
        this->dest = dest;
        this->weight = weight;
    }
};