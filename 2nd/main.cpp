//
// Created by avispa on 26/5/2018.
//

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "merkle_tree.h"

#define NBLOCKS 128
#define HASHES 4
#define STRLEN 512

std::string generate() {
    std::string ret = "";
    for (size_t i = 0; i < STRLEN; ++i) {
        ret += char('a' + rand() % 26);
    }
    return ret;
}


int produce(std::mutex &mtx, std::queue<std::string> &que, std::condition_variable &var) {
    int ret = 0;
    int t =  NBLOCKS * HASHES;
    for (size_t i = 0; i < t; ++i) {
        std::string str = generate();
        mtx.lock();
        que.push(str);
        if (que.size() >= HASHES) var.notify_all();
        mtx.unlock();
    }
    return ret;
}

inline bool ready(std::mutex &mtx, std::queue<std::string> &que) {
    std::lock_guard<std::mutex> guard(mtx);
    return que.size() >= HASHES;
}


void consume(std::mutex &mtx, std::queue<std::string> &que, std::condition_variable &var) {
    std::ofstream file("blocks.txt");
    for (size_t i = 0; i < NBLOCKS; ++i) {
        while (!ready(mtx, que)) {
            std::unique_lock<std::mutex> lock(mtx);
            var.wait(lock);
        }
        mtx.lock();
        std::vector<std::string> blocks;
        for (size_t j = 0; j < HASHES; ++j) {
            blocks.push_back(que.front());
            que.pop();
        }
        mtx.unlock();
        Node *node = new Node(blocks, 0, HASHES - 1);
        file << node->get_str() << "\n";
        delete node;
    }
    file.close();
}

int main() {
    srand(time(NULL));
    std::mutex mtx;
    std::queue<std::string> que;
    std::condition_variable var;
    std::thread consumer(consume, std::ref(mtx), std::ref(que), std::ref(var));
    std::thread producer(produce, std::ref(mtx), std::ref(que), std::ref(var));
    consumer.join();
    producer.join();
    return 0;
}

