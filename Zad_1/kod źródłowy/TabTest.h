#pragma once
class TabTest {
public:
    int counter;
    
    virtual void addFirst(int value) {} //dodanie w pierwsze miejsce

    virtual void addLast(int value) {}//dodawnie w ostatnie miejsce

    virtual void insert(int value, int position) {} //dodanie w losowe miejsce

    virtual    void deleteFirst() {}

    virtual void deleteLast() {}

    virtual void deleteAt(int position) {}

     virtual int findElem(int value) {
        return -1;
    }

    virtual void clear() {
        
    }
};