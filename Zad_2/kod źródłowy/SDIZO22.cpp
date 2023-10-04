#include <fstream>
#include <iostream>
#include "Macierz.h"
#include "Kopiec.h"
#include "edge.h"
#include "LinkedList.h"
#include "ArrayList.h"
#include "Timer.h"

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
        E++;
    }

    void addedge(Edge edge) {
        tablicalist[edge.src]->addFirst(edge);
        E++;
    }

    int findweight(int src, int dest) {
        LinkedList* l = tablicalist[src];
        ElemList* el = l->head;
        while (el != NULL ) {
            if (el->edge.dest == dest) return el->edge.weight;
            el = el->next;
        }
        return -1;
        
    }

    

    Pair firstsuccessor(int number) {
        Pair  p;
        succesor = tablicalist[number]->elementAt(0);
        if(succesor==NULL)
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
    void showList() {
        int i = 0;
        for (int u = 0; u < this->V; u++) {
            std::cout << i<<":   ";
            for (ElemList* p = tablicalist[u]->head; p != NULL; p = p->next) {
                std::cout << p->edge.dest << ":" << p->edge.weight<<" ";
            }
            std::cout << "\n";
            i++;
        }
    }
};
int licznik = 0;

int Infy = 100000000;
int PrimMstTable(Macierz* G, int r, int path[]) {
    Kopiec* S = new Kopiec();//kolejka wierzcholkow do rozpatrzenia
    for (int v = 0; v < G->V; v++) S->addwitweight(v, Infy);
    for (int v = 0; v < G->V; v++)  path[v] = -1;
    path[r] = 0;
    S->updateweight(r, 0);
    while (S->counter > 0) {
        int u = S->deleteRoot();
        for (int p = 0; p < G->V; p++) {
            if (G->table[u][p] == -10000000) continue;
            int position = S->positions[p];
            if (position < S->counter) {
                if (G->table[u][p] < S->weights[p]) {
                    S->updateweight(p, G->table[u][p]);
                    path[p] = u;
                }
            }
        }
    }
    int cost = 0;
    for (int x = 0; x < G->V; x++) 
        cost = cost + S->weights[x];
    
    delete S;
    return cost;

}
int PrimMstList(Lista* G, int r, int path[]) {
    Kopiec* S = new Kopiec();//kolejka wierzcholkow do rozpatrzenia
    for (int v = 0; v < G->V; v++)  S->addwitweight(v, Infy);
    for (int v = 0; v < G->V; v++)  path[v] = -1;
    
    S->updateweight(r, 0);
    while (S->counter > 0) {
        int u = S->deleteRoot();
        for (ElemList* p = G->tablicalist[u]->head; p != NULL; p = p->next) {
            int position = S->positions[p->edge.dest];
            if (position < S->counter) {
                if (p->edge.weight < S->weights[p->edge.dest]) {
                    S->updateweight(p->edge.dest, p->edge.weight);
                    path[p->edge.dest] = u;
                }
            }
        }
    }
    int cost = 0;
    for (int x = 0; x < G->V; x++) 
        cost = cost + S->weights[x];
    delete S;
    return cost;
  
}

void PrimObsluga(Macierz* macierz, Lista * lista, int startpoint) {
    int* path = new int[macierz->V];
    LinkedList* krawedzie = new LinkedList();
    int cost = PrimMstTable(macierz, startpoint, path);
    
    for (int u = 0; u < macierz->V; u++) {
        std::cout << u << " <-> " << path[u] << ": " << macierz->table[u][path[u]] << std::endl;
    }
    std::cout << "\n";
    std::cout <<"Reprezentacja macierzowa - Najmniejsze drzewo rozpinajace: "<< cost << std::endl;
    cost = PrimMstList(lista, startpoint, path);
    for (int u = 0; u < macierz->V; u++) {
        std::cout << u << " <-> " << path[u] << ": " << lista->findweight(u, path[u]) << std::endl;
    }
    std::cout << "Reprezentacja listowa - Najmniejsze drzewo rozpinajace: " << cost << std::endl;
    delete[] path;
    delete krawedzie;
}



void GgenSTShape(int V, int nrofex,int path[])
{

    Macierz* lok = new Macierz();
    lok->build(V);
    srand((nrofex + 1) * 1133);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i != j) {
                int weight = (rand() % 10000) + 1;
                lok->addedge(i, j, weight);
                lok->addedge(j, i, weight);
            }
        }
    }

    PrimMstTable(lok, 0, path);
    lok->destroy();
    delete lok;
}
void GenRandoOrder(KopiecKruskal* kopiec, int V, int nrofex)
{
    srand((nrofex + 1) * 1133);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i < j) {
                Edge edge = Edge(i, j, (rand() % 10000) + 1);
                kopiec->addedge(edge);
                edge = Edge(j, i, (rand() % 10000) + 1);
                kopiec->addedge(edge);
            }
        }
    }

}
void generate2(Macierz* macierz, int V, int nrofex, int density) {


    int* path = new int[V];
    GgenSTShape(V, nrofex, path);

    KopiecKruskal* kopiec = new KopiecKruskal(V * V * 2);
    GenRandoOrder(kopiec, V, nrofex);

    for (int i = 0; i < V; i++) {
        if (i == path[i]) continue;
        if (path[i] != -10000000 ) {
            int weight = rand() % 10000; weight += 1;
            macierz->addedge(i, path[i], weight);
            macierz->addedge(path[i], i, weight);
        }
    }
    delete[] path;

    int E = V * (V - 1) / 2; E = E * density / 100;

    while (kopiec->counter > 0) {
        if (macierz->E > 2 * E) break;
        Edge edge = kopiec->getedge();
        if (macierz->table[edge.src][edge.dest] != -10000000) {
            continue;
        }
        if (edge.src == edge.dest) continue;
        int weight = rand() % 10000 + 1;
        macierz->addedge(edge.src, edge.dest, weight);
        macierz->addedge(edge.dest, edge.src, weight);
    }   
    delete kopiec;
}
void generateforFulkerson(Macierz* G, int V, int nrofex, int density) {
    KopiecKruskal* kopiec = new KopiecKruskal(V * V * 2);
    GenRandoOrder(kopiec, V, nrofex);

    int e = 0;
    int E = V * (V - 1) / 2;
    E = E * density / 100;


    while (kopiec->counter > 0) {

        Edge edge = kopiec->getedge();
        if (G->table[edge.src][edge.dest] != -10000000) {
            continue;
        }

        if (edge.dest == 0) continue;

        if (edge.src == V - 1) continue;

        if (edge.dest == edge.src) continue;
        
        int weight = rand() % 10000;
        weight += 1;
        G->addedge(edge.src, edge.dest, weight);
        weight = rand() % 10000;
        weight += 1;
        G->addedge(edge.dest, edge.src, weight);
        e++;
        if (e == E) break;
    }
    G->addedge(0, G->V - 1, 1);

    delete kopiec;
}


