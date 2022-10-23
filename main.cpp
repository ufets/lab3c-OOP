#include <iostream>
#include "dialog.h"
#include "PCB.h"

//LAB3B

int main() {
    setlocale( LC_ALL,"Russian" );
    std::cout << "Welcome to the lab3" << std::endl;
    PCB pcb(1);
    D::Menu(pcb);
    return 0;
}
