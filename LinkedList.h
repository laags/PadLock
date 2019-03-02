#ifndef ASSIGNMENT1_LINKEDLIST_H
#define ASSIGNMENT1_LINKEDLIST_H
#include <iostream>
#include "node.h"

class LinkedList {
private:
    Node *first;
    Node *workingNode;
    void Add(int num, char direction);

public:
    LinkedList();
    virtual ~LinkedList();
    int workingValue;
    void SetWorkingValue(int num);
    void SubstituteValue(int value);
    friend std::ostream &operator<<(std::ostream &output, LinkedList &list);
};

#endif //ASSIGNMENT1_LINKEDLIST_H