void copytabletolist(Lista * lista, Macierz* macierz) {
    lista->build(macierz->V);
    for (int i = 0; i < macierz->V; i++) {
        for (int j = 0; j < macierz->V; j++) {
            if (macierz->table[i][j] != -10000000) {//Tu bylo -1
                lista->addedge(i, j, macierz->table[i][j]);
            }
        }
    }
}





//Kruskal obsluga

void makeset(int V, int rank[], int parent[]) {
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}
int findset(int parent[], int v) {
    if (parent[v] != v) {
        parent[v] = findset(parent, parent[v]);
    }
    return parent[v];

}
void Union1(int parent[], int rank[], int x, int y) {
    int a = findset(parent, x);
    int b = findset(parent, y);
    if (rank[a] < rank[b])
        parent[a] = b;
    else
        parent[b] = a;
    if (rank[a] == rank[b])
        rank[a] = rank[a] + 1;
}
void Union(int parent[], int rank[], int x, int y) {
    int a = findset(parent, x);
    int b = findset(parent, y);
    if (a == b) return; // x i y naleza juz do tego samego zbioru
    if (rank[a] < rank[b])
        parent[a] = b;
    else if (rank[a] > rank[b])
        parent[b] = a;
    else { // rank[a] == rank[b]
        parent[b] = a;
        rank[a] = rank[a] + 1;
    }
}

int KruskalTable(Macierz* G, int path[], LinkedList * krawedzie) {
    int * parent = new int[G->V];
    int* rank = new int[G->V];
    for (int v = 0; v < G->V; v++) {
        path[v] = -1;
    }
    KopiecKruskal* S = new KopiecKruskal(G->V * G->V);
    for (int u = 0; u < G->V; u++) {
        for (int p = 0; p < G->V; p++) {
            if (p <= u)continue;
            if (G->table[u][p] == -10000000) continue;
            Edge edge = Edge(u, p, G->table[u][p]);
            S->addedge(edge);
        }
    }
    makeset(G->V, rank, parent);
    int weight = 0;
    while (S->counter > 0) {
        Edge edge = S->getedge();

        if (findset(parent, edge.src) != findset(parent, edge.dest)) {
            krawedzie->addFirst(edge);
            Union(parent, rank, edge.src, edge.dest);
            weight = weight + edge.weight;
            path[edge.dest] = edge.src;
        }
    }
    delete S;
    delete[] parent;
    delete[] rank;
    return weight;
}
int KruskalList(Lista* G, int path[], LinkedList* krawedzie) {// dodac uaktualnianie sciezki
    int* parent = new int[G->V];
    int* rank = new int[G->V];
    KopiecKruskal* S = new KopiecKruskal(G->V * G->V);
    for (int v = 0; v < G->V; v++) {
        path[v] = -1;
    }

    for (int u = 0; u < G->V; u++) {
        for (ElemList* p = G->tablicalist[u]->head; p != NULL; p = p->next) {
            if (p->edge.src > p->edge.dest) continue;
                     
            S->addedge(p->edge);
        }
    }
    makeset(G->V, rank, parent);
    int weight = 0;
    while (S->counter > 0) {
        Edge edge = S->getedge();

        if (findset(parent, edge.src) != findset(parent, edge.dest)) {
            krawedzie->addFirst(edge);
            Union(parent, rank, edge.src, edge.dest);
            weight = weight + edge.weight;
            path[edge.dest] = edge.src;
        }
    }
    delete S;
    delete[] parent;
    delete[] rank;
    return weight;
}

void KruskalObsluga(Macierz * macierz, Lista * lista) {
    int* path = new int[macierz->V];
    LinkedList* krawedzie = new LinkedList();
    int cost = KruskalTable(macierz, path,krawedzie);
    
    std::cout << "Reprezentacja macierzowa - Najmniejsze drzewo rozpinajace: " << cost << std::endl;
    
    krawedzie->showList();
    krawedzie->clear();
    cost = KruskalList(lista, path,krawedzie);
    
    
    
    std::cout << "Reprezentacja listowa - Najmniejsze drzewo rozpinajace: " << cost << std::endl;
    krawedzie->showList();
    delete[] path;
    delete krawedzie;
}

