#pragma once
#include "BaseGraph.h"
#include "edge.h"

class Macierz : public BaseGraph
{

public:
    int** table;
    int successorid = 0;
    int srcidx = 0;

    //int* weights;
    Macierz() {
        BaseGraph();
        table = NULL;
    }

    void generate(int V, int E) {
        build(V);

    }

    void build1(int V) {
        this->V = V;
        E = 0;
        int size = V;
        table = new int* [size];
        for (int i = 0; i < size; i++) {
            table[i] = new int[size];
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                table[i][j] = -1;
            }
        }
    }

    void destroy1() {
        for (int i = V - 1; i >= 0; i--) {
            free(table[i]);
        }
        free(table);
    }

    void build(int V) {
        this->V = V;
        E = 0;
        int size = V;
        table = new int* [size];
        for (int i = 0; i < size; i++) {
            table[i] = new int[size];
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                table[i][j] = -10000000;
            }
        }

    }

    void destroy() {

        for (int i = V - 1; i >= 0; i--) {
            delete table[i];
            //free(table[i]);
        }
        delete table;
        // free(table);
    }

    void addedge(int src, int dest, int weight) {
        table[src][dest] = weight;
        E++;
    }

    void addedge(Edge edge) {
        table[edge.src][edge.dest] = edge.weight;
        E++;
    }


    void show() {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (table[i][j] == -10000000)
                    std::cout << 0 << " ";
                else
                    std::cout << table[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};