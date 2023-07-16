#include "BST.h"
void BST::addToTree(int value) {
    if (value <= 0) {
        std::cout << "Liczba musi byc wieksza od 0\n";
        return;
    }
    if (findInTree(head, value) != NULL) {
        return;
    }
    Element* el = new Element;
    el->value = value;
    el->right = NULL;
    el->left = NULL;
    el->parent = NULL;
    if (head == NULL) {
        head = el;
        counter++;
        return;
    }
    checkwheretogo(head, el);
    counter++;
}

void BST::add(int value) {
    addToTree(value);
}

void BST::checkwheretogo(Element* parent, Element* child) {
    child->parent = parent;
    child->left = NULL;
    child->right = NULL;
    if (child->value > parent->value) {
        if (parent->right == NULL) {
            parent->right = child;
            return;
        }
        checkwheretogo(parent->right, child);
    }
    if (child->value < parent->value) {
        if (parent->left == NULL) {
            parent->left = child;
            return;
        }
        checkwheretogo(parent->left, child);
    }
}

void BST::showinorder(Element* el) {
    if (el == NULL) return;
    showinorder(el->left);
    std::cout << el->value << " ";
    showinorder(el->right);
}

void BST::showpreorder(Element* el) {
    if (el == NULL) return;
    std::cout << el->value << " ";
    showinorder(el->left);
    showinorder(el->right);
}

void BST::showpostorder(Element* el) {
    if (el == NULL) return;
    showinorder(el->left);
    showinorder(el->right);
    std::cout << el->value << " ";
}

void BST::preparevisulaisation() {
    std::string cR, cL, cP;
    cR = cL = cP = "  ";
    cR[0] = 218; cR[1] = 196;
    cL[0] = 192; cL[1] = 196;
    cP[0] = 179;



    visualisation(cR, cL, cP, "", "", head);
}

void BST::visualisation(std::string cr, std::string cl, std::string cp, std::string sp, std::string sn, Element* v) {
    std::string s;
    if (v) {
        s = sp;
        if (sn == cr) s[s.length() - 2] = ' ';
        visualisation(cr, cl, cp, s + cp, cr, v->right);

        s = s.substr(0, sp.length() - 2);
        if(v->parent!=NULL)
            std::cout << s << sn << v->value << std::endl;
        else {
            std::cout << s << sn << v->value  << std::endl;
        }

        s = sp;
        if (sn == cl)s[s.length() - 2] = ' ';
        visualisation(cr, cl, cp, s + cp, cl, v->left);
    }
}

void BST::visualisation(std::string cr, std::string cl, std::string cp, std::string sp, std::string sn) {
    visualisation(cr, cl, cp, sp, sn, head);
}

int BST::deleteRoot() {
    return removeRoot();
}
int BST::findvalue(int value) {
    Element* el = NULL;
    el= findInTree(head, value);
    if (el != NULL)
        return el->value;
    return -1;
}

Element* BST::findInTree(Element* el, int value) {
    if (el == NULL) return NULL;
    if (el->value == value) return el;
    if (el->value > value) return findInTree(el->left, value);
    if (el->value < value) return findInTree(el->right, value);
}

Element* BST::findsmaller(Element* el) {
    if (el == NULL) return NULL;
    if (el->left == NULL) return el;
    return findsmaller(el->left);
}

Element* BST::nexter(Element* el) {
    if (el->right != NULL) return findsmaller(el->right);
    if (el->right == NULL) {
        while (el->parent != NULL) {

            if (el->parent->left == el) {
                return el->parent;
            }
            el = el->parent;
        }
        return NULL;
    }
}

int BST::removeFromTree(int value) {
    Element* eltodel = NULL;
    eltodel = findInTree(head, value);
    if (eltodel == NULL) return 1;
    Element* eltorep=NULL;
    Element* nx=NULL;
    if ((eltodel->left == NULL) || (eltodel->right == NULL)) nx = eltodel;
    else nx = nexter(eltodel);

    if (nx->left != NULL)
        eltorep = nx->left;

    else 
        eltorep = nx->right;

    if (eltorep != NULL) eltorep->parent = nx->parent;

    if (nx->parent == NULL)head = eltorep;
    else {
        if (nx == nx->parent->left) {
            nx->parent->left = eltorep;
        }
        else {
            nx->parent->right = eltorep;
        }
    }

    if (nx != eltodel)eltodel->value = nx->value;

    counter--;
    free(nx);
    return 0;
}


int BST::removeRoot() {
    removeFromTree(head->value);
    return 0;
}

void BST::rotateright(Element* el) {
    if (el->left != NULL) {
        if (el->parent != NULL) {
            if (el == el->parent->left) {
                el->parent->left = el->left;
            }
            else {
                el->parent->right = el->left;
            }
        }
        else {
            head = el->left;
        }
        el->left->parent = el->parent;
        el->parent = el->left;
        el->left = el->parent->right;
        if (el->left != NULL)
            el->left->parent = el;
        el->parent->right = el;
    }
}

void BST::rotateleft(Element* el) {
    if (el == NULL) return;
    if (el->right != NULL) {
        if (el->parent == NULL) {
            el->right->parent = el->parent;
            el->parent = el->right;
            el->right = el->parent->left;
            if (el->right != NULL)
                el->right->parent = el;
            el->parent->left = el;
            head = el->parent;
            return;
        }
        if (el->parent != NULL) {
            if (el == el->parent->left) {
                el->parent->left = el->right;
            }
            else {
                el->parent->right = el->right;
            }
            el->right->parent = el->parent;
            el->parent = el->right;
            el->right = el->parent->left;
            el->parent->left = el;
            if (el->right != NULL) el->right->parent = el;
        }
    }
}

void BST::makestraight(Element* el) {
    
    Element* temp = el;
    if (el->left != NULL) {
        rotateright(el);
        if (el->parent == NULL)return;
        makestraight(el->parent);
    }
    else {
        if (el->right == NULL) return;
        makestraight(el->right);
    }
}

void BST::DSW() {
    int log = log2(counter + 1);
    int m = pow(2, log) - 1;
    Element* temp = head;
    int num = counter - m;
    Element* tempnext;
    for (int i = num; i > 0; i--) {
        tempnext = temp->right->right;
        rotateleft(temp);
        temp = tempnext;
    }
    while (m > 1) {
        m = m / 2;
        temp = head;
        for (int i = m; i > 0; i--) {
            tempnext = temp->right->right;
            rotateleft(temp);
            temp = tempnext;
        }
    }
}

void BST::clear() {
    while (head != NULL) {
       removeFromTree(head->value);
    }
}