#include "LinkedList.h"

void LinkedList::showList() {
    for (ElemList* temp = head; temp != NULL; temp = temp->next) {
        std::cout << temp->value << " ";
    }
    std::cout << std::endl;
}

void LinkedList::showListReversed() {
    for (ElemList* temp = tail; temp != NULL; temp = temp->prev) {
        std::cout << temp->value << " ";
    }
    std::cout << std::endl;
}

void LinkedList::addFirst(int value) //dodanie w pierwsze miejsce
{
    ElemList* elem = new ElemList(value);
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

void LinkedList::addLast(int value) {//dodawnie w ostatnie miejsce
    ElemList* elem = new ElemList(value);
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

int LinkedList::lenght() {
    int lenght = 0;
    for (ElemList* temp = head; temp != NULL; temp = temp->next) {
        lenght++;
    }
    return lenght;
}

ElemList* LinkedList::findElement(int value) {
    for (ElemList* temp = head; temp != NULL; temp = temp->next) {
        if (temp->value == value) return temp;
    }
    return NULL;
}

int LinkedList::findElem(int value) {
    ElemList* el = findElement(value);
    if (el == NULL) return -1;
    if (el != NULL) return value;
}

ElemList* LinkedList::elementAt(int position) {
    int i = 0;
    if (position < 0)return NULL;
    for (ElemList* temp = head; temp != NULL; temp = temp->next) {
        if (i == position) return temp;
        i++;
    }
    return NULL;
}

void LinkedList::insert(int value, int position) {
    if (position == 0) { addFirst(value); return; }
    ElemList* temp = elementAt(position);
    if (temp == NULL) return;
    if (temp->next == NULL) {
        addLast(value);
        return;
    }
    ElemList* elem = new ElemList(value);
    elem->next = temp;//nastepnikiem wstawianego elementu bedzie temp
    elem->prev = temp->prev;//poprzednikiem wstawianego elementu bedzie poprzednik elementu temp
    temp->prev->next = elem; //nastepnikiem poprzednika temp bedzie elem
    temp->prev = elem;//poprzednikiem elementu temp bedzie elem
    counter++;
} //dodanie w losowe miejsce

void LinkedList::deleteFirst() {
    if (head == NULL) return;
    ElemList* temp = head;
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

void LinkedList::deleteLast() {
    if (tail == NULL) return;
    ElemList* temp = tail;
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

void LinkedList::deleteAt(int position) {
    if (position == 0) {
        deleteFirst();
        return;
    }
    ElemList* elem = elementAt(position);
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

void LinkedList::deleteValue(int value) {
    ElemList* el =findElement(value);
    if (el != NULL) {
        deleteNode(el);
    }          
}

void LinkedList::clear() {
    while (counter > 0) {
        deleteLast();
    }
}

void LinkedList::deleteNode(ElemList *el) {
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