int BellmanFordTable(Macierz* G, int r, int path[], int d[]) {
    for (int v = 0; v < G->V; v++) {
        d[v] = Infy;
        path[v] = -1;
    }
    d[r] = 0;
    for (int i = 1; i <= G->V - 1; i++) {
        for (int u = 0; u < G->V; u++) {
            for (int p = 0; p < G->V; p++) {
                if (G->table[u][p] == -10000000) continue;
                 if (d[p] > d[u] + G->table[u][p]) {
                    d[p] = d[u] + G->table[u][p];
                    path[p] = u;
                }
            }
        }
    }
    for (int u = 0; u < G->V; u++) {
        for (int p = 0; p < G->V; p++) {
            if (G->table[u][p] == -10000000) continue;
            if (d[p] > d[u] + G->table[u][p]) {
                return -1;
            }
        }
    }
    return 0;
}
int BellmanFordList(Lista* G, int r, int path[], int d[]) {
    for (int v = 0; v < G->V; v++) {
        d[v] = Infy;
        path[v] = -1;
    }
    d[r] = 0;
    for (int i = 1; i <= G->V - 1; i++) {
        for (int u = 0; u < G->V; u++) {
            for (ElemList* p = G->tablicalist[u]->head; p != NULL; p = p->next) {            
                if (d[p->edge.dest] > d[u] + p->edge.weight) {
                    d[p->edge.dest] = d[u] + p->edge.weight;
                    path[p->edge.dest] = u;
                }
            }
        }
    }

    for (int u = 0; u < G->V; u++) {
        for (ElemList* p = G->tablicalist[u]->head; p != NULL; p = p->next) {
            if (d[p->edge.dest] > d[u] + p->edge.weight) {
                return -1;
            }
        }
    }

    return 0;
}

void BellmanFordObsluga(Macierz * macierz, Lista * lista, int startpoint) {
    int* path = new int[macierz->V];
    int* distance = new int[macierz->V];
    BellmanFordTable(macierz, startpoint, path, distance);
    std::cout << "Belmann-Ford reprezentacja macierzowa\n";
    std::cout << "Odleglosci poszczegolnych wierzcholkow od wierzcholka startowego: " << startpoint << std::endl;
    std::cout << "----------------------------------------------------\n";
    for (int v = 0; v < macierz->V; v++) {
        std::cout << v<<" : "<<distance[v]<<std::endl;
    }
    std::cout << "----------------------------------------------------\n";
    std::cout << "Poprzedniki wierzcholkow\n";
    std::cout << "----------------------------------------------------\n";
    for (int v = 0; v < macierz->V; v++) {
        std::cout << v << " : " << path[v] << std::endl;
    }
    std::cout << "----------------------------------------------------\n";
    BellmanFordList(lista, startpoint, path, distance);
    std::cout << "Belmann-Ford reprezentacja listowa\n";
    std::cout << "Odleglosci poszczegolnych wierzcholkow od wierzcholka startowego: " << startpoint << std::endl;
    std::cout << "----------------------------------------------------\n";
    for (int v = 0; v < macierz->V; v++) {
        std::cout << v << " : " << distance[v] << std::endl;
    }
    std::cout << "----------------------------------------------------\n";
    std::cout << "Poprzedniki wierzcholkow\n";
    std::cout << "----------------------------------------------------\n";
    for (int v = 0; v < macierz->V; v++) {
        std::cout << v << " : " << path[v] << std::endl;
    }
    std::cout << "----------------------------------------------------\n";

    delete[] path;
    delete[] distance;
}


int DijkstraTable(Macierz* G, int r, int path[], int distance[]) {
    Kopiec* S = new Kopiec();//kolejka wierzcholkow do rozpatrzenia
    for (int v = 0; v <G->V; v++) {
        S->addwitweight(v, Infy);
        path[v] = -1;
    }
    S->updateweight(r, 0);
    while (S->counter > 0) {
        int u = S->deleteRoot();
        for (int p = 0; p < G->V; p++) {
            if (G->table[u][p] == -10000000) continue;
            int position = S->positions[p];
            if (position < S->counter) {
                int d = S->weights[u] + G->table[u][p];
                if (S->weights[p] > d) {
                    S->updateweight(p, d);
                    path[p] = u;
                }
            }
        }
    }
    for (int x = 0; x <G->V; x++) {
        distance[x] = S->weights[x];
    }
    delete S;
    return 0;
  
}
int DijkstraList(Lista* G, int r, int path[], int distance[]) {
    
    Kopiec* S = new Kopiec();//kolejka wierzcholkow do rozpatrzenia
    for (int v = 0; v <G->V; v++) {
        S->addwitweight(v, Infy);
        path[v] = -1;
    }
    S->updateweight(r, 0);
    while (S->counter > 0) {
        int u = S->deleteRoot();
        for (ElemList* p = G->tablicalist[u]->head; p != NULL; p = p->next) {
            int position = S->positions[p->edge.dest];
            if (position < S->counter) {
                int d = S->weights[u] + p->edge.weight;

                if (S->weights[p->edge.dest] > d) {
                    S->updateweight(p->edge.dest, d);
                    path[p->edge.dest] = u;
                }
            }
        }
    }
    for (int x = 0; x < G->V; x++) {
        distance[x] = S->weights[x];
    }
    delete S;
    return 0;
}
void DijkstraObsluga(Macierz * macierz, Lista * lista, int startpoint) {
    int* path = new int[macierz->V];
    int* distance = new int[macierz->V];
    DijkstraTable(macierz, startpoint, path, distance);
    std::cout << "Dijkstra reprezentacja macierzowa\n";
    std::cout << "Odleglosci poszczegolnych wierzcholkow od wierzcholka startowego: " << startpoint << std::endl;
    std::cout << "----------------------------------------------------\n";
    for (int v = 0; v < macierz->V; v++) {
        std::cout << v << " : " << distance[v] << std::endl;
    }
    std::cout << "----------------------------------------------------\n";
    std::cout << "Poprzedniki wierzcholkow\n";
    std::cout << "----------------------------------------------------\n";
    for (int v = 0; v < macierz->V; v++) {
        std::cout << v << " : " << path[v] << std::endl;
    }
    std::cout << "----------------------------------------------------\n";
    DijkstraList(lista, startpoint, path, distance);
    std::cout << "Dijkstra reprezentacja listowa\n";
    std::cout << "Odleglosci poszczegolnych wierzcholkow od wierzcholka startowego: " << startpoint << std::endl;
    std::cout << "----------------------------------------------------\n";
    for (int v = 0; v < macierz->V; v++) {
        std::cout << v << " : " << distance[v] << std::endl;
    }
    std::cout << "----------------------------------------------------\n";
    std::cout << "Poprzedniki wierzcholkow\n";
    std::cout << "----------------------------------------------------\n";
    for (int v = 0; v < macierz->V; v++) {
        std::cout << v << " : " << path[v] << std::endl;
    }
    std::cout << "----------------------------------------------------\n";

    delete[] path;
    delete[] distance;
}

