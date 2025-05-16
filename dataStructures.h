#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H
#define INVALID_SYMBOL  10000
#include <unordered_set>
#include <math.h>
#include <string>
#include <iostream>
#include <vector>
#include <climits>

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
        
        queueVectorSize = ceil(sqrt(stringSize));
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

    //Creates each of the linked lists. Function to be used only in the constructor
    LINKEDLIST* createLL();
    //Creates a node. Auxiiary function for addNode()
    NODE* createNode(unsigned appearancesC);
    //Adds a node to the priorityQ and orders it (insertion sort)
    NODE* addNode(unsigned appearancesC);
    //Removes a node from the priorityQ (/!\ not tested yet!)
    int removeNode(NODE* node);
    //Changes a node to its correct bucket
    int changeBucket(NODE* node);
    //Auxiliary function for addNode()
    int insertionSortNode(NODE** node);
    //[DEBUG] prints the linked list
    int printLL(int Pos);
    void printAll();
    LINKEDLIST** queueVector;

};

class stringArray
{
private:

    unsigned stringSize;
    std::string mainString;
    VECT* stringVector;

public:

    //Constructor
    stringArray(unsigned stringSize, std::string str = "") : stringSize(stringSize), mainString(str)
    {

        stringVector = new VECT[stringSize];
        for(int i = 0; i < stringSize; i++)
        {
            stringVector[i] = createVecTriple(str[i]);
        }
    }

    //Destructor
    ~stringArray()
    {
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

    unsigned getStringSize()
    {
        return stringSize;
    };

    VECT* getVectorizedString() const
    {
        return stringVector;
    };
    
    VECT createVecTriple(unsigned);

};

class PAIR
{
    public:
    
    unsigned symbol_LEFT;
    unsigned symbol_RIGHT;
    bool firstCheck;
    NODE* node;
    PAIR(unsigned symbol_LEFT, unsigned symbol_RIGHT) : symbol_LEFT(symbol_LEFT), symbol_RIGHT(symbol_RIGHT), firstCheck(0), node(nullptr) {}

    bool operator==(const PAIR& otherPAIR) const
    {
        return symbol_LEFT == otherPAIR.symbol_LEFT && symbol_RIGHT == otherPAIR.symbol_RIGHT;
    }
};

struct HASHPAIR
{
    std::size_t operator()(const PAIR& p) const 
    {
        return std::hash<int>()(p.symbol_LEFT) ^ (std::hash<int>()(p.symbol_RIGHT) << 1);
    }
};

class hashTablePair
{

    public:

    std::unordered_set<PAIR, HASHPAIR> table;

    hashTablePair() {}

    void updatePairFirstCheck(PAIR p, bool updater)
    {
        auto it = table.find(p);
        if (it != table.end()) 
        {
            PAIR pCopy = *it;
            pCopy.firstCheck = updater;
            table.erase(it);
            table.insert(pCopy);
        }
    }

    void printAll() 
    {
        for (const auto& p : table) 
        {
            std::cout << "{" <<static_cast<char>(p.symbol_LEFT) << ", "
             << static_cast<char>(p.symbol_RIGHT) << "}" << "bool:"
              << p.firstCheck << " ; Appearances: " << (this->getPairNode(p) ? this->getPairNode(p)->appearancesCounter : 1) << std::endl;
        }
    }
    bool pairInTable(PAIR p)
    {
        if(table.find(p) != table.end())
        {
            return true;
        }
        return false;
    }

    NODE* getPairNode(PAIR p)
    {
        auto it = table.find(p);
        if(it != table.end())
        {
            return it->node;
        }
        return nullptr;
    }

    void insertPair(PAIR p)
    {
        table.insert(p);
    }

    int getFirstCheck(PAIR p)
    {
        auto it = table.find(p);
        if(it != table.end())
        {
            return it->firstCheck; //IMPORTANT THIS IS TYPE BOOL
        }
        return -1;
    }

    int removeFromTable(PAIR p)
    {
        auto it = table.find(p);
        if(it != table.end())
        {
            table.erase(it);
            return 0;
        }
        return -1;
    }

    void pointTo(NODE* n, PAIR p)
    {
        auto it = table.find(p);
        if(it != table.end())
        {
            PAIR pCopy = *it;
            pCopy.node = n;
            table.erase(it);
            table.insert(pCopy);
        }
    }
};

class structureManager
{
    public:
    hashTablePair htp;
    PriorityQ pq;
    stringArray arr;

    structureManager(std::string str) : arr(str.size(), str), pq(str.size()) {}
    void insert(PAIR p);
    void countPairs();
    void linkArray();
    void decreaseAppearance(PAIR p);
    std::vector<VECT*> findAdjacents(VECT* vect);
    void decreaseAdjacents(VECT* vect);
    int replace(int variable, VECT* vect);
    void increaseNewPairs(VECT* vect);
    void iterativePairSubstitution(PAIR p, int);
};


#endif
