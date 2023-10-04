#include "Kopiec.h"

void Kopiec::show() {
    for (int i = 0; i < counter; i++) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}

void Kopiec::add(int value)  {
    tab[counter] = value;
    counter++;
    fixup(tab, counter - 1);
    
}



void Kopiec::visualisation(std::string cr, std::string cl, std::string cp, std::string sp, std::string sn, int index) {
    std::string s;
    if (tab[index]>0&&index<counter) {
        s = sp;
        if (sn == cr) s[s.length() - 2] = ' ';
        visualisation(cr, cl, cp, s + cp, cr, 2*index+2);

        s = s.substr(0, sp.length() - 2);
        std::cout << s << sn << tab[index] << std::endl;

        s = sp;
        if (sn == cl)s[s.length() - 2] = ' ';
        visualisation(cr, cl, cp, s + cp, cl, 2*index+1);
    }
}

void Kopiec::visualisation(std::string cr, std::string cl, std::string cp, std::string sp, std::string sn) {
    visualisation(cr, cl, cp, sp, sn, 0);
}

void Kopiec::create(int tab2[], int n) {
    for (int i = 0; i < n; i++) {
        add(tab2[i]);
    }
    counter = n;
    for (int i = (counter - 2) / 2; i >= 0; i--) {
        fixdown(tab, i);
    }
}

void Kopiec::fixup(int  numbers[], int index) {
    if (index == 0) return;
    int parent_pos = (index - 1) / 2;

    if (numbers[index] > numbers[parent_pos]) {
        int swap = numbers[parent_pos];
        numbers[parent_pos] = numbers[index];
        numbers[index] = swap;
        fixup(numbers, parent_pos);
    }
}

int Kopiec::findvalue(int value) {
    for (int i = 0; i < counter; i++) {
        if (tab[i] == value) return i;
    }
    return -1;
}

void Kopiec::deletevalue(int value) {//Tutaj
    int position = findvalue(value);
    if (position == NULL)return;
    tab[position] = tab[counter - 1];
    counter--;
    fixup(tab, position);
    fixdown(tab, position);
}

int Kopiec::deleteRoot() {
    int toreturn = tab[0];
    tab[0] = tab[counter - 1];
    counter--;
    fixdown(tab, 0);
    return toreturn;
}

void Kopiec::fixdown(int  numbers[], int parentindex) {
    int biggerchild_pos = 2 * parentindex + 1;
    if (biggerchild_pos >= counter) return;
    if (2 * parentindex + 2 < counter) {
        if (tab[biggerchild_pos] < tab[2 * parentindex + 2]) {
            biggerchild_pos = 2 * parentindex + 2;
        }
    }
    if (tab[biggerchild_pos] > tab[parentindex]) {
        int swap = tab[biggerchild_pos];
        tab[biggerchild_pos] = tab[parentindex];
        tab[parentindex] = swap;
        fixdown(numbers, biggerchild_pos);
    }
}

void Kopiec::clear() {
    counter = 0;
}

int Kopiec::rootElement() {
    return tab[0];
}