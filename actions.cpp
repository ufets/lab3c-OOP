#include "actions.h"
#include "dialog.h"

///тут у нас разные проверки, если норм всё, кидаем в метод
void add(PCB& pcb, char type, int x, int y){
    //если места нет
    if (pcb.get_type(pcb.get_size() - 1) != 0)
    {
        throw std::invalid_argument("No free place!");
    }

    //проверяем, чтобы не было совпадений по координатам
    int i = 0;
    while(pcb.get_type(i) != 0)
    {
        if(pcb.get_x(i) == x && pcb.get_y(i) == y)
        {
            throw std::invalid_argument("PCB already has contact on this dot");
        }
        i++;
    }
    std::cout<<"\nNumber of the new contact is "<<i<<std::endl;
    pcb.add_contact(i, type, x, y);
}



