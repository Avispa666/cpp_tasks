//
// Created by avispa on 26/5/2018.
//

#include "CBlockList.h"
#include <fstream>
#include <windows.h>
#include <iostream>
#include "picosha2.h"

#define NBLOCKS 512

CBlockList::CBlockList() : size(0), hashed(0) {}

bool CBlockList::push(std::vector<unsigned char> &block) {
    std::lock_guard<std::mutex> lock(mtx);
    if (size < NBLOCKS) {
        CBlock b;
        std::swap(b.data, block);
        lst.push_front(b);
        ++size;
        var.notify_all();
        return true;
    }
    return false;
}

void CBlockList::write(const char *filename) {
    std::ofstream file(filename, std::ios::binary);
    for (CBlock &b : lst) {
        for (unsigned char &ch : b.hash) file << ch;
    }
    file.close();
    std::cout << "\n";
    system("pause");

}

bool CBlockList::hashData() {
    std::unique_lock<std::mutex> locker(mtx);
    while (size == hashed && hashed < NBLOCKS) {
        var.wait(locker);
    }
    if (hashed >= NBLOCKS)
        return false;
    auto it = lst.begin();
    while (it->hash.size() != 0 && it != lst.end()) it++;
    it->hash.resize(picosha2::k_digest_size);
    picosha2::hash256(it->data, it->hash);
    ++hashed;
    system("cls");
    std::cout << "waiting: " << size - hashed << "\nhashed:  " << hashed
              << "\n" << hashed * 100 / NBLOCKS << "%";
    return hashed < NBLOCKS;
}
