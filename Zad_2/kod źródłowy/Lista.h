#include "BaseGraph.h"
#include "LinkedList.h"

class Lista : public BaseGraph
{

public:
    LinkedList** tablicalist;

    ElemList* succesor;

    //int* weights;
    Lista() {
        BaseGraph();
        tablicalist = NULL;
    }

    void build(int V) {
        this->V = V;
        this->E = 0;
        tablicalist = new LinkedList * [V];
        for (int v = 0; v < V; v++) {
            tablicalist[v] = new LinkedList();
        }
    }

    void destroy() {
        for (int v = 0; v < V; v++) {
            tablicalist[v]->clear();
            delete tablicalist[v];
        }
        delete tablicalist;
    }

    void addedge(int src, int dest, int weight) {
        Edge edge;
        edge.src = src;
        edge.dest = dest;
        edge.weight = weight;
        tablicalist[src]->addFirst(edge);
    }

    void show() {
        /*for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (table[i][j] == -1)
                    std::cout << 0 << " ";
                else
                    std::cout << table[i][j] << " ";
            }
            std::cout << std::endl;
        }*/
    }

    Pair firstsuccessor(int number) {
        Pair  p;
        succesor = tablicalist[number]->elementAt(0);
        if (succesor == NULL)
            return p;
        p.node = succesor->edge.dest;
        p.weight = succesor->edge.weight;
        return p;
    }

    Pair nextsuccessor() {
        Pair p;
        succesor = succesor->next;
        if (succesor == NULL)
            return p;
        p.node = succesor->edge.dest;
        p.weight = succesor->edge.weight;
        return p;
    }
};