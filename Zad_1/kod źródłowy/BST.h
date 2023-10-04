#include <iostream>
#include <string.h>
#include "TREE.h"
class Element {
public:
    int value;
    Element* left, * right, * parent;
};

class BST : public TREE {
public:
    Element* head;
    int counter;
    BST() {
        head = NULL;
        counter = 0;
    }
    void addToTree(int value);

    void add(int value);

    void checkwheretogo(Element* parent, Element* child);

    void showinorder(Element* el);

    void showpreorder(Element* el);

    void showpostorder(Element* el);

    void preparevisulaisation();

    void visualisation(std::string cr, std::string cl, std::string cp, std::string sp, std::string sn, Element* v);

    void visualisation(std::string cr, std::string cl, std::string cp, std::string sp, std::string sn);

    Element* findInTree(Element* el, int value);

    Element* findsmaller(Element* el);

    Element* nexter(Element* el);

    int removeFromTree(int value);

    int removeRoot();

    int deleteRoot();

    int findvalue(int value);

    void rotateright(Element* el);

    void rotateleft(Element* el);

    void makestraight(Element* el);

    void DSW();

    void clear();
};
