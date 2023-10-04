#pragma once
#define MAXSIZE 2000001
#include <iostream>
#include "TREE.h"
class Kopiec : public TREE
{
    
    
public:
    int tab[MAXSIZE];
    int counter=0;
    Kopiec(){
        counter = 0;
    }

    ~Kopiec(){}

    void show();

    void add(int value);

    void visualisation(std::string cr, std::string cl, std::string cp, std::string sp, std::string sn);

    void visualisation(std::string cr, std::string cl, std::string cp, std::string sp, std::string sn, int index);

    void create(int tab2[], int n);

    void fixup(int  numbers[], int index);

    int findvalue(int value);

    void deletevalue(int value);

    int deleteRoot();

    void fixdown(int  numbers[], int parentindex);

    void clear();

    int rootElement();
};