void wszerzlista(Lista* G, ElemList* path[], int sink, int t) {
   
    int* isvisited = new int[G->V];
    for (int u = 0; u < G->V; u++) isvisited[u] = 0;
    for (int i = 0; i < G->V; i++) path[i] = NULL;

    ArrayList* queue = new ArrayList();
    queue->addLast(sink);
   
    while (queue->counter > 0) {
        int s = queue->elementAt(0)->value;
        queue->deleteFirst();
        isvisited[s] = 1;
        for (ElemList* p = G->tablicalist[s]->head; p != NULL; p = p->next) {
            if (isvisited[p->edge.dest] == 1) continue;
            if (p->edge.weight == 0) continue;
            queue->addLast(p->edge.dest);
            path[p->edge.dest] = p;
        }
    }
    delete[] isvisited;
    queue->clear();
    delete queue;
}
void wglablista(Lista* G, ElemList* path[], int sink, int t) {
    int *isvisited=new int[G->V];
    for (int u = 0; u < G->V; u++)  isvisited[u] = 0;
    for (int i = 0; i < G->V; i++)   path[i] = NULL;

    ArrayList* queue = new ArrayList();
    queue->addFirst(sink); 
    
    while (queue->counter > 0) {
       int s = queue->elementAt(0)->value;
        queue->deleteFirst();
        isvisited[s] = 1;
        for (ElemList* p = G->tablicalist[s]->head; p != NULL; p = p->next) {
            if (isvisited[p->edge.dest] == 1) continue;
            if (p->edge.weight == 0) continue;
            queue->addLast(p->edge.dest);
            path[p->edge.dest] = p;
        }
    }
    delete[] isvisited;
    queue->clear();
    delete queue;
}
void wszerztablica(Macierz* G, int path[], int sink, int t) {
    int* isvisited = new int[G->V];
    for (int u = 0; u < G->V; u++)  isvisited[u] = 0;
    for (int i = 0; i < G->V; i++)  path[i] = -1;

    ArrayList* queue = new ArrayList();
    queue->addLast(sink);

    while (queue->counter > 0) {
        int s = queue->elementAt(0)->value;
        queue->deleteFirst();
        isvisited[s] = 1;

        for (int x = 0; x < G->V; x++) {
            if (isvisited[x] == 1) continue;
            if (G->table[s][x] == 0) continue;
            queue->addLast(x);
            path[x] = s;
        }
    }
    delete[] isvisited;
    queue->clear();
    delete queue;
}
void wglabtablica(Macierz* G, int path[], int sink, int t) {

    int* isvisited = new int[G->V];
    for (int u = 0; u < G->V; u++) isvisited[u] = 0;
    for (int i = 0; i < G->V; i++)  path[i] = -1;

    ArrayList* queue = new ArrayList();
    queue->addFirst(sink);

    while (queue->counter > 0) {
        int s = queue->elementAt(0)->value;
        queue->deleteFirst();
        isvisited[s] = 1;
        for (int x = 0; x < G->V; x++) {
            if (isvisited[x] == 1) continue;
            if (G->table[s][x] == 0) continue;
            queue->addLast(x);
            path[x] = s;
        }
    }
    delete[] isvisited;
    queue->clear();
    delete queue;
}
void wagi(Lista* G) {
    std::cout << "Wagi\n";
    for (int u = 0; u < G->V; u++) {

        for (ElemList* p = G->tablicalist[u]->head; p != NULL; p = p->next) {

            int weight2 = p->edge.weight;
            //  if (pp->edge.dest == p->edge.dest || pp->edge.src == p->edge.src)continue;
            std::cout << p->edge.src << " " << p->edge.dest /* << " " << weight2 << " " << weight */ << " " << weight2 << std::endl;

        }
    }
    std::cout << "Koniec\n";
}
void showlisted(Lista* G, Lista* R) {
    int** temp;
    temp = new int* [G->V];
    for (int i = 0; i < G->V; i++) {
        temp[i] = new int[G->V];
    }

    for (int i = 0; i < G->V; i++) {
        for (int j = 0; j < G->V; j++) {
            temp[i][j] = 0;
        }
    }

    for (int u = 0; u < G->V; u++) {


        for (ElemList* p = G->tablicalist[u]->head; p != NULL; p = p->next) {
            temp[p->edge.src][p->edge.dest] += p->edge.weight;

        }
    }
    for (int u = 0; u < R->V; u++) {


        for (ElemList* p = R->tablicalist[u]->head; p != NULL; p = p->next) {
            temp[p->edge.src][p->edge.dest] -= p->edge.weight;

        }
    }
    for (int i = 0; i < G->V; i++) {
        for (int j = 0; j < G->V; j++) {
            int val = temp[i][j];
            if (val > 0)std::cout << i << " " << j << " " << val << std::endl;
        }
    }
    for (int i = G->V - 1; i >= 0; i--) {
        free(temp[i]);
    }
    free(temp);
}
int FordFulkersonlistaWszerz(Lista* G, int s, int t) {
    Lista* R = new Lista();
    int flow=0;
    R->build(G->V);
    for (int u = 0; u < G->V; u++) {
        for (ElemList* p = G->tablicalist[u]->head; p != NULL; p = p->next) {
            Edge edge = Edge(p->edge.src, p->edge.dest, p->edge.weight);
            Edge edgeb = Edge(p->edge.dest, p->edge.src, 0);
            R->addedge(edge);
            R->addedge(edgeb);
            R->tablicalist[edge.src]->head->reversed = R->tablicalist[edgeb.src]->head;
            R->tablicalist[edgeb.src]->head->reversed = R->tablicalist[edge.src]->head;
        }
    }
    
    ElemList* *path=new ElemList*[G->V];

    while (true) {
        wszerzlista(R, path, s, t);
        if (path[t] == NULL) break;
        Edge edge = path[t]->edge;
        int minweight = edge.weight;
        while (edge.src != s) {
            edge = path[edge.src]->edge;
            if (edge.weight < minweight) {
                minweight = edge.weight;
                
                
            }
                
        }
        for (int node = t; node != s; node = path[node]->edge.src) {
            path[node]->reversed->edge.weight += minweight;
            path[node]->edge.weight = path[node]->edge.weight - minweight;
            
        }
        flow += minweight;
       
    }
    showlisted(G, R);
    R->destroy();
    delete R;

    //std::cout << "\n" << flow << " flow\n";
    delete []path;
    return flow;
}


