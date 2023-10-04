#include "ArrayList.h"

void ArrayList::showList() {
    for (ElemListA* temp = head; temp != NULL; temp = temp->next) {
        std::cout << temp->value << " ";
    }
    std::cout << std::endl;
}

void ArrayList::showListReversed() {
    for (ElemListA* temp = tail; temp != NULL; temp = temp->prev) {
        std::cout << temp->value << " ";
    }
    std::cout << std::endl;
}

void ArrayList::addFirst(int value) //dodanie w pierwsze miejsce
{
    ElemListA* elem = new ElemListA(value);
    elem->next = head;
    elem->prev = NULL;
    if (head != NULL)
        head->prev = elem;
    head = elem;
    if (tail == NULL) {
        tail = elem;
    }
    counter++;
}

void ArrayList::addLast(int value) {//dodawnie w ostatnie miejsce
    ElemListA* elem = new ElemListA(value);
    elem->prev = tail;
    elem->next = NULL;
    if (tail != NULL)
        tail->next = elem;
    tail = elem;
    if (head == NULL) {
        head = elem;
    }
    counter++;
}

int ArrayList::lenght() {
    int lenght = 0;
    for (ElemListA* temp = head; temp != NULL; temp = temp->next) {
        lenght++;
    }
    return lenght;
}

ElemListA* ArrayList::findElement(int value) {
    for (ElemListA* temp = head; temp != NULL; temp = temp->next) {
        if (temp->value == value) return temp;
    }
    return NULL;
}

int ArrayList::findElem(int value) {
    ElemListA* el = findElement(value);
    if (el == NULL) return -1;
    if (el != NULL) return value;
}

ElemListA* ArrayList::elementAt(int position) {
    int i = 0;
    if (position < 0)return NULL;
    for (ElemListA* temp = head; temp != NULL; temp = temp->next) {
        if (i == position) return temp;
        i++;
    }
    return NULL;
}

void ArrayList::insert(int value, int position) {
    if (position == 0) { addFirst(value); return; }
    ElemListA* temp = elementAt(position);
    if (temp == NULL) return;
    if (temp->next == NULL) {
        addLast(value);
        return;
    }
    ElemListA* elem = new ElemListA(value);
    elem->next = temp;//nastepnikiem wstawianego elementu bedzie temp
    elem->prev = temp->prev;//poprzednikiem wstawianego elementu bedzie poprzednik elementu temp
    temp->prev->next = elem; //nastepnikiem poprzednika temp bedzie elem
    temp->prev = elem;//poprzednikiem elementu temp bedzie elem
    counter++;
} //dodanie w losowe miejsce

void ArrayList::deleteFirst() {
    if (head == NULL) return;
    ElemListA* temp = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    else {
        tail = NULL;
    }
    delete(temp);
    counter--;
}

void ArrayList::deleteLast() {
    if (tail == NULL) return;
    ElemListA* temp = tail;
    tail = tail->prev;
    if (tail != NULL) {
        tail->next = NULL;
    }
    else {
        head = NULL;
    }

    delete(temp);
    counter--;
}

void ArrayList::deleteAt(int position) {
    if (position == 0) {
        deleteFirst();
        return;
    }
    ElemListA* elem = elementAt(position);
    if (elem == NULL) return;
    if (elem->next == NULL) {
        deleteLast();
        return;
    }
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;
    delete(elem);
    counter--;
}

void ArrayList::deleteValue(int value) {
    ElemListA* el = findElement(value);
    if (el != NULL) {
        deleteNode(el);
    }
}

void ArrayList::clear() {
    while (counter > 0) {
        deleteLast();
    }
}

void ArrayList::deleteNode(ElemListA* el) {
    if (el == head) {
        deleteFirst();
        return;
    }
    if (el == tail) {
        deleteLast();
        return;
    }
    el->prev->next = el->next;
    el->next->prev = el->prev;
    delete(el);
    counter--;
    return;
}