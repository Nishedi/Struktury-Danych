#pragma once
#include <iostream>
#include "Table.h"

#include "Timer.h"
class TableMenu
{
public:
    Timer timer;
    Table* table;
    TableMenu(){
        this->table = new Table();
    }
    ~TableMenu(){
        delete(table);
    }

    void clear(Table* table);

    void tabControll(int x);
   
};

