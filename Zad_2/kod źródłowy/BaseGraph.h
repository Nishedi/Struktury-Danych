#include "Pair.h"
#include <string>
#include <iostream>
#include <fstream>
class BaseGraph {
public:
    int V;
    int E;

    BaseGraph() {
        E = 0;
        V = 0;
    }


    virtual void build(int V) {

    }

    void terminate() {

    }

    virtual void addedge(int src, int dest, int weight) {

    }

    void loadfromfileMST(std::string filename) {

        std::ifstream file(filename);
        if (!file.good()) {
            std::cout << "Blednie podana nazwa pliku\n";
            return;
        }
        int edges = 0;
        int Vierzcholki = 0;

        int trash;
        file >> edges;
        file >> Vierzcholki;
        build(Vierzcholki);
        for (int e = 0; e < edges; e++) {
            int src, dest, weight;
            file >> src;
            file >> dest;
            file >> weight;
            addedge(src, dest, weight);
            addedge(dest, src, weight);
        }
        file.close();


    }

    void loadfromfileSP(std::string filename, int * start) {

        std::ifstream file(filename);
        if (!file.good()) {
            std::cout << "Blednie podana nazwa pliku\n";
            return;
        }
        int edges = 0;
        int Vierzcholki = 0;

        int trash;
        file >> edges;
        file >> Vierzcholki;
        file >> *start;
        build(Vierzcholki);
        
        for (int e = 0; e < edges; e++) {
            int src, dest, weight;
            file >> src;
            file >> dest;
            file >> weight;
            addedge(src , dest , weight);
        }
        file.close();


    }

    void loadfromfileFF(std::string filename, int * start, int * end) {

        std::ifstream file(filename);
        if (!file.good()) {
            std::cout << "Blednie podana nazwa pliku\n";
            return;
        }
        int edges = 0;
        int Vierzcholki = 0;

        int trash;
        file >> edges;
        file >> Vierzcholki;
        file >> *start;
        file >> *end;
        build(Vierzcholki);
        for (int e = 0; e < edges; e++) {
            int src, dest, weight;
            file >> src;
            file >> dest;
            file >> weight;
            addedge(src , dest , weight);
        }
        file.close();


    }

    
};