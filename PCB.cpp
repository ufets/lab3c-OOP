#include "PCB.h"
#include <cmath>
#include <cassert>

//CONTACTS

//setters
Contact& Contact::set_type(Type type_) {
    this -> type = type_;
    return *this;
}
Contact& Contact::set_x(int x_) {
    this -> x = x_;
    return *this;
}
Contact& Contact::set_y(int y_) {
    this -> y = y_;
    return *this;
}
Contact& Contact::set_num(int num_) {
    this -> num = num_;
    return *this;
}

//getters
Type Contact::get_type() const {
    return this -> type;
}
int Contact::get_x() const {
    return this -> x;
}
int Contact::get_y() const {
    return this -> y;
}
int Contact::get_num() const {
    return this -> num;
}

std::ostream &operator<<(std::ostream &os, const Contact &contact) {
    os << "{ " << contact.get_type() << ", (" << contact.get_x() << ';' << contact.get_y()
       << "), " << contact.get_num() << "}\n";
    return os;
}

//constructor

PCB::PCB(int value) {
    if (value < 0){
        throw std::invalid_argument("Size cannot be below zero!\n");
    }
    try{
        size = value;
        contacts = new Contact[value];
        for(int i = 0; i < value; i++){

            contacts[i].set_type(EMPTY);
            contacts[i].set_x(0);
            contacts[i].set_y(0);
            contacts[i].set_num(-1);
        }
    }
    catch(std:: bad_alloc& ex){
        std::cout<<ex.what();
    }
}

PCB::~PCB() {
    if (size!=0)
        delete[] contacts;
}


//PCB setters
PCB& PCB::set_type(int i, Type type) {
    if( i < 0 || i >= size){
        throw std::invalid_argument("Invalid index!\n");
    }
    contacts[i].set_type(type);
    return *this;
}
PCB& PCB::set_x(int i, int x){
    if( i < 0 || i >= size){
        throw std::invalid_argument("Invalid index!\n");
    }
    contacts[i].set_x(x);
    return *this;
}
PCB& PCB::set_y(int i, int y){
    if( i < 0 || i >= size){
        throw std::invalid_argument("Invalid index!\n");
    }
    contacts[i].set_y(y);
    return *this;
}
PCB& PCB::set_num(int i, int num) {
    if( i < 0 || i >= size){
        throw std::invalid_argument("Invalid index!\n");
    }
    if(num < 0 || num >= size || num==i)
        throw std::invalid_argument("Invalid values!");
    contacts[i].set_num(num);
    return *this;
}

//PCB getters
int PCB::get_size() const{
    return size;
}
Type PCB::get_type(int i) const {
    if( i < 0 || i >= size){
        throw std::invalid_argument("Invalid index!\n");
    }
    return contacts[i].get_type();
}
int PCB::get_x(int i) const {
    if( i < 0 || i >= size){
        throw std::invalid_argument("Invalid index!\n");
    }
    return contacts[i].get_x();
}
int PCB::get_y(int i) const {
    if( i < 0 || i >= size){
        throw std::invalid_argument("Invalid index!\n");
    }
    return contacts[i].get_y();
}
int PCB::get_num(int i) const {
    if( i < 0 || i >= size){
        throw std::invalid_argument("Invalid index!\n");
    }
    return contacts[i].get_num();
}

//methods
/**To add a contact to the PCB
 * \param i - index from array
 * \param type - 'i' - input, 'o' - output
 * \param x - x coordinate
 * \param y - y coordinate
 */
void PCB::add_contact(Type type, int x, int y) {

    //проверяем, чтобы не было совпадений по координатам, и есть ли свободные ячейки ещё
    int i = 0;
    int flag = 0;
    while(i < size){
        if (contacts[i].get_type() == EMPTY){
            flag++;
            break;
        }
        if(contacts[i].get_x() == x && contacts[i].get_y() == y){
            throw std::invalid_argument("PCB already has contact on this dot");
        }
        i++;
    }
    if (flag != 0){                             //есть пустые ячейки в массиве
        contacts[i].set_type(type);
        contacts[i].set_x(x);
        contacts[i].set_y(y);
    }
    else{                                       //нет пустых, делаем массив в два раза больше
        try {
            Contact* new_array = new Contact[2 * size];
            std::copy(contacts, contacts + size, new_array);
            printf("\nnew array = %p\ncontacts = %p\n", new_array, contacts);
            new_array[size].set_type(type);
            new_array[size].set_x(x);
            new_array[size].set_y(y);
            delete[] contacts;
            contacts = new_array;
            size = 2 * size;
        }
        catch(std:: bad_alloc& ex)
        {
            std::cout<<ex.what()<<std::endl;
        }
    }

}


