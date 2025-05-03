#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <vector>
#include <list>
#include <memory>
#include <math.h>
#include <string>

struct VECT
{
    char symbol;
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

struct PAIR
{
    int symbol_LEFT;
    int symbol_RIGHT;
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
    LINKEDLIST* createLL();
    NODE* createNode(unsigned appearancesC);
    NODE* addNode(unsigned appearancesC, int pos);
    int removeNode(NODE** node);
    int changeBucket(NODE** node);
    int incrementNodeOnBucket(NODE** node);
    int printLL(int Pos);
    LINKEDLIST** queueVector;

};

class stringArray
{
private:

    unsigned stringSize;
    std::string mainString;
    VECT** stringVector;

public:

    //Constructor
    stringArray(unsigned stringSize, std::string str = "") : stringSize(stringSize), mainString(str)
    {

        stringVector = new VECT*[stringSize]();
        for(int i = 0; i < stringSize; i++)
        {
            stringVector[i] = createVecTriple(str[i]);
        }
    }

    //Destructor
    ~stringArray()
    {
        for(int i = 0; i< stringSize; i++)
        {
            delete stringVector[i];
        }
        delete[] stringVector;
    }
    
    //Setter
    void setString(std::string mainStr)
    {
        mainString = mainStr;
    }
    
    //Getter
    std::string getString()
    {
        return mainString;
    };

    VECT** getVectorizedString()
    {
        return stringVector;
    };
    
    VECT* createVecTriple(char);
    PAIR link(PAIR pair);

};

#endif;
