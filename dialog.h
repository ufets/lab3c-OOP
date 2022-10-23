#include <iostream>
#include "PCB.h"

///RESULTS(enum)
namespace R{
    enum RESULTS{
        ///exit from dialog
        EXIT,
        ///back to menu
        RESUME,
        ///back to menu
        INPUT_ERROR
    };
}

///DIALOG
namespace D{
    template <class T>
    int getValue(T &a) {
        while(true) {
            std::cin >> a;
            if (!std::cin.good()) {
                std::cin.clear(); //перевести поток cin в прежнее состояние
                std::cin.sync(); //очистка буфера
                std::cout<<"\nInvalid value\n";
            }
            else return R::RESUME;
        }
    }

    void Menu(PCB& pcb);
    unsigned int Dialog(const char* msgs[], int num_msgs);
    int PRINT(PCB& pcb);
    int ADD(PCB& pcb);
    int ADD_LINK(PCB& pcb);
    int FIND_GROUP(PCB& pcb);
    int DISTANCE(PCB& pcb);
}
