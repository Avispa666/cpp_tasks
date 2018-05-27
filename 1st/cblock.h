//
// Created by avispa on 26/5/2018.
//

#ifndef CBLOCK_H
#define CBLOCK_H

#include <vector>

struct CBlock {
    std::vector<unsigned char> data, hash;
};
#endif // CBLOCK_H
