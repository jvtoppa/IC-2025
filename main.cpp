#include <iostream>
#include <climits>
#include "dataStructures.h" 
#define INVALID_SYMBOL 10000

void printChain(const structureManager& manager) {
    std::cout << "Cadeia de triplas: ";
    VECT* current = manager.arr.getVectorizedString();
    VECT* also = current;
    while (current != also + 19) {
        std::cout << static_cast<char>(current->symbol) << " "; 
        current = current + 1; 
    }
    std::cout << "\n";
}

int main() {
    std::string testStr = "baazazababababzaza";
    structureManager manager(testStr); 

    manager.countPairs();  
    manager.linkArray();   


    std::cout << "Fila de Prioridade após countPairs() e linkArray():\n";
    manager.pq.printAll(); 
    printChain(manager);
    manager.htp.printAll();

    PAIR testPair('a', 'b');


    manager.iterativePairSubstitution(testPair, 'S');

    std::cout << "\nFila de Prioridade após substituição:\n";
    manager.pq.printAll(); 
    printChain(manager);  
    manager.htp.printAll();
 
    return 0;
}

