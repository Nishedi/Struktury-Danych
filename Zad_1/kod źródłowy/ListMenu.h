#pragma once
#include <iostream>
#include "LinkedList.h"
#include "Timer.h"
#include "Timer.h"
class ListMenu
{
public:
    LinkedList* list;
    Timer timer;
	ListMenu() {
        list = new LinkedList();
	}

    ~ListMenu() {
        delete(list);
    }

    void listControll(int x);

};

