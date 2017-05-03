#ifndef EDGE_BH_H
#define EDGE_BH_H

#include "definitions.h"

struct Edge {
    U32 to;
    U32 weight;

    Edge() {
        to = INF;
        weight = INF;
    }

    Edge(U32 v, U32 w) {
        to = v;
        weight = w;
    }

    Edge(const Edge& other) {
        to = other.to;
        weight = other.weight;
    }
    
    static Edge Create(U32 to, U32 weight) {
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

    inline friend bool operator>(Edge& a, Edge& b) {
        return Edge::CompareWeights(a, b);
    }

    inline friend int operator<(const Edge& a, const Edge& b) {
        return a.weight - b.weight;
    }

    inline friend bool operator==(Edge& a, Edge& b) {
        return Edge::SameKey(a, b);
    }

    inline static bool CompareWeights(Edge& a, Edge& b) {
        return a.weight > b.weight;
    }
    
    inline static bool SameKey(Edge& a, Edge& b) {
        return a.to == b.to;
    }
    
    inline friend U32 operator%(const Edge& e, int mod) {
        return e.to;
    }

    inline friend std::ostream& operator<<(std::ostream& os, const Edge& e) {
        os << "{" << e.to << ", " << e.weight << "}";
        return os;
    }
};

#endif