int FordFulkersonlistaWglab(Lista* G, int s, int t) {
    Lista* R = new Lista();
    R->build(G->V);
    int iter = 0;
    int flow = 0;
    for (int u = 0; u < G->V; u++) {
        for (ElemList* p = G->tablicalist[u]->head; p != NULL; p = p->next) {

            Edge edge = Edge(p->edge.src, p->edge.dest, p->edge.weight);
            Edge edgeb = Edge(p->edge.dest, p->edge.src, 0);
            R->addedge(edge);
            R->addedge(edgeb);
            R->tablicalist[edge.src]->head->reversed = R->tablicalist[edgeb.src]->head;
            R->tablicalist[edgeb.src]->head->reversed = R->tablicalist[edge.src]->head;
        }
    }

    //int s = 0;
    //int t = G->V - 1;
    ElemList** path = new ElemList * [G->V];

    while (true) {
        wglablista(R, path, s, t);
        if (path[t] == NULL)break;
        Edge edge = path[t]->edge;
        int minweight = edge.weight;
        while (edge.src != s) {
            edge = path[edge.src]->edge;
            if (edge.weight < minweight)
                minweight = edge.weight;
        }
        for (int node = t; node != s; node = path[node]->edge.src) {
            path[node]->reversed->edge.weight += minweight;
            path[node]->edge.weight = path[node]->edge.weight - minweight;
        }
        flow += minweight;
    }
    
    
    showlisted(G, R);
    
    R->destroy();
    delete R;
    delete []path;
    return flow;
}


int FordFulkersonTablicaWszerz(Macierz* G, int s, int t) {
    Macierz* R = new Macierz();
    int flow = 0;
    R->build(G->V);
    for (int i = 0; i < R->V; i++) {
        for (int j = 0; j <R->V; j++) {
            R->table[i][j] = 0;
        }
    }

    int iter = 0;
    for (int u = 0; u < G->V; u++) {
        for(int x = 0 ; x < G->V;x++){
            if (G->table[u][x] != -10000000)
                R->table[u][x] = G->table[u][x];
            if (G->table[x][u] != -10000000)
                R->table[x][u] = G->table[x][u];
           
        }
        

    }
    
   // int s = 0;
   // int t =G->V - 1;
    int *path=new int[G->V];
    while (true) {
        wglabtablica(R, path, s, t);
        if (path[t] == -1)break;
        
        int minweight = 1000000;
        for (int node = t; node != s; node = path[node]) {
            int tempweight = R->table[path[node]][node];
            if (tempweight <= 0)continue;
            if (tempweight <  minweight)minweight = tempweight;
        }   
        
        for (int node = t; node != s; node = path[node]) {
            R->table[node][path[node]] += minweight;
            
            R->table[path[node]][node] -= minweight;

        }
        flow += minweight;
        
    }

    
    for (int i = 0; i < R->V; i++) {
        for (int j = 0; j < R->V; j++) {
            int weight = R->table[i][j];
            int weight2 = G->table[i][j];
            if (i == j)continue;

            if (weight2 == -10000000) {
                continue;
            }
            int r = weight2 - weight;
            if(r>0)
                std::cout << i << " " << j << " "/* << weight2 << " " << weight */<< " " << r << std::endl;
        }
    }

    R->destroy();
    delete R;
    delete[] path;
    return flow;
}



int FordFulkersonTablicaWglab(Macierz* G, int s, int t) {
    Macierz* R = new Macierz();
    int flow = 0;
    R->build(G->V);
    for (int i = 0; i < R->V; i++) {
        for (int j = 0; j < R->V; j++) {
            R->table[i][j] = 0;
        }
    }

    int iter = 0;
    for (int u = 0; u < G->V; u++) {
        for (int x = 0; x < G->V; x++) {
            if (G->table[u][x] != -10000000)
                R->table[u][x] = G->table[u][x];
            /*if (G->table[x][u] != -10000000)
                R->table[x][u] = G->table[x][u];*/

            
        }

    }
  //  int s = 0;
   // int t = G->V - 1;
    int* path = new int[G->V];

    while (true) {
        wszerztablica(R, path, s, t);
        if (path[t] == -1)break;

        int minweight = 1000000;
        for (int node = t; node != s; node = path[node]) {
            int tempweight = R->table[path[node]][node];
            if (tempweight <= 0)continue;
            if (tempweight < minweight)minweight = tempweight;
        }

        for (int node = t; node != s; node = path[node]) {
            R->table[node][path[node]] += minweight;
            R->table[path[node]][node] -= minweight;
        }
        flow += minweight;
    }

    
    //for (int node = t; node != s; node = path[node]) {
      //  std::cout << node << " -> " << path[node] << " " << R->table[node][path[node]]<<std::endl;
    //}
    for (int i = 0; i < R->V; i++) {
        for (int j = 0; j < R->V; j++) {
            int weight = R->table[i][j];
            int weight2 = G->table[i][j];
            if (i == j)continue;

            if (weight2 == -10000000) {
                continue;
            }
            int r = weight2 - weight;
            if (r > 0)
                std::cout << i << " " << j << " "/* << weight2 << " " << weight */<< " " << r << std::endl;
        }
    }



    
   
    R->destroy();
    delete R;
    delete[] path;
    return flow;
}

