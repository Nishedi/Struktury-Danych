#pragma once
#include "RB.h"
#include "Timer.h"
#include <fstream>
class RBMenu {
public:
	RB* rb = new RB();
	void deletetree();

	int checker(int tab[], int size, int value);

	void preparetable(int n, int tab[]);

	void rbControllerWithTimer(int x);
};