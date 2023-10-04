#include "Kopiec.h"
#include <iostream>
void Kopiec::show() {
    for (int i = 0; i < counter; i++) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}

void Kopiec::add(int value) {
    tab[counter] = value;
    counter++;
    fixup(counter - 1);

}

void Kopiec::fixup(int index) {
    if (index == 0) return;
    int parent_pos = (index - 1) / 2;

    if (compare(index, parent_pos) == 0) {
        swap(index, parent_pos);
        fixup(parent_pos);
    }
}


int Kopiec::deleteRoot() {
    int toreturn = tab[0];
    swap(0, counter - 1);
    counter--;
    fixdown(0);
    return toreturn;
}

void Kopiec::fixdown(int parentindex) {
    int smallerchild_pos = 2 * parentindex + 1;
    if (smallerchild_pos >= counter) return;
    if (2 * parentindex + 2 < counter) {
        if (compare((2 * parentindex + 2), smallerchild_pos) == 0) {
            smallerchild_pos = 2 * parentindex + 2;
        }
    }

    if (compare(smallerchild_pos, parentindex) == 0) {
        swap(smallerchild_pos, parentindex);
        fixdown(smallerchild_pos);
    }
}

void Kopiec::clear() {
    counter = 0;
}