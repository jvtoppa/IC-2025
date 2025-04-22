#include "dataStructures.h"
#include <math.h>
#include <list>
#include <memory>
#include <iostream>


LINKEDLIST* PriorityQ::createLL(void)
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
    newNode->next_NODE = newNode;
    newNode->previous_NODE = newNode;
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
    
    //incrementNodeOnBucket(&node);
    
    return node;
}


int PriorityQ::incrementNodeOnBucket(NODE** node) {
    if (!node || !*node || (*node)->appearancesCounter == -1) return -1;

    while ((*node)->next_NODE->appearancesCounter != -1 && (*node)->appearancesCounter > (*node)->next_NODE->appearancesCounter) {
        
        NODE* temp = *node;
        NODE* nextNode = temp->next_NODE;

        temp->previous_NODE->next_NODE = nextNode;
        nextNode->next_NODE->previous_NODE = temp;
        
        temp->next_NODE = nextNode->next_NODE;
        nextNode->previous_NODE = temp->previous_NODE;
        nextNode->next_NODE = temp;
        temp->previous_NODE = nextNode;

        *node = nextNode;
    }
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
    
    // Verifica se já está no bucket correto
    if ((*node)->previous_NODE->appearancesCounter == -1 && 
        (*node)->next_NODE->appearancesCounter == -1 && 
        queueVector[newBucket]->head->next_NODE == *node || queueVector[newBucket]->head->next_NODE->appearancesCounter > queueVectorSize)
    {    
        return 0;
    }

    // Remove da lista atual
    (*node)->previous_NODE->next_NODE = (*node)->next_NODE;
    (*node)->next_NODE->previous_NODE = (*node)->previous_NODE;

    (*node)->next_NODE = queueVector[newBucket]->head->next_NODE;
    (*node)->previous_NODE = queueVector[newBucket]->head;
    queueVector[newBucket]->head->next_NODE->previous_NODE = *node;
    queueVector[newBucket]->head->next_NODE = *node;

    return 0;
}

int PriorityQ::printLL(int Pos) {
    if (Pos < 0 || Pos >= static_cast<int>(queueVectorSize)) {
        std::cout << "Bucket inválido: " << Pos << std::endl;
        return -1;
    }

    LINKEDLIST* list = queueVector[Pos];
    NODE* curr = list->head->next_NODE;

    std::cout << "Bucket [" << Pos << "]: ";

    if (curr == list->head) {
        std::cout << "[vazia]" << std::endl;
        return 0;
    }

    while (curr != list->head) {
        std::cout << curr->appearancesCounter << " ";
        curr = curr->next_NODE;
    }

    std::cout << std::endl;
    return 0;
}
