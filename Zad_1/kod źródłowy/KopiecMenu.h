#pragma once
#include "Kopiec.h"
#include "Timer.h"
class KopiecMenu
{
public:
	Kopiec * kopiec = NULL;
	Timer timer;
	KopiecMenu() {
		kopiec = new Kopiec();
	}

	~KopiecMenu() {
		delete(kopiec);
	}

	void kopiecController(int x);
};

