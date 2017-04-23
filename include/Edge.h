#include <iostream>
#include <climits>

#ifndef EDGE_H
#define EDGE_H

#define INF INT_MAX

struct EdgeDistance {
    unsigned long distanceTo;
    bool visited;
    bool infinity;

    EdgeDistance() {
        distanceTo = INF;
        visited = false;
        infinity = true;
    }

    inline friend std::ostream& operator<<(std::ostream& os, const EdgeDistance& ed) {
        if (ed.infinity) os << "inf";
        else os << ed.distanceTo;
        return os;
    }
};

struct Edge {
    unsigned long to;
    unsigned long weight;

    Edge() {
        to = INF;
        weight = INF;
    }

    Edge(unsigned long v, unsigned long w) {
        to = v;
        weight = w;
    }

    Edge(const Edge& other) {
        to = other.to;
        weight = other.weight;
    }
    
    static Edge Create(unsigned long to, unsigned long weight) {
        Edge e;
        e.to = to;
        e.weight = weight;
        return e;
    }

    Edge& operator=(const Edge& b) {
        to = b.to;
        weight = b.weight;
        return *this;
    }
    
    static Edge Distinguished() {
        return {INF, INF};
    }

    inline friend unsigned long operator>(Edge& a, Edge& b) {
        return Edge::CompareWeights(a, b);
    }

    inline friend bool operator==(Edge& a, Edge& b) {
        return Edge::SameKey(a, b);
    }

    inline static unsigned long CompareWeights(Edge& a, Edge& b) {
        return a.weight > b.weight;
    }
    
    inline static bool SameKey(Edge& a, Edge& b) {
        return a.to == b.to;
    }
    
    inline friend std::ostream& operator<<(std::ostream& os, const Edge& e) {
        os << "{" << e.to << ", " << e.weight << "}";
        return os;
    }
};

#endif /*EDGE_H*/