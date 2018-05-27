//
// Created by avispa on 26/5/2018.
//

#ifndef MERKLE_TREE_H
#define MERKLE_TREE_H

#include <iostream>
#include <vector>

class Node {
	std::string str;
	Node *lhs, *rhs;

public:
	Node(std::vector<std::string> &blocks, int tl, int tr);
    std::string get_str();
	virtual ~Node();
};
#endif // MERKLE_TREE_H
