#include "dataStructures.h"
#include <math.h>
#include <list>
#include <memory>
#include <iostream>

//------------------------------------------------x------------------------------------------------//
//                                          Priority Queue

LINKEDLIST* PriorityQ::createLL()
{
    LINKEDLIST* list = new LINKEDLIST;
    list->head = createNode(-1);
    list->head->next_NODE = list->head;
    list->head->previous_NODE = list->head;
    return list;    
};

NODE* PriorityQ::createNode(unsigned appearancesC)
{
    NODE* newNode = new NODE;
    newNode->appearancesCounter = appearancesC;
    newNode->next_NODE = nullptr;
    newNode->previous_NODE = nullptr;
    newNode->VECTRIPLE = nullptr;
    
    return newNode;
}


NODE* PriorityQ::addNode(unsigned appearancesC, int bucket) {
    if (bucket < 0 || bucket >= queueVectorSize) return nullptr;

    NODE* node = createNode(appearancesC);
    if (!node) return nullptr;

    node->next_NODE = queueVector[bucket]->head->next_NODE;
    node->previous_NODE = queueVector[bucket]->head;

    queueVector[bucket]->head->next_NODE->previous_NODE = node;
    queueVector[bucket]->head->next_NODE = node;
    
    incrementNodeOnBucket(&node);
    
    return node;
}


int PriorityQ::incrementNodeOnBucket(NODE** node) {
    if (!node || !*node || (*node)->appearancesCounter == -1) return -1;

    NODE* current = *node;
    NODE* temp = current;

    while (temp->next_NODE && current->appearancesCounter > temp->next_NODE->appearancesCounter) {
        temp = temp->next_NODE;
    }

    if (temp == current) return 0; 

    current->previous_NODE->next_NODE = current->next_NODE;
    current->next_NODE->previous_NODE = current->previous_NODE;

    current->next_NODE = temp->next_NODE;
    current->previous_NODE = temp;

    temp->next_NODE->previous_NODE = current;
    temp->next_NODE = current;

    return 0;
}



int PriorityQ::removeNode(NODE** node)
{
        if (!node || !*node) return -1;
    
        if (*node == (*node)->next_NODE) return -2; 

        (*node)->previous_NODE->next_NODE = (*node)->next_NODE;
        (*node)->next_NODE->previous_NODE = (*node)->previous_NODE;
    
        delete (*node)->VECTRIPLE;
        delete *node;
    
        return 0;

}

int PriorityQ::changeBucket(NODE** node) {
    if (!node || !*node || (*node)->appearancesCounter == -1) return -1;

    unsigned newBucket = std::min((*node)->appearancesCounter, queueVectorSize - 1);
    
    if ((queueVector[newBucket]->head->appearancesCounter == (*node)->appearancesCounter || (*node)->appearancesCounter >= queueVectorSize - 1))
    {    
        return 0;
    }

    (*node)->previous_NODE->next_NODE = (*node)->next_NODE;
    (*node)->next_NODE->previous_NODE = (*node)->previous_NODE;

    (*node)->next_NODE = queueVector[newBucket]->head->next_NODE;
    (*node)->previous_NODE = queueVector[newBucket]->head;
    if(queueVector[newBucket]->head->next_NODE)
    {
        queueVector[newBucket]->head->next_NODE->previous_NODE = *node;
    }
    queueVector[newBucket]->head->next_NODE = *node;

    return 0;
}

int PriorityQ::printLL(int bucket) {
    if (bucket < 0 || bucket >= static_cast<int>(queueVectorSize)) {
        std::cout << "Bucket inválido: " << bucket << std::endl;
        return -1;
    }

    LINKEDLIST* list = queueVector[bucket];
    NODE* curr = list->head->next_NODE;

    std::cout << "Bucket [" << bucket << "]: ";

    if (curr == nullptr) {
        std::cout << "[vazia]" << std::endl;
        return 0;
    }

    while (curr != nullptr && curr->appearancesCounter != -1) {
        std::cout << curr->appearancesCounter << " ";
        curr = curr->next_NODE;
    }

    std::cout << std::endl;
    return 0;
}






//------------------------------------------------x------------------------------------------------//
//                                           String Array


VECT* stringArray::createVecTriple(char symbolString)
{
    VECT* vectTriple = new VECT;

    vectTriple->symbol=symbolString;
    vectTriple->next = nullptr;
    vectTriple->previous = nullptr;

    return vectTriple;
}

