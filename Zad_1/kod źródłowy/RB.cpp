#include "RB.h"
void RB::addToTree(int value) {
    if (value <= 0) {
        std::cout << "Klucz musi byc liczba dodatnia\n";
        return;
    }
    ElementRB* el = new ElementRB();
    el->value = value;
    el->right = NULL;
    el->left = NULL;
    el->parent = NULL;
    if (head == NULL) {
        head = el;
        head->color = 'b';
        counter++;
        return;
    }
    checkwheretogo(head, el);
    counter++;
    
    repair(el);
}

void RB::repair(ElementRB* el) {
    if (el == head) el->color = 'b';
    if (el->parent == NULL) return;
    if (el->parent->parent == NULL) return;
    ElementRB* grandpar = el->parent->parent;
    if (el->parent->color == 'r') {
        if (el->parent == grandpar->left) {
            ElementRB* parentrightbrother = grandpar->right;
            if ((parentrightbrother == NULL || parentrightbrother->color == 'b') && el == el->parent->left) {
                el->parent->color = 'b';
                grandpar->color = 'r';
                rotateright(grandpar);
                return repair(grandpar);
            }
            if ((parentrightbrother == NULL || parentrightbrother->color == 'b') && el == el->parent->right) {
                rotateleft(el->parent);
                return repair(el->left);
            }
            if (parentrightbrother != NULL && parentrightbrother->color == 'r') {
                el->parent->color = 'b';
                parentrightbrother->color = 'b';
                grandpar->color = 'r';
                return repair(grandpar);
            }
        }
        if (el->parent == grandpar->right) {
            ElementRB* parentleftbrother = grandpar->left;
            if ((parentleftbrother == NULL || parentleftbrother->color == 'b') && el == el->parent->right) {
                el->parent->color = 'b';
                grandpar->color = 'r';
                rotateleft(grandpar);
                return repair(grandpar);

            }
            if ((parentleftbrother == NULL || parentleftbrother->color == 'b') && el == el->parent->left) {
                rotateright(el->parent);
                return repair(el->right);
            }
            if ( parentleftbrother!=NULL && parentleftbrother->color == 'r') {
                el->parent->color = 'b';
                parentleftbrother->color = 'b';
                grandpar->color = 'r';
                return repair(grandpar);
            }
        }


    }
}

