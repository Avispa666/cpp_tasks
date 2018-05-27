#include <iostream>
#include <thread>
#include <random>
#include "CBlockList.h"
#include "picosha2.h"

void produce(CBlockList &lst)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0,255);
    auto rand = std::bind(dist, gen);
    while (true) {
        std::vector<unsigned char> block(512 * 1024);
        for (unsigned char& ch : block) {
            ch = (unsigned char) rand();
        }
        if (!lst.push(block)) break;
    }
}

void consume(CBlockList &lst)
{
    while (lst.hashData()) {}
}

int main()
{
    CBlockList lst;
    std::thread producer1(produce, std::ref(lst));
    std::thread producer2(produce, std::ref(lst));
    std::thread consumer1(consume, std::ref(lst));
    std::thread consumer2(consume, std::ref(lst));
    producer1.join();
    producer2.join();
    consumer1.join();
    consumer2.join();
    lst.write("D:\\hashes.bin");
    return 0;
}