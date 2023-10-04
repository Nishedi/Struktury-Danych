#include <iostream>
#include <string.h>
#include "TREE.h"
class ElementRB  {
public:
    int value;
    char color;//r - czerwony, b - czarny
    ElementRB* left, * right, * parent;
    ElementRB() {
        color = 'r';
    }
};

class RB : public TREE {
public:
    ElementRB* head;
    int counter;
    RB() {
        head = NULL;
        counter = 0;
    }
    void addToTree(int value);

    int walk();

    void repair(ElementRB* el);

    void checkwheretogo(ElementRB* parent, ElementRB* child);

    void showinorder(ElementRB* el);

    void showpreorder(ElementRB* el);

    void showpostorder(ElementRB* el);

    void visualisation(std::string cr, std::string cl, std::string cp, std::string sp, std::string sn, ElementRB* v);

    ElementRB* findInTree(ElementRB* el, int value);

    ElementRB* findsmaller(ElementRB* el);

    ElementRB* nexter(ElementRB* el);

    int removeFromTree(int value);

    void visualisation(std::string cr, std::string cl, std::string cp, std::string sp, std::string sn);

    int removeRoot();

    void repairafterremoving(ElementRB* el);

    void rotateright(ElementRB* el);

    void rotateleft(ElementRB* el);

    void clear();

    int findvalue(int value);

    int deleteRoot();

    void add(int value);

};