void RB::checkwheretogo(ElementRB* parent, ElementRB* child) {
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

void RB::showinorder(ElementRB* el) {
    if (el == NULL) return;
    showinorder(el->left);
    std::cout << el->value << "-";
    showinorder(el->right);
}

void RB::showpreorder(ElementRB* el) {
    if (el == NULL) return;
    std::cout << el->value << "-" << el->color << " ";
    showinorder(el->left);
    showinorder(el->right);
}

void RB::showpostorder(ElementRB* el) {
    if (el == NULL) return;
    showinorder(el->left);
    showinorder(el->right);
    std::cout << el->value << "-" << el->color << " ";
}

void RB::visualisation(std::string cr, std::string cl, std::string cp, std::string sp, std::string sn, ElementRB* v) {
    {
        std::string s;
        if (v) {
            s = sp;
            if (sn == cr) s[s.length() - 2] = ' ';
            visualisation(cr, cl, cp, s + cp, cr, v->right);

            s = s.substr(0, sp.length() - 2);
            std::cout << s << sn << v->value << v->color << std::endl;

            s = sp;
            if (sn == cl)s[s.length() - 2] = ' ';
            visualisation(cr, cl, cp, s + cp, cl, v->left);
        }
    }
}

void RB::visualisation(std::string cr, std::string cl, std::string cp, std::string sp, std::string sn) {
    visualisation(cr, cl, cp, sp, sn, head);
}

ElementRB* RB::findInTree(ElementRB* el, int value) {
    if (el == NULL) return NULL;
    if (el->value == value) return el;
    if (el->value > value) return findInTree(el->left, value);
    if (el->value < value) return findInTree(el->right, value);
}

ElementRB* RB::findsmaller(ElementRB* el) {
    if (el == NULL) return NULL;
    if (el->left == NULL) return el;
    return findsmaller(el->left);
}

ElementRB* RB::nexter(ElementRB* el) {
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

int RB::removeFromTree(int value) {
    ElementRB* el = NULL;
    el = findInTree(head, value);
    if (el == NULL) return 1;

    if (el->right == NULL && el->left == NULL) {
        if (el == head) {
            head = NULL;
            free(el);
            counter--;
            return 0;
        }
        
        counter--;
        if (el->color == 'b')
            repairafterremoving(el);
        if (el->parent->left == el) el->parent->left = NULL;
        if (el->parent->right == el) el->parent->right = NULL;

        
        free(el);
        
        return 0;
    }
    if (el->right == NULL) {
        if (el == head) {
            head = el->left;
            el->left->color = 'b';
            free(el);
            counter--;
            return 0;
        }
        if (el->parent->left == el) {
            el->parent->left = el->left;
            el->left->parent = el->parent;
            if (el->color == 'b') {
                if (el->right != NULL) {
                    repairafterremoving(el->right);
                }
                if (el->left != NULL) {
                    repairafterremoving(el->left);
                }
            }
            free(el);
            counter--;
            return 0;
        }
        if (el->parent->right = el) {
            el->parent->right = el->left;
            el->left->parent = el->parent;
            if (el->color == 'b') {
                if (el->right != NULL) {
                    repairafterremoving(el->right);
                }
                if (el->left != NULL) {
                    repairafterremoving(el->left);
                }
            }
            free(el);
            counter--;
            return 0;
        }
    }
    if (el->left == NULL) {
        if (el == head) {
            head = el->right;
            el->right->color = 'b';
            free(el);
            counter--;
            return 0;
        }
        if (el->parent->left == el) {
            el->parent->left = el->right;
            el->right->parent = el->parent;
            if (el->color == 'b') {
                if (el->right != NULL) {
                    repairafterremoving(el->right);
                }
                if (el->left!= NULL) {
                    repairafterremoving(el->left);
                }
            }
                
            free(el);
            counter--;
            return 0;
        }
        if (el->parent->right == el) {
            el->parent->right = el->right;
            el->right->parent = el->parent;
            if (el->color == 'b') {
                if (el->right != NULL) {
                    repairafterremoving(el->right);
                }
                if (el->left != NULL) {
                    repairafterremoving(el->left);
                }
            }
            free(el);
            counter--;
            return 0;
        }
    }
    int val = nexter(el)->value;
    removeFromTree(val);
    el->value = val;
    return 0;
}

int RB::removeRoot() {
    ElementRB* el = head;
    if (el == NULL) return 1;

    if (el->right == NULL && el->left == NULL) {
        if (el == head) {
            head = NULL;
            free(el);
            counter--;
            return 0;
        }

        counter--;
        if (el->color == 'b')
            repairafterremoving(el);
        if (el->parent->left == el) el->parent->left = NULL;
        if (el->parent->right == el) el->parent->right = NULL;


        free(el);

        return 0;
    }
    if (el->right == NULL) {
        if (el == head) {
            head = el->left;
            free(el);
            counter--;
            return 0;
        }
        if (el->parent->left == el) {
            el->parent->left = el->left;
            el->left->parent = el->parent;
            if (el->color == 'b') {
                if (el->right != NULL) {
                    repairafterremoving(el->right);
                }
                if (el->left != NULL) {
                    repairafterremoving(el->left);
                }
            }
            free(el);
            counter--;
            return 0;
        }
        if (el->parent->right = el) {
            el->parent->right = el->left;
            el->left->parent = el->parent;
            if (el->color == 'b') {
                if (el->right != NULL) {
                    repairafterremoving(el->right);
                }
                if (el->left != NULL) {
                    repairafterremoving(el->left);
                }
            }
            free(el);
            counter--;
            return 0;
        }
    }
    if (el->left == NULL) {
        if (el == head) {
            head = el->right;
            free(el);
            counter--;
            return 0;
        }
        if (el->parent->left == el) {
            el->parent->left = el->right;
            el->right->parent = el->parent;
            if (el->color == 'b') {
                if (el->right != NULL) {
                    repairafterremoving(el->right);
                }
                if (el->left != NULL) {
                    repairafterremoving(el->left);
                }
            }

            free(el);
            counter--;
            return 0;
        }
        if (el->parent->right == el) {
            el->parent->right = el->right;
            el->right->parent = el->parent;
            if (el->color == 'b') {
                if (el->right != NULL) {
                    repairafterremoving(el->right);
                }
                if (el->left != NULL) {
                    repairafterremoving(el->left);
                }
            }
            free(el);
            counter--;
            return 0;
        }
    }
    int val = nexter(el)->value;
    removeFromTree(val);
    el->value = val;
    return 0;
}

void RB::repairafterremoving(ElementRB* el) {
    if (el->color == 'r') {
        el->color = 'b';
        return;
    }
     if (el == head)return;
    

    if (el == el->parent->left) {
        ElementRB* rightbrother = el->parent->right;
        if (rightbrother == NULL) {
            return repairafterremoving(el->parent);
        }
        if (rightbrother!=NULL&& rightbrother->color == 'r') {
            el->parent->color = 'r';
            rightbrother->color = 'b';
            rotateleft(el->parent);
            return repairafterremoving(el);
        }
        if ( rightbrother->color == 'b'&& (rightbrother->right == NULL || rightbrother->right->color == 'b') && (rightbrother->left == NULL || rightbrother->left->color == 'b')) {
            rightbrother->color = 'r';
            return repairafterremoving(el->parent);
        }
        if ( rightbrother->color == 'b' && (rightbrother->right == NULL || rightbrother->right->color == 'b') && (rightbrother->left != NULL && rightbrother->left->color == 'r')) {
            rightbrother->left->color = 'b';
            rightbrother->color = 'r';
            rotateright(rightbrother);
            return repairafterremoving(el);
        }
        if ( rightbrother->color == 'b' && (rightbrother->right != NULL && rightbrother->right->color == 'r')) {
            ;
            rightbrother->color = el->parent->color;
            el->parent->color = 'b';
            rightbrother->right->color = 'b';
            rotateleft(el->parent);
            return;
        }
    }
    if (el == el->parent->right) {
        ElementRB* leftbrother = el->parent->left;
        if (leftbrother == NULL) {
            //leftbrother->color = 'r';
            return repairafterremoving(el->parent);
        }
        if (leftbrother!=NULL&&leftbrother->color == 'r') {
            leftbrother->color = 'b';
            el->parent->color = 'r';
            rotateright(el->parent);
            return repairafterremoving(el);
        }

        if (leftbrother->color == 'b' && (leftbrother->left == NULL || leftbrother->left->color == 'b') && (leftbrother->right == NULL || leftbrother->right->color == 'b')) {
            leftbrother->color = 'r';
            return repairafterremoving(el->parent);
        }

        if (leftbrother->color == 'b' && (leftbrother->right != NULL && leftbrother->right->color == 'r') && (leftbrother->left == NULL || leftbrother->left->color == 'b')) {
            leftbrother->right->color = 'b';
            leftbrother->color = 'r';
            rotateleft(leftbrother);
            return repairafterremoving(el);
        }

        if (leftbrother->color == 'b' && (leftbrother->left != NULL && leftbrother->left->color == 'r')) {
            leftbrother->color = el->parent->color;
            el->parent->color = 'b';
            leftbrother->left->color = 'b';
            rotateright(el->parent);          
            return;
        }
    }
}

void RB::rotateright(ElementRB* el) {
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

void RB::rotateleft(ElementRB* el) {
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

void RB::clear() {
    while (head != NULL) {
        removeRoot();
    }
}

void RB::add(int value) {
    addToTree(value);
}

int RB::deleteRoot() {
    return removeRoot();
}

int RB::findvalue(int value) {
    ElementRB* el = NULL;
    el = findInTree(head, value);
    if (el == NULL) {
        return -1;
    }
    
        return el->value;
}
