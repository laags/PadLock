#include "LinkedList.h"
#include <iostream>

// Default Constructor Sets the current working value to the first position
LinkedList::LinkedList() : first(nullptr), workingValue(1)
{
    // Set the flag for alternating left or right
    bool alternateFlag = true;

    // Loop 7 times, alternating the direction and populating the list with nodes
    for(int i = 0; i < 7; i++){
        if(alternateFlag) {
            Add(0, 'R');
            alternateFlag = false;
        }
        else {
            Add(0, 'L');
            alternateFlag = true;
        }
    }
};

// Destructor
LinkedList::~LinkedList()
{
    Node *node = first;

    // Delete each node in the list
    while (node != nullptr) {
        Node *temp = node;
        node = node->next;
        delete temp;
    }
}

// Set the working value position
void LinkedList::SetWorkingValue(int num)
{
    int index = -1;
    workingValue = num;
    workingNode = first;

    // Loop over nodes until you find the node at num index
    while (workingNode != nullptr) {
        index++;

        // If the node is the node at workingValue's-1 index break out of loop
        if (index == workingValue-1) {
            break;
        }

        // Set the node to the next node and loop again
        workingNode = workingNode->next;
    }
}

// Add a new node to the list
void LinkedList::Add(int num, char direction)
{
    // Create a new node and set its values
    Node *node = new Node();
    node->data = num;
    node->direction = direction;

    // If no node in the list yet, set the first node to this node
    if (first == nullptr) {
        first = node;
        workingNode = node;
    }
    else {
        Node *currNode = first;
        Node *prevNode = nullptr;

        // Find the end of the list
        while (currNode != nullptr) {
            prevNode = currNode;
            currNode = currNode->next;
        }

        // Set the previous nodes next to this node
        if (prevNode != nullptr) {
            prevNode->next = node;
        }
    }
}

// Substitute the value of the node at the current working position
void LinkedList::SubstituteValue(int value)
{
    // Set the value
    workingNode->data = value;
}

std::ostream& operator<<(std::ostream& output, LinkedList& list)
{
    Node *currNode = list.first;
    int workingCounter = 1;

    while (currNode != nullptr) {
        if(list.workingValue == workingCounter)
            output << "[" << currNode->direction << currNode->data << "] ";
        else
            output << currNode->direction << currNode->data << " ";
        currNode = currNode->next;
        workingCounter++;
    }
    output << std::endl;

    return output;
}
