#pragma once
#include <iostream>
#include "TabTest.h"
class Table : public TabTest
{
public:

    int* tab;
    //int counter;

    Table() {
        tab = NULL;
        counter = 0;
    }

    void resize(int newsize);


    void showTab();

    void showTabReversed();

    void addFirst(int value); //dodanie w pierwsze miejsce

    void addLast(int value);//dodawnie w ostatnie miejsce

    void insert(int value, int position); //dodanie w losowe miejsce

    void deleteFirst();

    void deleteLast();

    void deleteAt(int position);

    int findElem(int value);
       
    int lenght();

    

    int elementAt(int position);

    

    

    void clear();
};