int testFulker(int numer, int V, int numberofrepeat, int numberofexample, int density, std::ofstream& zapis, int struktura, std::string algorytm) {
    Macierz* macierz = new Macierz();
    Lista* lista = new Lista();
    int* path = new int[V];
    int* distance = new int[V];
    int ec = 0;
    //int* DD = new int[V];
    //int* BF = new int[V];
    int* DDL = new int[V];
    int* BFL = new int[V];
    macierz->build(V);
    int E = V * V * density / 100;
    generateforFulkerson(macierz, V, numer, density);
    lista->build(V);

    for (int i = 0; i < V; i++) {
        for (int p = 0; p < macierz->V; p++) {
            if (macierz->table[i][p] == -1)continue;
            lista->addedge(i, p, macierz->table[i][p]);
            licznik++;
        }
    }
    
    uint64_t time = 1000000000;
    Timer timer;



    for (int i = 0; i < 1; i++) {
        
        int ts = FordFulkersonTablicaWszerz(macierz,0,macierz->V-1);
            
                int tg = FordFulkersonTablicaWglab( macierz, 0, macierz->V - 1);
                 

                if (ts != tg) {
                    std::cout << "rozne\n";
                }
        
    }

    macierz->destroy();
    delete macierz;
    lista->destroy();
    delete lista;
    delete[] path;
    delete[] distance;
    delete[] BFL;
    delete[] DDL;
    return ec;

}
int bench(int numer, int V, int numberofrepeat, int numberofexample, int density, std::ofstream& zapis, int struktura, std::string algorytm) {
    Macierz* macierz = new Macierz();
    Lista* lista = new Lista();
    int* path = new int[V];
    int* distance = new int[V];
    int res = 0;;
    int* DDL = new int[V];
    int* BFL = new int[V];
    LinkedList* krawedzie = new LinkedList();
    macierz->build(V);

    if ((algorytm.compare("Fulkersonwglab") == 0) || (algorytm.compare("Fulkersonwszerz") == 0)) {
        generateforFulkerson(macierz, V, numer, density);
    }
    else
    {
        generate2(macierz, V, numer, density);
    }
    
    lista->build(V);

    for (int i = 0; i < V; i++) {
        for (int p = 0; p < macierz->V; p++) {
            if (macierz->table[i][p] == -10000000)continue;
            lista->addedge(i, p, macierz->table[i][p]);
            licznik++;
        }
    }

    Timer timer;
    for (int i = 0; i < numberofrepeat; i++) {
        timer.start();
        if (algorytm.compare("Dijkstra") == 0) {
            if (struktura == 1)
                DijkstraList(lista, 0, path, DDL);
            if (struktura == 0)
                DijkstraTable(macierz, 0, path, DDL);
        }
        if (algorytm.compare("Prim") == 0) {
            if (struktura == 1)
                res = PrimMstList(lista, 0, path);
            if (struktura == 0)
                res = PrimMstTable(macierz, 0, path);
        }
        if (algorytm.compare("Kruskal") == 0) {
            if (struktura == 1)
                res = KruskalList(lista, path,krawedzie);
            if (struktura == 0)
                res = KruskalTable(macierz, path, krawedzie);
        }
        if (algorytm.compare("Belmann") == 0) {
            if (struktura == 1)
                BellmanFordList(lista, 0, path, DDL);
            if (struktura == 0)
               BellmanFordTable(macierz, 0, path, DDL);
        }
        if (algorytm.compare("Fulkersonwglab") == 0) {
            if (struktura == 1)
                res = FordFulkersonlistaWglab(lista, 0, macierz->V - 1);
            if (struktura == 0) 
                res = FordFulkersonTablicaWglab(macierz, 0, macierz->V - 1);
        }
        if (algorytm.compare("Fulkersonwszerz") == 0) {
            if (struktura == 1)
                res = FordFulkersonlistaWszerz(lista, 0, macierz->V - 1);
            if (struktura == 0) 
                res = FordFulkersonTablicaWszerz(macierz, 0, macierz->V - 1);
        }
        timer.stop();
        uint64_t time = timer.timeperiod();

        if ((algorytm.compare("Dijkstra") == 0) || (algorytm.compare("Belmann") == 0)) {
            res = 0; for (int i = 0; i < V; i++) res += DDL[i];   
        }
        zapis << numer << "," << V << "," << i << "," << algorytm << "," << struktura << "," << density << "," << time << "," << res << std::endl;
    }

    macierz->destroy();
    delete macierz;
    lista->destroy();
    delete lista;
    delete krawedzie;
    delete[] path;
    delete[] distance;
    delete[] BFL;
    delete[] DDL;
    return res;

}
void test(std::string nazwa, int RV[], int RD[]) {
    std::ofstream zapis("C:\\2\\" + nazwa + ".csv");
    std::cout << '\n' << nazwa << '\n';
    int liczbauruchomien = 3;
    zapis << "testnumber,V,runnumber,algorytm,struktura,gestosc,czas,res" << std::endl;
    for (int it = 0; RD[it] != 0; it++) {
        int density = RD[it];
        for (int V = RV[0]; V <= RV[1]; V = V + RV[2]) {
            std::cout << density << '-' << V << ' ';
            for (int i = 0; i < 5; i++) {
                for (int struktura1 = 0; struktura1 < 2; struktura1++) {
                   if (nazwa.compare("Dijkstra")==0) bench(i, V, liczbauruchomien, 0, density, zapis, struktura1, "Dijkstra");
                   if (nazwa.compare("Prim") == 0) bench(i, V, liczbauruchomien, 0, density, zapis, struktura1, "Prim");
                   if (nazwa.compare("Kruskal") == 0) bench(i, V, liczbauruchomien, 0, density, zapis, struktura1, "Kruskal");
                   if (nazwa.compare("Belmann") == 0)  bench(i, V, liczbauruchomien, 0, density, zapis, struktura1, "Belmann");
                   if (nazwa.compare("Fulkersonwglab") == 0)  bench(i, V, liczbauruchomien, 0, density, zapis, struktura1, "Fulkersonwglab");
                   if (nazwa.compare("Fulkersonwszerz") == 0)  bench(i, V, liczbauruchomien, 0, density, zapis, struktura1, "Fulkersonwszerz");
                   std::cout << "*";
                }
            }
        }
    }
    zapis.close();
}
void test1(std::string nazwa, int RV[], int RD[]) {
    std::ofstream zapis("C:\\2\\" + nazwa + ".csv");
    std::cout << '\n' << nazwa << '\n';
    int liczbauruchomien = 3;
    zapis << "testnumber,V,runnumber,algorytm,struktura,gestosc,czas,res" << std::endl;
    for (int it = 0; RD[it] != 0; it++) {
        int density = RD[it];
        for (int V = RV[0]; V <= RV[1]; V = V + RV[2]) {
            std::cout << density << '-' << V << ' ';
            for (int i = 0; i < 1; i++) {
                for (int struktura1 = 0; struktura1 < 2; struktura1++) {
                    if (nazwa.compare("Dijkstra") == 0) bench(i, V, liczbauruchomien, 0, density, zapis, struktura1, "Dijkstra");
                    if (nazwa.compare("Prim") == 0) bench(i, V, liczbauruchomien, 0, density, zapis, struktura1, "Prim");
                    if (nazwa.compare("Kruskal") == 0) bench(i, V, liczbauruchomien, 0, density, zapis, struktura1, "Kruskal");
                    if (nazwa.compare("Belmann") == 0)  bench(i, V, liczbauruchomien, 0, density, zapis, struktura1, "Belmann");
                    if (nazwa.compare("Fulkersonwglab") == 0)  bench(i, V, liczbauruchomien, 0, density, zapis, struktura1, "Fulkersonwglab");
                    if (nazwa.compare("Fulkersonwszerz") == 0)  bench(i, V, liczbauruchomien, 0, density, zapis, struktura1, "Fulkersonwszerz");
                    std::cout << "*";
                }
            }
        }
    }
    zapis.close();
}



