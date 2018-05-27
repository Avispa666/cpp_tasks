//
// Created by avispa on 26/5/2018.
//

#ifndef PRODUCER_CONSUMER_CBLOCKLIST_H
#define PRODUCER_CONSUMER_CBLOCKLIST_H

#include <mutex>
#include <atomic>
#include <forward_list>
#include <condition_variable>
#include "cblock.h"

class CBlockList {
    std::forward_list<CBlock> lst;
    std::mutex mtx;
    std::condition_variable var;
    std::atomic<size_t> size, hashed;

public:
    CBlockList();
    bool push(std::vector<unsigned char> &block);
    bool hashData();
    void write(const char* filename);




};


#endif //PRODUCER_CONSUMER_CBLOCKLIST_H
