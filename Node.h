#ifndef ASSIGNMENT1_NODE_H
#define ASSIGNMENT1_NODE_H


class Node
{
public:
    int data;
    char direction;
    Node *next;

    Node() : next(nullptr), data(-1) {}
};


#endif //ASSIGNMENT1_NODE_H
