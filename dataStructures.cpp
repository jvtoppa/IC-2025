#include "dataStructures.h"
#include <math.h>
#include <list>
#include <memory>
#include <iostream>
#include <vector>
#include <climits>

#define INVALID_SYMBOL  10000

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


NODE* PriorityQ::addNode(unsigned appearancesC) {
    
    unsigned bucket = std::min(queueVectorSize - 1, appearancesC);
    

    if (bucket < 0 || bucket >= queueVectorSize) return nullptr;

    NODE* node = createNode(appearancesC);
    if (!node) return nullptr;

    node->next_NODE = queueVector[bucket]->head->next_NODE;
    node->previous_NODE = queueVector[bucket]->head;

    queueVector[bucket]->head->next_NODE->previous_NODE = node;
    queueVector[bucket]->head->next_NODE = node;
    
    return node;
}

int PriorityQ::insertionSortNode(NODE** node) {
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



int PriorityQ::removeNode(NODE* node)
{
        if (!node || !node) return -1;
    
        if (node == node->next_NODE) return -2; 

        node->previous_NODE->next_NODE = node->next_NODE;
        node->next_NODE->previous_NODE = node->previous_NODE;
    
       // delete node->VECTRIPLE;
        delete node;
    
        return 0;

}

int PriorityQ::changeBucket(NODE* node) {
    if (!node || node->appearancesCounter < 2 || node->appearancesCounter == static_cast<unsigned>(-1)) return -1;

    unsigned tryBucket = node->appearancesCounter - 2;
    unsigned newBucket = std::min(tryBucket, queueVectorSize - 1);

    node->previous_NODE->next_NODE = node->next_NODE;
    node->next_NODE->previous_NODE = node->previous_NODE;

    node->next_NODE = queueVector[newBucket]->head->next_NODE;
    node->previous_NODE = queueVector[newBucket]->head;

    if (queueVector[newBucket]->head->next_NODE)
        queueVector[newBucket]->head->next_NODE->previous_NODE = node;

    queueVector[newBucket]->head->next_NODE = node;

    return 0;
}


int PriorityQ::printLL(int bucket) {
    if (bucket < 0 || bucket >= static_cast<int>(queueVectorSize)) {
        std::cout << "Bucket inválido: " << bucket << std::endl;
        return -1;
    }

    LINKEDLIST* list = queueVector[bucket];
    NODE* curr = list->head->next_NODE;

    std::cout << "Bucket [" << bucket + 2 << "]: ";

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

void PriorityQ::printAll()
{
    for(int i = 0; i < this->queueVectorSize; i++)
    {
        this->printLL(i);
    }
}




//------------------------------------------------x------------------------------------------------//
//                                           String Array


VECT stringArray::createVecTriple(unsigned symbolString)
{
    VECT vectTriple;
    vectTriple.symbol = symbolString;
    vectTriple.next = nullptr;
    vectTriple.previous = nullptr;
    return vectTriple;
}

//------------------------------------------------x------------------------------------------------//
//                                          Struct Manager

void structureManager::insert(PAIR p)
{
    
    if(!this->htp.pairInTable(p))
    {
        //std::cout << "not in table";
        this->htp.insertPair(p);
        return;
    }

    if(this->htp.getFirstCheck(p) == 0)
    {
        NODE* node = this->pq.addNode(1);
        this->htp.pointTo(node, p);
        this->htp.updatePairFirstCheck(p,true);
    }
    NODE* temp = this->htp.getPairNode(p);
    if(this->htp.getFirstCheck(p) == 1)
    {
        temp->appearancesCounter++;
        
    }
    this->pq.changeBucket(temp);
    this->pq.insertionSortNode(&temp); //FIXME: might be slow.....

}

void structureManager::countPairs()
{
    for (unsigned i = 0; i < arr.getStringSize() - 1;)
    {
        unsigned first = arr.getVectorizedString()[i].symbol;
        unsigned second = arr.getVectorizedString()[i + 1].symbol;

        PAIR pair(first, second);
        structureManager::insert(pair);

        if (i + 2 < arr.getStringSize() && arr.getVectorizedString()[i + 1].symbol == first && arr.getVectorizedString()[i + 2].symbol == second)
        {
            i += 2;
        }
        
        else
        {
            i++;
        }
    }
}

void structureManager::linkArray()
{
    for (unsigned i = 0; i < arr.getStringSize() - 1;)
    {
        VECT* first = &arr.getVectorizedString()[i];
        VECT* second = &arr.getVectorizedString()[i + 1];

        PAIR pair(first->symbol, second->symbol);
        NODE* node = htp.getPairNode(pair);

        if(node != nullptr)
        {
            if(node->VECTRIPLE == nullptr)
            {
                node->VECTRIPLE = first;
            }
            else
            {
                first->next = node->VECTRIPLE->next;
                node->VECTRIPLE->next = first;
            }
            
            first->previous = node->VECTRIPLE;

        }
        if (i + 2 < arr.getStringSize() && arr.getVectorizedString()[i + 1].symbol == first->symbol && arr.getVectorizedString()[i + 2].symbol == second->symbol)
        {
            i += 2;
        }
        
        else
        {
            i++;
        }
    }

}

void structureManager::decreaseAppearance(PAIR p)
{
    NODE* node = this->htp.getPairNode(p);
    if(node == nullptr)
    {
        if(this->htp.table.find(p) != this->htp.table.end())
        {
            htp.removeFromTable(p); //FIXME: might bug  
        }
        return;
    } 

    node->appearancesCounter--;
    
    if (node->appearancesCounter < 2)
    {
        //pq.removeNode(node); //FIXME: o problema está relacionado com a funçao de addpairs
        this->htp.updatePairFirstCheck(p, false);
        //htp.removeFromTable(p);
        return;
    }
  pq.changeBucket(node);
}

std::vector<VECT*> structureManager::findAdjacents(VECT* vect)
{
    std::vector<VECT*> adjacents;
    
    VECT* curr = vect;
    VECT* start = this->arr.getVectorizedString();
    VECT* previous = nullptr;
    
    if (curr > start)
    {
        previous = curr - 1;

        while (previous->symbol == INVALID_SYMBOL && previous > start)
        {
            previous--;
        }
        if (previous->symbol != INVALID_SYMBOL)
        {
            adjacents.push_back(previous);
            std::cout << adjacents[0]->symbol << ",";
        }
    }

    VECT* next = nullptr;
    
    if (curr + 2 < start + this->arr.getStringSize())
    {
        next = curr + 2;

        while (next->symbol == INVALID_SYMBOL && next < start + this->arr.getStringSize())
        {
            next++;
        }
        if (next->symbol != INVALID_SYMBOL)
        {
            adjacents.push_back(next);
            std::cout << adjacents[1]->symbol<< " ";
        }
    }
    
    return adjacents;
}

void structureManager::decreaseAdjacents(VECT* vect)
{
    std::vector<VECT*> adjacents;
    VECT* pairPtr = vect;
    adjacents = this->findAdjacents(pairPtr);
    int i = 0;

    if (i < adjacents.size() && adjacents[i])
    {
        PAIR pair_left(adjacents[i]->symbol, (adjacents[i] + 1)->symbol);
        decreaseAppearance(pair_left);
    }

    i++; 

    if (i < adjacents.size() && adjacents[i])
    {
        PAIR pair_right((adjacents[i] - 1)->symbol, adjacents[i]->symbol);
        decreaseAppearance(pair_right);
    }


}

int structureManager::replace(int variable, PAIR p)
{
    NODE* node = this->htp.getPairNode(p);
    if (!node || !node->VECTRIPLE) return 0;

    VECT* pairPtr = node->VECTRIPLE;
    VECT* base = this->arr.getVectorizedString();

    for (pairPtr; pairPtr != nullptr; pairPtr = pairPtr->next)
    {
        int idx = pairPtr - base;

        if (idx < 0 || idx + 1 >= (int)this->arr.getStringSize()) continue;

        if (base[idx].symbol == INVALID_SYMBOL || base[idx + 1].symbol == INVALID_SYMBOL)
        {
            continue;
        }

        int nextIdx = idx + 1;
        
        while (base[nextIdx].symbol == INVALID_SYMBOL && nextIdx < (int)this->arr.getStringSize())
        {
            nextIdx++;
        }

        base[idx].symbol = variable;           
        base[nextIdx].symbol = INVALID_SYMBOL;    
    }

    return variable;
}
/*
void structureManager::increaseNewPairs(int variable, PAIR p)
{
    VECT* base = this->arr.getVectorizedString();
    size_t size = this->arr.getStringSize();
    
    for (size_t i = 0; i < size;i++)
    {
        if (base[i].symbol == variable)  // é o novo símbolo
        {
            // Vizinho à esquerda
            int left = i - 1;
            while (left >= 0 && base[left].symbol == INVALID_SYMBOL) left--;
            
            if (left >= 0 && base[left].symbol != INVALID_SYMBOL)
            {
                PAIR leftPair(base[left].symbol, variable);
                insert(leftPair);
            }
            
            // Vizinho à direita
            int right = i + 1;
            while (right < (int)size && base[right].symbol == INVALID_SYMBOL) right++;
            
            if (right < (int)size && base[right].symbol != INVALID_SYMBOL)
            {
                PAIR rightPair(variable, base[right].symbol);
                insert(rightPair);
            }
            
        }
    }
}
*/
void structureManager::increaseNewPairs(PAIR p)
{
    VECT* vect = this->htp.getPairNode(p)->VECTRIPLE;
    VECT* vectCopy = vect;
    unsigned end = this->arr.getStringSize();
    VECT* start = this->arr.getVectorizedString();
    for (; vect != nullptr; vect = vect->next)
    {
        VECT* left = vect - 1;
        while (left >= start && left->symbol == INVALID_SYMBOL) left--;
        if (left >= start && left->symbol != INVALID_SYMBOL)
            {
                PAIR leftPair(left->symbol, vectCopy->symbol);
                insert(leftPair);
            }
        VECT* right = vect + 1;
        while (right <= (start + end) && right->symbol == INVALID_SYMBOL) right++;
        if (right <= (start + end) && right->symbol != INVALID_SYMBOL)
            {
                PAIR rightPair(vectCopy->symbol, right->symbol);
                insert(rightPair);
            }    
    }
    

}


void structureManager::iterativePairSubstitution(PAIR p, int substitutionVar) //depois refatora isso pelo amor de deus
{
    VECT* i = this->htp.getPairNode(p)->VECTRIPLE;
    for(i; i != nullptr; i = i->next)
    {
       this->decreaseAdjacents(i);
    }   
    this->replace(substitutionVar, p);
    this->increaseNewPairs(p);
    substitutionVar++;
}
//TODO: mudar o for ali em cima 


