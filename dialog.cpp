#include <iostream>
#include "dialog.hpp"
#include "PCB.hpp"

void D::Menu(PCB& pcb)
{
    const char *msgs[] = {"0. Quit", "1. Print array", "2. Add contact", "3. Add link",
                             "4. Find group", "5. Calculate length of way between contacts"};
    const int num_msgs = sizeof(msgs) / sizeof(msgs[0]);
    int (*func[])(PCB&) = {nullptr, D::PRINT, D::ADD, D::ADD_LINK, D::FIND_GROUP, D::DISTANCE};
    unsigned int rc;
    while (rc = D::Dialog(msgs, num_msgs)) {
        if (func[rc](pcb) == R::EXIT) {
            break;
        }
    }
}

unsigned int D::Dialog(const char* msgs[], int num_msgs)
{
    unsigned int rc;
    std::cout<<"\n\n";
    for(int i = 0 ; i < num_msgs ; i++){
        std::cout<<"\n"<< msgs[i];
    }
    std::cout<<std::endl;
    do {
        D::getValue(rc);
        if ((rc >= 0) && (rc < num_msgs))
            return rc;
        std::cout<<"\nInvalid value!\n";
    }
    while(true);
}

///Добавление контакта на плату
int D::ADD(PCB& pcb)
{

    char type;
    std::cout<<"type('i'[input] or 'o'[output]) =";
    D::getValue(type);
    if(type != 'i' && type != 'o')
    {
        std::cout<<"Invalid value";
        return R::INPUT_ERROR;
    }

    int x;
    std::cout<<"x = ";
    D::getValue(x);
    int y;
    std::cout<<"y = ";
    D::getValue(y);
    try{
        if(type == 'i')
            pcb.add_contact(INPUT, x, y);
        else
            pcb.add_contact(OUTPUT, x, y);
    }
    catch(std::invalid_argument& inv){
        std::cout<<inv.what()<<"\nBack to menu...\n";
        return R::INPUT_ERROR;
    }
    return R::RESUME;

}

int D::ADD_LINK(PCB& pcb)
{
    int i;
    std::cout<<"number of input contact = ";
    D::getValue(i);
    std::cout<<std::endl;
    int num;
    std::cout<<"number of output contact = ";
    D::getValue(num);
    std::cout<<std::endl;

    try{
        pcb.add_way( i, num);
    }
    catch(std::invalid_argument& inv){
        std::cout<<inv.what()<<"\nBack to menu...\n";
        return R::INPUT_ERROR;
    }
    return R::RESUME;
}

int D::PRINT(PCB& pcb)
{
    std::cout << pcb;
    return R::RESUME;
}

int D::FIND_GROUP(PCB& pcb)
{
    std::string msgs[] = {"   0) Back", "   1) Find by type(input)", "   2) Find by type(output)", "   3) Find by x",
                          "   4) Find by y"};
    PCB newpcb(1);
    int mode;
    do{
        for(auto & msg : msgs){
            std::cout<<msg<<std::endl;
        }
        getValue(mode);
        if(mode == 0)
                break;
        if(mode == 1) {
            pcb.find_group('i', newpcb);
            break;
        }
        if(mode == 2) {
            pcb.find_group('o', newpcb);
            break;
        }
        if(mode == 3) {
            int x;
            std::cout<<"x = ";
            getValue(x);
            pcb.find_group('x', x, newpcb);
            break;
        }
        if(mode == 4) {
            int y;
            std::cout<<"y = ";
            getValue(y);
            pcb.find_group('y', y, newpcb);
            break;
        }
    }while(true);
    std::cout<<newpcb;
    return R::RESUME;
}

int D::DISTANCE(PCB& pcb)
{
    int i;
    std::cout<<"i = ";
    D::getValue(i);
    int j;
    std::cout<<"j = ";
    D::getValue(j);
    if((0 <= i < pcb.get_size()) && (0 <= j < pcb.get_size()) && pcb.get_type(i)!=0 && pcb.get_type(j) != 0)
        std::cout<<pcb.distance(i, j);
    else
    {
        std::cout<<"Invalid value!";
    }
    return R::RESUME;
}