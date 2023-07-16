#include "BSTStraight.h"
void BSTStraight::addToTree(int value) {
    if (value <= 0) {
        std::cout << "Liczba musi byc wieksza od 0\n";
        return;
    }
    if (findInTree(head, value) != NULL) {
        return;
    }
    Element* el = new Element;
    el->value = value;
    el->right = NULL;
    el->left = NULL;
    el->parent = NULL;
    if (head == NULL) {
        head = el;
        counter++;
        return;
    }
    checkwheretogo(head, el);
    counter++;
    make();
}


void BSTStraight::make() {
    if (head != NULL) {
        makestraight(head);
        DSW();
    }

}