void menu() {
    int startpoint = -1;
    int endpoint = -1;
    int option = 0;
    int option1 = 0;
    int V = 0;
    int density;
    std::string filename = "";
    Macierz* macierz=NULL;
    Lista* lista=NULL;
    while (true)
    {
        std::cout << "1. Wyszukiwanie minimalnego drzewa rozpinajacego\n";
        std::cout << "2. Wyszukiwanie najkrotszej drogi w grafie\n";
        std::cout << "3. Wyszukuwanie maksymalnego przeplywu\n";
        std::cout << "0. Zakoncz dzialanie programu\n";
        std::cin >> option;
        //option = 2;
        switch (option)
        {
        case 1:
        {
            system("cls");
            do {
                std::cout << "1. Wczytaj z pliku\n";
                std::cout << "2. Wygeneruj graf losowo\n";
                std::cout << "3. Wyswietl graf\n";
                std::cout << "4. Wykonaj algorytm Prima\n";
                std::cout << "5. Wykonaj algorytm Kruskal\n";
                std::cout << "0. Powrot do wyboru algorytmu\n";
                std::cin >> option1;
                switch (option1)
                {
                case 1:
                {
                    if (macierz != NULL) {
                        macierz->destroy();
                        delete macierz;

                    }
                    if (lista != NULL) {
                        lista->destroy();
                        delete lista;

                    }
                    macierz = new Macierz();
                    lista = new Lista();
                
                    std::cout << "Podaj nazwe pliku:\n";
                    std::cin >> filename;
                    macierz->loadfromfileMST(filename);
                    copytabletolist(lista, macierz);
                    macierz->show();
                    lista->showList();
                    break;
                }
                case 2:

                {
                    if (macierz != NULL) {
                        macierz->destroy();
                        delete macierz;

                    }
                    if (lista != NULL) {
                        lista->destroy();
                        delete lista;

                    }
                    macierz = new Macierz();
                    lista = new Lista();

                    std::cout << "Uwaga, wierzcholki numerowane sa od 0\n";
                    std::cout << "Ilosc wierzcholkow: ";
                    std::cin >> V;
                    std::cout << "Gestosc grafu (w procentach): ";
                    std::cin >> density;
                    macierz->build(V);
                    generate2(macierz, V, 0, density);
                    copytabletolist(lista, macierz);
                    macierz->show();
                    lista->showList();
                    break;
                }
                case 3:
                    macierz->show();
                    lista->showList();
                    break;
                case 4:
                {
                    PrimObsluga(macierz, lista, 0);
                    break;
                }
                case 5: 
                {
                    KruskalObsluga(macierz, lista);
                    break;
                }
                default:
                    break;
                }
                
            } while (option1 != 0);
            break;
        }
        case 2:
        {
            system("cls");
            do {
                std::cout << "1. Wczytaj z pliku\n";
                std::cout << "2. Wygeneruj graf losowo\n";
                std::cout << "3. Wyswietl graf\n";
                std::cout << "4. Wykonaj algorytm Dijkstry\n";
                std::cout << "5. Wykonaj algorytm Belmanna - Forda\n";
                std::cout << "0. Powrot do wyboru algorytmu\n";
                std::cin >> option1;
                switch (option1)
                {
                case 1:
                {
                    if (macierz != NULL) {
                        macierz->destroy();
                        delete macierz;

                    }
                    if (lista != NULL) {
                        lista->destroy();
                        delete lista;

                    }
                    macierz = new Macierz();
                    lista = new Lista();
                    std::cout << "Podaj nazwe pliku:\n";
                    std::cin >> filename;
                    macierz->loadfromfileSP(filename, &startpoint);
                    copytabletolist(lista, macierz);
                    macierz->show();
                    lista->showList();
                    break;
                }
                case 2:

                {
                    if (macierz != NULL) {
                        macierz->destroy();
                        delete macierz;

                    }
                    if (lista != NULL) {
                        lista->destroy();
                        delete lista;

                    }
                    macierz = new Macierz();
                    lista = new Lista();

                    std::cout << "Uwaga, wierzcholki numerowane sa od 0\n";
                    std::cout << "Ilosc wierzcholkow: ";
                    std::cin >> V;
                    std::cout << "Gestosc grafu (w procentach): ";
                    std::cin >> density;
                    std::cout << "Wierzcholek startowy: ";
                    std::cin >> startpoint;
                    macierz->build(V);
                    generate2(macierz, V, 0, density);
                    copytabletolist(lista, macierz);
                    macierz->show();
                    lista->showList();
                    break;
                }
                case 3:
                    macierz->show();
                    lista->showList();
                    break;
                case 4 :
                    DijkstraObsluga(macierz, lista, startpoint);
                    break;
                case 5:
                    BellmanFordObsluga(macierz, lista, startpoint);
                    break;
                default:
                    break;
                }
            } while (option1 != 0);
            break;
        }
        case 3:
        {
            system("cls");
            macierz = new Macierz();
            lista = new Lista();
            do {
                std::cout << "1. Wczytaj z pliku\n";
                std::cout << "2. Wygeneruj graf losowo\n";
                std::cout << "3. Wyswietl graf\n";
                std::cout << "4. Wykonaj algorytm Forda - Fulkersona z przeszukiwaniem grafu w glab\n";
                std::cout << "5. Wykonaj algorytm Forda - Fulkersona z przeszukiwaniem grafu wszerz\n";
                std::cout << "0. Powrot do wyboru algorytmu\n";
                std::cin >> option1;
                
                switch (option1)
                {
                    
                case 1:
                {
                    if (macierz != NULL) {
                        macierz->destroy();
                        delete macierz;
                        
                    }
                    if (lista != NULL) {
                        lista->destroy();
                        delete lista;
                        
                    }
                    macierz = new Macierz();
                    lista = new Lista();
                    std::cout << "Podaj nazwe pliku:\n";
                    std::cin >> filename;
       //             filename = "flow.txt";
                    macierz->loadfromfileFF(filename,&startpoint, &endpoint);
                    copytabletolist(lista, macierz);
                    macierz->show();
                    lista->showList();
                    break;
                }
                case 2:
                {
                    if (macierz != NULL) {
                        macierz->destroy();
                        delete macierz;
                    }
                    if (lista != NULL) {
                        lista->destroy();
                        delete lista;
                        
                    }
                    macierz = new Macierz();
                    lista = new Lista();
                    std::cout << "Uwaga, wierzcholki numerowane sa od 0\n";
                    std::cout << "Ilosc wierzcholkow: ";
                    std::cin >> V;
                    std::cout << "Gestosc grafu (w procentach): ";
                    std::cin >> density;
                    std::cout << "Wierzcholek startowy: ";
                    std::cin >> startpoint;
                    std::cout << "Wierzcholek koncowy: ";
                    std::cin >> endpoint;
                    macierz->build(V);
                    generateforFulkerson(macierz, V, 0,density);
                    copytabletolist(lista, macierz);
                    macierz->show();
                    lista->showList();
                    break;
                }
                case 3:
                    macierz->show();
                    lista->showList();
                    break;
                case 4:
                    std::cout<<"Reprezentacja macierzowa, przeszukiwanie w glab, maksymalny przeplyw: " << FordFulkersonTablicaWglab(macierz, startpoint, endpoint)<<std::endl;
                    std::cout << "Reprezentacja listowa, przeszukiwanie w glab, maksymalny przeplyw: " << FordFulkersonlistaWglab(lista, startpoint, endpoint) << std::endl;
                    break;
                case 5:
                    std::cout << "Reprezentacja macierzowa, przeszukiwanie wszerz, maksymalny przeplyw: " << FordFulkersonTablicaWszerz(macierz, startpoint, endpoint) << std::endl;
                    std::cout << "Reprezentacja listowa, przeszukiwanie wszerz, maksymalny przeplyw: " << FordFulkersonlistaWszerz(lista, startpoint, endpoint) << std::endl;
                    break;
                default:
                    break;
                }
            } while (option1 != 0);
            break;
        }
        case 0:
        {
            return;
        }
        default:
            break;
        }

    }
    


        
}
int main() {
   /* Macierz* macierz = new Macierz();
    int start,  end;
    macierz->loadfromfileFF("flow.txt", &start,&end);
    Lista* lista = new Lista();
    //generateList(lista, macierz);
    macierz->show();
    std::cout << FordFulkersonlistaWglab(lista, start, end);    // Lista* lista = new Lista();
     //lista->loadfromfile("file.txt");*/

    int R_V[] = { 100,1000,100 };
    int R_D[] = {1,5,10,25,50,75,99,0};

    // test("Dijkstra", R_V, R_D);
    // test("Prim", R_V, R_D);
    // test("Kruskal", R_V, R_D);


     
     int R_VB[] = { 100,1000,100 };
     int R_DB[] = { 1,5,10,25,50,75,99,0 };
   //  test("Belmann", R_VB, R_DB);

     int R_VF[] = { 10,100,10 };
     
     int R_DF[] = { 1,5,10,25,50,75,99,0 };
     //test("Fulkersonwglab", R_VF, R_DF);
     //test("Fulkersonwszerz", R_VF, R_DF);
  
    menu();

    return 0;
}