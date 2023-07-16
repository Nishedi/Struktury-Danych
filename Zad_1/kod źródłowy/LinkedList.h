#pragma once
#include <iostream>
#include "TabTest.h"
class ElemList {
public:
    int value;
    ElemList* next, * prev;

    ElemList(int value) {
        this->value = value;
        this->next = NULL;
        this->prev = NULL;
    }
};
class LinkedList : public TabTest
{
public:
    ElemList* head;
    ElemList* tail;
   // int counter;

    LinkedList() {
        head = NULL;
        tail = NULL;
        counter = 0;
    }

    void showList();

    void showListReversed();

    void addFirst(int value); //dodanie w pierwsze miejsce
    
    void addLast(int value);//dodawnie w ostatnie miejsce
       

    int lenght();

    ElemList* findElement(int value);

    int findElem(int value);

    ElemList* elementAt(int position);

    void insert(int value, int position); //dodanie w losowe miejsce

    void deleteFirst();

    void deleteLast();

    void deleteAt(int position);

    void deleteValue(int value);

    void clear();

    void deleteNode(ElemList* el);

};;

