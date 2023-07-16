class Pair {
public:
    int node;
    int weight;
    Pair() {
        this->node = -1;
        this->weight = -1;
    }
    int checkifNULL() {
        if (node == -1)return 1;
        return 0;
    }
};