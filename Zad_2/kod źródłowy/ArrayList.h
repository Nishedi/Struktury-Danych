#pragma once
#include <iostream>
class ElemListA {
public:
    int value;
    ElemListA* next, * prev;

    ElemListA(int value) {
        this->value = value;
        this->next = NULL;
        this->prev = NULL;
    }
};
class ArrayList 
{
public:
    ElemListA* head;
    ElemListA* tail;
    int counter;

    ArrayList() {
        head = NULL;
        tail = NULL;
        counter = 0;
    }

    void showList();

    void showListReversed();

    void addFirst(int value); //dodanie w pierwsze miejsce

    void addLast(int value);//dodawnie w ostatnie miejsce


    int lenght();

    ElemListA* findElement(int value);

    int findElem(int value);

    ElemListA* elementAt(int position);

    void insert(int value, int position); //dodanie w losowe miejsce

    void deleteFirst();

    void deleteLast();

    void deleteAt(int position);

    void deleteValue(int value);

    void clear();

    void deleteNode(ElemListA* el);

};;

#pragma once
