#ifndef EDGEDISTANCE_H
#define EDGEDISTANCE_H

#include <iostream>
#include "definitions.h"

#pragma pack(1)
struct EdgeDistance {
    U32 distanceTo : 32;
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