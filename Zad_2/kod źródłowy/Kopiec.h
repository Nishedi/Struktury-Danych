#pragma once
#include "edge.h"
#include <iostream>

#define MAXSIZE 2000000
class Kopiec
{


public:
    int*  tab;
    int* weights;
    int* positions;
    int size;
    int counter = 0;
    Kopiec() {
        this->size=10000;
        counter = 0;
        tab = new int[size];
        positions = new int[size];
        weights = new int[size];
    }
    Kopiec(int size) {
        this->size = size;
        counter = 0;
        tab = new int[size];
        positions = new int[size];
        weights = new int[size];
    }
    ~Kopiec() {
        delete tab;
        delete positions;
        delete weights;
    }

    
    void addwitweight(int numer, int waga) {
        weights[numer] = waga;
        positions[numer] = counter;
        add(numer);
    }
    int compare(int a, int b) {
        if (weights[tab[a]] < weights[tab[b]])
            return 0;
        else
            return 1;
    }
    void swap(int a, int b) {
        int swap = tab[a];
        tab[a] = tab[b];
        tab[b] = swap;
        swap = positions[tab[a]];
        positions[tab[a]] = positions[tab[b]];
        positions[tab[b]] = swap;
    }

    void updateweight(int numer, int weight) {
        weights[numer] = weight;
        fixup(positions[numer]);
    }

    void show();

    void add(int value);

    void fixup(int index);

    int deleteRoot();

    void fixdown(int parentindex);

    void clear();
};

class KopiecKruskal : public Kopiec
{
public:
   
    Edge* edges;
   
    KopiecKruskal():Kopiec() {
       edges = new Edge[2000000];
    }
    KopiecKruskal(int size):Kopiec(size) {
         edges = new Edge[size];
    }
    ~KopiecKruskal() {
        delete edges;
    }

    void addedge(Edge edge) {
        edges[counter] = edge;
        addwitweight(counter, edge.weight);
        
    }
    
   

    Edge getedge() {
        int i = deleteRoot();
        return edges[i];
    }
};