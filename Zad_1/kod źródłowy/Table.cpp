#include "Table.h"

void Table::resize(int newsize) {
    int* tab = this->tab;
    this->tab = new int[newsize];
    if (newsize < counter)counter = newsize;
    for (int i = 0; i < counter; i++) {
        this->tab[i]=tab[i];
    }
    delete(tab);
    
}

void Table::showTab() {
    for (int i = 0; i < counter; i++) {
        std::cout <<"|" << tab[i];
    }
    std::cout << "|\n";
}

void Table::showTabReversed() {
    for (int i = counter - 1; i >= 0; i--) {
        std::cout << "|" << tab[i];
    }
    std::cout << "|\n";
}




int Table::lenght() {
    return counter;
}

int Table::findElem(int value) {
    for (int i = 0; i < counter; i++) {
        if (tab[i] == value) return i;
    }
    return -1;
}

int Table::elementAt(int position) {
    if (position >= counter) return -1;
    return(tab[position]);
}

void Table::addFirst(int value) //dodanie w pierwsze miejsce
{
    insert(value, 0);
}

void Table::addLast(int value) {//dodawnie w ostatnie miejsce
    insert(value, counter);
}

void Table::insert(int value, int position) {
    resize(counter + 1);
    if (position < 0 || position > counter) return;

    for (int i = counter - 1; i >= position; i--) {
        tab[i + 1] = tab[i];
    }
    tab[position] = value;
    counter++;
} //dodanie w losowe miejsce

void Table::deleteFirst() {
    deleteAt(0);
}

void Table::deleteLast() {
    deleteAt(counter - 1);
}

void Table::deleteAt(int position) {
    if (position < 0 || position >= counter) return;
    for (int i = position; i < counter; i++) {
        tab[i] = tab[i + 1];
    }
    counter--;
    resize(counter);
}

void Table::clear() {
    while (counter > 0) {
        deleteLast();
    }
}