/**To add a contact to the PCB
 * \param i - index from array
 * \param type - 'i' - input, 'o' - output
 * \param x - x coordinate
 * \param y - y coordinate
 * \param num - the index of linked contact
*/
void PCB::add_contact(Type type, int x, int y, int num) {
    int i = 0;
    int flag = 0;
    while(i < size){
        if (contacts[i].get_type() == EMPTY){
            flag++;
            break;
        }
        if(contacts[i].get_x() == x && contacts[i].get_y() == y){
            throw std::invalid_argument("PCB already has contact on this dot");
        }
        i++;
    }
    if (flag != 0){                             //есть пустые ячейки в массиве
        contacts[i].set_type(type);
        contacts[i].set_x(x);
        contacts[i].set_y(y);
        contacts[i].set_num(num);
    }
    else{                                      //нет пустых, делаем массив в два раза больше
        try {
            Contact* new_array = new Contact[2 * size];
            std::copy(contacts, contacts + size, new_array);
            new_array[size].set_type(type);
            new_array[size].set_x(x);
            new_array[size].set_y(y);
            contacts[i].set_num(num);
            Contact *tmp = contacts;
            delete tmp;
            contacts = new_array;
        }
        catch(std:: bad_alloc& ex)
        {
            std::cout<<ex.what()<<std::endl;
        }
    }

}


/**To add the way between two contacts
 * \param i - index of the input contact
 * \param num - index of the output contact
*/
void PCB::add_way(int i, int num) {
    if (i<0 || num <0 || i >=size || num >= size)
    {
        throw std::invalid_argument("Invalid indexes!");
    }
    if (contacts[i].get_type() != INPUT || contacts[num].get_type() != OUTPUT)
    {
        throw std::invalid_argument("One of contacts does not exists");
    }
    contacts[i].set_num(num);
    contacts[num].set_num(i);
}


/**\n To find the group by type
 * \param type - type of contact('i' - input, 'o' - output)
*/
void PCB::find_group(char type, PCB& newpcb) const {
    int t;
    if (type == 'e')
    {
        t = 0;
    }
    else if (type == 'i')
    {
        t = 1;
    }
    else
        t = 2;
    for(int i = 0; i < size; i++)
    {
        if (contacts[i].get_type() == t)
        {
            newpcb+=contacts[i];
        }
    }
}


/**\n To find the group by x or y
 * \param axis - 'x' - OX, 'y' - OY
 * \param coordinate - the dot on axis
*/
void PCB::find_group(char axis, int coordinate, PCB& newpcb) const {
    if(axis == 'x')
    {
        for(int i = 0; i < size; i++)
        {
            if (contacts[i].get_type() != 0 && contacts[i].get_x() == coordinate)
            {
                newpcb+=contacts[i];
            }
        }
    }
    else{
        for(int i = 0; i < size; i++)
        {
            if (contacts[i].get_type() != 0 && contacts[i].get_y() == coordinate)
            {
                newpcb+=contacts[i];
            }
        }
    }
}


/**Distance between two contacts
 * \param i - index of the first contact
 * \param j - index of the second contact
*/
double PCB::distance(int i, int j) const{
    return sqrt((contacts[i].get_x() - contacts[j].get_x())^2 - (contacts[i].get_y() - contacts[j].get_y())^2);
}

//OPERATORS
//operators

std::ostream& operator<<(std::ostream& os, const PCB& pcb){
    for (int i = 0; i < pcb.get_size(); i++)
        os << "contacts[" << i << "] = "<< pcb.contacts[i];
    return os;
}


Contact& PCB::operator[](int i){
    return contacts[i];
}

/** () returns the array of contacts with indexes from "begin" to end */
PCB PCB::operator()(int begin, int end) const {
    PCB newpcb(0);
    assert(0 <= begin && begin <= end && end <= size);

    int count = begin;
    for(int i = 0; i <= end - begin; i++)
    {
        newpcb += contacts[count];
        count++;
    }
    return newpcb;
}

///PCB += Contact

PCB& PCB::operator+=(const Contact& contact) {
    int i = 0;
    while (contacts[i].get_type() != 0 && i < size){
        i++;
    }
    if(i >= size)
    {
        throw std::invalid_argument("PCB could be overloaded!\n");
    }
    add_contact(contact.get_type(), contact.get_x(), contact.get_y(), contact.get_num());
    return *this;
}

///PCB += PCB
PCB& PCB::operator+=(const PCB& pcb) {
    int count1 = 0, count2 = 0;
    for(int i = 0; i < size; i++){
        if(pcb.contacts[i].get_type() != 0)
        {
            count2++;
        }
        if(contacts[i].get_type() != 0)
        {
            count1++;
        }
    }

    if(count1 + count2 > size){
        throw std::invalid_argument("PCB could be overloaded!");
    }

    for(int j = 0; j < count2; j++)
    {
        *this += pcb.contacts[j];
    }
    return *this;
}

///PCB + PCB
PCB PCB::operator+(const PCB& pcb_right) const {
    PCB result(0);
    result = *this;
    return result+=pcb_right;
}

///PCB + Contact
PCB PCB::operator+(const Contact &c_right) const {
    PCB result(0);
    result = *this;
    return result +=c_right;
}

///Contact + PCB

PCB operator+(const Contact& c_left, const PCB& pcb_right ){
    PCB result(0);
    result += c_left;
    result += pcb_right;
    return result;
}




//contact + contact = pcb