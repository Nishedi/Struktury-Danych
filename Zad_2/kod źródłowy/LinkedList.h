#pragma once
#include "Kopiec.h"
#include <iostream>
class ElemList {
public:
    ElemList* next, * prev, * reversed;
    Edge edge;

    ElemList(Edge edge) {
        this->edge = edge;
        this->next = NULL;
        this->prev = NULL;
        this->reversed = NULL;
    }
};

class LinkedList
{
public:
    ElemList* head;
    ElemList* tail;
    int counter;

    LinkedList() {
        head = NULL;
        tail = NULL;
        counter = 0;
    }

    void showList();

    void addFirst(Edge edge); //dodanie w pierwsze miejsce

    ElemList* elementAt(int position);

    

    void deleteFirst();

    void clear();

};;

