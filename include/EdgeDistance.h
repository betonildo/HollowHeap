#ifndef EDGEDISTANCE_H
#define EDGEDISTANCE_H

#include <iostream>
#include "definitions.h"

struct EdgeDistance {
    U16 distanceTo : 16;
    U8 visited : 1;
    U8 infinity : 1;

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

#endif /*EDGEDISTANCE_H*/