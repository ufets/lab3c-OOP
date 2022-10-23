#include <iostream>
#include <typeinfo>

#pragma once
///type of contact
enum Type{
    EMPTY,
    INPUT,
    OUTPUT
};
///The Contact on PCB
typedef struct Contact{
private:
    ///Input/Output
    Type type;
    ///Coordinate X
    int x;
    ///Coordinate Y
    int y;
    ///Linked contact
    int num;
public:
    Contact ()
    {
        this -> type = EMPTY;
        this -> x = 0;
        this -> y = 0;
        this -> num = -1;
    }
    explicit Contact(Type type) {
        this -> type = type;
        this -> x = 0;
        this -> y = 0;
        this -> num = -1;
    };
    Contact(Type type, int x): Contact(type) {
        this -> x = x;
    }
    Contact(Type type, int x, int y): Contact(type, x){
        this -> y = y;
    }
    Contact(Type type, int x, int y, int num): Contact(type, x, y){
        this -> num = num;
    }

    Contact& set_type(Type type);
    Contact& set_x(int x);
    Contact& set_y(int y);
    Contact& set_num(int y);

    Type get_type() const;
    int get_x() const;
    int get_y() const;
    int get_num() const;

    friend std::ostream& operator<<(std::ostream& os, const Contact& contact);

}Contact;


/**Печатная плата (PCB или printed wiring board) — пластина из диэлектрика,
 * \n на поверхности и/или в объёме которой сформированы электропроводящие цепи электронной схемы.
 * \n Печатная плата предназначена для электрического и механического соединения электронных компонентов
 * \param size - size of contacts array
 * \param contacts - array of contacts
*/
class PCB{
private:
    int size;
    Contact* contacts;
public:
    explicit PCB(int size);
    ~PCB();
    PCB& set_type(int i, Type type); // i - index
    PCB& set_x(int i, int x);
    PCB& set_y(int i, int y);
    PCB& set_num(int i, int y);

    int get_size() const;
    Type get_type(int i) const;
    int get_x(int i) const;
    int get_y(int i) const;
    int get_num(int i) const;

    void add_contact(Type type, int x, int y);
    void add_contact(Type type, int x, int y, int num);
    void add_way(int i, int num);
    void find_group(char type, PCB& newpcb) const;
    void find_group(char axis, int coordinate, PCB& newpcb) const;
    double distance(int i, int j) const;

    friend std::ostream& operator<<(std::ostream& os, const PCB& pcb);

    Contact& operator[](int i);
    PCB operator()(int begin, int end) const;
    PCB& operator+=(const Contact& contact);
    PCB& operator+=(const PCB& pcb);
    PCB operator+(const PCB& pcb_right) const;
    PCB operator+(const Contact& c_right) const;
    friend PCB operator+(const Contact& c_left, const PCB& pcb_right );

};


