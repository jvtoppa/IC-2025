#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <vector>
#include <list>
#include <memory>
#include <math.h>

struct VECT
{
    int symbol;
    VECT* next;
    VECT* previous;
};

struct NODE
{
    unsigned appearancesCounter;
    VECT* VECTRIPLE;
    NODE* next_NODE;
    NODE* previous_NODE;
};

struct LINKEDLIST
{
    NODE* head;
};

class PriorityQ
{

private:

    unsigned stringSize;
    unsigned queueVectorSize;
    
public:

    //Constructor
    PriorityQ(unsigned stringSize) : stringSize(stringSize)
    {
        
        queueVectorSize = floor(sqrt(stringSize));
        queueVector = new LINKEDLIST*[queueVectorSize]();
        
        
        for(unsigned i = 0; i < queueVectorSize; i++)
        {
            queueVector[i] = createLL();
        }
    
    }

    //Destructor
    ~PriorityQ() {
        for(unsigned i = 0; i < queueVectorSize; i++)
        {
            if(queueVector[i] != nullptr)
            {
                NODE* curr = queueVector[i]->head->next_NODE;
                NODE* sentinel = queueVector[i]->head;
                
                for(NODE* next; curr != sentinel; curr = next)
                {
                    next = curr->next_NODE;
                    delete curr;
                }
                
                delete sentinel;
                delete queueVector[i];
            }
         
        }
        delete[] queueVector;
    }
    
    
    //Functions
    LINKEDLIST* createLL(void);
    NODE* createNode(unsigned appearancesC);
    NODE* addNode(unsigned appearancesC, int pos);
    int removeNode(NODE** node);
    int changeBucket(NODE** node);
    int incrementNodeOnBucket(NODE** node);
    int printLL(int Pos); //[DEBUG]
    LINKEDLIST** queueVector;

};

#endif