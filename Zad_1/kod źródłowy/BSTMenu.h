#pragma once
#include <iostream>
#include "BST.h"
#include "Timer.h"
#include <fstream>
class BSTMenu
{
public:
	BST* rb;
	BSTMenu() {
		rb = new BST();
	}
	~BSTMenu() {
		delete(rb);
	}

	void deletetree();

	int checker(int tab[], int size, int value);

	void preparetable(int n, int tab[]);

	void bstControllerWithTimer(int x);
};

