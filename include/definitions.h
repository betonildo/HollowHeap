#ifndef DEFINITIONS_H
#define DEFINITIONS_H

typedef unsigned int U32;

#define MAX(a, b) (a) < (b) ? (b) : (a)
#define PHI ((1.0 + sqrt(5.0)) / 2.0)
#define logBase(x, b) log((double)(x)) / log((double)(b))
#define Make2Pot(x) {\
        double ___AXHOADISJDOJQWDQ_L = logBase((*x), 2); \
        double ___AXHAOSDJSODIJOQW_intpart; \
        double ___AXHDASIUHDIUWQHD_fractpart = modf (___AXHOADISJDOJQWDQ_L, &___AXHAOSDJSODIJOQW_intpart); \
        (*x) = ___AXHDASIUHDIUWQHD_fractpart > 0 ? pow(2, ceil(___AXHOADISJDOJQWDQ_L)) : (*x); \
} \

#endif /*DEFINITIONS_H*/