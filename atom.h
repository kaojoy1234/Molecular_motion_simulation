#ifndef ATOM_H
#define ATOM_H
#include"tdvector.h"

struct Atom {
    struct TdVector pos;
    struct TdVector p;
    struct TdVector f;
};

#endif