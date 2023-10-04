#include "LinkedList.h"


void LinkedList::showList() {
    for (ElemList* temp = tail; temp != NULL; temp = temp->prev) {
        std::cout << temp->edge.src << " <-> " << temp->edge.dest << " : " << temp->edge.weight << std::endl;
    }
    std::cout << std::endl;
}

void LinkedList::addFirst(Edge edge) //dodanie w pierwsze miejsce
{
    ElemList* elem = new ElemList(edge);
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

ElemList* LinkedList::elementAt(int position) {
    int i = 0;
    if (position < 0)return NULL;
    for (ElemList* temp = head; temp != NULL; temp = temp->next) {
        if (i == position) return temp;
        i++;
    }
    return NULL;
}

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

void LinkedList::clear() {
    while (counter > 0) {
        deleteFirst();
    }
}
