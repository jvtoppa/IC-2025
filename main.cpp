    #include <iostream>
    #include "dataStructures.h"
    #include <time.h>

    int main()
    {
        PriorityQ pq3(100);

        for (int i = 0; i < 5; i++) {
            int randomValue = std::rand() % 100000 + 10;
            pq3.addNode(randomValue, 9);
        }
    
        pq3.printLL(9);  


        //----------------------------------x-------------------------------------------------//
        std::string teste;
        getline(std::cin, teste);
        stringArray sa(teste.size(), teste);
    
        std::cout << "String original: " << sa.getString() << "\n";
        std::cout << "Símbolos armazenados:\n";
    
        VECT** stringComplete = sa.getVectorizedString();

        for (unsigned i = 0; i < teste.size(); i++) {
            if(stringComplete[i]->previous == nullptr)
            {
                std::cout << "[-";
            }
            std::cout << stringComplete[i]->symbol;
            if(stringComplete[i]->next == nullptr)
            {
                std::cout << "-] ";
            }
        }
        std::cout << std::endl;
    
    return 0;

    
    }
