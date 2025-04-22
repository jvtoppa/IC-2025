#include <iostream>
#include "dataStructures.h"

int main()
{
    PriorityQ pq(100); // 10 buckets (sqrt(100))

    NODE* A = pq.addNode(10, 9);
    //pq.incrementNodeOnBucket(&A);
    NODE* B = pq.addNode(3, 3);
    //pq.incrementNodeOnBucket(&B);
    NODE* C = pq.addNode(10, 9);
    //pq.incrementNodeOnBucket(&C);
    NODE* D = pq.addNode(5, 5);
    //pq.incrementNodeOnBucket(&D);
    NODE* E = pq.addNode(200, 9);
    //pq.incrementNodeOnBucket(&E);
    pq.changeBucket(&E);
    pq.changeBucket(&A);

    std::cout << "Estado inicial:\n";
    for(int i = 0; i < 10; i++)
    {

        pq.printLL(i);
    }
    
    //pq.changeBucket(&A);
    //pq.changeBucket(&B);
    //pq.changeBucket(&C);
    //pq.changeBucket(&D);
    //pq.changeBucket(&E);
    //pq.incrementNodeOnBucket(&A);
    //pq.incrementNodeOnBucket(&B);
    //pq.incrementNodeOnBucket(&C);
    //pq.incrementNodeOnBucket(&D);
    //pq.incrementNodeOnBucket(&E);


    std::cout << "Estado Final:\n";
    for(int i = 0; i < 10; i++)
    {

        pq.printLL(i);
    }
return 0;
}
